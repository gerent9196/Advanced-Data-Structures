#include "SmoothSort.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

void SmoothSort::buildHeap(std::vector<double>& vec){
    
    int a[] = { 1, 1, 3, 5, 9, 15, 25, 41, 67, 109,
          177, 287, 465, 753, 1219, 1973, 3193, 5167, 8361, 13529, 21891,
                35421, 57313, 92735, 150049, 242785, 392835, 635621, 1028457,
                      1664079, 2692537, 4356617, 7049155, 11405773, 18454929, 29860703,
                            48315633, 78176337, 126491971, 204668309, 331160281, 535828591,
                                  866988873 // the next number is > 31 bits.
                                    };
    for(int i=0; i<30; i++){
        LN.push_back(a[i]);
}
    for(int i=0; i<30;i++){
    used_LN.push_back(0);
    tree_in.push_back(0);
}
    for(int head =0; head<vec.size(); head++){
        //check if theres 2 1s in the heap. if there is we need to merge it to a new one
        int added = merge(vec, head);
        selection_sort(vec, head);
        if(added == 0){
            if(used_LN[1] == 1){
                used_LN[0] = 1; tree_in[0] = head;
            }
            else{
                used_LN[1] = 1;
                tree_in[1] = head;
            }
        }
    }
}

//void SmoothSort::mergeHeap(std::vector<double>& vec, int LN_used[], int head){

int SmoothSort::merge(std::vector<double>& vec, int head){
    for(int i= 1; i< used_LN.size(); i++){
        if( used_LN[i-1]==1 and used_LN[i] ==1){
           //time to merge
           used_LN[i-1] =0; tree_in[i-1] = 0;
           used_LN[i] = 0; tree_in[i] = 0;
           used_LN[i+1] = 1; tree_in[i+1] = head;

            fix_down( vec,i+1 , head);
            return 1;
        }
    }
    return 0;
}

void SmoothSort::selection_sort( std::vector<double>& vec,int head){
    for(int i=used_LN.size(); i>=0; i--){
        if(used_LN[i] == 1){
            if( vec.at(tree_in[i]) > vec.at(head)){
                //swap and fix down
                    int temp;
                    temp = vec.at(tree_in[i]);
                    vec.at(tree_in[i]) = vec.at(head);
                    vec.at(head) = temp;
                    fix_down(vec, i, tree_in[i]);   
                }

            }
        }
    }

void SmoothSort::fix_down(std::vector<double>& vec ,int n, int index){

    // n is the leonardo number
    // index is the lenardo root var
    while(1){
        if(n<=1){
            return;
        }
        int rc = index-1;
        int lc = (index-1) - LN[n-2];
        int j = vec.at(lc)>vec.at(rc) ? lc : rc;
       if(vec.at(index) < vec.at(j)){
        double temp = vec.at(index);
        vec.at(index) = vec.at(j);
        vec.at(j) = temp;
        index = j;
       }
       else{
        break;
        }
       if(j == lc){
        n = n-1;
       }
       else{
        n = n-2;
       }
       }
       
}

/*
    if(n ==1 or n==0)
        return;

    int bound = (head +1)- (LN[n]);
    cout << "bound" <<  bound;
    int i = n;

    
    while( head >= bound){
        int lc =  bound+ LN[n-1] -1;
        int  rc = lc+LN[n-2];
        if( lc < 0)
            break;
        cout << "\n head is"<< head<< " n is"<< n<< " Left child is : "<< lc << " Right child is rc:" <<rc;
        cout << "\n value"<< vec.at(lc) << " "<< vec.at(rc);
        int j = lc;
            if( vec.at(lc) < vec.at(rc)){
                j = rc;
            }
        if(vec.at(head) < vec.at(j)){
            double temp = vec.at(head);
            vec.at(head) = vec.at(j);
            vec.at(j) = temp;
            head = j;
            n = n-2;
            if(n<0){
                return;
            }
            cout <<"\nexchanged";
            for(int i=0; i< head; i++){
                cout << "\t"<< vec.at(i);
            }
            lc = bound + LN[n-1]-1;
        }
        else{
            break;
        }

    }

}
*/

/*
    while( (LN[n-1]-1)){
        int lc = LN[n-1] - 1;
        int rc = lc + LN[n-2];
        int j = lc;
        cout << "\n j "<< j << " lc "<< lc <<" rc "<< rc << "Val at rc"<< vec.at(rc) << "val at lc"<< vec.at(lc);
        if (rc){
            if( vec.at(lc) < vec.at(rc)){
                j = rc;
            }
        }
        cout << "vec at n"<< vec.at(head) << "At j:"<< vec.at(j);
        if( vec.at(head) < vec.at(j)){
            cout << "Exchanged";
            double temp = vec.at(head);
            vec.at(head) = vec.at(j);
            vec.at(j) = temp;
            cout <<"\nexchanged";
            for(int i=0; i< head; i++){
                cout << "\t"<< vec.at(i);
            }
            n = j;
        }
        else{
            break;
        }
        if( n==j){ break;}
    }
        */
void SmoothSort::sort(std::vector<double>& vec){

    int head = vec.size()-1;
    while(head){
    head--;
    for(int i=0; i< used_LN.size(); i++){
            if(used_LN.at(i) ==1){
                int index = tree_in[i];
                //leonardo number is LN[i]
                if(i==0 or i==1){
                    //do selection sort only
                    used_LN.at(i)=0;
                    tree_in.at(i)=0;
                selection_sort(vec, head);
                }
                else{
                int rc = index-1;
                int lc = (index-1) - LN[i-2];
                used_LN.at(i) = 0;
                used_LN.at(i-1) = 1;
                used_LN.at(i-2) = 1;
                tree_in[i] = 0;
                tree_in[i-1] = lc;
                tree_in[i-2] = rc;
                selection_sort(vec, head);
                }
                break;
            }
    }
    }
    }






