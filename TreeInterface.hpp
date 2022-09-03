//
// Created by User on 23.08.2022.
//

#ifndef BINARYREEPROJECT_TREEINTERFACE_HPP
#define BINARYREEPROJECT_TREEINTERFACE_HPP

#include <string>

class TreeInterface{
public:
    virtual void AddElement() = 0;
    virtual void EraseElement()  =0;
    virtual void ToTreeWithCondition() =  0;
    virtual void Print() = 0;
    virtual void ModifyTree() = 0;
    virtual size_t SizeOfTree() = 0;
    virtual bool IfElementHere()  =0;
    virtual void ToString() = 0;
    virtual void TreeToSubTree() = 0;

};
#endif //BINARYREEPROJECT_TREEINTERFACE_HPP
