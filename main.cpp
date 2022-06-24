#include <iostream>
#include "BinaryTree.hpp"
int main() {
    auto* T = new BinaryTree<int>(5);
    for (int i = 0;i<5;i++){
        T->AddElement(i);
    }
    for (int i = 6;i<10;i++){
        T->AddElement(i);
    }
    auto* T2 = new BinaryTree<int>(1);
    T->CopyTree(T2->GetRoot(),T->GetRoot());
    std::cout<<T2->SearchElement(99)<<std::endl;


    return 0;
}
