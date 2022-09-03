//
// Created by User on 13.05.2022.
//

#ifndef LAB2PRJ_INDEXOUTOFRANGE_HPP
#define LAB2PRJ_INDEXOUTOFRANGE_HPP
#include <iostream>
#define EmptyList 0
#define WrongIndex 1
#define WrongInput 2
class IndexOutOfRange: std::exception{
private:
    static const char* IndexErrorList (int msg){

        if (msg == EmptyList) {

            auto string = "This List is empty\n";
            return string;
        }
        if (msg == WrongIndex){

            auto string = "Incorrect index\n";
            return string;
        }
        if (msg == WrongInput){

            auto string = "Incorrect input\n";
            return string;
        }
        auto string = "Something wrong, i can feel it(Maybe the error code?)\n";
        return string;

    }

public:

    explicit IndexOutOfRange(int msg):exception(){
        std::cout<<IndexOutOfRange::IndexErrorList(msg)<<std::endl;
    }
};
#endif //LAB2PRJ_INDEXOUTOFRANGE_HPP

