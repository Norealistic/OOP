#include <iostream>
#include "MyIterator.h"

namespace Dungeon {

template <class T>
    
class MyVector{
    private:
        T *array;
        const static unsigned int size = 4;
        unsigned int currentsize;
    public:
        MyVector() : array(nullptr), currentsize(0) {}
     
        ~MyVector(){
            delete[] array;
            currentsize = 0;
        }
        
        static unsigned int const_size(){return size;}
        unsigned int current_size(){return currentsize;}
    
    

        bool operator!=(MyVector<T> &vec) {
            if (this->size_ == vec.size_) {
                for (int i = 0; i < this->size_; i++) {
                    if (this->data_[i] != vec.data_[i])
                        return false;
                }
                return false;
            } else
                return true;
        }
    
    
    MyIterator <T> &Begin(){
        MyIterator <T> it(&(this->array[0]));
              return it;
          }
    
    MyIterator <T> &End(){
        MyIterator <T> it(&(this->array[this->currentsize]));
        return it;
    }
    

    MyVector(const unsigned int new_size){
        if (new_size <= size){
            array(new T[new_size]);
            currentsize(0);
        }
        else throw std::exception();
    }

    
    MyVector(const T *new_array){
        unsigned int arr_size = _msize(new_array)/sizeof(T);
        if (arr_size <= size){
            array(new T[arr_size]);
            for (int i = 0; i < arr_size; i++)
                array[i] = new_array[i];
            currentsize(arr_size);
        }
        else throw std::exception();
    }

    
    T& operator[](const unsigned int index){
        if (index > currentsize)
            throw std::exception();
        else
            return array[index];
    }

  
    void Push_back (const T &element){
        T *p = new T[currentsize + 1];
        for (int i = 0; i < currentsize; i++)
            p[i] = array[i];
        p[currentsize + 1] = element;
        delete[] array;
        array = p;
        currentsize++;
    }

    
    void Pop_back(){
        if (currentsize){
            T *p = new T[currentsize - 1];
            for (int i = 0; i < currentsize - 1; i++)
                p[i] = array[i];
            delete[] array;
            array = p;
            currentsize--;
        }
        else throw std::exception();
    }


    void Erase(const unsigned int index){
        if (index <= currentsize){
            T *p1 = new T[currentsize - 1];
            for (int i = 0; i < index; i++)
                p1[i] = array[i];
            for (int i = index + 1; i < currentsize; i++)
                p1[i] = array[i];
            delete [] array;
            array = p1;
            currentsize--;
        }
        else throw std::out_of_range("index is out of range");
    }


    void Clear(){
        if (array)
            delete[] array;
        currentsize = 0;
    }
    
    };

}

