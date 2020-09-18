#ifndef ITERATOR_H
#define ITERATOR_H
template <typename T>
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
#endif