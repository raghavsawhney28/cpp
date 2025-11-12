#include <iostream>
#include <stack>
#include <cctype>
#include <cmath>
using namespace std;

// ---------------- Node Structure ----------------
struct Node {
    char value;
    Node* left;
    Node* right;
    
    Node(char val) {
        value = val;
        left = right = nullptr;
    }
};

// ---------------- Expression Tree Class ----------------
class ExpressionTree {
private:
    Node* root;

    bool isOperator(char c) {
        return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
    }

    double evaluate(Node* node) {
        if (!node)
            return 0;

        // Leaf node (operand)
        if (!node->left && !node->right)
            return node->value - '0';  // convert char to number

        // Evaluate left and right subtrees
        double leftVal = evaluate(node->left);
        double rightVal = evaluate(node->right);

        switch (node->value) {
            case '+': return leftVal + rightVal;
            case '-': return leftVal - rightVal;
            case '*': return leftVal * rightVal;
            case '/': return leftVal / rightVal;
            case '^': return pow(leftVal, rightVal);
        }
        return 0;
    }

    void inorder(Node* node) {
        if (node) {
            if (isOperator(node->value)) cout << "(";
            inorder(node->left);
            cout << node->value;
            inorder(node->right);
            if (isOperator(node->value)) cout << ")";
        }
    }

    void preorder(Node* node) {
        if (node) {
            cout << node->value << " ";
            preorder(node->left);
            preorder(node->right);
        }
    }

    void postorder(Node* node) {
        if (node) {
            postorder(node->left);
            postorder(node->right);
            cout << node->value << " ";
        }
    }

public:
    ExpressionTree() { root = nullptr; }

    // Build from postfix expression (e.g., "23*54*+9-")
    void buildFromPostfix(string postfix) {
        stack<Node*> st;
        for (char c : postfix) {
            if (isalnum(c)) {
                st.push(new Node(c));
            } else if (isOperator(c)) {
                Node* node = new Node(c);
                node->right = st.top(); st.pop();
                node->left = st.top(); st.pop();
                st.push(node);
            }
        }
        root = st.top();
    }

    void displayTraversals() {
        cout << "\nInorder (Infix): ";
        inorder(root);
        cout << "\nPreorder (Prefix): ";
        preorder(root);
        cout << "\nPostorder (Postfix): ";
        postorder(root);
        cout << "\n";
    }

    void evaluateExpression() {
        cout << "\nEvaluated Result: " << evaluate(root) << endl;
    }
};

// ---------------- Main Program ----------------
int main() {
    ExpressionTree tree;
    string postfix;

    cout << "Enter postfix expression (e.g., 23*54*+9-): ";
    cin >> postfix;

    tree.buildFromPostfix(postfix);

    cout << "\n--- Expression Tree Traversals ---\n";
    tree.displayTraversals();

    cout << "\n--- Evaluation ---";
    tree.evaluateExpression();

    return 0;
}
