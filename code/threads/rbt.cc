#include "debug.h"
#include "rbt.h"

using namespace std;

Node::Node(Thread* t) {
    this->thread= t;
    color = R;
    left = right = par = NULL;
}

RBT::RBT() {
    root = NULL;
}

bool RBT::IsEmpty() {
    return root == NULL;
}

int RBT::getColor(Node *&node) {
    if (node == NULL)
        return B;

    return node->color;
}

void RBT::setColor(Node *&node, int color) {
    if (node == NULL)
        return;

    node->color = color;
}

Node* RBT::insertTree(Node *&root, Node *&ptr) {
    if (root == NULL)
        return ptr;

    if (ptr->thread->getVrunTime() < root->thread->getVrunTime()) {
        root->left = insertTree(root->left, ptr);
        root->left->par = root;
    } else if (ptr->thread->getVrunTime() >= root->thread->getVrunTime()) {
        root->right = insertTree(root->right, ptr);
        root->right->par = root;
    }

    return root;
}

void RBT::insert(Thread* t) {
    // cout<< t->getName()<<endl;
    Node *node = new Node(t);
    root = insertTree(root, node);

    insertHelper(node);
    
}

void RBT::rotateLeft(Node *&ptr) {
    Node *rightChild = ptr->right;
    ptr->right = rightChild->left;

    if (ptr->right != NULL)
        ptr->right->par = ptr;

    rightChild->par = ptr->par;

    if (ptr->par == NULL)
        root = rightChild;
    else if (ptr == ptr->par->left)
        ptr->par->left = rightChild;
    else
        ptr->par->right = rightChild;

    rightChild->left = ptr;
    ptr->par = rightChild;
}

void RBT::rotateRight(Node *&ptr) {
    Node *leftChild = ptr->left;
    ptr->left = leftChild->right;

    if (ptr->left != NULL)
        ptr->left->par = ptr;

    leftChild->par = ptr->par;

    if (ptr->par == NULL)
        root = leftChild;
    else if (ptr == ptr->par->left)
        ptr->par->left = leftChild;
    else
        ptr->par->right = leftChild;

    leftChild->right = ptr;
    ptr->par = leftChild;
}

void RBT::insertHelper(Node *&ptr) {
    Node *par = NULL;
    Node *grandpar = NULL;
    while (ptr != root && getColor(ptr) == R && getColor(ptr->par) == R) {
        par = ptr->par;
        grandpar = par->par;
        if (par == grandpar->left) {
            Node *uncle = grandpar->right;
            if (getColor(uncle) == R) {
                setColor(grandpar, R);
                setColor(uncle, B);
                setColor(par, B);
                
                ptr = grandpar;
            } else {
                if (ptr == par->right) {
                    rotateLeft(par);
                    ptr = par;
                    par = ptr->par;
                }
                rotateRight(grandpar);
                swap(par->color, grandpar->color);
                ptr = par;
            }
        } else {
            Node *uncle = grandpar->left;
            if (getColor(uncle) == R) {
                setColor(par, B);
                setColor(uncle, B);
                setColor(grandpar, R);
                ptr = grandpar;
            } else {
                if (ptr == par->left) {
                    rotateRight(par);
                    ptr = par;
                    par = ptr->par;
                }
                rotateLeft(grandpar);
                swap(par->color, grandpar->color);
                ptr = par;
            }
        }
    }
    setColor(root, B);
}

void RBT::dequeueHelper(Node *&node) {
    if (node == NULL)
        return;

    if (node == root) {
        root = NULL;
        return;
    }

    if (getColor(node) == R || getColor(node->left) == R || getColor(node->right) == R) {
        Node *child = node->left != NULL ? node->left : node->right;

        if (node == node->par->left) {
            node->par->left = child;
            if (child != NULL)
                child->par = node->par;
            setColor(child, B);
            delete (node);
        } else {
            node->par->right = child;
            if (child != NULL)
                child->par = node->par;
            setColor(child, B);
            delete (node);
        }
    } else {
        Node *sib = NULL;
        Node *par = NULL;
        Node *ptr = node;
        setColor(ptr, DB);
        while (ptr != root && getColor(ptr) == DB) {
            par = ptr->par;
            if (ptr == par->left) {
                sib = par->right;
                if (getColor(sib) == R) {
                    setColor(sib, B);
                    setColor(par, R);
                    rotateLeft(par);
                } else {
                    if (getColor(sib->left) == B && getColor(sib->right) == B) {
                        setColor(sib, R);
                        if(getColor(par) == R)
                            setColor(par, B);
                        else
                            setColor(par, DB);
                        ptr = par;
                    } else {
                        if (getColor(sib->right) == B) {
                            setColor(sib->left, B);
                            setColor(sib, R);
                            rotateRight(sib);
                            sib = par->right;
                        }
                        setColor(sib, par->color);
                        setColor(par, B);
                        setColor(sib->right, B);
                        rotateLeft(par);
                        break;
                    }
                }
            } else {
                sib = par->left;
                if (getColor(sib) == R) {
                    setColor(sib, B);
                    setColor(par, R);
                    rotateRight(par);
                } else {
                    if (getColor(sib->left) == B && getColor(sib->right) == B) {
                        setColor(sib, R);
                        if (getColor(par) == R)
                            setColor(par, B);
                        else
                            setColor(par, DB);
                        ptr = par;
                    } else {
                        if (getColor(sib->left) == B) {
                            setColor(sib->right, B);
                            setColor(sib, R);
                            rotateLeft(sib);
                            sib = par->left;
                        }
                        setColor(sib, par->color);
                        setColor(par, B);
                        setColor(sib->left, B);
                        rotateRight(par);
                        break;
                    }
                }
            }
        }
        if (node == node->par->left)
            node->par->left = NULL;
        else
            node->par->right = NULL;
        delete(node);
        setColor(root, B);
    }
}


Thread* RBT::dequeue() {
    Node *ptr = root;

    while (ptr->left != NULL)
        ptr = ptr->left;

    Thread* temp = ptr->thread;
    
    dequeueHelper(ptr);
    
    return temp;


}

int RBT::getTreeLengthHelper(Node *&ptr) {

    if (ptr == NULL)
        return 0 ;
    
    return 1 + getTreeLengthHelper(ptr->left) + getTreeLengthHelper(ptr->right);

}

int RBT::getTreeLength() {

    return getTreeLengthHelper(root);
}

void RBT::printHelper(Node *&ptr) {
    if (ptr == NULL)
        return;
    
    printHelper(ptr->left);
    cout <<"Tick: "<< ptr->thread->getVrunTime() << " Name: " << ptr->thread->getName()<<" Color: "<< ptr->color<<endl;
    printHelper(ptr->right);
}

void RBT::print() {
    cout<< "==========TREE CONTENT==========\n";
    printHelper(root);
    cout<<endl;
}

