//
// Created by User on 14.05.2022.
//

#ifndef LAB2PRJ_ARRAYSEQUENCE_HPP
#define LAB2PRJ_ARRAYSEQUENCE_HPP
#include "DynamicArray.hpp"
#include "Sequence.hpp"
#include "IndexOutOfRange.hpp"
#include <iostream>
template < class T> class ArraySequence : public Sequence<T>{
private:
    DynamicArray<T>* array;
    size_t capacity;
    size_t size;
public:
    ArraySequence (T* items, size_t count){
        array = new DynamicArray<T>(items,count);
        capacity = count;
        size = count;

    }
    ArraySequence (){
        array = new DynamicArray<T>(1);
        capacity = 1;
        size = 0;

    }
    explicit ArraySequence (const DynamicArray<T>& dynamicArray){
        array = new DynamicArray<T>(dynamicArray);
        capacity = dynamicArray.GetSize();
        size = dynamicArray.GetSize();

    }
    explicit ArraySequence(Sequence<T>& Seq){
        array = new DynamicArray<T>(Seq.GetLength());
        for (int i = 0;i<Seq.GetLength();i++){
            array->Set(i,Seq.Get(i));
        }
        capacity = Seq.GetLength();
        size = Seq.GetLength();

    }
public:
    ArraySequence<T>& operator =(Sequence<T>& Seq){
        if (this!=nullptr && this->array!=nullptr){
            delete this->array;
        }

        array = new DynamicArray<T>(Seq.GetLength());
        for (int i = 0;i<Seq.GetLength();i++){
            array->Set(i,Seq.Get(i));
        }
        capacity = Seq.GetLength();
        size = Seq.GetLength();
        return *this;

    }
public:
    ~ArraySequence(){
        delete array;
    };
public:
    T GetFirst() const override{
        if ((this->array == nullptr) || (size == 0)){
            throw IndexOutOfRange(EmptyList);
        }
        return this->array->Get(0);
    }
public:
    T GetLast() const override{
        if ((this->array == nullptr) || (size == 0)){
            throw IndexOutOfRange(EmptyList);
        }
        return this->array->Get(this->array->GetSize()-1);
    }
public:
    T Get(size_t index) const override{
        if ((this->array == nullptr) || (size == 0)){
            throw IndexOutOfRange(EmptyList);
        }

        T value = array->Get(index);




        return value;
    }
public:
    Sequence<T>* GetSubsequence(size_t startIndex, size_t endIndex) override{
        if ((this->array == nullptr) || (size == 0)){
            throw IndexOutOfRange(EmptyList);
        }
        if (endIndex>=size){
            throw IndexOutOfRange(WrongIndex);

        }

        auto* new_array = new ArraySequence<T>;
        new_array->array = new DynamicArray<T>(endIndex-startIndex+1);

        new_array->size = endIndex-startIndex+1;
        new_array->capacity = endIndex-startIndex+1;
        for (size_t i = startIndex;i <= endIndex;i++){

            new_array->array->Set(i,this->array->Get(i-startIndex));
        }

        return new_array;

    }
public:
    size_t GetLength() override{
        if (this->array == nullptr){
            throw IndexOutOfRange(EmptyList);
        }

        return size;
    }
public://check
    void Append(T item) override{
        if (this->array == nullptr){
            throw IndexOutOfRange(EmptyList);
        }

        if (capacity>size){

            this->array->Set(size,item);
            size=size+1;

        }else{
            this->array->Resize(2*size);
            capacity = 2*size;
            this->array->Set(size,item);
            size=size+1;
        }

    }
public://check
    void Prepend(T item) override{
        if (this->array == nullptr){
            throw IndexOutOfRange(EmptyList);
        }
        if ((size == 0)&&(capacity>size)){
            this->array->Set(0,item);
        }else if(capacity == 0){
            throw IndexOutOfRange(EmptyList);
        }else{
            T current;
            T prev= array->Get(0);
            if (size>=capacity){
                array->Resize(2*size);
                capacity = 2*size;
            }
            size = size+1;
            for (int i=1;i<size;i++) {
                current = array->Get(i);
                array->Set(i, prev);
                prev = current;
            }
            this->array->Set(0,item);
        }


    }
public://check
    void InsertAt(T item, size_t index) override{
        if (this->array == nullptr){
            throw IndexOutOfRange(EmptyList);
        }
        if (index>=this->GetLength()){
            throw IndexOutOfRange(WrongIndex);
        }
        T current;
        T prev= array->Get(index);
        if (size>=capacity){
            array->Resize(2*size);
            capacity = 2*size;
        }
        size = size+1;
        for (int i=index+1;i<size;i++){
            current = array->Get(i);
            array->Set(i,prev);
            prev = current;
        }

        this->array->Set(0,item);
        this->array->Set(index,item);
    }

public:
    Sequence <T>* Concat(Sequence <T> *list) override{
        if (list==nullptr){
            throw IndexOutOfRange(WrongInput);
        }
        if (this->array == nullptr){
            throw IndexOutOfRange(EmptyList);
        }
        for (int i =0;i< list->GetLength();i++){
            this->Append(list->Get(i));
        }
        return this;
    }
public:
    void Set(T item,size_t index) override{
        if (index>size){
            throw IndexOutOfRange(WrongIndex);
        }

        array->Set(index,item);
    }
    template <class U>
    friend std::ostream& operator<<(std::ostream &out ,const ArraySequence<U> &a);
};

template <class U>
std::ostream& operator<<(std::ostream &out ,const ArraySequence<U> &a){
    for (size_t i = 0; i<a.size;i++){
        out<<a.Get(i)<<" ";
    }
    return out;
}
#endif //LAB2PRJ_ARRAYSEQUENCE_HPP
