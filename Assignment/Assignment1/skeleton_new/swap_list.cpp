#include <iostream>
#include <cstring>
#include "swap_list.h"

using namespace std;

Swap::Swap(const char* const original_course_name, const char* const target_course_name, Swap* const next) {
    this->original_course_name = new char [strlen(original_course_name)+1];
    strcpy(this->original_course_name,original_course_name);
    this->target_course_name = new char[strlen(target_course_name)+1];
    strcpy(this->target_course_name,target_course_name);
    this->next = next;
}

Swap::~Swap() {
    delete [] original_course_name;
    delete [] target_course_name;
}

Swap_List::Swap_List() {
    // The head is a pointer that points to head of linked list
    // containing swaps 
    this->head = nullptr;
    
}

Swap_List::Swap_List(const Swap_List& swap_list) {
    // TODO
    // to be implemented after creating linked list 
    /*
    if (swap_list.get_head() == nullptr){
        this->head = nullptr;
        //cout<<"Wait_List: Nothing in wait_list!"<<endl;
    }
    else{
        // We need to copy all student_listnodes
        // func to get head of a wait list 
        Swap* head = swap_list.get_head(); // 1004
        //cout<<"Wait_List: "<<head->student_id<<endl;
        Swap* ptr = head; // 1004 
        Swap* tmp = nullptr; 
        Swap* ptz = nullptr;
        //creating the first element in a list 
        Swap* node_1 = new Swap(head->original_course_name,head->target_course_name,nullptr);

        if(head->next == nullptr){
            // meaning only 1 in the waitlist
            this->set_head(node_1);
        }

        else{
            int index = 0;
            while (ptr->next != nullptr){
                head = head->next;
                Swap* node = new Swap(head->original_course_name,head->target_course_name,nullptr);

            }
        }
    }
    */
    
}

Swap_List::~Swap_List() {
    // TODO
}

void Swap_List::print_list() const {
    Swap* temp = this->head;
    int index = 0;
    while(temp) {
        cout << "Swap: " << index++ << endl;
        cout << "Original Course: " << temp->original_course_name << endl;
        cout << "Target Course: " << temp->target_course_name << endl;
        temp = temp->next;
    }
}

Swap* Swap_List::get_head() const {
    return head;
}

void Swap_List::set_head(Swap* const head) {
    this->head = head;
}