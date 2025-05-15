#include "simplebintree.h"
#include <stddef.h>
#include <QDebug>
BinTree::Node* BinTree::insert(Node *x, Node *z)
{
    if( !x ) {
        root = new Node(z->key, z->name);
        return root;
    }

    if( z->key<x->key )
        x->left = insert(x->left,z);
    else
        x->right = insert(x->right,z);
    return balance(x);
}
BinTree::Node* BinTree::deleteNode(Node *x, size_t id) {
    if (!x) return nullptr;

    if (id < x->key) {
        x->left = deleteNode(x->left, id);
        if (x->left) x->left->parent = x;
    } else if (id > x->key) {
        x->right = deleteNode(x->right, id);
        if (x->right) x->right->parent = x;
    } else {
        if (x->left == nullptr && x->right == nullptr) {
            if (x->key == root->key) {
                root = nullptr;
                //qDebug () << root;
            }
            delete x;
            return nullptr;
        }
        Node* q = x->left;
        Node* r = x->right;
        Node* parent = x->parent;

        if (!r) {
            if (q) q->parent = parent;
            delete x;
            return q;
        }

        if (!q) {
            if (r) r->parent = parent;
            delete x;
            return r;
        }

        Node* min = findMin(r);
        x->key = min->key;
        x->name = min->name;
        x->right = deleteNode(r, min->key);
        if (x->right) x->right->parent = x;
        return balance(x);
    }

    return balance(x);
}
BinTree::BinTree()
{
    root = nullptr;
}

BinTree::~BinTree()
{
    deleteSubtree(root);
}

void BinTree::insertion(size_t id, QString name)
{
    Node *newNode = new Node(id, name);
    root = insert(root, newNode);
}

QString BinTree::findByID(size_t id)
{
    return findByKey(root, id);
}

void BinTree::deleteByID(size_t id)
{
    root = deleteNode(root, id);
   // qDebug() << "new root after deletion : " << root->key;
}

size_t BinTree::findMinKey(Node *t) {
    while (t->left != nullptr) {
        t = t->left;
    }
    return t->key;
}

QString BinTree::findByKey(Node *x, size_t key)
{
    if (x==nullptr) return "no such tree";

    if (x->key==key) return x->name;
    else {
        if (key>x->key && x->right!=nullptr) {
            return findByKey(x->right, key);
        }
        else if (key<x->key && x->left!=nullptr) {
            return findByKey(x->left, key);
        }
        else return "no such key in tree";
    }
}

size_t BinTree::getHeight(Node *x)
{
    return x==nullptr? 0 : x->height;
}

int BinTree::balanceFactor(Node *x)
{
    return getHeight(x->right)-getHeight(x->left);
}

void BinTree::fixHeight(Node *x)
{
    size_t h1 = getHeight(x->left);
    size_t h2 = getHeight(x->right);
    x->height = (h1>h2?h1:h2)+1;
}

void BinTree::deleteSubtree(Node *node)
{
    if (node) {
        deleteSubtree(node->left);
        deleteSubtree(node->right);
        delete node;
    }
}

BinTree::Node* BinTree::rotateRight(Node *x)
{
    Node* q = x->left;
    x->left = q->right;
    q->right = x;
    fixHeight(x);
    fixHeight(q);
    return q;
}

BinTree::Node* BinTree::rotateLeft(Node *x)
{
    Node* q = x->right;
    x->right = q->left;
    q->left = x;
    fixHeight(x);
    fixHeight(q);
    return q;
}

BinTree::Node* BinTree::balance(Node *x)
{
    fixHeight(x);
    if( balanceFactor(x)==2 )
    {
        if( balanceFactor(x->right) < 0 )
            x->right = rotateRight(x->right);
        return rotateLeft(x);
    }
    if( balanceFactor(x)==-2 )
    {
        if( balanceFactor(x->left) > 0  )
            x->left = rotateLeft(x->left);
        return rotateRight(x);
    }
    return x;
}

BinTree::Node* BinTree::removeMin(Node *x)
{
    if( x->left==0 )
        return x->right;
    x->left = removeMin(x->left);
    return balance(x);
}


BinTree::Node* BinTree::findMin(Node *x)
{
    return x->left? findMin(x->left) : x;
}

QString BinTree::allSorted(Node *x)
{
    if (x==nullptr) return "";
    qDebug() << "Visiting node with key:" << x->key << "name:" << x->name;
    return allSorted(x->left) + "\n" + x->name + "\n" + allSorted(x->right) + "\n";
}

QString BinTree::keyNodeFirst(Node *x)
{
    if (x==nullptr) return "";
    return x->name + "\n" + keyNodeFirst(x->left) + "\n" + keyNodeFirst(x->right) + "\n";
}

QString BinTree::keyNodeLast(Node *x)
{
    if (x==nullptr) return "";
    return keyNodeLast(x->left) + "\n" + keyNodeLast(x->right) + "\n" + x->name + "\n";
}

