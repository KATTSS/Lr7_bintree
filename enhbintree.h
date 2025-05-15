#ifndef ENHBINTREE_H
#define ENHBINTREE_H
#include <QTreeWidget>
#include "simplebintree.h"

class AdvancedBinTree : public BinTree
{
public:
    AdvancedBinTree() : BinTree() {};
    size_t countSymbols();
    void addToTreeWidget(QTreeWidget* treeWidget, bool straight, bool left, bool right);
private:
    void addNodeToTree(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, Node* node, bool straight, bool left, bool right);
};

#endif // ENHBINTREE_H
