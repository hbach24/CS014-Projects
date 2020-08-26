#include "AVLTree.h"
//#include "Node.h"
#include<string>
#include<sstream>
#include<fstream>

AVLTree::AVLTree() {
    root = nullptr;
}
void AVLTree::visualizeTree(const string& outputFilename) {
    ofstream outFS(outputFilename.c_str());
    if (!outFS.is_open()) {
        cout << "Error" << endl;
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

void AVLTree::visualizeTree(ofstream& outFS, Node* n) {
    if (n) {
        if (n->left) {
            visualizeTree(outFS, n->left);
            outFS << n->data << " -> " << n->left->data << ";" << endl;
        }

        if (n->right) {
            visualizeTree(outFS, n->right);
            outFS << n->data << " -> " << n->right->data << ";" << endl;
        }
    }
}

int AVLTree::height(Node* node) const {
    int leftHeight = 0;
    int rightHeight = 0;
    if (node == nullptr) {
        return -1;
    }

    leftHeight = height(node->left);
    rightHeight = height(node->right);

    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    }
    else {
        return 1 + rightHeight;
    }
}

/*Return the balance factor of a given node.*/
int AVLTree::balanceFactor(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    int leftHeight = -1;
    if (node->left != nullptr) {
        leftHeight = height(node->left);
    }
    int rightHeight = -1;
    if (node->right != nullptr) {
        rightHeight = height(node->right);
    }
    return leftHeight - rightHeight;
   
    //zyBooks Figure 7.2.1
}

void AVLTree::printBalanceFactors(Node* node) {
    if (node != nullptr) {
        printBalanceFactors(node->left);
        cout << node->data <<  "(" << balanceFactor(node) << "), ";
        printBalanceFactors(node->right);
        
    }
}
/*Traverse and print the tree in inorder notation. Print the string followed by
    its balance factor in parentheses followed by a , and one space.*/
void AVLTree::printBalanceFactors() {
    rotate(root);
    printBalanceFactors(root);
}

/*Insert an item to the binary search tree and perform rotation if necessary.*/
void AVLTree::insert(const string& newString) {
    Node* newNode = new Node(newString);
    if (root == nullptr) {
        root = newNode;
        return;
    }
    
    Node* curr = root;
    while (curr != nullptr) {
        if (newNode->data == curr->data) {
            return;
        }
        if (newNode->data < curr->data) {
            if (curr->left == nullptr) {
                curr->left = newNode;
                curr = nullptr;
            }
            else {
                curr = curr->left;
            }
        }

        else if (newNode->data > curr->data) {
            if (curr->right == nullptr) {
                curr->right = newNode;
                curr = nullptr;
            }
            else {
                curr = curr->right;
            }
        }
    }
    while (newNode != nullptr) {
        rotate(newNode);
        newNode = getParentNode(newNode);
    }
    rotate(newNode);
}

/*Find and return the closest unbalanced node (with balance factor of 2 or -2) to the inserted node.*/
Node* AVLTree::findUnbalancedNode(Node* node) {
    //return root;
    
    Node* curr = node;
    while (curr != nullptr) {
        if (balanceFactor(curr) >= 2 || balanceFactor(curr) <= -2) {
            return curr;
        }
        else {
            curr = getParentNode(curr);
        }
    }
    return nullptr;
 }

void AVLTree::rotate(Node* node) {
    
    if (balanceFactor(node) == 2) {
        if (balanceFactor(node->left) == -1) {
            rotateLeft(node->left);
        }
        rotateRight(node);
    }
    else if (balanceFactor(node) == -2) {
        if (balanceFactor(node->right) == 1) {
            rotateRight(node->right);
        }
        rotateLeft(node);
    }
    }


void AVLTree::rotateRight(Node* node) {
    
    Node* leftRightChild = node->left->right;
    if (getParentNode(node) == nullptr) { //if node is a root
        root = node->left;
    }
    else {
        replaceChild(getParentNode(node), node, node->left);
    }
    setChild(node->left, "right", node);
    setChild(node, "left", leftRightChild);

}

void AVLTree::rotateLeft(Node* node) {
    Node* rightLeftChild = node->right->left;
    
    if (getParentNode(node) == nullptr)
    {
        root = node->right;
    }
    else 
    {
        replaceChild(getParentNode(node), node, node->right);
    }
   
    setChild(node->right, "left", node);
    setChild(node, "right", rightLeftChild);
    /* node->left = node;
    node->right = rightLeftChild;*/
}

Node* AVLTree::getParentNode(Node* node) {
    //Node* node = nodeLoc(key);
    Node* curr = root;
    Node* parent = nullptr;

    while (curr != node) {
        if (curr->data < node->data) {
            if (curr->right != node) {
                curr = curr->right;
            }
            else {
                parent = curr;
                break;
            }
        }
        else {
            if (curr->left != node) {
                curr = curr->left;
            }
            else
            {
                parent = curr;
                break;
            }
        }
    }
    return parent;
}

void AVLTree::setChild(Node* parent, string whichChild, Node* child) {
    //Node* parent = nullptr;
    if (whichChild == "left") {
        parent->left = child;
    }
    else {
        parent->right = child;
            if (child != nullptr) {
                Node* parent = getParentNode(child);
                parent = parent;
            }
    }
}

void AVLTree::replaceChild(Node* parent, Node* currentChild, Node* newChild) {
    if (parent->left == currentChild) {
        return setChild(parent, "left", newChild);
    }
    else if (parent->right == currentChild) {
        setChild(parent, "right", newChild);
    }

}