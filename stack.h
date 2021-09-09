#include "circulararray.h"

template <typename T>
class StackArray : public CircularArray<T> { 
    private:
        T *stack; 
        int top;
        int capacity; 
    public:
        StackArray();
        StackArray(int _capacity);
        ~StackArray();
        void push(T data);
        T pop();
        T peek();
        bool is_full();
        bool is_empty();
        void clear();
        void display();
        int size();
    private:
        int next(int index);
        int prev(int index);
};

template <class T>
StackArray<T>::StackArray(){
    StackArray(0);
}

template <class T>
StackArray<T>::StackArray(int _capacity){
    this->capacity = _capacity;
    this->top = -1;
    this->stack = new T[_capacity];
}

template <class T>
StackArray<T>::~StackArray()
{
   delete[] stack;
}

template<class T>
int StackArray<T>::next(int index){
    return (index + 1);
}

template<class T>
int StackArray<T>::prev(int index){
    return index - 1;
}

template <class T>
bool StackArray<T>::is_full(){
    return top == capacity-1 && !is_empty();
}

template <class T>
bool StackArray<T>::is_empty(){
    return top == -1;
}

template <class T>
void StackArray<T>::clear(){
    while(!is_empty()){
        pop();
    }
}

template <class T>
void StackArray<T>::push(T data){
   if(is_full()){
       cout<<"Is full"<<endl;
       return;
   }
   else if (is_empty()){
       this->top = 0;
       *(this->stack + this->top) = data;
   }
    else{
        top = next(top);
        *(this->stack + this->top) = data;
    }
}

template <class T>
T StackArray<T>::pop(){
    if (is_empty()){
       return -1;
   }
   int temp = *(this->stack + this->top);
   *(this->stack + this->top) = -1;
   if (top == 0){
       top = -1;
   }
   else{
       top = prev(top);
   }
   return temp;
}

template <class T>
T StackArray<T>::peek(){
    if (is_empty()){
        return -1;
    }
    else{
        return *(this->stack + this->top);
    }
}

template <class T>
void StackArray<T>::display(){
    for (int i = 0; i < size(); i++)
        cout << (*this)[i] << ",";
    cout << endl;
}


template<class T>
int StackArray<T>::size(){
    return top+1;
}
