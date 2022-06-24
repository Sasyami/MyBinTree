//
// Created by User on 24.06.2022.
//

#ifndef BINARYREEPROJECT_BINARYTREE_HPP
#define BINARYREEPROJECT_BINARYTREE_HPP
#include <iostream>
#include "TreeExceptions.hpp"
#define LeftRightRoot 0
#define RightLeftRoot 1
#define RootLeftRight 2
#define RootRightLeft 3
#define LeftRootRight 4
#define RightRootLeft 5

template <typename T>
class BinaryTree{
private:

    class TreeElement{
    private:
        T element;
        TreeElement* right;
        TreeElement* left;
    public:
        explicit TreeElement(T el){
            element = el;
            right = nullptr;
            left =nullptr;
        }
        ~TreeElement(){
            if (right!= nullptr){
                delete right;
            }
            if (left!= nullptr){
                delete left;
            }
        }
        TreeElement& operator=(const TreeElement& elem ){
            this->SetValue(elem.GetValue());
            return *this;
        }
        TreeElement* GetRight(){
            return this->right;
        }
        TreeElement* GetLeft(){
            return this->left;
        }
        T GetValue(){
            return this->element;
        }
        void SetRight(TreeElement* element_tree){
            this->right = element_tree;
        }
        void SetLeft(TreeElement* element_tree){
            this->left = element_tree;
        }
        void SetValue(T new_element){
            element  = new_element;
        }
    };
    TreeElement* root;
public:
    explicit BinaryTree(T element){
        root = new TreeElement(element);
    }
    explicit BinaryTree (TreeElement* new_root){
        root = new TreeElement(new_root->element);
    }
    ~BinaryTree() = default;
    TreeElement* SearchElement(T element){
        BinaryTree<T> current_tree(root->GetValue());
        auto* current_element = root;

        if (current_element->GetValue() == element){

            return current_element;
        }else if(current_element->GetValue() >element){
            current_element = current_element->GetLeft();

            if (current_element == nullptr){
                return nullptr;
            }
            current_tree.root = current_element;
            return current_tree.SearchElement(element);
        }else{
            current_element = current_element->GetRight();

            if (current_element == nullptr){
                return nullptr;
            }
            current_tree.root = current_element;
            return current_tree.SearchElement(element);
        }
    }
    void AddElement(T element){
        auto* current_element = root;
        BinaryTree<T> current_tree(root->GetValue());

        if (element>= current_element->GetValue()){
            if (current_element->GetRight() ==nullptr){
                auto* new_element = new TreeElement(element);
                current_element->SetRight(new_element);
            }else{
                current_element = current_element->GetRight();
                current_tree.root = current_element;
                current_tree.AddElement(element);
            }

        }
        if (element< current_element->GetValue()){
            if (current_element->GetLeft() ==nullptr){
                auto* new_element = new TreeElement(element);
                current_element->SetLeft(new_element);
            }else{
                current_element = current_element->GetLeft();
                current_tree.root = current_element;
                current_tree.AddElement(element);
            }

        }
    }
    TreeElement* GetRoot(){
        return root;
    }
    void CopyTree(TreeElement* to,TreeElement* from){
        to->SetValue(from->GetValue());
        if (from->GetRight()!=nullptr) {
            auto* right_element = new TreeElement(from->GetValue());
            to->SetRight(right_element);
            CopyTree(right_element,from->GetRight());
        }else{
            to->SetRight(nullptr);
        }
        if (from->GetLeft()!=nullptr) {
            auto* left_element = new TreeElement(from->GetValue());
            to->SetLeft(left_element);
            CopyTree(left_element,from->GetLeft());
        }else{
            to->SetLeft(nullptr);
        }
    }
    void ModifyTree(TreeElement* to,TreeElement* from,T function(T)){
        to->SetValue(from->GetValue());
        if (from->GetRight()!=nullptr) {
            auto* right_element = new TreeElement(function(from->GetValue()));
            to->SetRight(right_element);
            CopyTree(right_element,from->GetRight());
        }else{
            to->SetRight(nullptr);
        }
        if (from->GetLeft()!=nullptr) {
            auto* left_element = new TreeElement(from->GetValue());
            to->SetLeft(left_element);
            CopyTree(left_element,function(from->GetLeft()));
        }else{
            to->SetLeft(nullptr);
        }
    }
    BinaryTree* SubTree(T element){

        BinaryTree<T> new_bin_tree(new TreeElement(element));
        new_bin_tree.CopyTree(new_bin_tree.root,this->SearchElement(element));
        return new_bin_tree;
    }
    BinaryTree* map(T function(T)){
        BinaryTree<T> new_bin_tree(new TreeElement(this->root->GetValue()));

        new_bin_tree.ModifyTree(new_bin_tree.root,this->root,function());
        return new_bin_tree;

    }
    void ConvertTreeToString(int traversalType, std::string* treeToString, TreeElement* rootElement) {
        switch(traversalType) {
            case LeftRootRight:
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                break;
            case RootLeftRight:
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                break;
            case RootRightLeft:
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                break;
            case LeftRightRoot:
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                break;
            case RightLeftRoot:
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                break;
            case RightRootLeft:
                if (rootElement->GetRight() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetRight());
                }
                treeToString->append(std::to_string(rootElement->GetValue()).substr(0, std::to_string(rootElement->GetValue()).find(".") + 4) + " ");
                if (rootElement->GetLeft() != nullptr) {
                    ConvertTreeToString(traversalType, treeToString, rootElement->GetLeft());
                }
                break;
            default:

                throw TreeExceptions;
                break;
        }
    };
};
#endif //BINARYREEPROJECT_BINARYTREE_HPP
