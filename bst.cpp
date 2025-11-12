#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
};

// Function to create a new node
Node* createNode(int value) {
    Node* newNode = new Node();
    newNode->data = value;
    newNode->left = newNode->right = nullptr;
    return newNode;
}

// Insertion in BST
Node* insertNode(Node* root, int value) {
    if (root == nullptr)
        return createNode(value);
    if (value < root->data)
        root->left = insertNode(root->left, value);
    else if (value > root->data)
        root->right = insertNode(root->right, value);
    return root;
}

// Find minimum node (used in deletion)
Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Deletion in BST
Node* deleteNode(Node* root, int key) {
    if (root == nullptr)
        return root;

    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one or no child
        if (root->left == nullptr) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (root->right == nullptr) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Node with two children
        Node* temp = findMin(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Searching in BST
bool search(Node* root, int key) {
    if (root == nullptr)
        return false;
    if (root->data == key)
        return true;
    else if (key < root->data)
        return search(root->left, key);
    else
        return search(root->right, key);
}

// Traversals
void inorder(Node* root) {
    if (root != nullptr) {
        inorder(root->left);
        cout << root->data << " ";
        inorder(root->right);
    }
}

void preorder(Node* root) {
    if (root != nullptr) {
        cout << root->data << " ";
        preorder(root->left);
        preorder(root->right);
    }
}

void postorder(Node* root) {
    if (root != nullptr) {
        postorder(root->left);
        postorder(root->right);
        cout << root->data << " ";
    }
}

// Find Kth smallest element
void kthSmallest(Node* root, int &k, int &result) {
    if (root == nullptr)
        return;
    kthSmallest(root->left, k, result);
    if (--k == 0) {
        result = root->data;
        return;
    }
    kthSmallest(root->right, k, result);
}

// ------------------------
// Main menu
// ------------------------
int main() {
    Node* root = nullptr;
    int choice, val, k, result;

    while (true) {
        cout << "\n===== BINARY SEARCH TREE MENU =====\n";
        cout << "1. Insert\n";
        cout << "2. Delete\n";
        cout << "3. Search\n";
        cout << "4. Traversals\n";
        cout << "5. Kth Smallest Element\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value to insert: ";
                cin >> val;
                root = insertNode(root, val);
                cout << "Inserted.\n";
                break;

            case 2:
                cout << "Enter value to delete: ";
                cin >> val;
                root = deleteNode(root, val);
                cout << "Deleted if found.\n";
                break;

            case 3:
                cout << "Enter value to search: ";
                cin >> val;
                if (search(root, val))
                    cout << "Value found in BST.\n";
                else
                    cout << "Value not found.\n";
                break;

            case 4:
                cout << "Inorder (Sorted): ";
                inorder(root);
                cout << "\nPreorder: ";
                preorder(root);
                cout << "\nPostorder: ";
                postorder(root);
                cout << endl;
                break;

            case 5:
                cout << "Enter k (for Kth smallest): ";
                cin >> k;
                result = -1;
                kthSmallest(root, k, result);
                if (result != -1)
                    cout << "Kth smallest element: " << result << endl;
                else
                    cout << "Less than k elements in tree.\n";
                break;

            case 6:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice! Try again.\n";
        }
    }
}