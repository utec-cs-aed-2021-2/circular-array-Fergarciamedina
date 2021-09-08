#include <iostream>
using namespace std;

template <class T>
class CircularArray
{
private:
    T *array;
    int capacity;
    int back, front;

public:
    CircularArray();
    CircularArray(int _capacity);
    
    // Default destructor
    virtual ~CircularArray();
    
    void push_front(T data);
    void push_back(T data);
    void insert(T data, int pos);
    T pop_front();
    T pop_back();
    bool is_full();
    bool is_empty();
    int size();
    void display();
    void clear();
    T &operator[](int);
    void sort();
    bool is_sorted();
    CircularArray *reverse();

private:
    int next(int);
    int prev(int);
};

template <class T>
CircularArray<T>::CircularArray()
{
    CircularArray(0);
}

template <class T>
CircularArray<T>::CircularArray(int _capacity)
{
    this->capacity = _capacity;
    this->front = this->back = -1;
    this->array = new T[_capacity];
}

template <class T>
CircularArray<T>::~CircularArray()
{
    delete[] array;
}

template <class T>
int CircularArray<T>::prev(int index)
{
    return (index == 0) ? capacity - 1 : index - 1;
}

template <class T>
int CircularArray<T>::next(int index)
{
    return (index + 1) % capacity;
}

template <class T>
T &CircularArray<T>::operator[](int index){
    if (index>=capacity){
        exit(0);
    }
    return *(this->array + index); 
}

template <class T>
int CircularArray<T>::size(){
    if (is_empty()){
        return 0;
    } 
    if (back<front){
        return capacity+1-(front-back);
    }
    else {
        return (back-front) +1;
    }
}

template <class T>
bool CircularArray<T>::is_empty()
{
    return front == -1;
}

template <class T>
bool CircularArray<T>::is_full()
{
    return front == next(back) && !is_empty();
}


template <class T>
void CircularArray<T>::push_front(T data){
    if(is_full()){
        cout<<"Array full"<<endl;
        return;
    }
    else if(is_empty()){
        this->front = this->back = 0;
        *(this->array + this->back) = data;
    }
    else{
        int temp = back;
        back = next(back);
        while(temp!=prev(front)){
            *(this->array + this->next(temp)) = *(this->array + temp);
            temp = prev(temp);
        }
        // when temp == front
        *(this->array+this->front) =  data;
    }
}

template <class T>
void CircularArray<T>::push_back(T data)
{
    if(is_full()){
        cout<<"Array full"<<endl;
        return;
    }
    else if(is_empty()){
        this->front = this->back = 0;
        *(this->array + this->back) = data;
    }
    else{
        *(this->array + this->next(back)) = data;
        back = next(back);
    } 
}

template <class T>
T CircularArray<T>::pop_front(){
    if(is_empty()){
        cout<<"Cola vacia"<<endl;
        return 0;
    }
    int temp = *(this -> array + this -> front);
    *(this -> array + this -> front) = -1;
    if(front == back){
        front = back= -1;
    }
    else{
        front = next(front);
    }
    return temp;
}

template <class T>
T CircularArray<T>::pop_back(){
    if(is_empty()){
        cout<<"Cola vacia"<<endl;
        return 0;
    }
    int temp = *(this -> array + this->back);
    *(this -> array + this->back) = -1;
    if (front == back){
        front = back = -1;
    }
    else{
        back = prev(back);
    }
    return temp;    
}


template <class T>
void CircularArray<T>::clear(){
    while(size()!=0){
        pop_back();
    }
}

template<class T> 
CircularArray<T> *CircularArray<T>::reverse(){
    CircularArray<int>* newArray = new CircularArray<int>(capacity);
    int first = front;
    while(first!=back){
        newArray->push_front(*(this->array + first));
        first = next(first);
    }
    newArray->push_front(*(this->array + back));
    return newArray;
}

template<class T> 
void CircularArray<T>::sort(){
    int actual = front;
    if (is_empty()){
        return;
    }
    else{
        do{
            int pivote = next(actual);
            while (pivote != next(back)){
                if (*(this->array + actual) > *(this->array + pivote)){
                    int temp = *(this->array + actual);
                    *(this->array + actual) = *(this->array + pivote);
                    *(this->array + pivote) = temp;
                }
                pivote = next(pivote);
            }
        actual = next(actual);
        }while(next(actual) != next(back));
    }

}

template<class T> 
bool CircularArray<T>::is_sorted(){
    int first = front;
    int last = back;
    if (first == last){
        return true;
    }
    int pivote = first;
    while (++pivote != last){
        if (*(this -> array + pivote)<*(this->array + first)){
            return false;
        }
        ++first;
    }
    return true;
}

template<class T>
void CircularArray<T>::insert(T data, int pos){
    if (is_full()){
        cout<<"Array full"<<endl;
        return;
    }
    else if (is_empty()){
        if (pos!=0){
            cout<<"Invalid position, empty array"<<endl;
            return;
        }
        else{
            push_front(data);
        }
    }
    else if (pos>next(back) && pos<=prev(front)){
        cout<<"Invalid position"<<endl; 
        return;
    }
    else{
        if (pos==front){
            push_front(data);           
        }
        else if (pos == next(back)){
            push_back(data);
        }
        else{
            int temp;
            temp = back;
            back = next(back);
            while(temp!=prev(pos)){
                *(this->array + next(temp)) = *(this->array + temp);
                temp = prev(temp);
            }
            *(this->array + pos) = data;
        }
    }   

}

template <class T>
void CircularArray<T>::display()
{
    for (int i = 0; i < size(); i++)
        cout << (*this)[i] << ",";
    cout << endl;
}
