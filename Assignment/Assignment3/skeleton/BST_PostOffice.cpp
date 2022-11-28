//
// Created by Yigit Sen on 27/10/2022.
//

#include "BST_PostOffice.h"

// TODO: Constructors and Destructors

//TIP: root will be nullptr at first, and we'll add a node once we try to add a mail object.
BST_PostOffice::BST_PostOffice()
{
    root = nullptr;
}

BST_PostOffice_Node::BST_PostOffice_Node(Mail *mail)
{
    //std::cout<<"\t\tBST_PostOffice_Node contructor called\n";
    this->district = mail->getDistrict();
    this->left = nullptr;
    this->right = nullptr; 
    this->addMail(mail);

}

BST_PostOffice::~BST_PostOffice()
{
    delete root;
}

BST_PostOffice_Node::~BST_PostOffice_Node()
{
    delete left;
    delete right;
}

// TODO: Accessor functions.
BST_PostOffice * BST_PostOffice_Node::getLeftBST() const
{
    return left;
}

BST_PostOffice * BST_PostOffice_Node::getRightBST() const
{
    return right;
}

District BST_PostOffice_Node::getDistrict() const
{
    return district;
}


//TODO: Given a district, id and street name, find the mail object.
Mail *BST_PostOffice::find(District dist, int id, std::string streetName)
{
    if(root){
        //std::cout<<"BST_PostOffice::find called\n";
        //std::cout<<"District to find: "<<dist<<"\n";
        //std::cout<<"root->getDistrict(): "<<root->getDistrict()<<"\n";
        
        if(this->root == nullptr){
            //std::cout<<"Root is empty!\n";
            return nullptr;
        }
        
        if(this->root->getDistrict() == dist){
            //std::cout<<"District found!\n";
            return root->find(id, streetName);
        }
        

        else if(dist < root->getDistrict()){
            //std::cout<<"District is smaller!\n";
            if(root->left){
                return root->left->root->find(id,streetName);
            }
            else{
                //std::cout<<"District not found!\n"; 
                return nullptr;
            } 
        }
        
        else
            //std::cout<<"District is bigger!\n"; 
            if(root->right){
                return root->right->root->find(id,streetName);
            }
            else{
                //std::cout<<"District not found!\n"; 
                return nullptr;
            } 
        /**/
        //std::cout<<"ERROR in BST_PostOffice::find!\n";
        return nullptr;
    }
    return nullptr;
}

Mail *BST_PostOffice_Node::find(int id, std::string streetName)
{
    //std::cout<<"\tBST_PostOffice_Node::find called\n";
    for(int k=0; k<HASH_MODULO;k++){
        Mail* return_mail = mailman[k].find(id,streetName);
        if(return_mail)
        {
            return return_mail;
        }
    }
    //std::cout<<"\tBST_Mailman_Node::find No ID found!\n";
    return nullptr; 
}


// TODO: Given a district, id and street name, remove the mail object from the
// system.
bool BST_PostOffice::remove(District dist, int id, std::string streetName)
{
    //std::cout<<"BST_PostOffice::remove called\n";
    if(root){
        //std::cout<<"BST_PostOffice::remove called"<<dist<<"\n";
        //std::cout<<"BST_PostOffice::remove called"<<root->getDistrict()<<"\n";
        if(root->getDistrict() == dist){
            //std::cout<<"BST_PostOffice::remove called -> same district\n";
            return root->remove(id,streetName);
        }
        else if(dist < root->getDistrict()){
            if(root->left){
                //std::cout<<"BST_PostOffice::remove called -> dist < district\n";
                root->left->remove(dist, id,streetName);
            }
            else{
                return false;
            }
        }
        else if(dist > root->getDistrict()){
            if(root->right){
                //std::cout<<"BST_PostOffice::remove called -> dist > district\n";
                return root->right->remove(dist, id,streetName);
            }
            else{
                return false;
            }
        }
        else
            ;
    }

    return false;
    
}

bool BST_PostOffice_Node::remove(int id, std::string streetName)
{
    /*
    std::cout<<"BST_PostOffice_Node ::remove called\n";
    for(int k=0; k<HASH_MODULO;k++){
        bool yes_or_no = mailman[k].remove(id,streetName);
        if(yes_or_no){
            return yes_or_no;
        }
    }
    */
    //std::cout<<"BST_PostOffice_Node::remove called\n";
    int value = 0;
    Mail* remove_mail = find(id,streetName);
    if(remove_mail){
        //std::cout<<"\t\t\tMail found! Time to remove\n";
        value = remove_mail->getAddressHash();
        return mailman[value].remove(id,streetName);
        return true;
    }

    //std::cout<<"Didn't find mail\n";    
    return false;
    
}

// TODO: Add mail to the system
void BST_PostOffice::addMail(Mail *mail)
{
    //std::cout<<"BST_PostOffice::addMail\n";
    if(root){
        //std::cout<<"\tmail district is : "<<mail->getDistrict()<<"\n";
        if(mail->getDistrict() == root->district){
        //std::cout<<"\tmail->getDistrict() == root->district\n";
        //root = new BST_PostOffice_Node(mail); // no need to create a new node
        root->addMail(mail);
        return;
    }

    else if(mail->getDistrict() < root->district){
        //std::cout<<"\tmail->getDistrict() < root->district\n";
        if(root->getLeftBST()){
            root->left->addMail(mail);
        }
        else{
            //std::cout<<"left of "<<mail->getDistrict()<<" is new\n";
            root->left = new BST_PostOffice;
            root->left->root = new BST_PostOffice_Node(mail);
        }
    }

    else if(mail->getDistrict() > root->district){
        //std::cout<<"\tmail->getDistrict() > root->district\n";
        if(root->getRightBST()){
            root->right->addMail(mail);
        }
        else{
            //std::cout<<"right of "<<mail->getDistrict()<<" is new\n";
            root->right =  new BST_PostOffice;
            root->right->root = new BST_PostOffice_Node(mail);
        }
    }

    else
        ;
    // more stuff
    }

    else{
        //std::cout<<"root == nullptr\n";
        //std::cout<<"\tmail district is : "<<mail->getDistrict()<<"\n";
        root = new BST_PostOffice_Node(mail); 
    }
}

void BST_PostOffice_Node::addMail(Mail *mail)
{
    //std::cout<<"\t\t BST_PostOffice_Node::addMail\n";
    int value = mail->getAddressHash();
    //std::cout<<"\t\t Hash Value Post Office: "<<value<<"\n";
    mailman[value].addMail(mail);

}

// TODO: Given a district, print all of the data in it.
// TIP: Print style depends on type.
void BST_PostOffice::printDistrict(District dist, printType type) const
{
    if(root==nullptr){
        return;
    }

    if(root->district == dist){
        std::cout<<"The District Mail Report for district "<<dist<<"\n";
        root->print(type);
    }

    
    else if (dist < root->district){
        if(root->left){
            root->left->printDistrict(dist,type);
        }
        else{
            return;
        }  
    }

    else if (dist > root->district){
        if(root->right){
            root->right->printDistrict(dist,type);
        }
        else{
            return;
        }  
    }
    
    

    else
        return;
}

void BST_PostOffice_Node::print(printType type) const
{
    if(type == inorder){
        for(int k=0; k<HASH_MODULO;k++){
            std::cout<<"For Mailman "<<k<<"\n";
            mailman[k].printInOrder();
        }
    }
    else if (type == postorder){
        for(int k=0; k<HASH_MODULO;k++){
            std::cout<<"For Mailman "<<k<<"\n";
            mailman[k].printPostOrder();
        }
    }
    else {
        for(int k=0; k<HASH_MODULO;k++){
            std::cout<<"For Mailman "<<k<<"\n";
            mailman[k].printPreOrder();
        }
    }
}

// TODO: Given a district and ID of the mailman, print all mail in it
// TIP: Print style depends on type - see the header file
void BST_PostOffice::printMailman(District district, int i, printType type) const
{
    if(root==nullptr){
        return;
    }

    if(root->district == district){
        //std::cout<<"\troot->district == district\n";
        root->printMailman(i,type);
    }

    else if (district < root->district){
        if(root->left){
            //std::cout<<"\troot->district == district\n";
            root->left->printMailman(district,i,type);
        }
        else{
            return;
        }  
    }

    else if (district > root->district){
        if(root->right){
            //std::cout<<"\troot->district == district\n";
            root->right->printMailman(district,i,type);
        }
        else{
            return;
        }  
    }

    else
        return;
    
}

void BST_PostOffice_Node::printMailman(int i, printType type) const
{
    //std::cout<<"\tBST_PostOffice_Node::printMailman called\n";
    if(type == inorder){
        for(int k=0; k<HASH_MODULO;k++){
            mailman[k].printInOrder();
        }   
    }
    else if(type == postorder){
        for(int k=0; k<HASH_MODULO;k++){
            mailman[k].printPostOrder();
        }   
    }
    else if(type == preorder){
        for(int k=0; k<HASH_MODULO;k++){
            mailman[k].printPreOrder();
        }   
    }
    else
        return; 
}

// TODO: Other print functions.
void BST_PostOffice::printInOrder() const
{
    if(root == nullptr){return;}

    /*
    for(int k =0; k<HASH_MODULO;k++){
        root->mailman[k].printInOrder();
    }
    */
   if(root){
        if(root->left != nullptr){
            //std::cout<<"BST Node for District: "<<root->left->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->left->printInOrder();
            //}
        }

        if(root != nullptr){
            std::cout<<"BST Node for District: "<<root->getDistrict()<<"\n";
            for(int k =0; k<HASH_MODULO;k++){
            root->mailman[k].printInOrder();
            }
        }

        if(root->right != nullptr){
            //std::cout<<"BST Node for District: "<<root->right->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->right->printInOrder();
            //}
        }
   }
    

    else
        ;
}

void BST_PostOffice::printPostOrder() const
{
    if(root == nullptr){return;}

   if(root){
        if(root->left != nullptr){
            //std::cout<<"BST Node for District: "<<root->left->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->left->printPostOrder();
            //}
        }

        if(root->right != nullptr){
            //std::cout<<"BST Node for District: "<<root->right->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->right->printPostOrder();
            //}
        }

        if(root != nullptr){
            std::cout<<"BST Node for District: "<<root->getDistrict()<<"\n";
            for(int k =0; k<HASH_MODULO;k++){
            root->mailman[k].printPostOrder();
            }
        }
   }
    

    else
        ;
}

void BST_PostOffice::printPreOrder() const
{
    if(root == nullptr){return;}

    /*
    for(int k =0; k<HASH_MODULO;k++){
        root->mailman[k].printInOrder();
    }
    */
   if(root){

        if(root != nullptr){
            std::cout<<"BST Node for District: "<<root->getDistrict()<<"\n";
            for(int k =0; k<HASH_MODULO;k++){
            root->mailman[k].printPreOrder();
            }
        }

        if(root->left != nullptr){
            //std::cout<<"BST Node for District: "<<root->left->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->left->printPreOrder();
            //}
        }

        if(root->right != nullptr){
            //std::cout<<"BST Node for District: "<<root->right->root->getDistrict()<<"\n";
            //for(int k =0; k<HASH_MODULO;k++){
            root->right->printPreOrder();
            //}
        }
   }
    

    else
        ;
}