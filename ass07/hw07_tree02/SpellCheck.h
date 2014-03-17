#pragma once
#include "Interfaces07.h"

class SpellCheck: public ISpellCheck{
    public:
        std::vector<std::string> words;
        SpellCheck(){
        }
        ~SpellCheck(){
        }
        void loadDictionary(std::vector<std::string>& words);
        std::vector<std::string> suggestCorrections(std::string word);
    
};
