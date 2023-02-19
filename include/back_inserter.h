#include <iostream>
#include <vector>
#include "export.h"


#define back_inserter_MSG "When copying a vector, the vector we are copying in needs to be the right size at risk of overwriting stuff, we can use a back inserter to automatically add the elements at the end of the vector instead of using error-prone C-style memory management.\nExample :\nstd::copy(v1.begin(), v1.end(), std::back_inserter(v2))"

extern "C"{
    void EXPORT back_inserter(std::vector<void*> args){
        std::cout << back_inserter_MSG << std::endl;
        std::vector<int> tI = {1, 2, 3, 4, 5, 6}, tI2, tI3;
        // back_inserter() version
        std::copy(tI.begin(), tI.end(), std::back_inserter(tI2));

        // push_back() version
        for(auto it = tI.begin(); it != tI.end(); it++){
            tI3.push_back(*it);
        }

    }
}