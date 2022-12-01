//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_Mailman.h"

// TODO: Constructors and Destructors
BST_Mailman::BST_Mailman()
{
    root = nullptr;
    //std::cout<<"\tConstructor of BST_Mailman Called\n";
}

BST_Mailman_Node::BST_Mailman_Node(Mail *mail) // this is essentially the insert
{
    for(int k=0; k<MAX_NUM_MAILS; k++){
        mailPtr[k] = nullptr;
    }
    this->streetName = mail->getStreetName();
    mailPtr[currentMailsStored] = mail;
    //std::cout<<"currentMailsStored Before: "<<currentMailsStored<<"\n";
    currentMailsStored++;
    //std::cout<<"currentMailsStored After: "<<currentMailsStored<<"\n";
    right = nullptr;
    left = nullptr;
}

BST_Mailman::~BST_Mailman()
{
    delete root;
}

BST_Mailman_Node::~BST_Mailman_Node()
{
    for(int k=0;k<MAX_NUM_MAILS;k++){
        delete mailPtr[k];
    }
    delete right;
    delete left;
}

// TODO: Getters
std::string BST_Mailman_Node::getStreetName() const
{
    return streetName;
}

BST_Mailman * BST_Mailman_Node::getRightBST() const
{
    return right;
}

BST_Mailman * BST_Mailman_Node::getLeftBST() const
{
    return left;
}


// TODO add mail to the array mailPtr[] - NOTE: WE WILL NEVER ASK YOU TO
//  PUT TOO MANY MAILS. (a max of MAX_NUM_MAILS add_mail calls)
void BST_Mailman::addMail(Mail *mail)
{
    //std::cout<<"\t\t\tAdded mail in BST_Mailman::addMail\n";
    
    if(root == nullptr){
        //std::cout<<"\troot == nullptr in BST_Mailman::addMail\n";
        root = new BST_Mailman_Node(mail);
    }

    else if(root->getStreetName() == mail->getStreetName()){
        //std::cout<<"\troot->getStreetName() == mail->getStreetName()\n";
        root->addMail(mail);
    }

    else if(mail->getStreetName() < root->getStreetName()){
        //std::cout<<"\tmail->getStreetName() < root->getStreetName()\n";
        if(root->getLeftBST()){
            root->left->addMail(mail);
        }
        else{
            root->left = new BST_Mailman();
            root->left->root = new BST_Mailman_Node(mail); 
        }
    }

    else if(mail->getStreetName() > root->getStreetName()){
        //std::cout<<"\tmail->getStreetName() > root->getStreetName()\n";
        if(root->getLeftBST()){
            root->right->addMail(mail);
        }
        else{
            root->right = new BST_Mailman();
            root->right->root = new BST_Mailman_Node(mail); 
        }
    }

    else
        ;
    // more stuff*/
    
}

void BST_Mailman_Node::addMail(Mail *mail)
{
    //std::cout<<"\t\t\t\tAdded mail in BST_Mailman_Node::addMail\n";
    //std::cout<<"Current Mail: "<<currentMailsStored<<"\n";
    mailPtr[currentMailsStored]=mail;
    currentMailsStored++;
    //print();
    /*
    std::cout<<"\t\t\t\t\t------------\n";
    for(int k=0; k<MAX_NUM_MAILS;k++){
        if(mailPtr[k] == nullptr){std::cout<<"\t\t\t\t\tNothing\n";}
        else{std::cout<<"\t\t\t\t\t"<<mailPtr[k]->getContent()<<"\n";}
    }
    std::cout<<"\t\t\t\t\t------------\n";
    if(!mailPtr[mail->getAddressHash()]){
        mailPtr[mail->getAddressHash()] = mail;
        std::cout<<mail->getAddressHash()<<"\n";
        return;
    }
    else{
        std::cout<<mail->getAddressHash()+1<<"\n";
        mailPtr[mail->getAddressHash()+1] = mail;
        return;
    }
    */
}

// TODO: Remove a mail, given its street name and ID
bool BST_Mailman::remove(int id, std::string streetName)
{
    Mail* remove_mail = find(id,streetName);
    if(remove_mail){
        //std::cout<<"\t\t\tMail found inside mailman! Time to remove\n";
        return root->remove(id);
    }

    //std::cout<<"Didn't find mail\n";    
    return false;
}

bool BST_Mailman_Node::remove(int id)
{
    //std::cout<<"BST_Mailman_Node remove called\n";   
    Mail* to_be_removed_mail = find(id);
    if(to_be_removed_mail){
        //std::cout<<"\t\t\tMail with id: "<<id<<" is being removed\n";
        //print();
        //std::cout<<"Print stopped\n";
        //std::cout<<"Current number of mails: "<<currentMailsStored<<"\n";
        for(int k=0; k<MAX_NUM_MAILS;k++){
        if(mailPtr[k]!=nullptr){
            if(mailPtr[k]->getId()==id){
                //std::cout<<"\t\t\tID found! It is: "<<id<<"\n";
                //mailPtr[k]->printMail();
                delete mailPtr[k];
                mailPtr[k] = nullptr;
                //currentMailsStored = currentMailsStored-1;
            }
        }
    }
        //delete mailPtr[currentMailsStored-1]; incorrect
        //mailPtr[currentMailsStored-1] = nullptr;
        //std::cout<<"Finish deleting\n";
        //to_be_removed_mail = nullptr;
        //currentMailsStored -= 1;
        return true;
    }

    else{
        //std::cout<<"Could not find a Mail with id: "<<id<<"\n";
        return false; 
    }
}

// TODO: Find a mail item, given its street name and ID
Mail * BST_Mailman::find(int id, std::string streetName)
{
    //std::cout<<"\t\tBST_Mailman::find called\n";
    if(root != nullptr){
        if(this->root->getStreetName() == streetName){
            //std::cout<<"\t\t"<<root->getStreetName()<<"\n";
            //std::cout<<"\t\t"<<streetName<<"\n";
            //std::cout<<"\t\tStreet Name found!\n";
            return root->find(id);
        }

        if (streetName < root->getStreetName()){
            //std::cout<<"\t\tStreet Name is smaller!\n";
            if(root->left){
                return root->left->find(id,streetName);
            }
            else{
                //std::cout<<"\t\tStreet Name not found!\n"; 
                return nullptr;
            } 
        }

        else{
            //std::cout<<"\t\tStreet Name is bigger!\n"; 
            if(root->right){
                return root->right->find(id,streetName);
            }
            else{
                //std::cout<<"\t\tStreet Name not found!\n"; 
                return nullptr;
            }
        } 
    }

    return nullptr;
    /*
    if(this->root){
        
        std::cout<<"\t\troot->getstreetName(): "<<root->getStreetName()<<"\n";

        if(this->root == nullptr){
            std::cout<<"Root is empty!\n";
            return nullptr;
        }

        if(this->root->getStreetName() == streetName){
            std::cout<<"\t\tStreet Name found!\n";
            return root->find(id);
        }

        if (streetName < root->getStreetName()){
            std::cout<<"\t\tStreet Name is smaller!\n";
            if(root->left){
                return root->left->find(id,streetName);
            }
            else{
                std::cout<<"\t\tStreet Name not found!\n"; 
                return nullptr;
            } 
        }

        else
            std::cout<<"\t\tStreet Name is bigger!\n"; 
            if(root->right){
                return root->right->find(id,streetName);
            }
            else{
                std::cout<<"\t\tStreet Name not found!\n"; 
                return nullptr;
         } 

    }
    
    */

}

Mail *BST_Mailman_Node::find(int id)
{
    
    //std::cout<<"\t\t\tBST_Mailman_Node::find called\n";
    for(int k=0; k<MAX_NUM_MAILS;k++){
        if(mailPtr[k]!=nullptr){
            if(mailPtr[k]->getId()==id){
                //std::cout<<"\t\t\tID found! It is: "<<id<<"\n";
                //mailPtr[k]->printMail();
                return mailPtr[k];
            }
        }
    }
    /**/
    //std::cout<<"BST_Mailman_Node::find No ID found!\n";
    return nullptr; 
}


// TODO: Print functions. See example outputs for the necessary formats.
void BST_Mailman::printInOrder() const
{
    //std::cout<<"printInOrder\n";
    if(!root){
        return;
    }

    if(root){
        root->print();
    }
    
    if(root->left){
        root->left->printInOrder();
    }

    if(root->right){
        root->right->printInOrder();
    }

    return;
}

void BST_Mailman::printPostOrder() const
{
    //std::cout<<"printPostOrder\n";
    if(!root){return;}
        root->print();
    return;
}

void BST_Mailman::printPreOrder() const
{
    //std::cout<<"printPreOrder\n";
    if(!root){return;}
    root->print();
    return;
}

void BST_Mailman_Node::print() const
{
    std::cout << "BST Node for Street: " << streetName << std::endl;
    for (int i = 0; i < MAX_NUM_MAILS; ++i) {
        if(mailPtr[i])
        {
            mailPtr[i]->printMail();
        }
    }
}