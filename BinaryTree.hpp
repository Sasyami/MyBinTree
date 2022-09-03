//
// Created by User on 24.06.2022.
//

#ifndef BINARYREEPROJECT_BINARYTREE_HPP
#define BINARYREEPROJECT_BINARYTREE_HPP
#include <iostream>
#include <string>
#include "TreeExceptions.hpp"
#include <cmath>
#include "ArraySequence.hpp"
#define LeftRightRoot 0
#define RightLeftRoot 1
#define RootLeftRight 2
#define RootRightLeft 3
#define LeftRootRight 4
#define RightRootLeft 5
#define Right 1
#define Left -1
#define Root 0
int size_of_array = 0;
int depth_checker = 0;
int max_length = 0;
int new_depth = 0;
int comp1 (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

std::string StringToStringWithLength(const std::string& str,size_t length){
    std::string new_string = std::string((length-str.size())/2,' ');
    new_string+=str;
    new_string+=std::string(length-new_string.size(),' ');
    return new_string;
}
template <typename T>
class BinaryTree {

private:
    class TreeElement {
    private:
        T element;
        TreeElement *right;
        TreeElement *left;
    public:
        /*explicit TreeElement() {
            element = 0;
            right = nullptr;
            left = nullptr;
        }*/
        TreeElement() = delete;
        explicit TreeElement(T el) {
            element = el;
            right = nullptr;
            left = nullptr;
        }

        ~TreeElement() {
            delete right;
            delete left;

        }

        TreeElement &operator=(const TreeElement &elem) {
            this->SetValue(elem.GetValue());
            this->SetLeft(elem.GetLeft());
            this->SetRight(elem.GetRight());
            return *this;
        }

        TreeElement *GetRight() {
            return this->right;
        }

        TreeElement *GetLeft() {
            return this->left;
        }

        T GetValue() const {
            return this->element;
        }

        void SetRight(TreeElement *element_tree) {
            this->right = element_tree;
        }

        void SetLeft(TreeElement *element_tree) {
            this->left = element_tree;
        }

        void SetValue(T new_element) {
            element = new_element;
        }
    };

    TreeElement *root;
    size_t depth;
public:
    BinaryTree(){
        root = nullptr;
        depth = 0;
    }
    explicit BinaryTree(T element) {
        root = new TreeElement(element);
        depth = 1;
    }

    explicit BinaryTree(TreeElement *new_root) {
        root = new TreeElement(new_root->GetValue());
        depth = 1;

    }

    BinaryTree(BinaryTree<T> &tree) {
        root = new TreeElement(tree.root->GetValue());
        CopyTree(root, tree.root);
        depth = tree.depth;
    }

    ~BinaryTree() {
        delete root;
    }

    size_t GetDepth() {
        return depth;
    }

    size_t CheckDepth() {
        depth_checker = 0;
        if (root == nullptr){
            return 0;
        }
        CheckDepthRaw(1, root);
        size_t for_return = depth_checker;
        depth_checker = 0;
        return for_return;
    }
    size_t CheckDepth(TreeElement* element){
        depth_checker = 0;
        if (element == nullptr){
            return 0;
        }
        CheckDepthRaw(1, element);
        size_t for_return = depth_checker;
        depth_checker = 0;
        return for_return;
    }
    void SmallRightRotatedTree(){
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        SmallRightRotatedTree(root,root->GetRight(), Right);
        SmallRightRotatedTree(root,root->GetLeft(), Left);

        if ((root->GetLeft()!=nullptr)&&abs(CheckBalance(root))>1&&(abs((int)CheckDepth(root->GetLeft()->GetLeft())+1-(int)CheckDepth(root->GetRight()))>1)){

            root = SmallRightRotate(root);
        }
        depth = this->CheckDepth();


    }
    void SmallLeftRotatedTree(){
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        SmallLeftRotatedTree(root,root->GetRight(), Right);
        SmallLeftRotatedTree(root,root->GetLeft(), Left);

        if ((root->GetRight()!=nullptr)&&abs(CheckBalance(root))>1&&(abs((int)CheckDepth(root->GetRight()->GetRight())+1-(int)CheckDepth(root->GetLeft()))>1)){

            root = SmallLeftRotate(root);
        }
        depth = this->CheckDepth();


    }
    void BigLeftRotatedTree(){
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        BigLeftRotatedTree(root,root->GetRight(), Right);
        BigLeftRotatedTree(root,root->GetLeft(), Left);

        if (root->GetRight()->GetLeft()&&root->GetRight()&&abs(CheckBalance(root))>1&&((int)CheckDepth(root->GetRight()->GetLeft())>(int)CheckDepth(root->GetRight()->GetRight()))){

            root->SetRight(SmallRightRotate(root->GetRight()));
            root = SmallLeftRotate(root);
        }
        depth = this->CheckDepth();


    }
    void BigRightRotatedTree(){
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        BigLeftRotatedTree(root,root->GetRight(), Right);
        BigLeftRotatedTree(root,root->GetLeft(), Left);

        if (root->GetLeft()->GetRight()&&root->GetLeft()&&abs(CheckBalance(root))>1&&((int)CheckDepth(root->GetLeft()->GetRight())>(int)CheckDepth(root->GetLeft()->GetLeft()))){

            root->SetLeft(SmallLeftRotate(root->GetLeft()));
            root = SmallRightRotate(root);
        }
        depth = this->CheckDepth();


    }
    void BalancedWithRotation(){
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        this->SmallRightRotatedTree();
        this->SmallLeftRotatedTree();


    }
private:
    int CheckBalance(TreeElement* element){
        return CheckDepth(element->GetRight())-CheckDepth(element->GetLeft());
    }
    void BigLeftRotatedTree(TreeElement* parent,TreeElement* child, int i){
        if(!child||!parent){
            return;
        }
        if (child->GetRight()!=nullptr){
            BigLeftRotatedTree(child,child->GetRight(),Right);
        }
        if (child->GetLeft()!=nullptr){

            BigLeftRotatedTree(child,child->GetLeft(),Left);
        }

        if (child->GetRight()&&child->GetRight()->GetLeft()&&abs(CheckBalance(child))>1&&((int)CheckDepth(child->GetRight()->GetLeft())>(int)CheckDepth(child->GetRight()->GetRight()))){

            child->SetRight(SmallRightRotate(child->GetRight()));
            if (i>0){
                parent->SetRight(SmallLeftRotate(child));
            }
            else if (i<0){
                parent->SetLeft(SmallLeftRotate(child));
            } else{
                throw TreeError(WrongInput);
            }

        }
    }
    void BigRightRotatedTree(TreeElement* parent,TreeElement* child, int i){
        if(!child||!parent){
            return;
        }
        if (child->GetRight()!=nullptr){
            BigRightRotatedTree(child,child->GetRight(),Right);
        }
        if (child->GetLeft()!=nullptr){

            BigRightRotatedTree(child,child->GetLeft(),Left);
        }

        if (child->GetLeft()&&child->GetLeft()->GetRight()&&abs(CheckBalance(child))>1&&((int)CheckDepth(child->GetLeft()->GetRight())>(int)CheckDepth(child->GetLeft()->GetLeft()))){

            child->SetLeft(SmallLeftRotate(child->GetLeft()));
            if (i>0){
                parent->SetRight(SmallRightRotate(child));
            }
            else if (i<0){
                parent->SetLeft(SmallRightRotate(child));
            } else{
                throw TreeError(WrongInput);
            }

        }
    }
    void SmallRightRotatedTree(TreeElement* parent,TreeElement* child, int i){
        if(!child||!parent){
            return;
        }
        if (child->GetRight()!=nullptr){
            SmallRightRotatedTree(child,child->GetRight(),Right);
        }
        if (child->GetLeft()!=nullptr){

            SmallRightRotatedTree(child,child->GetLeft(),Left);
        }
        if (child->GetLeft()&&abs(CheckBalance(child))>1&&(abs((int)CheckDepth(child->GetLeft()->GetLeft())+1-(int)CheckDepth(child->GetRight()))>1)){
            if (i>0){
                parent->SetRight(SmallRightRotate(child));
            }
            else if (i<0){
                parent->SetLeft(SmallRightRotate(child));
            } else{
                throw TreeError(WrongInput);
            }
        }
    }
    void SmallLeftRotatedTree(TreeElement* parent,TreeElement* child, int i){
        if(!child||!parent){
            return;
        }
        if (child->GetRight()!=nullptr){
            SmallRightRotatedTree(child,child->GetRight(),Right);
        }
        if (child->GetLeft()!=nullptr){

            SmallRightRotatedTree(child,child->GetLeft(),Left);
        }
        if (child->GetRight()&&abs(CheckBalance(child))>1&&(abs((int)CheckDepth(child->GetRight()->GetRight())+1-(int)CheckDepth(child->GetLeft()))>1)){
            if (i>0){
                parent->SetRight(SmallLeftRotate(child));
            }
            else if (i<0){
                parent->SetLeft(SmallLeftRotate(child));
            } else{
                throw TreeError(WrongInput);
            }
        }



    }
    TreeElement* SmallRightRotate(TreeElement* element){
        TreeElement* small_root = element;
        if (small_root == nullptr){
            throw TreeError(NoRotate);
        }
        TreeElement* new_root = small_root->GetLeft();
        if (new_root == nullptr){
            throw TreeError(NoRotate);
        }
        TreeElement* branch_to_change = new_root->GetRight();
        small_root->SetLeft(branch_to_change);
        new_root->SetRight(small_root);
        return new_root;


    }
    TreeElement* SmallLeftRotate(TreeElement* element){
        TreeElement* small_root = element;
        if (small_root == nullptr){
            throw TreeError(NoRotate);
        }
        TreeElement* new_root = small_root->GetRight();
        if (new_root == nullptr){
            throw TreeError(NoRotate);
        }
        TreeElement* branch_to_change = new_root->GetLeft();
        small_root->SetRight(branch_to_change);
        new_root->SetLeft(small_root);
        return new_root;


    }

    void CheckDepthRaw(int current_depth, TreeElement *current_root) {
        if (current_depth > depth_checker) {
            depth_checker = current_depth;
        }
        current_depth++;
        if (current_root&&current_root->GetLeft() != nullptr) {
            CheckDepthRaw(current_depth, current_root->GetLeft());
        }
        if (current_root&&current_root->GetRight() != nullptr) {
            CheckDepthRaw(current_depth, current_root->GetRight());
        }
    }

    void MaxElementLength(TreeElement *element) {
        if (std::to_string(element->GetValue()).size() > max_length) {
            max_length = (std::to_string(element->GetValue())).size();
        }
        if (element->GetRight() != nullptr) {
            MaxElementLength(element->GetRight());
        }
        if (element->GetLeft() != nullptr) {
            MaxElementLength(element->GetLeft());
        }
    }

public:
    size_t MaxElementLength() {
        if (root == nullptr){
            return 0;
        }
        max_length = 0;
        MaxElementLength(root);
        size_t to_return = max_length;
        max_length = 0;
        return to_return;
    }

    BinaryTree &operator=(const BinaryTree &tree) {
        delete root;
        root = new TreeElement(tree.root->GetValue());
        CopyTree(root, tree.root);
        return *this;
    }

    TreeElement *SearchElement(T element) {
        /*BinaryTree<T> current_tree(root->GetValue());
        auto *current_element = root;

        if (current_element->GetValue() == element) {
            std::cout<<current_element->GetValue();
            return current_element;
        } else if (current_element->GetValue() > element) {

            current_element = current_element->GetLeft();

            if (current_element == nullptr) {
                return nullptr;
            }
            current_tree.root = current_element;
            return current_tree.SearchElement(element);
        } else {

            current_element = current_element->GetRight();

            if (current_element == nullptr) {
                return nullptr;
            }
            current_tree.root = current_element;
            return current_tree.SearchElement(element);
        }*/
        return SearchElement(root,element);
    }
private:
    TreeElement* SearchElement(TreeElement* tree_element,T element){
        if (tree_element == nullptr){
            return nullptr;
        }
        if (element> tree_element->GetValue()){
            return SearchElement(tree_element->GetRight(),element);
        }else if(element == tree_element->GetValue()){
            return tree_element;
        }else{
            return SearchElement(tree_element->GetLeft(),element);
        }
    }

    void AddElement(T element, TreeElement *cur_root, int i) {

        i++;
        if (element >= cur_root->GetValue()) {

            if (cur_root->GetRight() == nullptr) {
                auto *new_element = new TreeElement(element);
                cur_root->SetRight(new_element);
                new_depth = i;


            } else {
                cur_root = cur_root->GetRight();

                AddElement(element, cur_root, i);
            }

        } else if (element < cur_root->GetValue()) {

            if (cur_root->GetLeft() == nullptr) {
                auto *new_element = new TreeElement(element);
                cur_root->SetLeft(new_element);
                new_depth = i;

            } else {
                cur_root = cur_root->GetLeft();

                AddElement(element, cur_root, i);
            }

        }

    }

public:
    void AddElement(T element) {

        AddElement(element, root, 1);
        new_depth>depth ? depth = new_depth : new_depth = depth;
        new_depth = 0;
        this->BalancedWithRotation();



    }

private:
    TreeElement *GetRoot() {
        return root;
    }

    void CopyTree(TreeElement *to, TreeElement *from) {
        to->SetValue(from->GetValue());
        if (from->GetRight() != nullptr) {
            auto *right_element = new TreeElement(from->GetValue());
            to->SetRight(right_element);
            CopyTree(right_element, from->GetRight());
        } else {
            to->SetRight(nullptr);
        }
        if (from->GetLeft() != nullptr) {
            auto *left_element = new TreeElement(from->GetValue());
            to->SetLeft(left_element);
            CopyTree(left_element, from->GetLeft());
        } else {
            to->SetLeft(nullptr);
        }
    }

    void ModifyTree(TreeElement *to, TreeElement *from, T function(T)) {
        to->SetValue(function(from->GetValue()));
        if (from->GetRight() != nullptr) {

            auto *right_element = new TreeElement(function(from->GetValue()));
            to->SetRight(right_element);
            ModifyTree(right_element, from->GetRight(),function);
        } else {
            to->SetRight(nullptr);
        }
        if (from->GetLeft() != nullptr) {
            auto *left_element = new TreeElement(from->GetValue());
            to->SetLeft(left_element);
            ModifyTree(left_element, from->GetLeft(),function);
        } else {
            to->SetLeft(nullptr);
        }
    }

    void SizeOfTree(TreeElement *cur_root, size_t *size) {

        *size = *size + 1;


        if (cur_root->GetRight() != nullptr) {

            SizeOfTree(cur_root->GetRight(), size);
        }
        if (cur_root->GetLeft() != nullptr) {

            SizeOfTree(cur_root->GetLeft(), size);
        }
    }

    void SizeOfTreeWithCondition(TreeElement *cur_root, size_t *size, bool f(T)) {
        if (f(cur_root->GetValue())) {
            *size = *size + 1;
        }

        if (cur_root->GetRight() != nullptr) {

            SizeOfTreeWithCondition(cur_root->GetRight(), size,f);
        }
        if (cur_root->GetLeft() != nullptr) {

            SizeOfTreeWithCondition(cur_root->GetLeft(), size,f);
        }
    }

    void TreeToArray(TreeElement *cur_root, T *array) {
        array[size_of_array] = cur_root->GetValue();
        size_of_array = size_of_array + 1;
        if (cur_root->GetRight() != nullptr) {

            TreeToArray(cur_root->GetRight(), array);
        }
        if (cur_root->GetLeft() != nullptr) {

            TreeToArray(cur_root->GetLeft(), array);
        }

    }

    void TreeToArrayWithCondition(TreeElement *cur_root, T *array, bool f(T)) {
        if (f(cur_root->GetValue())) {
            array[size_of_array] = cur_root->GetValue();
            size_of_array = size_of_array + 1;
        }
        if (cur_root->GetRight() != nullptr) {

            TreeToArrayWithCondition(cur_root->GetRight(), array,f);
        }
        if (cur_root->GetLeft() != nullptr) {

            TreeToArrayWithCondition(cur_root->GetLeft(), array,f);
        }

    }

public:
    T *BinaryTreeToArray() {
        if (root == nullptr){
            return nullptr;
        }
        auto *new_array = new T[this->SizeOfBinaryTree()];
        size_of_array = 0;
        TreeToArray(root, new_array);

        return new_array;
    }

    T *ToArrayWhere(bool f(T)) {

        auto *new_array = new T[this->SizeOfBinaryTreeWithCondition(f)];
        size_of_array = 0;
        TreeToArrayWithCondition(root, new_array, f);

        return new_array;
    }

    BinaryTree<T> *TreeWithCondition(bool f(T)) {
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        if (f== nullptr) {
            throw TreeError(WrongInput);
        }
        if (this->SizeOfBinaryTreeWithCondition(f) == 0) {
            throw TreeError(NoSuchElement);
        }
        auto *new_array = this->ToArrayWhere(f);

        qsort(new_array, SizeOfBinaryTreeWithCondition(f), sizeof(T), comp1);

        auto *new_tree = new BinaryTree<T>(new_array[SizeOfBinaryTreeWithCondition(f) / 2]);
        for (int i = 0; i < SizeOfBinaryTreeWithCondition(f); i++) {
            if (i != SizeOfBinaryTreeWithCondition(f) / 2) {
                new_tree->AddElement(new_array[i]);
            }
        }
        return new_tree;
    }

    BinaryTree<T> *ToBalancedTree() {
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        auto *new_array = BinaryTreeToArray();

        qsort(new_array, SizeOfBinaryTree(), sizeof(T), comp1);

        auto *new_tree = new BinaryTree<T>(new_array[SizeOfBinaryTree() / 2]);

        for (int i = 0; i < SizeOfBinaryTree(); i++) {

            if (i != SizeOfBinaryTree() / 2) {
                new_tree->AddElement(new_array[i]);
            }
        }
        return new_tree;
    }

    size_t SizeOfBinaryTree() {
        if (root == nullptr){
            return 0;
        }
        auto *size = new size_t;
        *size = 0;
        SizeOfTree(this->root, size);
        return *size;

    }

    size_t SizeOfBinaryTreeWithCondition(bool f(T)) {
        if (root == nullptr){
            return 0;
        }
        auto *size = new size_t;
        *size = 0;
        SizeOfTreeWithCondition(this->root, size, f);
        return *size;

    }

    BinaryTree *SubTree(T element) {
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        auto *new_bin_tree = new BinaryTree<T>(element);
        if (this->SearchElement(element) == nullptr) {
            throw TreeError(NoSuchElement);
        }
        new_bin_tree->CopyTree(new_bin_tree->root, this->SearchElement(element));
        new_bin_tree->depth = new_bin_tree->CheckDepth();
        return new_bin_tree;
    }

    BinaryTree *map(T function(T)) {
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        if (function == nullptr) {
            throw TreeError(WrongInput);
        }
        auto* new_bin_tree = new BinaryTree<T> (new TreeElement(function(this->root->GetValue())));

        new_bin_tree->ModifyTree(new_bin_tree->root, this->root, function);
        new_bin_tree->depth = depth;
        return new_bin_tree;

    }

private:
    void ConvertTreeToString(int TraversalType, std::string *TreeToString, TreeElement *root_element) {
        switch (TraversalType) {
            case LeftRootRight :

                if (root_element->GetLeft() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());

                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetRight() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                break;

            case RootLeftRight :

                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
                if (root_element->GetLeft() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());

                }
                if (root_element->GetRight() != nullptr) {

                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                break;

            case RootRightLeft :
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
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
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
                break;
            case RightLeftRoot :
                if (root_element->GetRight() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                if (root_element->GetLeft() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetLeft());
                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
                break;
            case RightRootLeft :
                if (root_element->GetRight() != nullptr) {
                    ConvertTreeToString(TraversalType, TreeToString, root_element->GetRight());
                }
                TreeToString->append(std::to_string(root_element->GetValue()).substr(0, std::to_string(
                        root_element->GetValue()).find(".") + 4) + " ");
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
        if (root == nullptr){
            throw TreeError(NoRoot);
        }
        auto *treeToString = new std::string;
        ConvertTreeToString(TraversalType, treeToString, this->root);
        std::string result;
        result.append(*treeToString);
        delete treeToString;
        return result;
    }

    void erase(T key) {
        TreeElement *curr = root;
        TreeElement *parent = NULL;

        while (curr && curr->GetValue() != key) {
            parent = curr;
            if (curr->GetValue() > key) {
                curr = curr->GetLeft();
            } else {
                curr = curr->GetRight();
            }
        }
        if (curr == root){
            throw TreeError(DeleteRoot);
        }
        if (!curr) {
            throw TreeError(NoSuchElement);
        }
        if (curr->GetLeft() == NULL) {

            // Вместо curr подвешивается его правое поддерево
            if (parent && parent->GetLeft() == curr) {
                parent->SetLeft(curr->GetRight());
            }
            if (parent && parent->GetRight() == curr) {

                parent->SetRight(curr->GetRight());
            }


            //delete curr;
            depth = this->CheckDepth();
            return;
        }

        if (curr->GetRight() == NULL) {
            // Вместо curr подвешивается его левое поддерево
            if (parent && parent->GetLeft() == curr) {
                parent->SetLeft( curr->GetLeft());
            }
            if (parent && parent->GetRight() == curr) {
                parent->SetRight(curr->GetLeft());
            }

            depth = this->CheckDepth();
            return;
        }

        TreeElement *replace = curr->GetRight();
        while (replace->GetLeft()) {
            replace = replace->GetLeft();
        }
        T replace_value = replace->GetValue();
        erase(replace_value);
        curr->SetValue(replace_value);

        depth = this->CheckDepth();

    }

public:
    void PrintTree() {

        int number_of_spaces = (pow(2, this->GetDepth()) - 1) / 2;
        std::string space_element = std::string(this->MaxElementLength(), ' ');

        auto *old_array = new ArraySequence<TreeElement *>();
        auto *new_array = new ArraySequence<TreeElement *>();


        old_array->Append(root);
        for (int i = 0; i < depth; i++) {

            for (int j = 0; j < old_array->GetLength(); j++) {

                std::cout << std::string(number_of_spaces*this->MaxElementLength(), ' ');
                if (old_array->Get(j) == nullptr) {
                    new_array->Append(nullptr);
                    new_array->Append(nullptr);
                    std::cout << space_element;
                } else {
                    std::cout << StringToStringWithLength(std::to_string(old_array->Get(j)->GetValue()),space_element.size());
                    new_array->Append(old_array->Get(j)->GetLeft());
                    new_array->Append(old_array->Get(j)->GetRight());


                }
                std::cout << std::string((number_of_spaces + 1)*this->MaxElementLength(), ' ');
            }

            std::cout << "\n";
            number_of_spaces = number_of_spaces / 2;
            old_array = new ArraySequence<TreeElement *>(*new_array);

            new_array = new ArraySequence<TreeElement *>();
        }

        delete new_array;
        delete old_array;
    }

public:
    template<class U>
    friend std::ostream &operator<<(std::ostream &out, const BinaryTree<U> &a);
};
template<class U>
std::ostream& operator<<(std::ostream &out, const BinaryTree<U> &a) {
    a.PrintTree();
    return out;

}
#endif //BINARYREEPROJECT_BINARYTREE_HPP
