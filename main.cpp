#include <iostream>
#include "BinaryTree.hpp"
template <typename T>
bool iseven(T element){
    if (element%2 == 0){
        return true;
    }
    return false;
}
template <typename T>
bool isodd(T element){
    if (element%2 == 0){
        return true;
    }
    return false;
}
int main() {

    auto* T = new BinaryTree<int>(5);
    for (int i = 0;i<5;i++){
        T->AddElement(i);
    }
    for (int i = 6;i<10;i++){
        T->AddElement(i);
    }
    auto* T2 = new BinaryTree<int>(1);
    T2 = T->ToBalancedTree();
    std::string new_str = T2->ConvertTreeToString(RootRightLeft);
    std::cout << new_str<<std::endl;
    std::cout<<T->SizeOfBinaryTree()<<std::endl;
    bool programm = true;
    bool programm2 = true;
    while(programm){

        std::cout<<"1. Int tree \n2.Float Tree \n3.Exit\n"<<std::endl;
        std::string type;
        std::string type2;
        std::string type3;
        std::string type4;
        std::string quantity;
        std::string element_str;
        BinaryTree<int>*Tree;
        BinaryTree<float>*TreeF;
        int element,size;
        float elementf;
        getline(std::cin, type);
        if (type.length()!=1){
            programm = false;
            throw TreeError(WrongInput);
        }
        switch((int)type[0]){
            case 49:
                std::cout<<"1.Insert with hands\n 2.Big data(3000)\n 3.Exit\n"<<std::endl;
                getline(std::cin, type2);
                if (type2.length()!=1){
                    programm = false;
                    throw TreeError(WrongInput);
                }switch((int)type2[0]){
                    case 49:
                        std::cout<<"Insert how many elements"<<std::endl;
                        getline(std::cin, quantity);
                        size = stoi(quantity);
                        if (size<1){
                            throw TreeError(WrongInput);
                        }
                        std::cout<<"Insert elements one by one"<<std::endl;
                        getline(std::cin, element_str);
                        element = stoi(element_str);
                        Tree = new BinaryTree<int>(element);
                        for (int i = 1;i<size;i++){
                            getline(std::cin, element_str);
                            element = stoi(element_str);
                            Tree->AddElement(element);
                        }
                        Tree = Tree->ToBalancedTree();

                        break;
                    case 50:

                        Tree = new BinaryTree<int>(500);

                        for (int i = 0;i<3000;i++){

                            Tree->AddElement(rand()%1000);
                            //std::cout<<Tree->SizeOfBinaryTree()<<" "<<Tree->ConvertTreeToString(RightRootLeft)<<std::endl;

                        }
                        //std::cout<<Tree->SizeOfBinaryTree()<<std::endl;
                        Tree = Tree->ToBalancedTree();
                        break;

                    case 51:
                        programm2 = false;
                        programm = false;
                        break;
                    default:
                        throw TreeError(WrongInput);
                        break;
                }
                while (programm2){
                    std::cout<<"0.Where(condition) \n1.Is element here?\n 2.Transfer to subtree by element\n 3.LeftRightRoot\n 4.RightLeftRoot\n 5.RootLeftRight\n 6.RootRightLeft\n 7.LeftRootRight\n 8.RightRootLeft\n 9.Exit\n"<<std::endl;
                    getline(std::cin, type3);
                    if (type3.length()!=1) {
                        programm = false;
                        throw TreeError(WrongInput);
                    }switch(type3[0]){
                        case 48:
                            std::cout<<"1.Is odd\n 2.Is even\n"<<std::endl;
                            getline(std::cin, type4);
                            if (type4.length()!=1) {
                                programm = false;
                                throw TreeError(WrongInput);
                            }
                            switch(type4[0]){
                                case 50:
                                    Tree = Tree->TreeWithCondition(iseven);
                                    Tree = Tree->ToBalancedTree();
                                    break;
                                case 49:
                                    Tree = Tree->TreeWithCondition(isodd);
                                    Tree = Tree->ToBalancedTree();
                                    break;
                                default:
                                    throw TreeError(WrongInput);
                                    break;

                            }
                            break;
                        case 49:
                            getline(std::cin, element_str);
                            element = stoi(element_str);
                            if (Tree->SearchElement(element)!=nullptr){
                                std::cout<<"YEs"<<std::endl;

                            }
                            else{
                                std::cout<<"No"<<std::endl;
                            }
                            break;
                        case 50:
                            getline(std::cin, element_str);
                            element = stoi(element_str);
                            Tree= Tree->SubTree(element);
                            break;
                        case 51:

                            std::cout<<Tree->ConvertTreeToString(LeftRightRoot)<<std::endl;
                            break;
                        case 52:
                            std::cout<<Tree->ConvertTreeToString(RightLeftRoot)<<std::endl;
                            break;
                        case 53:
                            std::cout<<Tree->ConvertTreeToString(RootLeftRight)<<std::endl;
                            break;
                        case 54:
                            std::cout<<Tree->ConvertTreeToString(RootRightLeft)<<std::endl;
                            break;
                        case 55:
                            std::cout<<Tree->ConvertTreeToString(LeftRootRight)<<std::endl;
                            break;
                        case 56:
                            std::cout<<Tree->ConvertTreeToString(RightRootLeft)<<std::endl;
                            break;
                        case 57:
                            programm = false;
                            programm2 = false;
                            break;
                        default:
                            throw TreeError(WrongInput);
                            break;


                    }

                }

                break;
            case 50:
                std::cout<<"1.Insert with hands\n 2.Big data(3000)\n  3.Exit\n"<<std::endl;
                getline(std::cin, type2);
                if (type2.length()!=1){
                    programm = false;
                    throw TreeError(WrongInput);
                }switch((int)type2[0]) {
                    case 49:
                        std::cout << "Insert how many elements" << std::endl;
                        getline(std::cin, quantity);
                        size = stoi(quantity);
                        if (size < 1) {
                            throw TreeError(WrongInput);
                        }
                        std::cout << "Insert elements one by one" << std::endl;
                        getline(std::cin, element_str);
                        elementf = stof(element_str);
                        TreeF = new BinaryTree<float>(elementf);
                        for (int i = 1; i < size; i++) {
                            getline(std::cin, element_str);
                           elementf = stof(element_str);
                           TreeF->AddElement(elementf);
                        }
                        TreeF = TreeF->ToBalancedTree();

                        break;
                    case 50:

                        TreeF = new BinaryTree<float>(500);

                        for (int i = 0; i < 3000; i++) {

                            TreeF->AddElement(rand() % 1000/10);
                    //std::cout<<Tree->SizeOfBinaryTree()<<" "<<Tree->ConvertTreeToString(RightRootLeft)<<std::endl;

                        }

                        TreeF = TreeF->ToBalancedTree();
                        break;

                    case 51:
                        programm2 = false;
                        programm = false;
                        break;
                    default:
                        throw TreeError(WrongInput);
                        break;
                }
                while (programm2){
                    std::cout<<"1.Is element here?\n 2.Transfer to subtree by element\n 3.LeftRightRoot\n 4.RightLeftRoot\n 5.RootLeftRight\n 6.RootRightLeft\n 7.LeftRootRight\n 8.RightRootLeft\n 9.Exit\n"<<std::endl;
                    getline(std::cin, type3);
                    if (type3.length()!=1) {
                        programm = false;
                        throw TreeError(WrongInput);
                    }switch(type3[0]){

                        case 49:
                            getline(std::cin, element_str);
                            elementf = stof(element_str);
                            if (TreeF->SearchElement(elementf)!=nullptr){
                                std::cout<<"YEs"<<std::endl;

                            }
                            else{
                                std::cout<<"No"<<std::endl;
                            }
                            break;
                        case 50:
                            getline(std::cin, element_str);
                            elementf = stof(element_str);
                            TreeF= TreeF->SubTree(elementf);
                            break;
                        case 51:

                            std::cout<<TreeF->ConvertTreeToString(LeftRightRoot)<<std::endl;
                            break;
                        case 52:
                            std::cout<<TreeF->ConvertTreeToString(RightLeftRoot)<<std::endl;
                            break;
                        case 53:
                            std::cout<<TreeF->ConvertTreeToString(RootLeftRight)<<std::endl;
                            break;
                        case 54:
                            std::cout<<TreeF->ConvertTreeToString(RootRightLeft)<<std::endl;
                            break;
                        case 55:
                            std::cout<<TreeF->ConvertTreeToString(LeftRootRight)<<std::endl;
                            break;
                        case 56:
                            std::cout<<TreeF->ConvertTreeToString(RightRootLeft)<<std::endl;
                            break;
                        case 57:
                            programm = false;
                            programm2 = false;
                            break;
                        default:
                            throw TreeError(WrongInput);
                            break;


                    }

                }

                break;

                break;
            case 51:
                programm = false;
                break;
            default:
                throw TreeError(WrongInput);
                break;

        }
    }

    return 0;
}


