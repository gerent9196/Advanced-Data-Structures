#include "VectorDoubleSort.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void VectorDoubleSort::sort(std::vector<double>& vec){
    unsigned double *p = (unsigned double*) calloc(200000, sizeof(double));
    unsigned long to_and[] = {1,2,4,8,16,32,64,128};
    for(int i=0 ; i<vec.size();i++){
        unsigned long val = vec.at(i);
        if( val < 8){
            p[0] = (int)(unsigned long) p[0] | to_and[val];
            continue;
        }
        unsigned long pos = val & (unsigned long) 7;
        val = val >> (unsigned long) 3;
        p[val] = (unsigned long) p[val] | to_and[pos];
    }
    vec.clear();
    int count = 0;
    for(int i=0; i< 25*1024; i++){
        for(int j = 0; j< 8; j++){
            if((((p[i]) & to_and[j])) == to_and[j] ){
                vec.push_back(double( i*8 +j));
                count++;
            }
        }
    }
 


}
