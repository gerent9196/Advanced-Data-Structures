#pragma once
#include "Interfaces03.h"

class RunningMedian : public IRunningMedian
{
    public:
        RunningMedian() { }
        ~RunningMedian() { }
        std::vector<int> compute(std::vector<int> vec, int window_size);
        void max_fix_up(int* max_heap, int& max_index, std::vector<int>& vec, std::vector<int>& heap_index, int &element);
        void min_fix_up(int* min_heap, int& min_index, std::vector<int>& vec, std::vector<int>& heap_index, int &element);
        void max_fix_down(int* max_heap, int index, std::vector<int>& vec, std::vector<int>& heap_index , int max_index);
        void min_fix_down(int* min_heap, int index, std::vector<int>& vec, std::vector<int>& heap_index , int min_index);
        void calculate_median(int& max_index, int& min_index, std::vector<int>& final, std::vector<int>& vec,int *min_heap, int* max_heap, std::vector<int>& heap_flag, std::vector<int>& heap_index);

};
