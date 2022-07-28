//
// Created by User on 22.06.2022.
//

#ifndef LAB2PRJ_POLYNOMIAL_HPP
#define LAB2PRJ_POLYNOMIAL_HPP
#include <iostream>
#include "Sequence.hpp"
#include "PolyError.hpp"
#include "ArraySequence.hpp"
#include <cmath>
size_t minimum(size_t a,size_t b){
    if (a>b){
        return b;
    }else{
        return a;
    }
}
template <typename T>
class Polynomial{
private:
    Sequence<T>* coefficients;
    size_t size;
public:
    Polynomial(){
        coefficients = new ArraySequence<T>();
        size = 0;
    }
    explicit Polynomial(Sequence<T>* seq){
        if (seq->GetLength()<seq->GetLength()){
            throw PolyError(WrongPoly);
        }
        size = seq->GetLength();
        coefficients = new ArraySequence<T>(*seq);
    }
    Polynomial(const Polynomial& poly){
        coefficients = new ArraySequence<T>(*(poly.coefficients));
        size = poly.size;

    }
public:
    Polynomial<T> operator+ (const Polynomial<T>& poly){
        if (poly.size>size) {
            Polynomial<T> new_pol(poly);
            for (int i =0;i<minimum(size, poly.size); i++){
                new_pol.coefficients->Set(poly.coefficients->Get(i)+coefficients->Get(i),i);
            }
            return new_pol;
        }else{
            Polynomial<T> new_pol(*this);
            for (int i =0;i<minimum(size, poly.size); i++){
                new_pol.coefficients->Set(poly.coefficients->Get(i)+coefficients->Get(i),i);
            }
            return new_pol;
        }

    }
    Polynomial<T> operator- (const Polynomial<T>& poly){
        if (poly.size>size) {
            Polynomial<T> new_pol(poly);
            for (int i =0;i<minimum(size, poly.size); i++){
                new_pol.coefficients->Set(coefficients->Get(i)-poly.coefficients->Get(i),i);
            }
            return new_pol;
        }else{
            Polynomial<T> new_pol(*this);
            for (int i =0;i<minimum(size, poly.size); i++){
                new_pol.coefficients->Set(coefficients->Get(i)-poly.coefficients->Get(i),i);
            }
            return new_pol;
        }

    }
    Polynomial<T>& operator= (const Polynomial<T>& poly){

        for (int i =0;i<minimum(size, poly.size); i++){
            coefficients->Set(poly.coefficients->Get(i),i);
        }
        for (int j = minimum(size, poly.size); j < poly.size; j++){
            coefficients->Append(poly.coefficients->Get(j));
        }
        size = poly.size;
        return *this;
    }
    Polynomial<T> operator* (const Polynomial<T>& poly){
        Polynomial<T> new_pol;
        for (int i =0 ;i<size;i++){
            for (int j = 0;j<poly.size;j++){

                if (i+j>=new_pol.size){
                    new_pol.coefficients->Append(coefficients->Get(i)*poly.coefficients->Get(j));
                    new_pol.size = new_pol.size+1;
                }else{
                    new_pol.coefficients->Set(new_pol.coefficients->Get(i+j)+coefficients->Get(i)*poly.coefficients->Get(j),i+j);
                }
            }
        }

        return new_pol;

    }
    /*
    Polynomial<T> operator* (int value){
        Polynomial<T> new_pol (*this);
        for (int i = 0;i<size;i++){
            new_pol.coefficients->Set(coefficients->Get(i)*value,i);
        }
        return new_pol;
    }
    Polynomial<T> operator* (float number){
        Polynomial<T> new_pol (*this);
        for (int i = 0;i<size;i++){
            new_pol.coefficients->Set(coefficients->Get(i)*number,i);
        }
        return new_pol;
    }
    Polynomial<T> operator* (ComplexNumber<T> number){
        Polynomial<T> new_pol (*this);
        for (int i = 0;i<size;i++){
            new_pol.coefficients->Set(coefficients->Get(i)*number,i);
        }
        return new_pol;
    }
    Polynomial<T> operator* (QuadMatrix<T> number){
        Polynomial<T> new_pol (*this);
        for (int i = 0;i<size;i++){
            new_pol.coefficients->Set(coefficients->Get(i)*number,i);
        }
        return new_pol;
    }*/
    Polynomial<T> operator* (T number){
        Polynomial<T> new_pol (*this);
        for (int i = 0;i<size;i++){
            new_pol.coefficients->Set(coefficients->Get(i)*number,i);
        }
        return new_pol;
    }
    T operator()(T value){
        if (size<1){
            throw PolyError(WrongSize);
        }
        T current_value = value;
        T sum = coefficients->Get(0);
        for (int i = 1;i<size;i++){
            sum = sum+coefficients->Get(i)*current_value;
            current_value = current_value*value;
        }
        return sum;
    }
    Polynomial<T> operator()(Polynomial<T>& poly){
        if ((size<2)||(poly.size<2)){
            throw PolyError(WrongSize);
        }
        Polynomial<T> current_poly = poly;
        Polynomial<T> sum = current_poly*(this->Get(1));
        sum.coefficients->Set(this->Get(0)+this->Get(1)*poly.Get(0),0);
        for (int i = 2;i<this->GetSize();i++){
            current_poly = current_poly*poly;
            sum = sum+current_poly*(this->Get(i));
        }
        return sum;
    }

public:
    size_t GetSize() const{
        return size;
    }
    T Get(size_t index){
        if (index>= this->GetSize()){
            throw PolyError(WrongIndexPol);
        }
        return coefficients->Get(index);
    }

};


#endif //LAB2PRJ_POLYNOMIAL_HPP
