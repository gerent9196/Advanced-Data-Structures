#include "Compress.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace std;

std::string Compress::compress(std::string input){
    //run length encoding
    std::string output;
    for(int i=0; i< input.size(); ){
        int count = 1;
        int j=1;
        bool flag = true;
        while(input[i] == input[i+j]){
           j++; 
           count++;
           flag = false;
        }
        stringstream s;
        s<<count<< input[i];
        output+=s.str();
        if(flag)
            i=i+1;
        else
            i+=(count);
    }
    return output;
}
std::string Compress::decompress(std::string compressed){
   std::string output;
    cout<<compressed;
   for(int i=0; i< compressed.size(); i+=2){
        char count = compressed[i];
        std::stringstream buffer;
        buffer << count;
        int val;
        buffer>>val;
        for(int j=0;j<val;j++){
            output+=compressed[i+1];
        }
        cout<< output;
    } 
    return output;
} 
