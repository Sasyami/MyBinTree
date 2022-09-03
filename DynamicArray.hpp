//
// Created by User on 13.05.2022.
//

#ifndef LAB2PRJ_DYNAMICARRAY_HPP
#define LAB2PRJ_DYNAMICARRAY_HPP
#include "IndexOutOfRange.hpp"
#include <iostream>
template <class T> class DynamicArray{
private:
    T* array;
    size_t length;

public:
    DynamicArray(T* items,size_t count){
        int i;

        length = count;




        this->array = new T[this->length];
        for (i = 0;i<count;i++){


            this->array[i] = items[i];

        }

    }
public:
    explicit DynamicArray(size_t size){
        this->array = new T[size];
        length = size;


    }
public:
    //Перегрузка оператора =
    DynamicArray<T>& operator=(const DynamicArray<T>& dynamicArray){
        if (this!=nullptr && this->array!=nullptr){
            delete[] this->array;
        }
        this->array = new T[dynamicArray.GetSize()];
        length = dynamicArray.GetSize();

        for (int i = 0;i<length;i++){
            this->Set(i,dynamicArray.Get(i)) ;
        }
        return *this;
    }
public:
    ~DynamicArray(){
        delete[] array;

        array = NULL;
    }
public:
    DynamicArray(const DynamicArray<T>& dynamicArray){
        this->array = new T[dynamicArray.GetSize()];
        length = dynamicArray.GetSize();

        for (int i = 0;i<length;i++){
            this->Set(i,dynamicArray.Get(i)) ;
        }
    }
public:
    T Get(size_t index) const{


        if ((index<0)||(index+1>length)){
            throw IndexOutOfRange(WrongIndex);
        }

        T value = array[index];

        return value;
    }
public:
    size_t GetSize() const{
        //std::cout << "Im get size da "<<this->current_elements << std::endl;
        return this->length;
    }
public:
    void Set(size_t index,T value){
        if ((index>length)||(index<0)){
            throw IndexOutOfRange(WrongIndex);
        }
        array[index] = value;
    }
public:
    void Resize(size_t newSize){
        int i;
        T* new_array = new T[newSize];
        for (i = 0;i<length;i++){
            new_array[i] = this->array[i];

        }
        this->array = new_array;
        this->length = newSize;

    }



};

#endif //LAB2PRJ_DYNAMICARRAY_HPP

