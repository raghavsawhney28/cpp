// bst.cpp
#include <bits/stdc++.h>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;
    Node(int k): key(k), left(nullptr), right(nullptr) {}
};

Node* insert(Node* root,int key){
    if(!root) return new Node(key);
    if(key < root->key) root->left = insert(root->left,key);
    else if(key > root->key) root->right = insert(root->right,key);
    // duplicates ignored
    return root;
}

Node* minNode(Node* n){ while(n && n->left) n=n->left; return n; }

Node* deleteNode(Node* root, int key){
    if(!root) return root;
    if(key < root->key) root->left = deleteNode(root->left, key);
    else if(key > root->key) root->right = deleteNode(root->right, key);
    else{
        if(!root->left){
            Node* r = root->right; delete root; return r;
        } else if(!root->right){
            Node* l = root->left; delete root; return l;
        } else {
            Node* succ = minNode(root->right);
            root->key = succ->key;
            root->right = deleteNode(root->right, succ->key);
        }
    }
    return root;
}

bool search(Node* root, int key){
    if(!root) return false;
    if(root->key==key) return true;
    return key < root->key ? search(root->left,key) : search(root->right,key);
}

void inorder(Node* root, vector<int>& out){
    if(!root) return;
    inorder(root->left,out);
    out.push_back(root->key);
    inorder(root->right,out);
}
void preOrder(Node* root){ if(!root) return; cout<<root->key<<" "; preOrder(root->left); preOrder(root->right); }
void postOrder(Node* root){ if(!root) return; postOrder(root->left); postOrder(root->right); cout<<root->key<<" "; }

int kthSmallest(Node* root,int k){
    vector<int> arr; inorder(root,arr);
    if(k<=0 || k> (int)arr.size()) throw runtime_error("k out of range");
    return arr[k-1];
}

int main(){
    Node* root = nullptr;
    int choice;
    while(true){
        cout<<"\n--- BST MENU ---\n1.Insert\n2.Delete\n3.Search\n4.Display (in/pre/post)\n5.K-th smallest\n0.Exit\nChoice: ";
        if(!(cin>>choice)) break;
        if(choice==0) break;
        if(choice==1){ int x; cout<<"Insert: "; cin>>x; root = insert(root,x); }
        else if(choice==2){ int x; cout<<"Delete: "; cin>>x; root = deleteNode(root,x); }
        else if(choice==3){ int x; cout<<"Search: "; cin>>x; cout<<(search(root,x)?"Found\n":"Not Found\n"); }
        else if(choice==4){
            cout<<"Inorder: "; vector<int> v; inorder(root,v); for(int a:v) cout<<a<<" "; cout<<"\n";
            cout<<"Preorder: "; preOrder(root); cout<<"\n";
            cout<<"Postorder: "; postOrder(root); cout<<"\n";
        } else if(choice==5){
            int k; cout<<"k: "; cin>>k;
            try{ cout<<kthSmallest(root,k)<<"\n"; } catch(exception& e){ cout<<e.what()<<"\n"; }
        } else cout<<"Invalid\n";
    }
    return 0;
}
