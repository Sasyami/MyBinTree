//
// Created by User on 24.06.2022.
//

#ifndef BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#define BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#include <iostream>
#define WrongBypass 0
class TreeError: std::exception{
private:
    static const char* MatrixErrorMsg (int msg){

        if (msg == WrongBypass){

            auto string = "Bypass is wrong\n";
            return string;
        }

        auto string = "Something wrong, i can feel it(Maybe the error code?)\n";
        return string;

    }

public:

    explicit TreeError(int msg):exception(){
        std::cout<<TreeError::MatrixErrorMsg(msg)<<std::endl;
    }
};
#endif //BINARYREEPROJECT_TREEEXCEPTIONS_HPP
