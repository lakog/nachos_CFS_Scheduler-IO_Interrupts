#ifndef RED_BLACK_TREE_RBT_H
#define RED_BLACK_TREE_RBT_H

#include "thread.h"

enum Color {R, B, DB};

struct Node
{
    Thread* thread;
    int color;
    Node *left, *right, *par;

    explicit Node(Thread*);
};

class RBT
{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void insertHelper(Node *&);
        void dequeueHelper(Node *&);
        int getTreeLengthHelper(Node *&);
        void printHelper(Node *&);
        Node* insertTree(Node *&, Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);

    public:
        RBT();
        int getTreeLength();

        void insert(Thread*);
        Thread* dequeue();       
        void print();
        bool IsEmpty();
};


#endif //RED_BLACK_TREE_RBT_H