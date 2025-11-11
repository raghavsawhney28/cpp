#include <iostream>
using namespace std;

// -------------------------
// Node structure
// -------------------------
struct Node {
    int key;
    Node* left;
    Node* right;
    int height;
};

// -------------------------
// Utility functions
// -------------------------
int height(Node* N) {
    return (N == nullptr) ? 0 : N->height;
}

int max(int a, int b) {
    return (a > b)? a : b;
}

Node* newNode(int key) {
    Node* node = new Node();
    node->key = key;
    node->left = node->right = nullptr;
    node->height = 1;  // new node is initially at leaf
    return node;
}

// -------------------------
// Rotations
// -------------------------
Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

int getBalance(Node* N) {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

// -------------------------
// Insertion
// -------------------------
Node* insert(Node* node, int key) {
    // 1. Normal BST insert
    if (node == nullptr)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else
        return node;  // No duplicates

    // 2. Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // 3. Get balance factor
    int balance = getBalance(node);

    // 4. Balancing cases
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);  // Left Left
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);   // Right Right
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);  // Left Right
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);   // Right Left
    }

    return node;
}

// -------------------------
// Find node with minimum value (used in deletion)
// -------------------------
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// -------------------------
// Deletion
// -------------------------
Node* deleteNode(Node* root, int key) {
    // 1. Normal BST deletion
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        // Node with one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp; // Copy contents

            delete temp;
        } else {
            // Node with two children
            Node* temp = minValueNode(root->right);
            root->key = temp->key;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    // If the tree had only one node
    if (root == nullptr)
        return root;

    // 2. Update height
    root->height = 1 + max(height(root->left), height(root->right));

    // 3. Get balance factor
    int balance = getBalance(root);

    // 4. Rebalance the tree

    // Left Left
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

// -------------------------
// Traversal functions
// -------------------------
void preOrder(Node* root) {
    if (root != nullptr) {
        cout << root->key << " ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

// -------------------------
// Main Function
// -------------------------
int main() {
    Node* root = nullptr;

    // Example case: insertion
    int keys[] = {10, 20, 30, 40, 50, 25};
    for (int key : keys)
        root = insert(root, key);

    cout << "Preorder traversal of the constructed AVL tree:\n";
    preOrder(root);

    // Example case: deletion
    cout << "\n\nDeleting 40...\n";
    root = deleteNode(root, 40);

    cout << "Preorder traversal after deletion:\n";
    preOrder(root);

    return 0;
}
