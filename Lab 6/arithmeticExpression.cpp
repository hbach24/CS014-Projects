#include "arithmeticExpression.h"
#include <sstream>
#include <fstream>
#include <stack>
#include<string>
using namespace std;

int arithmeticExpression::priority(char op) {
    int priority = 0;
    if (op == '(') {
        priority = 3;
    }
    else if (op == '*' || op == '/') {
        priority = 2;
    }
    else if (op == '+' || op == '-') {
        priority = 1;
    }
    return priority;
}

string arithmeticExpression::infix_to_postfix() {
    stack<char> s;
    ostringstream oss;
    char c;
    for (unsigned i = 0; i < infixExpression.size(); ++i) {
        c = infixExpression.at(i);
        if (c == ' ') {
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '(' || c == ')') { //c is an operator
            if (c == '(') {
                s.push(c);
            }
            else if (c == ')') {
                while (s.top() != '(') {
                    oss << s.top();
                    s.pop();
                }
                s.pop();
            }
            else {
                while (!s.empty() && priority(c) <= priority(s.top())) {
                    if (s.top() == '(') {
                        break;
                    }
                    oss << s.top();
                    s.pop();
                }
                s.push(c);
            }
        }
        else { //c is an operand
            oss << c;
        }
    }
    while (!s.empty()) {
        oss << s.top();
        s.pop();
    }
    return oss.str();
}

/* Calls the recursive visualizeTree function and generates the .png file using system call. */
void arithmeticExpression::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error opening " << outputFilename << endl;
        return;
    }
    outFS << "digraph G {" << endl;
    visualizeTree(outFS, root);
    outFS << "}";
    outFS.close();
    string jpgFilename = outputFilename.substr(0, outputFilename.size() - 4) + ".jpg";
    string command = "dot -Tjpg " + outputFilename + " -o " + jpgFilename;
    system(command.c_str());
}
arithmeticExpression::arithmeticExpression(const string& s) {
    root = nullptr;
    infixExpression = s;
}

/* Calls the recursive infix function. */
void arithmeticExpression::infix() {
    infix(root);
}

/* Helper function that outputs the infix notation of the arithmetic expression tree
       by performing the inorder traversal of the tree.
       An opening and closing parenthesis must be added at the
       beginning and ending of each expression. */
void arithmeticExpression::infix(TreeNode* node) {
    if (node == nullptr) {
        return;
    }
    if (node->left != nullptr) {
        cout << "(";
    }
        
    infix(node->left);
    cout << node->data;
    infix(node->right);
    
    if (node->right != nullptr) {
        cout << ")";
    }
    
}

/* Calls the recursive prefix function. */
void arithmeticExpression::prefix() {
    prefix(root);
}

/* Helper function that outputs the prefix notation of the arithmetic expression tree
       by performing the preorder traversal of the tree. */
void arithmeticExpression::prefix(TreeNode* node) {
    if (node != nullptr) {
        cout << node->data;
        prefix(node->left);
        prefix(node->right);
    }
}

/* Calls the recursive postfix function. */
void arithmeticExpression::postfix() {
    postfix(root);
}

/* Helper function that outputs the postfix notation of the arithmetic expression tree
       by performing the postorder traversal of the tree. */
void arithmeticExpression::postfix(TreeNode* node) {
    if (node != nullptr) {
        postfix(node->left);
        postfix(node->right);
        cout << node->data;
    }
}

/* Converts the infixExpression to its equivalent postfix string
         and then generates the tree and assigns the root node to the
         root data field. The key for the first node is 'a', 'b' for the second node and so on. */
void arithmeticExpression::buildTree() {
    string post = infix_to_postfix();
    char key = 'a';
    stack<TreeNode*> s;

    for (unsigned i = 0; i < post.size(); i++) {
        TreeNode* node = new TreeNode(post.at(i), key);
        if (priority(node->data) != 0) {
            TreeNode* rNode = s.top();
            s.pop();
            TreeNode* lNode = s.top();
            s.pop();
            node->left = lNode;
            node->right = rNode;
        }
        s.push(node);
        key++;
    }
    root = s.top();
}
/* Helper function for generating the dotty file. This is a recursive function. */
void arithmeticExpression::visualizeTree(ofstream& fout, TreeNode* node) {
    //visualizeTree()
    if (node != nullptr) {
        if (node->left != nullptr) {
            fout << node->key << " [ label = " << "\"" << node->data << "\"" << "];" << endl;
            fout << node->left->key << " [ label = " << "\"" << node->left->data << "\"" << "];" << endl;
            fout << node->key << " -> " << node->left->key << endl;
            if (node->right != nullptr) {
                fout << node->right->key << " [ label = " << "\"" << node->right->data << "\"" << "];" << endl;
                fout << node->key << " -> " << node->right->key << endl;
                visualizeTree(fout, node->left);
                visualizeTree(fout, node->right);
            }
            else {
                visualizeTree(fout, node->left);
            }
        }
        else {
            if (node->right != nullptr) {
                fout << node->key << " [ label = " << "\"" << node->data << "\"" << "];" << endl;
                fout << node->right->key << " [ label = " << "\"" << node->right->data << "\"" << "];" << endl;
                fout << node->key << " -> " << node->right->key << endl;
                visualizeTree(fout, node->right);
            }
        }
    }
}

//void arithmeticExpression::visualizeTree(const string& outputFilename) {