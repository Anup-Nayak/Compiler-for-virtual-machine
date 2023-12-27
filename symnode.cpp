/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symnode.h"

//Write your code below this line


SymNode::SymNode(){
    height = 1;
    key="";
}

SymNode::SymNode(string k){
    key=k;
    height = 1;
}

SymNode* SymNode::LeftLeftRotation(){
    SymNode* waste = new SymNode();
    return waste;
}

SymNode* SymNode::RightRightRotation(){
    SymNode* waste = new SymNode();
    return waste;
}

SymNode* SymNode::LeftRightRotation(){
    SymNode* waste = new SymNode();
    return waste;
}

SymNode* SymNode::RightLeftRotation(){
    SymNode* waste = new SymNode();
    return waste;
}

SymNode::~SymNode(){
    key="";
    height = 1 ;
    par = NULL;
    left = NULL;
    right = NULL;
}

