#include <iostream>
#include "wait_list.h"

using namespace std;

Student_ListNode::Student_ListNode(const int student_id, Student_ListNode* const next) {
    // copy assignment for all data members from the function parameters 
    this->student_id = student_id;
    this->next = next;
}

Wait_List::Wait_List() {
    // TODO
    head = nullptr;
    end = nullptr;
}

Wait_List::Wait_List(const Wait_List& wait_list) {
    // TODO
    // Copy contructor of waitlist, performs deep copy of the whole wait_list
    // checks if the head is nullptr, if yes then no need to copy 
    //cout<<"debugging"<<endl;
    if (wait_list.get_head() == nullptr){
        this->head = nullptr;
        this->end = nullptr;
        //cout<<"nothing in wait_list"<<endl;
    }

    else{
        // We need to copy all student_listnodes
        // func to get head of a wait list 
        Student_ListNode* head = wait_list.get_head();
        Student_ListNode* ptr = head;
        Student_ListNode* tmp; 
        //creating the first element in a list 
        Student_ListNode* node_1 = new Student_ListNode(head->student_id,nullptr);
        node_1->next = nullptr;

        while (ptr->next != nullptr){
            int index = 0;
            Student_ListNode* node = new Student_ListNode(head->student_id,nullptr);
            
            if(index == 0){
                node_1->next = node;
                tmp = node_1->next;
                //cout<<"first of waitlist"<<endl;
            }
            else{
                tmp->next = node;
                tmp = tmp->next;
                index++;
                //cout<<"subsequent of waitlist"<<endl;
            }
            ptr = ptr->next;
        }
    }

    // head is a Student_ListNode* (pointer)
}

Wait_List::~Wait_List() {
    // TODO
    
}

void Wait_List::print_list() const {
    Student_ListNode* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Waitlist Number: " << index++ << endl;
        cout << temp->student_id << endl;
        temp = temp->next;
    }
}

Student_ListNode* Wait_List::get_head() const {
    return head;
}

Student_ListNode* Wait_List::get_end() const {
    return end;
}

void Wait_List::set_head(Student_ListNode* const head) {
    this->head = head;
}

void Wait_List::set_end(Student_ListNode* const end) {
    this->end = end;
}