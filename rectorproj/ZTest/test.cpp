#include <iostream>
#include <string.h>

int LastLengthWord(std::string s){
    int result = 0;
    int len = s.size()-1;
    while( len >= 0 && s[len] == ' ' ){
        len--;
    }
    while (len >= 0 && s[len] != ' ' ){
        result++;
        len--;
    }
    return result;
}

int main()
{
    std::string str = "hello world";
    char s = 'hello nihao  ';
}