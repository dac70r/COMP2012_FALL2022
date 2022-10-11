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
    
    head = wait_list.head; // performing shallow copying
    end = wait_list.end; // performing shallow copying
    //first_players = new char* [match.num_first_players];
    //for(int k=0;k<match.num_first_players;k++){
    //    first_players[k] = new char [strlen(match.first_players[k])+1];
    //    strcpy(first_players[k],match.first_players[k]);    
    //}

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