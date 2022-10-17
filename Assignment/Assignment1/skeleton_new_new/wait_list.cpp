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
    //cout<<"Wait_List: Copy Constructor of Wait_List is called"<<endl;
    if (wait_list.get_head() == nullptr){
        this->head = nullptr;
        this->end = nullptr;
        //cout<<"Wait_List: Nothing in wait_list!"<<endl;
    }

    else{
        // We need to copy all student_listnodes
        // func to get head of a wait list 
        Student_ListNode* head = wait_list.get_head(); // 1004
        //cout<<"Wait_List: "<<head->student_id<<endl;
        Student_ListNode* ptr = head; // 1004 
        Student_ListNode* tmp = nullptr; 
        Student_ListNode* ptz = nullptr;
        //creating the first element in a list 
        Student_ListNode* node_1 = new Student_ListNode(head->student_id,nullptr);
        node_1->next = nullptr;

        if(head->next == nullptr){
            // meaning only 1 in the waitlist
            this->set_head(node_1);
            this->set_end(node_1);
        }

        else{
            int index = 0;
            while (ptr->next != nullptr){
                head = head->next;
                Student_ListNode* node = new Student_ListNode(head->student_id,nullptr);
                
                if(index == 0){
                    node_1->next = node;
                    tmp = node_1->next;
                    //cout<<"Wait_List: First of Waitlist added"<<endl;
                    //this->set_head()
                    //this->set_end(node_1);
                    //this->print_list();
                    }

                else{
                    tmp->next = node;
                    tmp = tmp->next;
                    //cout<<"Wait_List: Subsequent of Waitlist added"<<endl;
                }
                index++;
                ptr = ptr->next;
                if(ptr->next == nullptr){ptz = ptr;}
            }
            this->set_head(node_1);
            this->set_end(ptz);
        }
    }

    // head is a Student_ListNode* (pointer)
}

Wait_List::~Wait_List() {
    // TODO
    //this->head
    /*
    if (this->get_head() == nullptr){
        head = nullptr;
        end = nullptr;
    }
    else if ( this ->get_end() == this ->get_head()){
        delete head; 
        head = nullptr;
        end = nullptr;
    }
    else{
        Student_ListNode* ptr = nullptr;
        Student_ListNode* header = nullptr; 
        ptr = this->get_head();
        while(ptr->next != nullptr)
        {   
            header = ptr;
            ptr = ptr->next;
            delete header;    
            header = nullptr;
        }
        // last step should have leak if  
    }
    */
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