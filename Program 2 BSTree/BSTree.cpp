#include "BSTree.h"
#include<iostream>

using namespace std;

BSTree::BSTree() {
	root = nullptr; 
}

BSTree::~BSTree() {
	delete root;
}


/* Search for a string in the binary search tree.
       It should return true if the string is in the tree, and false otherwise.
     */
bool BSTree::search(const string& key) const {
    if (root == nullptr) {
        return false;
    }
    return search(key, root);
    
}
bool BSTree::search(const string& key, Node* curr) const {
    if (curr == nullptr) {
        return false;
    }
    if (curr->getString() == key) {
        return true;
    }
    else if (curr->getString() < key) {
            return search(key, curr->getRight());
    }
    else 
            return search(key, curr->getLeft());
    
}


void BSTree::inOrder(Node* curr) const{
    if (curr != nullptr) {
        inOrder(curr->getLeft());
        cout << curr->getString() << "(" << curr->getCount() << "), ";
        inOrder(curr->getRight());
    }
}

void BSTree::inOrder() const {
    inOrder(root);
}

/* Find and return the largest value in the tree. Return an empty string if the tree is empty */

string BSTree::largest() const {
    Node* curr = root;
    Node* large = nullptr;

    if (root == nullptr) {
        return "";
    }

    while (curr != nullptr) {
        large = curr;
        curr = curr->getRight();
    }
    //if (large != nullptr) {
        return large->getString();
    //}
}

/* Find and return the smallest value in the tree. Return an emtpy string if the tree is empty */
string BSTree::smallest() const {
    Node* curr = root;
    Node* small = nullptr;

    if (root == nullptr) {
        return "";
    }

    while (curr != nullptr) {
        small = curr;
        curr = curr->getLeft();
    }
        return small->getString();
   
}

void BSTree::preOrder() const {
    preOrder(root);
}

void BSTree::preOrder(Node* curr) const {
    if (curr == nullptr) {
        return;
    }

    if (curr != nullptr) {
        cout << curr->getString() << "(" << curr->getCount() << "), ";
        preOrder(curr->getLeft());
        preOrder(curr->getRight());
    }
}

void BSTree::postOrder() const {
    postOrder(root);
}

void BSTree::postOrder(Node* curr) const {
    if (curr == nullptr) {
        return;
    }
    if (curr != nullptr) {
        postOrder(curr->getLeft());
        postOrder(curr->getRight());
        cout << curr->getString() << "(" << curr->getCount() << "), ";
    }
}
/*BSTGetHeight(node) {
   if (node is null)
      return -1

   leftHeight = BSTGetHeight(node->left)
   rightHeight = BSTGetHeight(node->right)
   return 1 + max(leftHeight, rightHeight)
}*/
/* Compute and return the height of a particular string in the tree.
      The height of a leaf node is 0 (count the number of edges on the longest path).
      Return -1 if the string does not exist.
    */
int BSTree::height(const string& key) const {
    if (!search(key)) {
        return -1;
    }
        Node* node = nodeLoc(key);
    
   return height(node, key);
}

int BSTree::height(Node* curr, const string key) const {
    
    int leftHeight = 0;
    int rightHeight = 0;
    if (curr == nullptr) {
        return -1;
    }

        leftHeight = height(curr->getLeft(), key);

        rightHeight = height(curr->getRight(), key);
    if (leftHeight > rightHeight) {
        return 1 + leftHeight;
    }
    else {
        return 1 + rightHeight;
    }

}

Node* BSTree::nodeLoc(const string& key) const {
    Node* curr = root;

    while (curr != nullptr) {
        if (key == curr->getString()) {
            return curr;
        }
        else if (key < curr->getString()) {
            curr = curr->getLeft();
        }
        else {
            curr = curr->getRight();
        }
    }
    return nullptr;
}
/* Insert an item into the binary search tree.
       Be sure to keep BST properties.
       When an item is first inserted into the tree the count should be set to 1.
       When adding a duplicate string (case sensitive), rather than adding another node,
       the count variable should be incremented
     */
void BSTree::insert(const string& newString) {
    Node* newNode = new Node(newString);
    if (root == nullptr) {
        root = newNode;
        return;
    }

    Node* curr = root;
    while (curr != nullptr) {
        if (newNode->getString() == curr->getString()) {
            int count = curr->getCount();
            count++;
            curr->setCount(count);
            return;
        }
        if (newNode->getString() < curr->getString()) {
            if (curr->getLeft() == nullptr) {
                curr->setLeft(newNode);
                curr = nullptr;
            }
            else {
                curr = curr->getLeft();
            }
        }

        else if (newNode->getString() > curr->getString()) {
            if (curr->getRight() == nullptr) {
                curr->setRight(newNode);
                curr = nullptr;
            }
            else {
                curr = curr->getRight();
            }
        }
    }
    //newNode->setLeft(nullptr); //seg fault?
    //newNode->setRight(nullptr); // seg fault?

   
}


/* Remove a specified string from the tree.
       Be sure to maintain all bianry search tree properties.
       If removing a node with a count greater than 1, just decrement the count, otherwise,
       if the count is simply 1, remove the node.
        You MUST follow the remove algorithm shown in the slides and discussed in class or else
        your program will not pass the test functions.
        When removing,
            if removing a leaf node, simply remove the leaf. Otherwise,
            if the node to remove has a left child, replace the node to remove with the largest
            string value that is smaller than the current string to remove
            (i.e. find the largest value in the left subtree of the node to remove).
            If the node has no left child, replace the node to remove with the smallest value
            larger than the current string to remove
            (i.e. find the smallest value in the right subtree of the node to remove.
     */
void BSTree::remove(const string& key) {
    if (!search(key)) {
        return;
    }
    Node* node = nodeLoc(key);
    //Node* parent = nullptr;

    if (root == nullptr) {
        return;
    }
    if (node->getCount() > 1) {
        int count = (node->getCount()) - 1;
        node->setCount(count);
        return;
    }

    remove(key, node);
}

/* When removing,
            if removing a leaf node, simply remove the leaf. Otherwise,
            
            case 2: if the node to remove has a left child, replace the node to remove with the largest
            string value that is smaller than the current string to remove <-- SUCCESSOR
(i.e. find the largest value in the left subtree of the node to remove, PREDECESSOR).

            case 3: If the node has no left child, replace the node to remove with the smallest value
            larger than the current string to remove <-- SUCCESSOR
(i.e. find the smallest value in the right subtree of the node to remove, SUCCESSOR)*/

void BSTree::remove(const string& key, Node* curr) {
    if (curr == nullptr) {
        return;
    }

    if (key == curr->getString() && (curr->getLeft() == nullptr && curr->getRight() == nullptr)) {
        if (curr->getCount() > 1) {
            curr->setCount(curr->getCount() - 1);
        }

        else {
            Node* beforeCurr = root;

            while (beforeCurr->getRight() != curr && beforeCurr->getLeft() != curr) {
                if (key > beforeCurr->getString()) {
                    beforeCurr = beforeCurr->getRight();
                }
                else {
                    beforeCurr = beforeCurr->getLeft();
                }
                if (beforeCurr == nullptr) {
                    break;
                }
            }
            if (beforeCurr != nullptr) {
                if (beforeCurr->getRight() == curr) {
                    beforeCurr->setRight(nullptr);
                }
                else if (beforeCurr->getLeft() == curr) {
                    beforeCurr->setLeft(nullptr);
                }
            }

            Node* toDelete = curr;
            if (curr == root) {
                root = nullptr;
            }
            curr = nullptr;
            delete toDelete;



        }


    }
    else if (key == curr->getString() && curr->getCount() > 1) {
        curr->setCount(curr->getCount());
    }
    else if (key == curr->getString() && curr->getLeft()!= nullptr) {
        if (curr == root && curr->getRight() == nullptr) {
            root = curr->getLeft();
            delete curr;
            curr = nullptr;
            return;
        }

        string replace;
        int replaceCount;
        Node* findReplace = curr->getLeft();

        while (findReplace->getRight() != nullptr) {
            findReplace = findReplace->getRight();
        }

        replace = findReplace->getString();
        replaceCount = findReplace->getCount();

        remove(replace, findReplace);

        curr->setString(replace); //data = replace;
        curr->setCount(replaceCount); // = replaceCount;
    }
    else if (key == curr->getString() && curr->getRight() != nullptr) {
        if (curr == root && curr->getLeft() == nullptr) {
            root = curr->getRight();
            delete curr;
            curr = nullptr;
            return;
        }

        string replace;
        int replaceCount;
        Node* findReplace = curr->getRight();

        while (findReplace->getLeft() != nullptr) {
            findReplace = findReplace->getLeft();
        }

        replace = findReplace->getString();
        replaceCount = findReplace->getCount();

        remove(replace, findReplace);

        curr->setString(replace);
        curr->setCount(replaceCount);
    }
    else if (key > curr->getString()) {
        remove(key, curr->getRight());
    }
    else if (key < curr->getString()) {
        remove(key, curr->getLeft());
    }

    return;
}


//(i.e. find the smallest value in the right subtree of the node to remove, SUCCESSOR)
Node* BSTree::successor(Node* node) {
    Node* curr = node;
    if (node->getLeft() == nullptr) {
        return curr;
    }
    else {
        while (curr != nullptr) {
            if (curr->getLeft() == nullptr) {
                return curr;
            }
            else {
                curr = curr->getLeft();
            }
        }
    }
    return curr;
}

//(i.e.find the largest value in the left subtree of the node to remove, PREDECESSOR).
Node* BSTree::predecessor(Node* node) {
    Node* curr = node;
    if (node->getRight() == nullptr) {
        return curr;
    }
    else {
        while (curr != nullptr) {
            if (curr->getRight() == nullptr) {
                return curr;
            }
            else {
                curr = curr->getRight();
            }
        }
    }
    return curr;
}

Node* BSTree::getParent(const string& key) {
    Node* node = nodeLoc(key);
    Node* curr = root;
    Node* parent = nullptr;
    
    while (curr != node) {
        if (curr->getString() < key) {
            if (curr->getRight() != node) {
                curr = curr->getRight();
            }
            else {
                parent = curr;
                break;
            }
        }
        else {
            if (curr->getLeft() != node) {
                curr = curr->getLeft();
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
Node* BSTree::getParentNode(Node* node) {
    //Node* node = nodeLoc(key);
    Node* curr = root;
    Node* parent = nullptr;

    while (curr != node) {
        if (curr->getString() < node->getString()) {
            if (curr->getRight() != node) {
                curr = curr->getRight();
            }
            else {
                parent = curr;
                break;
            }
        }
        else {
            if (curr->getLeft() != node) {
                curr = curr->getLeft();
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
