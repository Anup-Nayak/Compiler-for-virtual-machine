/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "eppcompiler.h"

//Write your code below this line

EPPCompiler::EPPCompiler(){
    memory_size = 1;
    mem_loc.push_back(-4);
}

EPPCompiler::EPPCompiler(string out_file,int mem_limit){
    memory_size = mem_limit;
    output_file = out_file;
    for(int i=0;i<mem_limit;i++){
        mem_loc.push_back(-4);
    }
}

int FMI(vector<int> memloc){
    int n = memloc.size();
    for(int i=0;i<n;i++){
        if(memloc[i]==-4){
            return i;
        }
    }
}

void EPPCompiler::compile(vector<vector<string>> code){
    for(auto line: code){
        targ.parse(line);
        if(targ.expr_trees.back()->left->type == "VAR"){
            int is = targ.symtable->search(targ.expr_trees.back()->left->id);
            if(is == -1){
                int address =  FMI(mem_loc);
                mem_loc[address] = 4;
                targ.symtable->assign_address(targ.expr_trees.back()->left->id,address);
            }
        }else if(targ.expr_trees.back()->left->type == "DEL"){
            int is = targ.last_deleted;
            mem_loc[is] = -4;
        }   

        vector<string> comm = generate_targ_commands();
        write_to_file(comm);
    }
}

void GEN(ExprTreeNode* root, vector<string> &ans, SymbolTable* symt){
    string a = "";
    if(root==NULL){
        return;
    }
    if(root->type == "MUL"){
        a += "MUL" ;
    }else if(root->type == "DIV"){
        a += "DIV" ;
    }else if(root->type == "ADD"){
        a += "ADD";
    }else if(root->type == "SUB"){
        a += "SUB";
    }else if(root->type == "VAL"){
        a += "PUSH "+ root->id;
    }else if(root->type == "VAR"){
        int add = symt->search(root->id);
        a += "PUSH mem[" + to_string(add) +"]";
    }

    ans.push_back(a);
}

void RLN(ExprTreeNode* root, vector<string> &ans, SymbolTable* symt){
    if(root == NULL){
        return;
    }

    if(root -> type == "MUL" or root->type == "DIV" or root->type == "ADD" or root->type == "SUB"){
        RLN(root->right, ans,symt);
        RLN(root->left, ans,symt);
        GEN(root, ans, symt);
    }else if (root->type == "VAR" or root->type == "VAL"){
        GEN(root,ans, symt);
    }
}

vector<string> EPPCompiler::generate_targ_commands(){
    vector<string> result;
    ExprTreeNode* last = targ.expr_trees.back();
    SymbolTable* symt = targ.symtable ;
    
    
    //handle root and leftchild
    ExprTreeNode* leftChild = last->left;

    if(leftChild->type == "DEL"){
        string a;
        a+= "DEL = ";
        ExprTreeNode* rightChild = last->right;
        int add = symt->search(rightChild->id);
        a += "mem[" + to_string(add) +"]";
        result.push_back(a);
        return result;
    }

    // generate command for last (root node)
    RLN(last->right, result, symt);

    if(leftChild->type == "VAR"){
        string a;
        a += "mem[";
        int add = symt->search(leftChild->id);
        a += to_string(add);
        a += "] = POP";
        result.push_back(a);
        return result;
    
    }else if(leftChild->type == "RET"){
        string a = "RET = POP";
        result.push_back(a);
        return result;
    }

    return result;

}

void EPPCompiler::write_to_file(vector<string> commands){
    ofstream out (output_file, fstream::app);
    
    for(auto i : commands){
        out << i << endl;
        
    }
    out << endl;
    // out.close();
    
}

EPPCompiler::~EPPCompiler(){
    targ.~Parser();
}

