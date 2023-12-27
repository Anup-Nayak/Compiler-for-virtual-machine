/* Do NOT add/remove any includes statements from this header file */
/* unless EXPLICTLY clarified on Piazza. */
#include "symtable.h"

//Write your code below this line

int getHeight(SymNode* node){
    if(node==NULL){
        return 0;
    }
    return node->height;
}

void heightUpdate(SymNode* node){
    if(node==NULL){
        return;
    }
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
}

int getBalance(SymNode* root){
    int lh = getHeight(root->left);
    int rh = getHeight(root->right);
    return lh-rh;

};

// A(root) B C -> A B(root) C
SymNode* LLRotation(SymNode* root){
    SymNode* B = root->right;
    root->right = B->left;
    B->left = root;

    B->par = root->par;
    root->par = B;
    if(root->right){
        root->right->par = root;
    }

    heightUpdate(root);
    heightUpdate(B);

    return B;
}

// A B C(root) -> A B(root) C
SymNode* RRRotation(SymNode* root){
    SymNode* B = root->left;
    root->left = B->right;
    B->right = root;

    B->par = root->par;
    root->par = B;
    if(root->right){
        root->left->par = root;
    }

    heightUpdate(root);
    heightUpdate(B);

    return B;
}

SymNode* LRRotation(SymNode* root){
    root->left = LLRotation(root->left);
    return RRRotation(root);
}

SymNode* RLRotation(SymNode* root){
    root->right = RRRotation(root->right);
    return LLRotation(root);
}

SymbolTable::SymbolTable(){}

SymNode* INSERT(SymNode* root, string k){
    if(root==NULL){
        return new SymNode(k);
    }else{
        if(k > root->key){
            SymNode* z = INSERT(root->right , k);
            root->right = z;
            z->par = root;
            
        }else if(k < root->key){
            SymNode* z = INSERT(root->left , k);
            root->left = z;
            z->par = root;
            
        }else{
            return root;
        }
    }

    root->height = 1 + max(getHeight(root->left),getHeight(root->right));  

    int balance = getBalance(root);  

    if (balance > 1 && k < root->left->key){
        return RRRotation(root);
    }if (balance < -1 && k > root->right->key){
        return LLRotation(root);
    }if (balance > 1 && k > root->left->key)  {  
        return LRRotation(root);
    }if (balance < -1 && k < root->right->key)  {  
        return RLRotation(root);
    } 
    return root;  
    
}

void SymbolTable::insert(string k){
    size++;
    if(root == NULL){
        root = new SymNode(k);
    }else{
        root = INSERT(root,k);
    }
}

SymNode* MIN(SymNode *node){
    SymNode *current = node;
    while (current->left != NULL){
        current = current->left;
    }
    return current;
}


SymNode* BALANCE(SymNode* node){
    node->height = 1 + max(getHeight(node->left),getHeight(node->right));
    string k = node->key;
    int balance = getBalance(node);  

    if (balance > 1 && k < node->left->key){
        return RRRotation(node);
    }if (balance < -1 && k > node->right->key){
        return LLRotation(node);
    }if (balance > 1 && k > node->left->key)  {  
        return LRRotation(node);
    }if (balance < -1 && k < node->right->key)  {  
        return RLRotation(node);
    }  

    heightUpdate(node);
    return node;
}

void REM(SymNode* root, string k){
    if(root==NULL){
        return;
    }else{
        SymNode* temp = root->par;
        if (k < root->key){
            REM(root->left, k);
            heightUpdate(root->left);
        }else if (k > root->key){
            REM(root->right, k);
            heightUpdate(root->right);
        }else{
            if(root->left == NULL and root->right == NULL){
                if(root == root->par->left){
                    temp = root->par;
                    root->par->left = NULL;
                    root->par = NULL;
                    delete root;
                    heightUpdate(temp);
                    if(temp->par){
                        heightUpdate(temp->par);
                    }
                    if(temp!=NULL){
                        temp = BALANCE(temp);
                    }
                    
                }else{
                    temp = root->par;
                    root->par->right = NULL;
                    root->par = NULL;
                    delete root;
                    heightUpdate(temp);
                    if(temp->par){
                        heightUpdate(temp->par);
                    }
                    if(temp!=NULL){
                        temp = BALANCE(temp);
                    }
                }
            }else if(root->right == NULL){
                temp = root->par;
                if(root == root->par->right){
                    root->par->right = root->left;
                    root->left->par = root->par;
                }else{
                    root->par->left = root->left;
                    root->left->par = root->par;
                }
                
                root->left = NULL;
                root->par = NULL;
                delete root;
                heightUpdate(temp);
                if(temp->par){
                    heightUpdate(temp->par);
                }
                if(temp!=NULL){
                        temp = BALANCE(temp);
                    }

            }else if(root->left == NULL){
                temp = root->par;
                if(root == root->par->right){
                    root->par->right = root->right;
                    root->right->par = root->par;
                }else{
                    root->par->left = root->right;
                    root->right->par = root->par;
                }
                root->right = NULL;
                root->par = NULL;
                delete root;
                heightUpdate(temp);
                if(temp->par){
                    heightUpdate(temp->par);
                }
                if(temp!=NULL){
                        temp = BALANCE(temp);
                    }
            }else{
                SymNode *temp1 = MIN(root->right);

                root->key = temp1->key;
                root->address = temp1->address;
                
                if(temp1 == temp1->par->left){
                    temp1->par->left = NULL;
                    temp1->par = NULL;
                    delete temp1;
                }else{
                    temp1->par->right = NULL;
                    temp1->par = NULL;
                    delete temp1;
                }
                if(temp!=NULL){
                        temp = BALANCE(temp);
                    }
                BALANCE(root);

                SymNode* le = root->left;
                SymNode* ri = root->right;
                root->height = 1 + max(getHeight(le),getHeight(ri));
                heightUpdate(root);
                if(root->par){
                    heightUpdate(root->par);
                }
                heightUpdate(root->left);
                heightUpdate(root->right);
            }
        }
    }
}

void SymbolTable::remove(string k){
    
    if(search(k)==-2){
        return;
    }else{
        //remove karo
        SymNode* nod = get_root();
        REM(nod,k);
        heightUpdate(get_root());
        size--;
    }
}

SymNode* SEARCH(SymNode* node, string k){
    if(node == NULL){
        return NULL;
    }
    if(k==node->key){
        return node;
    }else if(k < node->key){
        return SEARCH(node->left,k);
    }else{
        return SEARCH(node->right,k);
    }
}

int SymbolTable::search(string k){
    SymNode* node = SEARCH(root,k);
    if(node==NULL){
        return -2;
    }else{
        return node->address;
    }
}

void ASS(SymNode* root, string k, int idx){
    if(root==NULL){
        return;
    }else if(root->key > k){
        ASS(root->left,k,idx);
    }else if(root->key < k){
        ASS(root->right,k,idx);
    }else{
        root->address = idx;
    }
}

void SymbolTable::assign_address(string k,int idx){
    if(root==NULL){
        return;
    }else{
        ASS(get_root(),k,idx);
    }
}

int SymbolTable::get_size(){
    return size;
}

SymNode* SymbolTable::get_root(){
    return root;
}

void d(SymNode* root){
    if(root != NULL){
        d(root->right);
        d(root->left);
        delete root;
    }
}

SymbolTable::~SymbolTable(){
    size=0;
    d(root);
}


