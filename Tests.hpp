//
// Created by User on 23.08.2022.
//

#ifndef BINARYREEPROJECT_TESTS_HPP
#define BINARYREEPROJECT_TESTS_HPP

#include <variant>

#include "BinaryTree.hpp"
#include <iostream>
#include <vector>





template <class T>
class tests{
private:

    BinaryTree<T>* tree;
public:
    tests() = delete;
    explicit tests(T element){
        tree = new BinaryTree<T> (element);
    }
    void AddElementButSilent(T element_to_add){
        tree->AddElement(element_to_add);
    }
    void AddElement(T element_to_add){
        std::cout<<"Adding to tree "<<element_to_add;
        std::cout<<"\n";
        tree->AddElement(element_to_add);
    }
    void EraseElement(T element_to_erase){
        std::cout<<"Erase from tree "<<element_to_erase;
        std::cout<<"\n";
        tree->erase(element_to_erase);
    }

    void SubTree(T element_to_subtree){
        std::cout<<"Sub tree of tree from element "<<element_to_subtree;
        std::cout<<"\n";
        auto* new_tree = tree->SubTree(element_to_subtree);
        new_tree->PrintTree();
    }
    void MultiplyTree(T func(T)){

        auto* new_tree = tree->map(func);
        new_tree->PrintTree();
    }
    void size_of_tree(){
        std::cout<<"Size of tree "<<std::endl;
        std::cout<<tree->SizeOfBinaryTree()<<std::endl;
    }
    void wrong_erasing(T element_not_in_tree){
        try{
            tree->erase(element_not_in_tree);
        }catch(TreeError& e){
            std::cout<<"tried to erase element not in tree \n";
        }
    }
    void wrong_subtree(T element_not_in_tree){
        try{
            tree->SubTree(element_not_in_tree);
        }catch(TreeError& e){
            std::cout<<"tried to subtree from element not in tree \n";
        }
    }
    void print_tree(){
        tree->PrintTree();
    }
    void to_tree_where(bool func(T)){
        auto* new_tree = tree->TreeWithCondition(func);
        new_tree->PrintTree();
    }
    void map(T func(T)){
        auto* new_tree = tree->map(func);
        new_tree->PrintTree();
    }


};
int MultiplyBy2(int element){
    return 2*element;
}
bool LessThan5(int element){
    if (element<5){
        return true;
    }else{
        return false;
    }
}
bool LessThan5WithAHalf(float element){
    if (element<5.5){
        return true;
    }else{
        return false;
    }
}
float MultiplyBy0Point5(float element){
    return (float)0.5*element;
}
void FloatTestRun(){
    float root_value = 5.5;
    tests<float> FloatTest(root_value);
    FloatTest.AddElementButSilent(3.5);
    FloatTest.AddElementButSilent(2.25);
    FloatTest.AddElementButSilent(1.125);
    FloatTest.AddElementButSilent(4.5);
    FloatTest.AddElementButSilent(8.5);
    FloatTest.AddElementButSilent(6.75);
    FloatTest.AddElementButSilent(7.25);
    FloatTest.AddElementButSilent(9.5);

    FloatTest.print_tree();
    FloatTest.AddElement(10.33);
    FloatTest.print_tree();
    FloatTest.EraseElement(10.33);
    FloatTest.print_tree();
    FloatTest.SubTree(8.5);
    FloatTest.size_of_tree();
    FloatTest.wrong_erasing(11);
    FloatTest.wrong_subtree(11);
    std::cout<<"To tree less than 5.5"<<std::endl;
    FloatTest.to_tree_where(LessThan5WithAHalf);
    std::cout<<"To tree multiplyed by 0.5"<<std::endl;
    FloatTest.map(MultiplyBy0Point5);
}
void IntTestRun(){
    int root_value = 5;
    tests<int> IntTest(root_value);
    IntTest.AddElementButSilent(3);
    IntTest.AddElementButSilent(2);
    IntTest.AddElementButSilent(1);
    IntTest.AddElementButSilent(4);
    IntTest.AddElementButSilent(8);
    IntTest.AddElementButSilent(6);
    IntTest.AddElementButSilent(7);
    IntTest.AddElementButSilent(9);

    IntTest.print_tree();
    IntTest.AddElement(10);
    IntTest.print_tree();
    IntTest.EraseElement(10);
    IntTest.print_tree();
    IntTest.SubTree(8);
    IntTest.size_of_tree();
    IntTest.wrong_erasing(11);
    IntTest.wrong_subtree(11);
    std::cout<<"To tree less than 5"<<std::endl;
    IntTest.to_tree_where(LessThan5);
    std::cout<<"To tree multiplyed by 2"<<std::endl;
    IntTest.map(MultiplyBy2);

}
#endif //BINARYREEPROJECT_TESTS_HPP
