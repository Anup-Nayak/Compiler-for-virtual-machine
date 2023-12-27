/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "exprtreenode.h"

//Write your code below this line

ExprTreeNode::ExprTreeNode(){
    type="";
    id="";
    num=1;
}

ExprTreeNode::ExprTreeNode(string t,int v){
    num =v;
    type=t;
}

ExprTreeNode::~ExprTreeNode(){
    num=1;
    id="";
    type="";
}

