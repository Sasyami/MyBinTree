//
// Created by User on 24.06.2022.
//

#ifndef BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#define BINARYREEPROJECT_TREEEXCEPTIONS_HPP
#include <iostream>
#define WrongBypass 0
#define NoSuchElement 1
#define WrongInput 2
#define DeleteRoot 3
#define NoRotate 4
#define NoRoot 5
class TreeError: std::exception{
private:
    static const char* MatrixErrorMsg (int msg){

        if (msg == WrongBypass){

            auto string = "Bypass is wrong";
            return string;
        }if (msg == NoSuchElement){

            auto string = "No Such Element";
            return string;
        }
        if (msg == WrongInput){

            auto string = "Wrong Input";
            return string;
        }
        if (msg == DeleteRoot){

            auto string = "Tried to delete root";
            return string;
        }
        if (msg == NoRotate){

            auto string = "Cant rotate some root";
            return string;
        }
        if (msg == NoRoot){

            auto string = "No root in tree";
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

