#include <iostream>
#include <cstring>
#include "system.h"
#include "student.h"
#include "course.h"
#include "course_database.h"
#include "student_database.h"
#include "wait_list.h"
#include "swap_list.h"

using namespace std;

/*
The following 3 helper functions may be useful in add/swap/drop function. You may implement them if you find them useful.
If not, you can remove these 3 helper functions as we will NOT set any test case testing these helper functions.
*/

// Helper function: add the Student to the end of the waitlist of the Course.
void join_waitlist(const int student_id, Course* course) {
    // TODO
}

// Helper function: find the index of a course within the enrolled course list of a student.
int search_course_index(const Student* const student, const char* const course_name) {
    // TODO
    int index = 0;
    char** enrolled_courzez_delete = student->get_enrolled_courses();
    for (int k=0; k<student->get_num_enrolled_course(); k++){
        //cout<<"Number of enrolled courses: "<<tmp_student->get_num_enrolled_course()<<endl;
        if (strcmp(enrolled_courzez_delete[k],course_name)==0){
            index = k; // saving the index of the dropped course (name)
        } 
    } 
    return index;
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO
    int k1 = 1000;  // returns then there is problem
    int* student_list = course->get_students_enrolled();
    for (int k=0; k<course->get_size();k++){
        if(student_list[k] == student_id){
            k1 = k;
        }
    }
    return k1;
}


System::System(const int max_num_course, const int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    //cout<<"System: Copy Constructor of System is called"<<endl;
    
    student_database = new Student_Database(*system.student_database);//cout<<"System: Student_Database ok"<<endl;
    course_database = new Course_Database(*system.course_database);//cout<<"System: Course_Database ok"<<endl;
}

System::~System() {
    delete course_database; //cout<<"System: Course database delete ok"<<endl;
    delete student_database; //cout<<"System: Student database delete ok"<<endl;
}

void System::admit(const char* const name, const int student_id, const double gpa) {
    //cout<<"admitting"<<endl;
    this->student_database->create_entry(name, student_id, gpa);
}

bool System::apply_overload(const int student_id, const int request_credit) {
    //TODO
    //Rules
    //Students can never request more than 30 credits, meaning that a student can study 30 credits at maximum.
    //If a student would like to overload to more than or equal to 24 credits, the student should have a GPA of at least 3.7.
    //If a student would like to overload to more than 18 credits, the student should have a GPA of at least 3.3.
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student
    int curr_credit = tmp_student->get_curr_credit(); // student
    double gpaz = tmp_student->get_gpa();

    if (request_credit >= 30)
        return false;

    else if (request_credit >=24){
        if (gpaz >= 3.7){
            tmp_student->set_max_credit(request_credit);
            return true;
        }
        else
            return false;
    }

    else if (request_credit > 18){
        if (gpaz >= 3.3){
            tmp_student->set_max_credit(request_credit);
            return true;
        }
        else
            return false;
    }

    else
        return false;

        
    
}

bool System::add(const int student_id, const char* const course_name){
    //TODO
    // Creates a tmp_course and tmp_student
    //cout<<"adding"<<endl;
    Course* tmp_course = this->course_database->get_course_by_name(course_name); // course object
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student object
    Wait_List* waiting_list = tmp_course->get_wait_list(); // get the wait_list to a course 

    // Before doing anything, enforce the worst case credit control policy
    // curr_credit + pending_credit =< max_credit
    if (tmp_student->get_pending_credit() + tmp_student->get_curr_credit() > tmp_student->get_max_credit()){
        return false; 
    }

    // Checks if there are any vacancies, if yes add to immediate behind (last entry)
    if (tmp_course->get_capacity() - tmp_course->get_size() > 0){
        int* student_enrolled  = tmp_course->get_students_enrolled();
        student_enrolled[tmp_course->get_size()] = student_id; // if current size is 3/4 then student_enrolled[3] = student_id 
        
        // Update data members of course
        tmp_course->set_size(tmp_course->get_size()+1); // size is now 4/4
        tmp_course->set_students_enrolled(student_enrolled); // set students_enrolled in course

        /* Update data members of student */ 
        char** enrolled_courzez = tmp_student->get_enrolled_courses();
        int course_numbers = tmp_student->get_num_enrolled_course();
        //char* new_mem = new char [strlen(course_name)+1]; 
        //strcpy(new_mem,course_name);
        enrolled_courzez[course_numbers] = tmp_course->get_name(); 
        //enrolled_courzez[course_numbers] = new char [strlen(course_name)+1]; 
        //strcpy(enrolled_courzez[course_numbers],course_name);

        // Update the number of courses by student 
        tmp_student->set_num_enrolled_course(course_numbers+1);
        tmp_student->set_curr_credit(tmp_student->get_curr_credit()+tmp_course->get_num_credit());
    }

    // Else if there are no vacancies we have to add these people to the waitlist for a course
    else if (tmp_course->get_capacity() - tmp_course->get_size() == 0){

        // Sees if our wait list is empty
        Student_ListNode* head = waiting_list->get_head();
        if(head == nullptr){
            // Nothing in the waitlist, we will add first entry to the waitlist
            Student_ListNode* node_student = new Student_ListNode(student_id, nullptr); // next = nullptr
            waiting_list->set_head(node_student);
            waiting_list->set_end(node_student);
            tmp_course->set_wait_list(waiting_list);
            tmp_student->set_pending_credit(tmp_student->get_pending_credit() + tmp_course->get_num_credit());
            //cout<<"adding first to wait_list"<<endl;

        }

        // else we will add to the end of the wait_list
        else{
            Student_ListNode* another_node = new Student_ListNode(student_id, nullptr); 
            Student_ListNode* ptr = head;
            //end pointer now points to another_node
            waiting_list->set_end(another_node);
            // Code to traverse the linked list
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            // finally when we reach the end, we link zem together 
            ptr->next = another_node;
            // then we need to set_wait_list to "save" changes

            tmp_course->set_wait_list(waiting_list);
            tmp_student->set_pending_credit(tmp_student->get_pending_credit() + tmp_course->get_num_credit());
            //cout<<"Student added to waitlist"<<endl;
        }
    }
    //tmp_student->print_info();
    return true;
}


bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO
    Course* tmp_original_course = this->course_database->get_course_by_name(original_course_name); // course object
    Course* tmp_target_course = this->course_database->get_course_by_name(target_course_name); // course object
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student object
    
    // 1. Enforcing the Worst Case Credit Control Policy
    if (tmp_student->get_pending_credit() + tmp_student->get_curr_credit() > tmp_student->get_max_credit()){
        return false; 
    }

    // 2. Check if target course has any vacancies, update Course and Student class data members
    /*
    Enroll the student into the target_course and 
    update the corresponding Course and Student class data members.
    */ 
    if(tmp_target_course->get_capacity()-tmp_target_course->get_size() > 0){
        //add(student_id,target_course_name);
        int* list_students = tmp_target_course->get_students_enrolled();
        list_students[tmp_target_course->get_size()] = student_id;
        char** enrolled_courses = tmp_student->get_enrolled_courses();
        enrolled_courses[tmp_student->get_num_enrolled_course()] = tmp_target_course->get_name();
        tmp_student->set_num_enrolled_course(tmp_student->get_num_enrolled_course()+1);
        tmp_target_course->set_size(tmp_target_course->get_size()+1);
        tmp_student->set_curr_credit(tmp_target_course->get_num_credit()+tmp_student->get_curr_credit());
        drop(student_id,original_course_name);
        return true;
    }
    else{
        // if no vacancy 
        // See if our wait list is empty
        Wait_List* waiting_list = tmp_target_course->get_wait_list();
        Student_ListNode* head = waiting_list->get_head();

        if(head == nullptr){
            // Nothing in the waitlist, we will add first entry to the waitlist
            Student_ListNode* node_student = new Student_ListNode(student_id, nullptr); // next = nullptr
            waiting_list->set_head(node_student);
            waiting_list->set_end(node_student);
            tmp_target_course->set_wait_list(waiting_list);
            //tmp_student->set_pending_credit(tmp_student->get_curr_credit());
            //cout<<"adding first to wait_list"<<endl;
            
        }

        // else we will add to the end of the wait_list
        else{
            Student_ListNode* another_node = new Student_ListNode(student_id, nullptr); 
            Student_ListNode* ptr = head;
            //end pointer now points to another_node
            waiting_list->set_end(another_node);
            // Code to traverse the linked list
            while(ptr->next!=NULL){
                ptr = ptr->next;
            }
            // finally when we reach the end, we link zem together 
            ptr->next = another_node;
            // then we need to set_wait_list to "save" changes

            tmp_target_course->set_wait_list(waiting_list);
            //tmp_student->set_pending_credit(tmp_student->get_pending_credit() + tmp_target_course->get_num_credit());
            //cout<<"Student added to waitlist"<<endl;
        }

        // if no vacancy add swap to swap_list
        // See if our swap list is empty
        Swap_List* swapping_list = tmp_student->get_swap_list();
        Swap* swap_head = swapping_list->get_head();

        if (swap_head == nullptr){
            // Nothing in the swap_list, we will add first entry to the swap_list
            Swap* swap_node = new Swap(original_course_name, target_course_name, nullptr); // next = nullptr
            swapping_list->set_head(swap_node);
            tmp_student->set_swap_list(swapping_list);
            //tmp_student->set_pending_credit(tmp_student->get_curr_credit() - tmp_target_course->get_num_credit());
            //cout<<"adding first to wait_list"<<endl;
            //cout<<"yes"<<endl;
        }
        else{
            Swap* another_node = new Swap(original_course_name, target_course_name, nullptr);
            //Swap* ptr = swap_head; 
            //Student_ListNode* another_node = new Student_ListNode(student_id, nullptr); 
            //Student_ListNode* ptr = head;
            //end pointer now points to another_node
            another_node->next = swap_head;
            //waiting_list->set_end(another_node);
            // Code to traverse the linked list
            //while(ptr->next!=NULL){
            //    ptr = ptr->next;
            //}
            // finally when we reach the end, we link zem together 
            //ptr->next = another_node;
            // then we need to set_wait_list to "save" changes
            swapping_list->set_head(another_node);
            tmp_student->set_swap_list(swapping_list);
            //tmp_target_course->set_wait_list(waiting_list);
            //tmp_student->set_pending_credit(tmp_student->get_pending_credit() + tmp_target_course->get_num_credit());
            //cout<<"Student added to waitlist"<<endl;
            //cout<<"no"<<endl;
        }
        // need to implement worst case credit 
    
    }
    Wait_List* waiting_list = tmp_target_course->get_wait_list();
    Student_ListNode* head = waiting_list->get_head();
    Swap_List* swapping_list = tmp_student->get_swap_list();
    Swap* swap_head = swapping_list->get_head();
    int worst_case_credit = 0;
    while (head -> next != nullptr){
        
    }

    return true; 
}
    
  

void System::drop(const int student_id, const char* const course_name) {
    // TODO
    Course* tmp_course = this->course_database->get_course_by_name(course_name); // course
    Student* drop_student = this->student_database->get_student_by_id(student_id); // student 
    Wait_List* waiting_list = tmp_course->get_wait_list();
    int copy_of_dropped_student_id = 0;
    
    int index = 0;

    // Simple drop, no waitlist
    if (waiting_list->get_head() == nullptr){
        int* students_enrolled = tmp_course->get_students_enrolled();
        int student_id_last_entry = students_enrolled[tmp_course->get_size()-1];
        int last_index = drop_student->get_num_enrolled_course()-1;
        int index_drop = search_course_index(drop_student,course_name);
        //cout<<"Index drop "<<index_drop<<endl; 
        char** drop_student_course = drop_student->get_enrolled_courses();
        //cout<<"Before"<<endl;
        //drop_student->print_info();
        drop_student_course[index_drop] = drop_student_course[last_index];
        //cout<<"After"<<endl;
        //drop_student->print_info();
        drop_student->set_curr_credit(drop_student->get_curr_credit()-tmp_course->get_num_credit());
        drop_student->set_num_enrolled_course(drop_student->get_num_enrolled_course()-1);
        tmp_course->set_size(tmp_course->get_size()-1);

        
        int index_student_drop = search_student_id(student_id,tmp_course);
        
        //cout<<"Replaced student id: "<<student_id_last_entry<<endl;
        //cout<<"Index "<<index_student_drop<<endl; // for debugging
        students_enrolled[index_student_drop] = student_id_last_entry;

    }
    // Special Case 1: Dropped and Replace 
    else if (waiting_list->get_head() != nullptr)
    {
        Student_ListNode* next_on_the_list_id = waiting_list->get_head();
        int* students_enrolled = tmp_course->get_students_enrolled();
        int index_student_drop = search_student_id(student_id,tmp_course);
        //cout<<"Index "<<index_student_drop<<endl; // for debugging
        students_enrolled[index_student_drop] = next_on_the_list_id->student_id;
        int copy_of_added_student_id = next_on_the_list_id->student_id;

        // Removing the first entry in a wait_list
        Student_ListNode* ptr = nullptr;
        ptr = next_on_the_list_id;
        next_on_the_list_id = next_on_the_list_id->next;
        waiting_list->set_head(next_on_the_list_id);
        tmp_course->set_wait_list(waiting_list);
        delete ptr;
        //cout<<"okay"<<endl;

        // Updating Dropped Student - Brian's Details 
        drop_student->set_curr_credit(drop_student->get_curr_credit()-tmp_course->get_num_credit());
        drop_student->set_num_enrolled_course(drop_student->get_num_enrolled_course()-1);

        // Updating Added Student Desmond's Details 
        Student* Added_student = this->student_database->get_student_by_id(copy_of_added_student_id);
        char** enrolled_courzez_add = Added_student->get_enrolled_courses();
        int course_numbers_add = Added_student->get_num_enrolled_course();
        enrolled_courzez_add[course_numbers_add] = tmp_course->get_name();
        
        Added_student->set_curr_credit(Added_student->get_curr_credit()+tmp_course->get_num_credit());
        Added_student->set_num_enrolled_course(Added_student->get_num_enrolled_course()+1);
        Added_student->set_pending_credit(Added_student->get_pending_credit()-tmp_course->get_num_credit());
        //cout<<"Checking waiting list"<<endl;
        //waiting_list->print_list();
    }
    else{
        //
    }
    
    

    //tmp_course->set_size(tmp_course->get_size()-1);
    // Before delete, check if all entries exist
    //cout<<"Before drop debugging"<<endl;
    //tmp_student->print_info();

    // First drop the student from the course 
    // for loop: Iterating over the list of enrolled students to find the student who will drop
    // Processing the student id first

    //cout<<"Total number of enrolled courses "<<tmp_student->get_num_enrolled_course()<<endl;
    /*
    char** enrolled_courzez_delete = tmp_student->get_enrolled_courses();
    for (int k=0; k<tmp_student->get_num_enrolled_course(); k++){
        //cout<<"Number of enrolled courses: "<<tmp_student->get_num_enrolled_course()<<endl;
        if (strcmp(enrolled_courzez_delete[k],course_name)==0){
            index = k; // saving the index of the dropped course (name)
            //cout<<"Same course is "<<enrolled_courzez_delete[k]<<endl;
            //cout<<index<<endl;
        } 
    }
    */
    //tmp_student->set_enrolled_courses(enrolled_courzez_delete);
    //tmp_student->print_info();

    //int* list_of_student_id_of_enrolled_students = tmp_course->get_students_enrolled();

    //Student* dropped_student = this->student_database->get_student_by_id(student_id);
    //char** dropped_student_enrolled_courses = dropped_student->get_enrolled_courses();
    //cout<<"Index: "<<index<<endl;
    //cout<<"Index: "<<search_course_index(tmp_student,course_name)<<endl;
    /*
        delete [] enrolled_courzez_delete[index];
    */
    
    /*
    
    cout<<"Course size "<<tmp_course->get_size()<<endl;
    for (int k=0; k<tmp_course->get_size(); k++){
        int* list_of_student_id_of_enrolled_students = tmp_course->get_students_enrolled();
        if (list_of_student_id_of_enrolled_students[k] == student_id){
            //cout<<k<<endl;
            // If got people on waitlist: students_enrolled[k] = wait_list->student_id
            // delete the first Student_Listnode in wait_list
            copy_of_dropped_student_id = list_of_student_id_of_enrolled_students[k];
            copy_of_added_student_id = next_on_the_list_id->student_id;
            if(next_on_the_list_id != nullptr){
                
                list_of_student_id_of_enrolled_students[k] = next_on_the_list_id->student_id;
                Student_ListNode* ptr = nullptr;
                ptr = next_on_the_list_id;
                next_on_the_list_id = next_on_the_list_id->next;
                waiting_list->set_head(next_on_the_list_id);
                tmp_course->set_wait_list(waiting_list);
                delete ptr;
                cout<<"okay"<<endl;

                //edit Dropped Student's Details 
                //cout<<copy_of_dropped_student_id<<endl;
                tmp_student->set_curr_credit(tmp_student->get_curr_credit()-tmp_course->get_num_credit());
                tmp_student->set_num_enrolled_course(tmp_student->get_num_enrolled_course()-1);

                //edit Added Student's Details 
                Student* Added_student = this->student_database->get_student_by_id(copy_of_added_student_id);
                char** added_student_enrolled = Added_student->get_enrolled_courses();
                added_student_enrolled[Added_student->get_num_enrolled_course()] = new char [strlen(course_name)+1];
                strcpy(added_student_enrolled[Added_student->get_num_enrolled_course()],course_name);
                Added_student->set_curr_credit(Added_student->get_curr_credit()+tmp_course->get_num_credit());
                Added_student->set_num_enrolled_course(Added_student->get_num_enrolled_course()+1);
                Added_student->set_pending_credit(Added_student->get_pending_credit()-tmp_course->get_num_credit());

            }
            // Otherwise, there is no one on the waitlist
            else{
                list_of_student_id_of_enrolled_students[k] = list_of_student_id_of_enrolled_students[tmp_course->get_size()-1];
                list_of_student_id_of_enrolled_students[tmp_course->get_size()-1] = 0;
                //Update values need to be later after update enrolled courzez
                //strcpy(enrolled_courzez_delete[k],enrolled_courzez_delete[tmp_course->get_size()-1]);
                tmp_course->set_size(tmp_course->get_size()-1);
                tmp_student->set_curr_credit(tmp_student->get_curr_credit()-tmp_course->get_num_credit());
                tmp_student->set_num_enrolled_course(tmp_student->get_num_enrolled_course()-1);
            }
        }
    }*/
    

    

    
    //cout<<"end"<<endl;
    //tmp_student->print_info();
}
    
void System::add_course(const char* const name, const int num_credit, const int course_capacity) {
    this->course_database->create_entry(name, num_credit, course_capacity);
}

void System::print_info() const {
    this->course_database->print_all_course();
    this->student_database->print_all_students();
    
    
}

Course_Database* System::get_course_database() const {
    return course_database;
}

Student_Database* System::get_student_database() const {
    return student_database;
}

void System::set_course_database(Course_Database* const course_database) {
    this->course_database = course_database;
}

void System::set_student_database(Student_Database* const student_database) {
    this->student_database = student_database;
}
