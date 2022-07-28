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
int size_of_array = 0;
int comp1 (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}
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
    BinaryTree(BinaryTree<T>& tree){
        root = new TreeElement(tree.root->GetValue());
        CopyTree(root,tree.root);
    }
    ~BinaryTree() = default;
    BinaryTree& operator=(const BinaryTree& tree){
        delete root;
        root = new TreeElement(tree.root->GetValue());
        CopyTree(root,tree.root);
    }
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
    void AddElement(T element,TreeElement* cur_root){


        if (element>= cur_root->GetValue()){
            //std::cout<<element<<" - Gone right "<<std::endl;
            if (cur_root->GetRight() ==nullptr){
                auto* new_element = new TreeElement(element);
                cur_root->SetRight(new_element);
            }else{
                cur_root = cur_root->GetRight();

                AddElement(element,cur_root);
            }

        }
        else if (element< cur_root->GetValue()){
            //std::cout<<element<<" - Gone left "<<std::endl;
            if (cur_root->GetLeft() ==nullptr){
                auto* new_element = new TreeElement(element);
                cur_root->SetLeft(new_element);
            }else{
                cur_root = cur_root->GetLeft();

                AddElement(element,cur_root);
            }

        }
    }
    void AddElement(T element){
        //std::cout<<this->ConvertTreeToString(RightRootLeft)<<std::endl;
        //std::cout<<this->SizeOfBinaryTree()<<std::endl;
        AddElement(element,root);
    }
private:
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
    void SizeOfTree(TreeElement* cur_root,size_t* size){

        *size=*size+1;


        if (cur_root->GetRight()!=nullptr) {

            SizeOfTree(cur_root->GetRight(),size);
        }
        if (cur_root->GetLeft()!=nullptr) {

            SizeOfTree(cur_root->GetLeft(),size);
        }
    }
    void SizeOfTreeWithCondition(TreeElement* cur_root,size_t* size,bool f(T)){
        if (f(cur_root->GetValue())) {
            *size = *size + 1;
        }

        if (cur_root->GetRight()!=nullptr) {

            SizeOfTree(cur_root->GetRight(),size);
        }
        if (cur_root->GetLeft()!=nullptr) {

            SizeOfTree(cur_root->GetLeft(),size);
        }
    }
    void TreeToArray(TreeElement* cur_root,T* array){
        array[size_of_array] = cur_root->GetValue();
        size_of_array = size_of_array+1;
        if (cur_root->GetRight()!=nullptr) {

            TreeToArray(cur_root->GetRight(),array);
        }
        if (cur_root->GetLeft()!=nullptr) {

            TreeToArray(cur_root->GetLeft(),array);
        }

    }
    void TreeToArrayWithCondition(TreeElement* cur_root,T* array,bool f(T)){
        if (f(cur_root->GetValue())) {
            array[size_of_array] = cur_root->GetValue();
            size_of_array = size_of_array + 1;
        }
        if (cur_root->GetRight()!=nullptr) {

            TreeToArray(cur_root->GetRight(),array);
        }
        if (cur_root->GetLeft()!=nullptr) {

            TreeToArray(cur_root->GetLeft(),array);
        }

    }
public:
    T* BinaryTreeToArray(){
        auto* new_array = new T[this->SizeOfBinaryTree()];
        size_of_array = 0;
        TreeToArray(root,new_array);

        return new_array;
    }
    T* ToArrayWhere(bool f(T)){
        auto* new_array = new T[this->SizeOfBinaryTreeWithCondition(f)];
        size_of_array = 0;
        TreeToArrayWithCondition(root,new_array,f);

        return new_array;
    }
    BinaryTree<T>* TreeWithCondition(bool f(T)){
        auto* new_array = this->ToArrayWhere(f);
        if (this->SizeOfBinaryTreeWithCondition(f) == 0){
            throw TreeError(NoSuchElement);
        }
        qsort(new_array,SizeOfBinaryTreeWithCondition(f),sizeof(T),comp1);
        auto* new_tree = new BinaryTree<T>(new_array[SizeOfBinaryTree()/2]);
        for (int i = 0;i<SizeOfBinaryTree();i++){
            if (i!=SizeOfBinaryTree()/2){
                new_tree->AddElement(new_array[i]);
            }
        }
        return new_tree;
    }

    BinaryTree<T>* ToBalancedTree(){
        auto* new_array =BinaryTreeToArray();

        qsort(new_array,SizeOfBinaryTree(),sizeof(T),comp1);

        auto* new_tree = new BinaryTree<T>(new_array[SizeOfBinaryTree()/2]);

        for (int i = 0;i<SizeOfBinaryTree();i++){

            if (i!=SizeOfBinaryTree()/2){
                new_tree->AddElement(new_array[i]);
            }
        }
        return new_tree;
    }
    size_t SizeOfBinaryTree(){

        auto* size = new size_t;
        *size = 0;
        SizeOfTree(this->root,size);
        return *size;

    }
    size_t SizeOfBinaryTreeWithCondition(bool f(T)){

        auto* size = new size_t;
        *size = 0;
        SizeOfTreeWithCondition(this->root,size,f);
        return *size;

    }
    BinaryTree* SubTree(T element){

        auto* new_bin_tree = new BinaryTree<T> (element);
        if (this->SearchElement(element) == nullptr){
            throw TreeError(NoSuchElement);
        }
        new_bin_tree->CopyTree(new_bin_tree->root,this->SearchElement(element));
        return new_bin_tree;
    }
    BinaryTree* map(T function(T)){
        if (function == nullptr){
            throw TreeError(WrongInput);
        }
        BinaryTree<T> new_bin_tree(new TreeElement(this->root->GetValue()));

        new_bin_tree.ModifyTree(new_bin_tree.root,this->root,function());
        return new_bin_tree;

    }
private:
    void ConvertTreeToString(int TraversalType, std::string* TreeToString, TreeElement* root_element) {
        switch(TraversalType) {
            case LeftRootRight :

                if (root_element->GetLeft() != nullptr){
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());

                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetRight() != nullptr){

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                break;
                
            case RootLeftRight :

                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetLeft() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());

                }
                if (root_element->GetRight() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                break;

            case RootRightLeft :
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetRight() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                if (root_element->GetLeft() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());
                }
                break;

            case LeftRightRoot :
                if (root_element->GetLeft() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());
                }
                if (root_element->GetRight() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                break;
            case RightLeftRoot :
                if (root_element->GetRight() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                if (root_element->GetLeft() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());
                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                break;
            case RightRootLeft :
                if (root_element->GetRight() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetLeft() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());
                }
                break;
            default:

                throw TreeError(WrongBypass);
                break;
        }
    }
public:
    std::string ConvertTreeToString(int TraversalType) {
        auto* treeToString = new std::string;
        ConvertTreeToString(TraversalType, treeToString, this->root);
        std::string result;
        result.append(*treeToString);
        delete treeToString;
        return result;
    }
    void erase(T key){
        TreeElement * curr = root;
        TreeElement * parent = NULL;
        while (curr && curr->GetValue() != key)
        {
            parent = curr;
            if (curr->GetValue() > key)
            {
                curr = curr->GetLeft();
            }
            else
            {
                curr = curr->GetRight();
            }
        }
        if (!curr)
            throw TreeError(NoSuchElement);
        if (curr->GetLeft() == NULL)
        {
            // Вместо curr подвешивается его правое поддерево
            if (parent && parent->GetLeft() == curr)
                parent->GetLeft() = curr->GetRight();
            if (parent && parent->GetRight() == curr)
                parent->GetRight() = curr->GetRight();

            delete curr;
            return;
        }
        if (curr->GetRight() == NULL)
        {
            // Вместо curr подвешивается его левое поддерево
            if (parent && parent->GetLeft() == curr)
                parent->GetLeft() = curr->GetLeft();
            if (parent && parent->GetRight() == curr)
                parent->GetRight() = curr->GetLeft();

            delete curr;
            return;
        }
        // У элемента есть два потомка, тогда на место элемента поставим
        // наименьший элемент из его правого поддерева
        TreeElement * replace = curr->GetRight();
        while (replace->GetLeft())
            replace = replace->GeLeft();
        T replace_value = replace->GetValue();
        erase(replace_value);
        curr->SetValue() = replace_value;
    }
};
#endif //BINARYREEPROJECT_BINARYTREE_HPP

