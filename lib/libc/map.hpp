#ifndef MAP_H
#define MAP_H
#include <lib/libc/vector.hpp>


template<typename typ1,typename typ2>
class map {
private:
    vector<typ1> keyVect;
    vector<typ2> valueVect;
    class proxy {
        map &a;
        typ1 idx;
    public:
        proxy(map &a, typ1 idx) : a(a), idx(idx) {}
        void operator= (typ2 x) { 
            bool done = false;
            for(int i=0; i<a.keyVect.size(); i++){
                if(a.keyVect[i].value() == idx){
                    a.valueVect[i] = x;
                    done = true;
                }
            }
            if(!done){
                a.keyVect.push_back(idx);
                a.valueVect.push_back(x);
            }
        }
        typ2 value(){
            for(int i=0; i<a.keyVect.size(); i++){
                if(a.keyVect[i].value() == idx){
                    return a.valueVect[i].value();
                }
            }
            return NULL;
        }
    };
public:
    vector<typ1> keys(){
        return keyVect;
    }
    vector<typ2> values(){
        return valueVect;
    }
    proxy operator[](typ1 k){
        return proxy(*this,k);
    }
    
};


#endif