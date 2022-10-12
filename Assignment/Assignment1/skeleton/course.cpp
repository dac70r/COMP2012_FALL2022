#include "iostream"
#include <cstring>
#include "course.h"
#include "wait_list.h"

using namespace std;

Course::Course(const char* const name, const int num_credit, const int course_capacity) :students_enrolled(new int [course_capacity]){
    // 
    this->name = new char [strlen(name)+1];
    strcpy(this->name,name);
    this->num_credit = num_credit;
    this->capacity = course_capacity;
    this->size = 0;
    this->wait_list = new Wait_List;
    
    // Init the values inside the dynamic array to be 0.
    //this->students_enrolled = new int [course_capacity];
    //for (int k = 0;k<course_capacity;k++){this->students_enrolled[k]=0;}
}

Course::Course(const Course& course) {
    // TODO
    // Perform deep copy of all data members 
    /*
    char* name;
    int num_credit;
    int capacity;
    int size;
    Wait_List* wait_list;
    int* students_enrolled;
    */
    name = new char [strlen(course.name)+1]; // char data member 
    strcpy(name,course.name);
    //
    num_credit = course.num_credit;
    capacity = course.capacity;
    size = course.size;
    Wait_List* waiting_list = course.get_wait_list();
    Student_ListNode* ptr = waiting_list->get_head();
    while(ptr->next!=NULL){
        Student_ListNode* new_student = new Student_ListNode(ptr->student_id,nullptr);
        ptr = ptr->next;
    }
    wait_list = new Wait_List;
    // This is shallow copy, will lead to undefined behaviour
    wait_list = course.wait_list; 
    int get_size = course.get_size();
    students_enrolled = new int [get_size];

    for(int k=0;k<get_size;k++){
        students_enrolled[k] = course.students_enrolled[k];
    }
}

Course::~Course() {
    // TODO
    delete [] name;
    delete wait_list; // will call destructor of wait_list
    delete [] students_enrolled; 
}

void Course::print_info() const {
    cout << "---------------------" << endl;
    cout << "Course Name: " << this->name << endl;
    cout << "Num Credit: " << this->num_credit << endl;
    cout << "Current Size: " << this->size << " out of Capacity: " << this->capacity << endl;
    cout << endl;
    cout << "Student Enrolled: " << endl;
    for(int i = 0; i < this->size; ++i) {
        cout << this->students_enrolled[i] << endl;
    }
    cout << endl;
    cout << "Waitlist Information: " << endl;
    this->wait_list->print_list();
    cout << endl;
}

char* Course::get_name() const {
    return name;
}

int Course::get_num_credit() const {
    return num_credit;
}

int Course::get_capacity() const {
    return capacity;
}

int Course::get_size() const {
    return size;
}

Wait_List* Course::get_wait_list() const {
    return wait_list;
}

int* Course::get_students_enrolled() const {
    return students_enrolled;
}

void Course::set_name(char* const name) {
    this->name = name;
}

void Course::set_num_credit(const int num_credit) {
    this->num_credit = num_credit;
}

void Course::set_capacity(const int capacity) {
    this->capacity = capacity;
}

void Course::set_size(const int size) {
    this->size = size;
}

void Course::set_wait_list(Wait_List* const wait_list) {
    this->wait_list = wait_list;
}

void Course::set_students_enrolled(int* const students_enrolled){
    this->students_enrolled = students_enrolled;
}