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
    // Gets course name from course_database, get the num of credits associated with that course and updates the occupany (size).
    Course* tmp_course = this->course_database->get_course_by_name(course_name); // course 
    int course_credit = tmp_course->get_num_credit(); // course 
    int num_course = tmp_course->get_size(); // course
    tmp_course->set_size(num_course+1); //course
    int* students_enrolled_in_a_course = tmp_course->get_students_enrolled();
    students_enrolled_in_a_course[num_course] = student_id;
    tmp_course->set_students_enrolled(students_enrolled_in_a_course);           

    // Gets the pointer to student with student id: student id and get his number of credits. 
    // Add credit of student by num of credits associated with course as mentioned above and updates it as this is an add func. 
    Student* tmp_student = this->student_database->get_student_by_id(student_id); // student
    int curr_credit = tmp_student->get_curr_credit(); // student
    curr_credit += course_credit; // student
    tmp_student->set_curr_credit(curr_credit); //student

    // Gets the number of courses student is enrolled in, add by 1 and updates it as this is an add func.
    int num_enrolled_course = tmp_student->get_num_enrolled_course(); // student
    num_enrolled_course += 1; //student
    tmp_student->set_num_enrolled_course(num_enrolled_course); // student

    // Gets the pointer to a list of enrolled courses by student (char**),use it to add a course to the list using new and strcpy. 
    char** enrolled_courzez = tmp_student->get_enrolled_courses(); // student
    enrolled_courzez[num_enrolled_course-1] = new char [strlen(course_name)+1];//student
    strcpy(enrolled_courzez[num_enrolled_course-1],course_name);
    // cout<<"Self-defined---> The Number of Credits is: "<<curr_credit<<endl;

    // Gets the pointer to a list of enrolled students (in a course), use it to add student to the list
    //int* enrolled_studentz = tmp_course->get_students_enrolled();
    //enrolled_studentz[num_course-1] = student_id; // be ware of double defining the uneeded memory
    //tmp_course->
    //void Course::set_students_enrolled(int* const students_enrolled){
    //this->students_enrolled = students_enrolled;
    //cout<<"called add"<<endl;
}

bool System::swap(const int student_id, const char* const original_course_name, const char* const target_course_name) {
    // TODO
}

void System::drop(const int student_id, const char* const course_name) {
    // TODO
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
