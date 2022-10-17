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
    cout<<"Calls the copy constructor of swap_list "<<endl;
    Swap* headnode = swap_list.get_head(); //swap head of copied class
    Swap* ptr = headnode;
    Swap* tmp = nullptr;
    
    if (headnode == nullptr){
        head = nullptr;
        this->set_head(head);
    }
    else{
        if(ptr->next == nullptr){
            Swap* node_1 = new Swap(headnode->original_course_name,headnode->target_course_name,nullptr);
            this->set_head(node_1);
        }

        else{
            while (ptr->next != nullptr)
            {
                Swap* local_head = this->get_head();
                Swap* node = new Swap(ptr->next->original_course_name,ptr->next->target_course_name,nullptr);
                local_head->next = node;
                ptr  = ptr->next;
        }
            /*
            int index = 0;
            while (ptr->next != nullptr){        
                Swap* node = new Swap(ptr->next->original_course_name,ptr->next->target_course_name,nullptr);
                if(index == 0){
                    node->next = node_1;
                    tmp = node;
                    index = 1; 
                }
                else{
                    node->next = tmp;

                }
                ptr = ptr->next;
            }   
            */
        }
    }
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