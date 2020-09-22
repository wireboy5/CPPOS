#ifndef VECTOR_H
#define VECTOR_H
#include <lib/libc/op.h>
#include <lib/libc/iterator.hpp>

template <typename T> 
class vector { 
private: 
     
    long long capacity; 
    long long length; 
    T* arr;
    
    class proxy {
        vector &a;
        long long idx;
        T valuet;
    public:
        proxy(vector &a, long long idx, T value) : a(a), idx(idx), valuet(value){}
        T value(){
            return valuet;
        }
        void operator=(T val){
            a.arr[idx] = val;
        }
    };
public:
    
    vector(long long = 100); 
    vector(long long,T init[] = {}); 
    long long push_back(T); 
    T pop_back(); 
    long long size() const; 
    proxy operator[](long long); 
    void operator=(T a){
        for(int i=0; i<sizeof(a)/sizeof(T); i++){
            push_back(a[i]);
        }
    }
    class iterator { 
    private: 
        T* ptr; 
  
    public: 
        explicit iterator() 
            : ptr(nullptr) 
        { 
        } 
        explicit iterator(T* p) 
            : ptr(p) 
        { 
        } 
        bool operator==(const iterator& rhs) const
        { 
            return ptr == rhs.ptr; 
        } 
        bool operator!=(const iterator& rhs) const
        { 
            return !(*this == rhs); 
        } 
        T operator*() const
        { 
            return *ptr; 
        } 
        iterator& operator++() 
        { 
            ++ptr; 
            return *this; 
        } 
        iterator operator++(int) 
        { 
            iterator temp(*this); 
            ++*this; 
            return temp; 
        } 
    }; 
    
    // Begin iterator 
    iterator begin() const; 
  
    // End iterator 
    iterator end() const; 
}; 
  
// Template class to return the size of 
// vector of different data_type 
template <typename T> 
vector<T>::vector(long long n) 
    : capacity(n), arr(new T[n]), length(0) 
{ 
} 
template <typename T> 
vector<T>::vector(long long n,T init[]) 
    : capacity(sizeof(init)/sizeof(T)), arr(init), length(0) 
{ 

} 
  
// Template class to insert the element 
// in vector 
template <typename T> 
long long vector<T>::push_back(T data) 
{ 
    if (length == capacity) { 
        T* old = arr; 
        arr = new T[capacity = capacity * 2]; 
        mem::memcpy((uint32_t *)old, (uint32_t *)(old + length), (int)arr); 
        delete[] old; 
    } 
    arr[length++] = data; 
    return length; 
} 
  
// Template class to return the popped element 
// in vector 
template <typename T> 
T vector<T>::pop_back() 
{ 
    return arr[length-- - 1]; 
} 
  
// Template class to return the size of 
// vector 
template <typename T> 
long long vector<T>::size() const
{ 
    return length; 
} 
  
// Template class to return the element of 
// vector at given index 
template <typename T> 
typename vector<T>::proxy vector<T>::operator[](long long index) 
{ 
    // if given index is greator than the 
    // size of vector print Error 
    if (index >= length) { 
        return vector<T>::proxy(*this,size()+1,*(arr + size()));
    } else {
        return vector<T>::proxy(*this,index,*(arr + index));
        //return *(arr + index);
    }
}


  
// Template class to return begin iterator 
template <typename T> 
typename vector<T>::iterator  
                      vector<T>::begin() const
{ 
    return iterator(arr); 
} 
  
// Template class to return end iterator 
template <typename T> 
typename vector<T>::iterator  
                        vector<T>::end() const
{ 
    return iterator(arr + length); 
} 



#endif