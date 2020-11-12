#include "string.h"


namespace string {


string::string(char * str)
{
    set(str);
}


string::string(int n){
    set(n);
}
void string::reallocate(uint32_t len){
    mem::realloc(arr,(size_t)len);
    scapacity = len;
}
void string::set(char * s){
    if(sizeof(s) > scapacity){
        arr = (char*)mem::malloc(sizeof(s));
    }
    arr = s;
    slength = strlen(s);
}
void string::set(int n){
    char *a;
    int_to_ascii(n,a);
    if(sizeof(a)>scapacity){
        arr = (char*)mem::malloc(sizeof(a));
    }
    arr = a;
    slength = strlen(a);
}
char* string::c_str(){
    return arr;
}
uint32_t string::size(){
    return slength;
}
uint32_t string::length(){
    return slength;
}
size_t string::max_size(){
    return 4294967291;
}
void string::resize(uint32_t n){
    if(n>max_size()){
        return;
    }
    
    if(n<slength){
        char * a = new char[n];
        for(int i=0; i<n; i++){
            a[i] = arr[i];
        }
        a[n] = *"\0";
        arr = a;
        delete[] a;
        
    }
    reallocate(n);
    
    
}
uint32_t string::capacity(){
    return scapacity;
}
string string::operator=(char * str) {
    set(str);
    return *this;
}
string string::operator*(int num) {
    if(sizeof(arr)*num > scapacity){
        reallocate(sizeof(arr)*num);
    }
    arr = new char[scapacity];
    return *this;
}




void int_to_ascii(int n, char str[]) {
    int i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}
char intToASCII(int n){
    char * str = new char[256];
    int_to_ascii(n,str);
    return *str;
}

char hexToASCII(int n){
    char * str = new char[256];
    hex_to_ascii(n,str);
    return *str;
}

void hex_to_ascii(int n, char str[]) {
    append(str, '0');
    append(str, 'x');
    char zeros = 0;

    int32_t tmp;
    int i;
    for (i = 28; i > 0; i -= 4) {
        tmp = (n >> i) & 0xF;
        if (tmp == 0 && zeros == 0) continue;
        zeros = 1;
        if (tmp > 0xA) append(str, tmp - 0xA + 'a');
        else append(str, tmp + '0');
    }

    tmp = n & 0xF;
    if (tmp >= 0xA) append(str, tmp - 0xA + 'a');
    else append(str, tmp + '0');
}


void reverse(char s[]) {
    int c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}


int strlen(char s[]) {
    int i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void append(char s[], char n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(char s[]) {
    int len = strlen(s);
    s[len-1] = '\0';
}


int strcmp(char s1[], char s2[]) {
    int i;
    for (i = 0; s1[i] == s2[i]; i++) {
        if (s1[i] == '\0') return 0;
    }
    return s1[i] - s2[i];
}


} // namespace string

