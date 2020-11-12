#ifndef STRING_H
#define STRING_H
#include <stdint.h>
#include <lib/libc/iterator.hpp>
#include <lib/libc/mem.h>


namespace string {

class string{
private:
    uint32_t slength;
    uint32_t scapacity = 8;
    char* arr;

public:
    string(char * str);
    string(int n);
    void reallocate(uint32_t len);
    void set(char * s);
    void set(int n);
    char* c_str();
    uint32_t size();
    uint32_t length();
    size_t max_size();
    void resize(uint32_t n);
    uint32_t capacity();
    string operator=(char * str);
    string operator*(int num);
};


void int_to_ascii(int n, char str[]);
void hex_to_ascii(int n, char str[]);
void reverse(char s[]);
int strlen(char s[]);
void backspace(char s[]);
void append(char s[], char n);
int strcmp(char s1[], char s2[]);
char  hexToASCII(int n);
char  intToASCII(int n);
} // namespace string
#endif