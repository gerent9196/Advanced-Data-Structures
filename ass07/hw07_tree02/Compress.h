#pragma once
#include "Interfaces07.h"

class Compress: public ICompress{
    public:
        
        Compress() { }
        ~Compress() { }
        std::string compress(std::string input);
        std::string decompress(std::string compressed);
};
