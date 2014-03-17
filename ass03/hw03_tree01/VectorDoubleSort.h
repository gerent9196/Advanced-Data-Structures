#pragma once

#include "Interfaces03.h"

class VectorDoubleSort : public IVectorDoubleSort{
    public:
    VectorDoubleSort() { }
    ~VectorDoubleSort() {}
    void sort(std::vector<double>& vec);
};

