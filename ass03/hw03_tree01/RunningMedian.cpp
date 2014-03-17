#include "RunningMedian.h"
#include <vector>
#include <iostream>
using namespace std;

std::vector<int> RunningMedian::compute(std::vector<int> vec, int window_size){
    int mid_win_size = window_size/2;
    int max_heap[mid_win_size];
    int min_heap[mid_win_size];
    int min_index=1;
    int max_index=1;
    vector<int> heap_index;
    vector<int> heap_flag;
    vector<int> final;

    //min heap is 0 , max heap is 1
    int start_index=0;
    final.push_back(vec.at(0));
    if (vec.at(0) > vec.at(1)) {
       max_heap[0] = 1;
       min_heap[0] = 0;
       heap_index.push_back(0);
       heap_index.push_back(0);
       heap_flag.push_back(0);
       heap_flag.push_back(1);
        
    }
    else{
       max_heap[0] = 0;
       min_heap[0] = 1;
       heap_index.push_back(0);
       heap_index.push_back(0);
       heap_flag.push_back(1);
       heap_flag.push_back(0);
    }
    final.push_back((vec.at(0) + vec.at(1))/2);

    //fill array till window size reached;
    for(int i = 2; i<window_size; i++){
        int element =vec.at(i);
        if (element< vec.at(max_heap[0])){
            //add to max_heap
            //add_to_max_heap(max_heap, max_index,element,i, heap_index, heap_flag);
            max_index++;
            max_heap[max_index-1] = i;
            heap_flag.push_back(1);
            heap_index.push_back(max_index-1);
    /*cout << "\nmax heap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" <<max_heap[i];
    }
        cout << "\n max fix upheap_index";
        for(int i=0; i< heap_index.size(); i++){
            cout << "\t" << heap_index.at(i);
            }
            */
            max_fix_up(max_heap, max_index, vec, heap_index, element);
            /*
    cout << "\nmax  after upheap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" <<max_heap[i];
    }
        cout << "\n max fix upheap_index";
        for(int i=0; i< heap_index.size(); i++){
            cout << "\t" << heap_index.at(i);
            }
            */
        }
        else{
            //add to min heap
            //add_to_min_heap(min_heap,min_index, element,i, heap_index, heap_flag);
            min_index++;
            min_heap[min_index-1] = i;
            heap_flag.push_back(0);
            heap_index.push_back(min_index-1);
            /*
    cout << "\nmax  after upheap";
    cout << "\nmin heap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" <<min_heap[i];
    }
        cout << "\n min fix upheap_index";
        for(int i=0; i< heap_index.size(); i++){
            cout << "\t" << heap_index.at(i);
            }
            */
            min_fix_up(min_heap, min_index, vec, heap_index, element);
            /*
    cout << "\nmax  after upheap";
    cout << "\nmin after heap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" <<min_heap[i];
    }
        cout << "\n heap_index";
        for(int i=0; i< heap_index.size(); i++){
            cout << "\t" << heap_index.at(i);
            }
            */
        }
    calculate_median(max_index, min_index, final, vec,min_heap, max_heap, heap_flag, heap_index);
    }
    for(int i=window_size; i< vec.size(); i++){
          int element = vec.at(i);
          int prev_i = i-window_size;
          heap_flag.push_back(heap_flag.at(prev_i));
          heap_index.push_back(heap_index.at(prev_i));
        /* 
            cout << "\n\nmin heap+ element" << element;
        for(int j=0; j< mid_win_size; j++){
            cout << "\t" << vec.at(min_heap[j]);
            }
            cout << "\nmax heap";
        for(int j=0; j< mid_win_size; j++){
            cout << "\t" << vec.at(max_heap[j]);
            }
*/
          if(heap_flag[prev_i] == 0){
           // its a min heap 
           //if its a min heap, the new ele > its root
           if (element < vec.at(min_heap[0])){
                //place max heap root in its position and do a fix up
                min_heap[heap_index[i]] = max_heap[0];
                heap_index.at(min_heap[heap_index[i]]) = heap_index[i];
                heap_flag[max_heap[0]] = 0;
                //do a fix up
                int j = heap_index[i]+1;
                min_fix_up(min_heap, j, vec, heap_index, element);


                heap_index[i] = 0;
                heap_flag[i] = 1;
                max_heap[0] = i;
                //do a fix down
                max_fix_down(max_heap, heap_index[i], vec, heap_index, max_index);

           }
           else{
                //do a fix up or fix down accordingly
                min_heap[heap_index[i]] = i;
                if(element < vec.at(prev_i)){
                //do a fix up
                    int j = heap_index[i]+1;
                    min_fix_up(min_heap, j, vec, heap_index, element);
               }
               else{
               //do a fix down
                    min_fix_down(min_heap, heap_index[i], vec, heap_index, min_index);
               }
           }
          }
          else{
            if(element > vec.at(min_heap[0])){
                //place min heap root in its position and do a fix up
                max_heap[heap_index[i]] = min_heap[0];
                heap_index.at(max_heap[heap_index[i]]) = heap_index[i];
                heap_flag[min_heap[0]] = 1;
                //do a fix up
                int j = heap_index[i]+1;
                max_fix_up(max_heap, j, vec, heap_index, element);


                heap_index[i] = 0;
                heap_flag[i] = 0;
                min_heap[0] = i;
                //do a fix down
                min_fix_down(min_heap, heap_index[i], vec, heap_index, min_index);

            }
            else{
                max_heap[heap_index[i]] = i;
                if(element > vec.at(prev_i)){
                //do a fix up
                    int j = heap_index[i]+1;
                    max_fix_up(max_heap, j, vec, heap_index, element);
               }
               else{
               //do a fix down
                    max_fix_down(max_heap, heap_index[i], vec, heap_index, max_index);
               }
           }
          //its a max heap
          }
          /*
            cout << "\nBefore calc median min heap";
        for(int j=0; j< mid_win_size; j++){
            cout << "\t" << vec.at(min_heap[j]);
            }
            cout << "\nmax heap";
        for(int j=0; j< mid_win_size; j++){
            cout << "\t" << vec.at(max_heap[j]);
            }
            */
    //calculate_median(max_index, min_index, final, vec,min_heap, max_heap, heap_flag, heap_index);
    //cout<< "Median is:"<< ((vec.at(max_heap[0]) + vec.at(min_heap[0])) /2);
        final.push_back((vec.at(max_heap[0]) + vec.at(min_heap[0])) /2);
    }
    /*
    cout << "\nvector";
    for(int i=0; i< window_size; i++){
        cout << "\t" << vec.at(i);
    }
    cout << "\nmax heap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" << vec.at(max_heap[i]);
    }
    cout << "\nmin heap";
    for(int i=0; i< mid_win_size; i++){
        cout << "\t" << vec.at(min_heap[i]);
    }
    cout << "\n heap_index";
    for(int i=0; i< heap_index.size(); i++){
        cout << "\t" << heap_index.at(i);
    }
    cout << "\n heap_flag";
    for(int i=0; i< heap_flag.size(); i++){
        cout << "\t" << heap_flag.at(i);
    }

    cout<< "\n final";
    for(int i=0; i< final.size(); i++){
        cout << "\t"<< final.at(i);
    }
    */
    return final;
}
/*
void add_to_max_heap(int& max_heap[], int& max_index, int& element, int& i, int& heap_index[], int& heap_flag){
}
void add_to_min_heap(int& min_heap[], int& min_index, int& element, int& i, int& heap_index[], int& heap_flag){
}
*/
void RunningMedian::max_fix_down(int* max_heap, int index, std::vector<int>& vec, std::vector<int>& heap_index , int max_index){
    while( (2*index+1) <= (max_index-1)){
        int j = (2*index+1);
        if( (2*index+2) <= (max_index-1)){
           if (vec.at(max_heap[2*index+2]) > vec.at(max_heap[j])){
                 j = (2*index+2);
           }
        }
        if ( vec.at(max_heap[index]) < vec.at(max_heap[j])){
            //exchange index and j
            int temp = max_heap[index];
            int temp_hi = heap_index.at(max_heap[index]);
            heap_index[max_heap[index]] = heap_index[max_heap[j]];
            max_heap[index] = max_heap[j];
            heap_index[max_heap[j]] = temp_hi;
            max_heap[j] = temp;
        }
        else{
            break;
        }
        index = j;
    }
}

void RunningMedian::min_fix_down(int* min_heap, int index, std::vector<int>& vec, std::vector<int>& heap_index , int min_index){
    while( (2*index+1) <= (min_index-1)){
        int j = (2*index+1);
        if( (2*index+2) <= (min_index-1)){
           if (vec.at(min_heap[2*index+2]) < vec.at(min_heap[j])){
                j = (2*index+2);
           }
        }
        if ( vec.at(min_heap[index]) > vec.at(min_heap[j])){
            //exchange index and j
            int temp = min_heap[index];
            int temp_hi = heap_index.at(min_heap[index]);
            heap_index[min_heap[index]] = heap_index[min_heap[j]];
            min_heap[index] = min_heap[j];
            heap_index[min_heap[j]] = temp_hi;
            min_heap[j] = temp;
        }
        else{
            break;
        }
        index = j;
    }
}

void RunningMedian::max_fix_up(int* max_heap, int& max_index, std::vector<int>& vec, std::vector<int>& heap_index, int &element){
   int k = max_index-1;
   while(k>0 and vec.at(max_heap[((k+1)/2-1)]) < vec.at(max_heap[k])){
        //swap 
        int temp = max_heap[k];
        int temp_hi = heap_index.at(max_heap[k]);
        heap_index[max_heap[k]] = heap_index[max_heap[((k+1)/2-1)]];
        max_heap[k] = max_heap[((k+1)/2-1)];
        heap_index[max_heap[((k+1)/2-1)]] = temp_hi;
        max_heap[((k+1)/2-1)] = temp;
        k = ((k+1)/2-1);
   }
}

void RunningMedian::min_fix_up(int* min_heap, int& min_index, std::vector<int>& vec, std::vector<int>& heap_index, int &element){
   int k = min_index-1;
   while(k>0 and vec.at(min_heap[((k+1)/2-1)]) > vec.at(min_heap[k])){
        //swap 
        int temp = min_heap[k];
        int temp_hi = heap_index[min_heap[k]];
        heap_index[min_heap[k]] = heap_index[min_heap[((k+1)/2-1)]];
        min_heap[k] = min_heap[((k+1)/2-1)];
        heap_index[min_heap[((k+1)/2-1)]] = temp_hi;
        min_heap[((k+1)/2-1)] = temp;
        k = ((k+1)/2-1);
   }
}

void RunningMedian::calculate_median(int& max_index, int& min_index, std::vector<int>& final, std::vector<int>& vec,int *min_heap, int* max_heap, std::vector<int>& heap_flag, std::vector<int>& heap_index){

        int diff = max_index-min_index;
        int element;
        if(diff!=0 and diff!=1 and diff!=-1){
            if(diff >0){
                //remove from max_heap and put it in min_heap
                int temp = max_heap[0];
                int temp_hi = heap_index[max_heap[0]];
                heap_flag.at(temp) = 0;
                min_index++;
                min_heap[min_index-1] = temp;
                heap_index[max_heap[0]] = min_index-1;
                element= vec.at(temp);
                min_fix_up(min_heap, min_index, vec, heap_index, element);

                //fix_down max_heap
                max_heap[0] = max_heap[max_index-1];
                heap_index[max_heap[0]] = temp_hi;
                max_index--;
                max_fix_down(max_heap, 0, vec, heap_index, max_index);
            }
            else{
                //remove from min_heap and put it in max_heap
                int temp = min_heap[0];
                int temp_hi = heap_index[min_heap[0]];
                heap_flag.at(temp) = 1;
                max_index++;
                max_heap[max_index-1] = temp;
                heap_index[min_heap[0]] = max_index-1;
                element= vec.at(temp);
                max_fix_up(max_heap, max_index, vec, heap_index, element);

                //fix_down min_heap
                min_heap[0] = min_heap[min_index-1];
                heap_index[min_heap[0]] = temp_hi;
                min_index--;
                min_fix_down(min_heap, 0, vec, heap_index, min_index);
            }
        }
        if(max_index == min_index){
            final.push_back((vec.at(max_heap[0]) + vec.at(min_heap[0])) /2);
        }
        else if( max_index > min_index) {
            final.push_back(vec.at((max_heap[0])));
        }
        else{
            final.push_back(vec.at((min_heap[0])));
        }
}
