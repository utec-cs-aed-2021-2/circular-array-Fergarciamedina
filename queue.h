#include "circulararray.h"

template <typename T>
class QueueArray : public CircularArray<T> { 
        T *queue; 
        int front,back;
        int capacity; 
    public:
        QueueArray();
        QueueArray(int _capacity);
        ~QueueArray();
        void enqueue(T data);
        T dequeue();
        bool is_full();
        bool is_empty();
        void clear();
        int size();
    private:
        int next(int index);
        int prev(int index);
};


template <class T>
QueueArray<T>::QueueArray(){
    QueueArray(0);
}

template <class T>
QueueArray<T>::QueueArray(int _capacity){
    this->capacity = _capacity;
    this->front = this->back = -1;
    this->queue = new T[_capacity]; 
}

template <class T>
QueueArray<T>::~QueueArray(){
    delete[] queue;
}

template<class T>
int QueueArray<T>::next(int index){
    return (index + 1);
}

template<class T>
int QueueArray<T>::prev(int index){
    return index - 1;
}

template <class T>
bool QueueArray<T>::is_full(){
    return front == capacity-1 && !is_empty();
}

template <class T>
bool QueueArray<T>::is_empty(){
    return front == -1;
}

template <class T>
void QueueArray<T>::enqueue(T data){
    if(is_full()){
       cout<<"Is full"<<endl;
       return;
   }
   else if (is_empty()){
       this->front = this->back = 0;
       *(this->queue + this->top) = data;
   }
   else{
       back = next(back);
       *(this->queue + this->back) = data;
   }
}

template <class T>
T QueueArray<T>::dequeue(){
    if(is_empty()){
        return -1;
    }
    int temp = *(this->queue + this->front);
    if(back == front){
        front = back = -1;
    }
    else{
        for(int i=front;i<prev(back),i++){
            *(this->queue + i) = *(this->queue + next(i));
        }
        back = prev(back);
    }
    return temp;
}

template <class T>
void QueueArray<T>::clear(){
    dequeue();
}

template <class T>
int QueueArray<T>::size(){
    if(is_empty()){
        return 0;
    }
    else{
        return back+1;
    }
}