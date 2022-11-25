#include "hash_table.h"
#include <cmath>
#include <iostream>

int HashTable::hashFunction(const std::string &name, int base, int table_size) {
  int res = 0;
  for (unsigned int i = 0; i < name.size(); i++) {
    res = (base*res + name[i] - 'a') % table_size;
  }
  return res;
}

int HashTable::getNextHashTableSize(int now_hash_table_size) {
  int res = now_hash_table_size*2;
  bool is_prime = false;
  while (true) {
    is_prime = true;
    int sq = sqrt(res);
    for (int i = 2; i <= sq; i++) {
      if (res % i == 0) {
        is_prime = false;
        break;
      }
    }
    if (is_prime)
      break;
    res++;
  }
  return res;
}

HashTable::HashTable(int init_size, int maximum_probe_num,
                     ProbeMode probe_mode)  {  // Task 1
                     hash_table_size_ = init_size;
                     maximum_probe_num_= maximum_probe_num;
                     probe_mode_ = probe_mode;    
                     base_1_ = 37;
                     base_2_ = 41;
                     table_ = new HashCell [hash_table_size_];
                    for (int k=0; k<hash_table_size_;k++){
                      table_[k] = HashCell();
                      table_[k].student = nullptr;
                    }
                    // hash(k) = k mod m // k: num of elements 

                    if (probe_mode == ProbeMode::Linear){
                      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size) {return (hash_value1 + num_probe) % hash_table_size;};
                    }
                    else if (probe_mode == ProbeMode::Quadratic){
                      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size) {return (hash_value1 + num_probe*num_probe) % hash_table_size;};
                    }
                    else {
                      probe_func_ = [] (int hash_value1, int hash_value2, int num_probe, int hash_table_size) {return (hash_value1 + num_probe*hash_value2) % hash_table_size;};
                    } 
}

HashTable::~HashTable() {  // Task 1
  delete [] table_;
}

bool HashTable::add(const std::string &name, int score) {  // Task 2 & 5
//std::cout<<"Sanity check: ProbeMode:: add\n";
  int hash_value1 = HashTable::hashFunction(name, base_1_, hash_table_size_);
  int hash_value2;

  if (probe_mode_ == ProbeMode::DoubleHash){
    hash_value2 = HashTable::hashFunction(name, base_2_, hash_table_size_);
    //std::cout<<"Sanity check: ProbeMode:: Double Hash\n";
    // if hash_value2 is equal to 0, set it to 1. 
    if (hash_value2 == 0){
      hash_value2 = 1;
    }
  }

  for (int k = 0; k< maximum_probe_num_; k++){
    int num_probe = probe_func_(hash_value1,hash_value2,k,hash_table_size_);
    std::cout << "Probing for the position: " << num_probe << std::endl;

    if (table_[num_probe].state == HashCellState::Active && table_[num_probe].student->name().compare(name) == 0){
      //std::cout<<table_[num_probe].student->name()<<"\n";
      return false;
    }

    if (table_[num_probe].state == HashCellState::Empty || table_[num_probe].state == HashCellState::Deleted){
      //delete table_[num_probe].student;
      table_[num_probe].student = new Student(name,score);
      table_[num_probe].state = HashCellState::Active;
      return true;
    }
  }

  return false;
}

int HashTable::search(const std::string &name) const {  // Task 3
  int hash_value1 = HashTable::hashFunction(name, base_1_, hash_table_size_);
  int hash_value2;

  if (probe_mode_ == ProbeMode::DoubleHash){
    hash_value2 = HashTable::hashFunction(name, base_2_, hash_table_size_);
    //std::cout<<"Sanity check: ProbeMode:: Double Hash\n";
    // if hash_value2 is equal to 0, set it to 1. 
    if (hash_value2 == 0){
      hash_value2 = 1;
    }
  }

  for (int k = 0; k< hash_table_size_; k++){
    int num_probe = probe_func_(hash_value1,hash_value2,k,hash_table_size_);
    std::cout << "Probing for the position: " << num_probe << std::endl;

    if(table_[num_probe].state == HashCellState::Deleted){
      continue;
    }

    if(table_[num_probe].state == HashCellState::Active){
      if (table_[num_probe].student->name().compare(name) == 0){
        return table_[num_probe].student->score();
      }
    }

    if(table_[num_probe].state == HashCellState::Empty){
      return -1;
    }
    /*
    if(k+1 == hash_table_size_){
      return -1;
    }
    */
   
  }

  return -1;
  
}

bool HashTable::remove(const std::string &name) {  // Task 4
  int hash_value1 = HashTable::hashFunction(name, base_1_, hash_table_size_);
  int hash_value2;

  if (probe_mode_ == ProbeMode::DoubleHash){
    hash_value2 = HashTable::hashFunction(name, base_2_, hash_table_size_);
    //std::cout<<"Sanity check: ProbeMode:: Double Hash\n";
    // if hash_value2 is equal to 0, set it to 1. 
    if (hash_value2 == 0){
      hash_value2 = 1;
    }
  }

  for (int k = 0; k< hash_table_size_; k++){
    int num_probe = probe_func_(hash_value1,hash_value2,k,hash_table_size_);
    std::cout << "Probing for the position: " << num_probe << std::endl;

    if(table_[num_probe].state == HashCellState::Deleted){
      continue;
    }

    if(table_[num_probe].state == HashCellState::Active){
      if (table_[num_probe].student->name().compare(name) == 0){
        delete table_[num_probe].student;
        table_[num_probe].student = nullptr;
        table_[num_probe].state = HashCellState::Deleted;
        return true;
      }
    }

    if(table_[num_probe].state == HashCellState::Empty){
      return false;
    }
  }

  return false;
}

void HashTable::reHashUntilSuccess() {
  int next_hash_table_size = getNextHashTableSize(hash_table_size_);
  while (true) {
    if (reHash(next_hash_table_size)) {
      return;
    }
    next_hash_table_size = getNextHashTableSize(next_hash_table_size);
  }
}

bool HashTable::reHash(int rehash_table_size) {  // Task 5

  

}

void HashTable::print() const {
  std::cout << "hash_table_size:" << hash_table_size_ << std::endl;
  for (int i = 0; i < hash_table_size_; i++) {
    std::cout << i << ": state = ";
    if (table_[i].state == HashCellState::Empty) {
      std::cout << "Empty" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Deleted) {
      std::cout << "Deleted" << std::endl;
    } 
    else if (table_[i].state == HashCellState::Active) {
      std::cout << "Active ";
      std::cout << "Student = (" << table_[i].student->name() << ", "
                << table_[i].student->score() << ")" << std::endl;
    }
  }
}

