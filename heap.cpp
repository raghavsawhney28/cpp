#include <iostream>
#include <queue>
using namespace std;

// ---------------- Node Structure ----------------
struct Node {
    int data;
    int priority;
    Node* left;
    Node* right;
    
    Node(int d, int p) {
        data = d;
        priority = p;
        left = right = nullptr;
    }
};

// ---------------- Helper Class ----------------
class PriorityQueue {
private:
    Node* root;
    bool isMinHeap;

    // For heapifying up and down (recursive)
    Node* insertNode(Node* root, int data, int priority) {
        if (root == nullptr)
            return new Node(data, priority);

        // Insert according to priority
        if (isMinHeap) {
            if (priority < root->priority)
                root->left = insertNode(root->left, data, priority);
            else
                root->right = insertNode(root->right, data, priority);
        } else {
            if (priority > root->priority)
                root->left = insertNode(root->left, data, priority);
            else
                root->right = insertNode(root->right, data, priority);
        }

        return root;
    }

    Node* findExtrema(Node* node) {
        if (node == nullptr)
            return nullptr;

        Node* current = node;
        if (isMinHeap)
            while (current->left != nullptr)
                current = current->left;
        else
            while (current->left != nullptr)
                current = current->left;

        return current;
    }

    Node* deleteNode(Node* root, int priority) {
        if (root == nullptr)
            return root;

        if (isMinHeap) {
            if (priority < root->priority)
                root->left = deleteNode(root->left, priority);
            else if (priority > root->priority)
                root->right = deleteNode(root->right, priority);
            else {
                if (root->left == nullptr) {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                } else if (root->right == nullptr) {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }

                Node* temp = findExtrema(root->right);
                root->priority = temp->priority;
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->priority);
            }
        } else {
            if (priority > root->priority)
                root->left = deleteNode(root->left, priority);
            else if (priority < root->priority)
                root->right = deleteNode(root->right, priority);
            else {
                if (root->left == nullptr) {
                    Node* temp = root->right;
                    delete root;
                    return temp;
                } else if (root->right == nullptr) {
                    Node* temp = root->left;
                    delete root;
                    return temp;
                }

                Node* temp = findExtrema(root->right);
                root->priority = temp->priority;
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->priority);
            }
        }

        return root;
    }

    void inorder(Node* root) {
        if (root != nullptr) {
            inorder(root->left);
            cout << "(" << root->data << ", P:" << root->priority << ") ";
            inorder(root->right);
        }
    }

public:
    PriorityQueue(bool minHeap = true) {
        root = nullptr;
        isMinHeap = minHeap;
    }

    void insert(int data, int priority) {
        root = insertNode(root, data, priority);
    }

    void remove(int priority) {
        root = deleteNode(root, priority);
    }

    void display() {
        cout << (isMinHeap ? "MinHeap" : "MaxHeap") << " Priority Queue:\n";
        inorder(root);
        cout << "\n";
    }

    void getTop() {
        if (root == nullptr) {
            cout << "Queue is empty.\n";
            return;
        }

        Node* top = findExtrema(root);
        cout << "Top element -> Data: " << top->data
             << ", Priority: " << top->priority << "\n";
    }
};

// ---------------- Main Menu ----------------
int main() {
    int choice;
    PriorityQueue pq_min(true);   // Min Heap based Priority Queue
    PriorityQueue pq_max(false);  // Max Heap based Priority Queue

    do {
        cout << "\n--- Priority Queue Menu ---\n";
        cout << "1. Insert (Min Heap)\n";
        cout << "2. Insert (Max Heap)\n";
        cout << "3. Delete (Min Heap)\n";
        cout << "4. Delete (Max Heap)\n";
        cout << "5. Display (Min Heap)\n";
        cout << "6. Display (Max Heap)\n";
        cout << "7. Get Top (Min Heap)\n";
        cout << "8. Get Top (Max Heap)\n";
        cout << "9. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        int data, priority;

        switch (choice) {
        case 1:
            cout << "Enter data & priority: ";
            cin >> data >> priority;
            pq_min.insert(data, priority);
            break;
        case 2:
            cout << "Enter data & priority: ";
            cin >> data >> priority;
            pq_max.insert(data, priority);
            break;
        case 3:
            cout << "Enter priority to delete: ";
            cin >> priority;
            pq_min.remove(priority);
            break;
        case 4:
            cout << "Enter priority to delete: ";
            cin >> priority;
            pq_max.remove(priority);
            break;
        case 5:
            pq_min.display();
            break;
        case 6:
            pq_max.display();
            break;
        case 7:
            pq_min.getTop();
            break;
        case 8:
            pq_max.getTop();
            break;
        case 9:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice.\n";
        }
    } while (choice != 9);

    return 0;
}
