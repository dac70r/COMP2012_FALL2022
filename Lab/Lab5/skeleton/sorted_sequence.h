#ifndef __SORTED_SEQUENCE__
#define __SORTED_SEQUENCE__

#include <iostream>
#include <sstream>
#include <string>

template <typename T>
class SortedSequence{
  public:
    SortedSequence() : capacity_(0), size_(0), data_(nullptr) {}
    ~SortedSequence() { delete[] data_; }

    void add(const T &a) {  // Task 2 - To Do

      // k is index used to traverse the array
      int k = 0;
      
      // checks if there is enough space for data
      if(capacity_ <= size_){
        // 
        if(data_ == nullptr){
          capacity_ = 1;
          data_ = new T[1];
          // allocating 1 space only 
        }
        else{
          capacity_ = capacity_*2;
          T* new_data = new T[capacity_];
          //copy everything for old array to new_array 
          for (int k=0; k<size_; k++){
            new_data[k] = data_[k];
          }
          // delete the old array
          delete [] data_;
          data_ = nullptr;
          // assign new_array to the pointer array 
          data_ = new_data;
        }
      }

      // looking for the index of the number in the array 
      // that is bigger than a 
      while (k<size_ && data_[k]<a){
        k++;
      }
      //shift the array positions to the right by 1 based 
      // on the index 
      for (int j= size_;j>k;j--){
        data_[j] = data_[j-1];
      }
      // add the element to index location 
      data_[k] = a;

      // always increment the size at the end 
      size_++;
    }

    std::string toString() const {
      std::stringstream ss;
      ss << "capacity: " << capacity_ << ", size: " << size_
        << ", data: " << std::endl;
      if (data_ == nullptr) {
        ss << "None";
      } else {
        for (int i = 0; i < size_; i++) {
          ss << data_[i] << " ";
        }
      }
      return ss.str();
    }

  private:
    int capacity_;
    int size_;
    T *data_;
};

template <typename T>
std::ostream& operator<<(std::ostream& os, const SortedSequence<T>& t) {
  os << t.toString();
  return os;
}

#endif 