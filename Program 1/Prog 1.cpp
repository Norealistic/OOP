#include <iostream>
#include "Prog 1.h"

namespace NS1 {
void Create_Node(struct Node*& matrix, int element, int row_index, int column_index) {
        struct Node *temp, *rows;
        temp = matrix;
        
        if (!temp) {
           try {
               temp = new struct Node;
           }
           catch (std::bad_alloc &ba) {
               std::cout << "Error in allocating memory: " << ba.what() << std::endl;
               return;
           }
           temp->value = element;
           temp->row = row_index;
           temp->column = column_index;
           temp->next = nullptr;
           matrix = temp;
        }
        else {
           while (temp->next != nullptr) {
              temp = temp->next;
           }
           try {
               rows = new struct Node;
           }
           catch (std::bad_alloc &ba) {
               std::cout << "Error in allocating memory: " << ba.what() << std::endl;
               return;
           }
           rows->value = element;
           rows->row = row_index;
           rows->column = column_index;
           rows->next = nullptr;
           temp->next = rows;
        }
    }
    
    struct Node* Create_Matrix(int &rm, int &rn) {
        const char *pr = "";
        struct Node *matrix = nullptr;
        int m, n, i, j;
        int item;
        int flag = 1;
        
        do {
            std::cout << pr;
            std::cout << "Enter the matrix dimensions: ";
            pr = "Invalid input, please try again!\n";
            if (getNum(m) < 0 || getNum(n) < 0) {
               return nullptr;
            }
        } while (m < 1 || n < 1);
        
        while (flag){
        std::cout << "Enter the line, the row and the value of the element: ";
        if (getNum(i) < 0 || getNum(j) < 0) {
                      return nullptr;
                   }
        if (getNum(item) < 0) {
           Erase_Matrix(matrix);
           return nullptr;
        }
        else{
        Create_Node(matrix, item, i, j);
            std::cout << "[1] - add another " << std::endl;
            std::cout << "[0] - stop input " << std::endl;
            getNum(item);
            if (item != 1 && item != 0 ) {
                std::cout << "Incorrect data detected!" << std::endl;
            }
            if (item == 0){
                flag = 0;
            }
        }
        }
      
        rm = m;
        rn = n;
        return matrix;
    }
    
    
    void Print_Matrix(const char *msg, struct Node* matrix, int m, int n) {
        std::cout << msg << std::endl;
        struct Node *temp = matrix;
        selectionSort1(temp);
        while (temp) {
            std::cout << "matrix[" << temp->row << "][" << temp->column << "] = " << temp->value << std::endl;
            temp = temp->next;
        }
            std::cout << std::endl;
    }
    
    void Print_Vector(const char *msg, int vector[], int m) {
        std::cout << msg << std::endl;
        for (int i = 0; i < m; i++) {
            std::cout << vector[i] << " ";
        }
        std::cout << std::endl;
    }
    
    struct Node* Erase_Matrix(struct Node* matrix) {
        struct Node *curr, *tmp;
        curr = matrix;
        while (curr) {
           tmp = curr;
           curr = curr->next;
           delete tmp;
        }
        return nullptr;
    }

     void selectionSort(struct Node* matrix, int row_index) {
        struct Node *temp = matrix;
     
        while (temp) {
            struct Node *min = temp;
            struct Node *r = temp->next;
               while (r) {
                  if (min->value > r->value && r->row == row_index && min->row == row_index) {
                     min = r;
                  }
                  r = r->next;
                }
    
               int x = temp->value;
               temp->value = min->value;
               min->value = x;
               temp = temp->next;
            }
    }


     void selectionSort1(struct Node* matrix) {
        struct Node *temp = matrix;
        while (temp) {
            struct Node *min = temp;
            struct Node *r = temp->next;
               while (r) {
                  if (r->row <= min->row && r->column <= min->column) {
                     min = r;
                  }
                  r = r->next;
                }
            int x = temp->value;
            temp->value = min->value;
            min->value = x;
            
            int m = temp->row;
            temp->row = min->row;
            min->row = m;
            
            int k = temp->column;
            temp->column = min->column;
            min->column = k;
            temp = temp->next;
            }
    }


    int* Create_Vector(struct Node* matrix, int m, int n) {
            struct Node *temp = matrix;
            int *vector = nullptr;
            int num_of_equals = 1;
            int max_num_of_equals = 1;
            int current_value = 0;
            int current_row = 0;
            
            try {
                vector = new int[m];
            }
            catch (std::bad_alloc &ba) {
                std::cout << ba.what() << std::endl;
                return nullptr;
            }
    
            for (int i = 0; i < m; i++) {
                selectionSort(temp, i);
            }
        
        for (int i = 0; i<=m; i++) {
            vector[i] = 0;
        }

        int prev = temp->row;
        
        while (temp) {
           if (temp->row == current_row) {
              if (temp->value == current_value) {
                 num_of_equals++;
              }
              else {
                 current_value = temp->value;
                 num_of_equals = 1;
              }
            if (num_of_equals > max_num_of_equals){
                max_num_of_equals = num_of_equals;
            }
               if (!temp->next){
                 vector[temp->row] = max_num_of_equals;
               }
           }
           else {
               if (!temp->next){
                 vector[temp->row] = max_num_of_equals;
               }
               else{
               current_row = temp->row;
               vector[prev] = max_num_of_equals;
               current_value = temp->value;
               num_of_equals = max_num_of_equals = 1;
               }
           }
           prev = temp->row;
           temp = temp->next;
        }
            return vector;
        }
    
}
