//
// Created by User on 24.06.2022.
//

#ifndef BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#define BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#include <iostream>
#define WrongBypass 0
#define NoSuchElement 1
#define WrongInput 2

class TreeError: std::exception{
private:
    static const char* MatrixErrorMsg (int msg){

        if (msg == WrongBypass){

            auto string = "Bypass is wrong\n";
            return string;
        }if (msg == NoSuchElement){

            auto string = "No Such Element\n";
            return string;
        }
        if (msg == WrongInput){

            auto string = "Wrong Input\n";
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
