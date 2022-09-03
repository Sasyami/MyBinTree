//
// Created by User on 23.08.2022.
//

#ifndef BINARYREEPROJECT_FLOATTREEINTERFACE_HPP
#define BINARYREEPROJECT_FLOATTREEINTERFACE_HPP
#include "TreeInterface.hpp"
#include "BinaryTree.hpp"
#include "MenuError.hpp"

float float_global_element = 0;

bool LessThan(float  element){
    if (element<float_global_element){
        return true;
    }
    return false;
}
bool MoreThan(float  element){
    if (element>float_global_element){
        return true;
    }
    return false;
}
float  Multiply(float  element){
    return element*float_global_element;
}
float  Add(float  element){
    return element+float_global_element;
}
float  Substract(float  element){
    return element-float_global_element;
}

class FloatTreeInterface:public TreeInterface{
private:
    BinaryTree<float>* tree;

public:

public:
    FloatTreeInterface(){
        std::string element_str;
        std::cout<<"Insert how many elements \n"<<std::endl;
        size_t count;
        float element;
        getline(std::cin, element_str);
        count = stoi(element_str);
        if (count<1){
            throw MenuError(WrongMenuInput);
        }
        std::cout<<"Insert root"<<std::endl;
        getline(std::cin, element_str);
        element = stof(element_str);
        tree = new BinaryTree<float>(element);
        for (int i = 1;i<count;i++){
            std::cout<<"Insert number"<<std::endl;
            getline(std::cin, element_str);
            element = stof(element_str);
            tree->AddElement(element);
        }

    }
    explicit FloatTreeInterface(size_t count){
        tree = new BinaryTree<float>((float)(rand()%100)/(float)100);
        for (int i = 0;i<count-1;i++){
            tree->AddElement(rand()%100);
        }
    }
    explicit FloatTreeInterface(float element){
        tree = new BinaryTree<float>(element);
    }
    ~FloatTreeInterface(){
        delete tree;
    }
    void AddElement() override{
        std::string element_str;
        std::cout<<"Insert number"<<std::endl;


        float element;
        getline(std::cin, element_str);
        element = stof(element_str);
        tree->AddElement(element);
    }
    void EraseElement() override{
        std::string element_str;
        std::cout<<"Insert number"<<std::endl;


        float element;
        getline(std::cin, element_str);
        element = stof(element_str);
        tree->erase(element);
    }
    void ToTreeWithCondition() override{
        std::string element_str;
        std::cout<<"1. Less than \n2.More than \n"<<std::endl;
        size_t func;
        getline(std::cin, element_str);
        func = stoi(element_str);

        std::cout<<"Insert element\n"<<std::endl;
        getline(std::cin, element_str);
        float_global_element = stof(element_str);
        switch(func){
            case 1:

                tree->operator=(*(tree->TreeWithCondition(LessThan)));
                break;
            case 2:
                tree->operator=(*(tree->TreeWithCondition(MoreThan)));
                break;
            default:
                throw MenuError(WrongMenuInput);

        }


    }
    void Print() override{
        tree->PrintTree();
    }
    void ModifyTree() override{
        std::string element_str;
        std::cout<<"1. Multiply by \n2.Add \n3.Substract\n"<<std::endl;
        size_t func;
        getline(std::cin, element_str);
        func = stoi(element_str);

        std::cout<<"Insert element\n"<<std::endl;
        getline(std::cin, element_str);
        float_global_element = stof(element_str);
        switch(func){
            case 1:

                tree->operator=(*(tree->map(Multiply)));
                break;
            case 2:

                tree->operator=(*(tree->map(Add)));
                break;
            case 4:

                tree->operator=(*(tree->map(Substract)));
                break;
            default:
                throw MenuError(WrongMenuInput);

        }


    }
    size_t SizeOfTree() override{
        return tree->SizeOfBinaryTree();
    }
    bool IfElementHere() override{
        std::string element_str;
        std::cout<<"Insert number"<<std::endl;


        float element;
        getline(std::cin, element_str);
        element = stof(element_str);
        if(tree->SearchElement(element) !=nullptr){
            return true;
        }
        return false;
    }
    void ToString() override{
        std::string element_str;
        std::cout<<"1. LeftRightRoot \n2.RightLeftRoot \n3.RootLeftRight\n4.RootRightLeft\n5.LeftRootRight\n6.RightRootLeft\n"<<std::endl;
        size_t func;
        getline(std::cin, element_str);
        func = stoi(element_str);

        switch(func){
            case 1:

                std::cout<<tree->ConvertTreeToString(LeftRightRoot)<<std::endl;
                break;
            case 2:

                std::cout<<tree->ConvertTreeToString(RightLeftRoot)<<std::endl;
                break;
            case 3:

                std::cout<<tree->ConvertTreeToString(RootLeftRight)<<std::endl;
                break;
            case 4:

                std::cout<<tree->ConvertTreeToString(RootRightLeft)<<std::endl;
                break;
            case 5:

                std::cout<<tree->ConvertTreeToString(LeftRootRight)<<std::endl;
                break;
            case 6:

                std::cout<<tree->ConvertTreeToString(RightRootLeft)<<std::endl;
                break;
            default:
                throw MenuError(WrongMenuInput);

        }

    }
    void TreeToSubTree() override{
        std::string element_str;
        std::cout<<"Insert number"<<std::endl;


        float element;
        getline(std::cin, element_str);
        element = stof(element_str);
        tree->operator=(*(tree->SubTree(element)));
    }
};
#endif //BINARYREEPROJECT_FLOATTREEINTERFACE_HPP
