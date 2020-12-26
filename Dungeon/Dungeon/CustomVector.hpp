#include <iostream>
#include "MyIterator.h"

namespace Dungeon {

/**
 \brief Шаблонный класс 
 \author Галацан Никита
 \version 2.0
 Шаблонный класс MyVector, который используется для хранение класса Armor
 */


template <class T>
class MyVector{
    private:
        T *array;         ///< Массив значений
        const static unsigned int size = 4;  ///< Максимальный размер вектора
        unsigned int currentsize; ///<Текущий размер вектора
    public:
        MyVector() : array(nullptr), currentsize(0) {} ///< Инициализирующий коструктор
     
     /*!
      Деструктор
      */
    
        ~MyVector(){
            delete[] array;
            currentsize = 0;
        }
    
        /*!
           Метод для определения максимальной длины вектора
           \return Максимальную длину
          */
        static unsigned int const_size(){return size;}
    /*!
        Метод для определения текущей длины вектора
        \return Текущую длину
    */
        unsigned int current_size(){return currentsize;} ///< Возвращает текущий размер вектора
    
    /*!
        Перегруженный оператор неравенста
     \param vec {вектор}
    */

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
    
    /*!
           Метод, возвращаюций итератор, который указывает на первый элемент массива
        \return Итератор, указывающий на первый элемент
       */
    
    MyIterator <T> &Begin(){
        MyIterator <T> it(&(this->array[0]));
              return it;
          }
    
    /*!
        Метод, возвращаюций итератор, который указывает на последний элемент массива
        \return Итератор, указывающий на последний элемент
    */
    
    MyIterator <T> &End(){
        MyIterator <T> it(&(this->array[this->currentsize]));
        return it;
    }
    
    /*!
        Конструктор, инициализирующий текущую длину вектора
     \param new_size {текущая длина вектора}
     \throw std::out_of_range В случае если текущая длина вектора больше максимального
     */

    MyVector(const unsigned int new_size){
        if (new_size <= size){
            array(new T[new_size]);
            currentsize(0);
        }
        else throw std::out_of_range("Too big");
    }

    /*!
    Конструктор, инициализирующий текущий вектор в сооствествии с указанным вектором
     \param new_array {инициализирующий вектор}
     \throw std::out_of_range В случае если текущая длина вектора больше максимального
    */
    
    MyVector(const T *new_array){
        unsigned int arr_size = _msize(new_array)/sizeof(T);
        if (arr_size <= size){
            array(new T[arr_size]);
            for (int i = 0; i < arr_size; i++)
                array[i] = new_array[i];
            currentsize(arr_size);
        }
        else throw std::out_of_range("Too big");
    }

/*!
Перегруженный оператор взятия элемента массива
 \param index {индекс элемента}
 \throw std::out_of_range В случае если индекс элемента  больше максимального
*/
    
    T& operator[](const unsigned int index){
        if (index > currentsize)
            throw std::out_of_range("Ellement is non-existent");
        else
            return array[index];
    }

  
/*!
Метод, добавляющий элемент в конец вектора
 \param element {элемент вектора}
*/
    void Push_back (const T &element){
        T *p = new T[currentsize + 1];
        for (int i = 0; i < currentsize; i++)
            p[i] = array[i];
        p[currentsize + 1] = element;
        delete[] array;
        array = p;
        currentsize++;
    }

    /*!
    Метод, удаляющий последний элемент вектора
     \throw std::out_of_range В случае, если вектор пустой
    */
    
    void Pop_back(){
        if (currentsize){
            T *p = new T[currentsize - 1];
            for (int i = 0; i < currentsize - 1; i++)
                p[i] = array[i];
            delete[] array;
            array = p;
            currentsize--;
        }
        else throw std::out_of_range("Empty");
    }

    /*!
    Метод, удаляющий элемент по индексу в массиве
     \param index {индекс элемента}
      \throw std::out_of_range В случае если индекс элемента  больше максимального
    */

    
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
    
    /*!
    Метод, удаляющий все элементы массива
    */

    void Clear(){
        if (array)
            delete[] array;
        currentsize = 0;
    }
    
    };

}

