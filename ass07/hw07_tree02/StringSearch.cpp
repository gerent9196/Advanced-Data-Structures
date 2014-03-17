#include "StringSearch.h"
#include <string>
#include <iostream>
using namespace std;

void StringSearch::prepareText(std::string text){
    data = text;
}

std::vector<int> StringSearch::search(std::string pattern){
   std::vector<int> final;
   for(int i=0; i<data.size(); i++){
        
        int k = i;
        int s=0;
        while(pattern[s] == data[k]){
            s++;
            k++;
            if(s == pattern.size()-1){
                final.push_back(i);
                break;
            }      
            }
    }
   return final;
}
