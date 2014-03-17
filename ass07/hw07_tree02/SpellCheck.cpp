#include "SpellCheck.h"
#include <iostream>
using namespace std;


void SpellCheck::loadDictionary(std::vector<std::string>& words){
    this->words = words;
}

std::vector<std::string> SpellCheck::suggestCorrections(std::string word){
    //cout << "Word: ";
    //cout<< word;
    std::vector<std::string> final;
    for(int i=0; i< words.size(); i++){
        std::string wi = words[i];
        int wiSize = wi.size();
        int wordSize = word.size();
        int cost[wiSize+1][wordSize+1] ;
        for(int i=0; i<= wiSize; i++)
            cost[i][0] = i;
        for(int i=0; i<= wordSize; i++)
            cost[0][i] = i;
        for(int i=1; i<=wiSize; i++){
            for(int j=1; j<=wordSize; j++){
                    int sub = cost[i-1][j-1];
                    int del = cost[i-1][j]+1;
                    int ins = cost[i][j-1]+1;
                    if(wi[i-1] != word[j-1]){
                       sub = sub+1; 
                    } 
                    int min =  (sub<del)? sub : del;
                    min = (min<ins)? min : ins;
                    cost[i][j] = min;
            }
        }

        if(cost[wiSize][wordSize] == 1){
            final.push_back(wi);
        }
    }
    return final;
}

