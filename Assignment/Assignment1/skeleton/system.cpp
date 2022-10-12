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
}

// Helper function: find the index of the student_id in the enrolled student list
int search_student_id(const int student_id, const Course* const course) {
    // TODO
}


System::System(const int max_num_course, const int max_num_student) {
    course_database = new Course_Database(max_num_course);
    student_database = new Student_Database(max_num_student);
}

System::System(const System& system) {
    //cout<<"Copy Constructor of System is called"<<endl;
    course_database = new Course_Database(*system.course_database);//cout<<"Course_Database ok"<<endl;
    student_database = new Student_Database(*system.student_database);//cout<<"Student_Database ok"<<endl;
   
}

System::~System() {
    delete course_database;
    delete student_database;
}

void System::admit(const char* const name, const int student_id, const double gpa) {
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

bool System::add(const int student_id, const char* const course_name) {
    //TODO
    // Creates a tmp_course and tmp_student
    Course* tmp_course = this->course_database->get_course_by_name(course_name); // course object
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student object
    Wait_List* waiting_list = tmp_course->get_wait_list(); // get the wait_list to a course 

    // Before doing anything, enforce the worst case credit control policy
    // curr_credit + pending_credit =< max_credit
    if (tmp_student->get_pending_credit() + tmp_student->get_curr_credit() > tmp_student->get_max_credit()){
        return false; 
    }

    // Check if course has vacancies, if yes enroll student, if no add the student to the wait list 
    if (tmp_course->get_capacity() - tmp_course->get_size() == 0){
        //cout<<"No vacancy liao"<<endl;
        // if vacancy is 0 we create a node with student id and next = nullptr
        // Student_ListNode* node_student = new Student_ListNode(student_id, nullptr);
        Student_ListNode* head = waiting_list->get_head();

        if(head == nullptr){
            
            Student_ListNode* node_student = new Student_ListNode(student_id, nullptr);
            waiting_list->set_head(node_student);
            waiting_list->set_end(node_student);
            tmp_course->set_wait_list(waiting_list);
            tmp_student->set_pending_credit(tmp_student->get_pending_credit() + tmp_course->get_num_credit());
            //cout<<"adding first to wait_list"<<endl;
        }

        else{
            // Rules to adding items to wait_list: head link up with second // end point to second
            // creating a new node to store any waitlist information
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
        return true;
    }

    // update the corresponding data members of the student and course. Return true. 
    else if (tmp_course->get_capacity() - tmp_course->get_size() > 0){
    //cout<<"Capacity: "<<tmp_course->get_capacity() - tmp_course->get_size() <<endl;
    //cout<<"Got vacancy, adding 1 student to course"<<endl;

    int* students_enrolled_in_a_course = tmp_course->get_students_enrolled();
    students_enrolled_in_a_course[tmp_course->get_size()] = student_id; 
    // course side changes 
    tmp_course->set_size(tmp_course->get_size()+1); 
    tmp_course->set_students_enrolled(students_enrolled_in_a_course);
    //don't change the student's     
    /*
    for (int k =0; k<tmp_course->get_size();k++)
    {
        cout<<students_enrolled_in_a_course[k]<<" ";

    }
    cout<<""<<endl;
    */
    

    // Add course to list of enrolled course by student 
    char** enrolled_courzez = tmp_student->get_enrolled_courses(); 
    enrolled_courzez[tmp_student->get_num_enrolled_course()] = new char [strlen(course_name)+1];//student
    strcpy(enrolled_courzez[tmp_student->get_num_enrolled_course()],course_name);
    tmp_student->set_enrolled_courses(enrolled_courzez);

    // Update other data members of student 
    tmp_student->set_curr_credit(tmp_student->get_curr_credit()+tmp_course->get_num_credit()); //student
    int num_of_enrolled_courses = tmp_student->get_num_enrolled_course();
    tmp_student->set_num_enrolled_course(num_of_enrolled_courses+1);
    //cout<<"No of enrolled courses by this student is "<<tmp_student->get_num_enrolled_course()<<endl; 

    // Set Pending Credit of Student
    // if pending credit == 0 then no need to do anything, but if got pending credit
    // this means the student got in the waitlist before, need to minus the course credit 
    if(tmp_student->get_pending_credit()!=0){
        tmp_student->set_pending_credit(tmp_student->get_pending_credit() - tmp_course->get_num_credit());
    }
        return true;
    }

    else
        return false;
    
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
    if(tmp_target_course->get_capacity()-tmp_target_course->get_size() >0){
        //bigger than 0 means got vacancy
        add(student_id,target_course_name); // call the add function
        

    }



}

void System::drop(const int student_id, const char* const course_name) {
    // TODO

    /*Drop the student from the course. Update the corresponding class data members of the student. 
    You should delete the dynamically allocated memory corresponding to the dropped course name 
    in enrolled_courses for the dropped student.*/

    // 3 things: size of course -1 , num_of_course take by students - 1, delete char name 
    Course* tmp_course = this->course_database->get_course_by_name(course_name); // course
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student 
    int course_credit = tmp_course->get_num_credit(); // course credit  
    int num_course = tmp_course->get_size(); // course size (how many people currently enrolled)
    int curr_credit = tmp_student->get_curr_credit(); // student 
    int vacancy = tmp_course->get_capacity() - tmp_course->get_size(); // get the vacancy of a course 

    // for loop to find out the index of the student who drop the course 
    int* list_of_student_id_of_enrolled_students = tmp_course->get_students_enrolled();
    int tmp_student_for_replace = list_of_student_id_of_enrolled_students[num_course-1]; // last entry put into vessel  
    int index_for_the_empty_space_in_array = 0; // the index of the student_id to be deleted 
    for (int k=0; k<num_course; k++){
        if (list_of_student_id_of_enrolled_students[k] == student_id)
        {
            index_for_the_empty_space_in_array = k;
            //list_of_student_id_of_enrolled_students[k] = 0;
        }
    }

    // dropping the student from course: delete him from course_database, 
    char** enrolled_courzez_delete = tmp_student->get_enrolled_courses();
    for (int k=0; k<tmp_student->get_num_enrolled_course(); k++){
        if (strcmp(enrolled_courzez_delete[k],course_name)==1)
        {
            delete [] enrolled_courzez_delete[k];
        }
    }

    //updating data members for the dropped student 
    tmp_student->set_curr_credit(tmp_student->get_curr_credit()-tmp_course->get_num_credit());
    tmp_student->set_num_enrolled_course(tmp_student->get_num_enrolled_course()-1);
    tmp_student->set_enrolled_courses(enrolled_courzez_delete);
    //tmp_student->set_pending_credit(tmp_student);
    tmp_course->set_size(tmp_course->get_size()-1);

    
    
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
