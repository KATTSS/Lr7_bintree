#include "enhbintree.h"
#include <QDebug>

size_t AdvancedBinTree::countSymbols()
{
    qDebug () << "count all symbols in: " << allSorted(root);
    return (allSorted(root).replace("\n", "")).length();
}


void AdvancedBinTree::addNodeToTree(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, Node* node, bool straight, bool left, bool right) {
    if (!node) return;

    QTreeWidgetItem* item = nullptr;
    if (straight) {
        addNodeToTree(treeWidget, parentItem, node->left, straight, left, right);
        if (parentItem)
            item = new QTreeWidgetItem(parentItem);
        else
            item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString("%1: %2").arg(node->key).arg(node->name));
        addNodeToTree(treeWidget, parentItem, node->right, straight, left, right);
    } else if (left) {
        if (parentItem)
            item = new QTreeWidgetItem(parentItem);
        else
            item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString("%1: %2").arg(node->key).arg(node->name));
        addNodeToTree(treeWidget, item, node->left, straight, left, right);
        addNodeToTree(treeWidget, item, node->right, straight, left, right);
    } else if (right) {
        addNodeToTree(treeWidget, parentItem, node->left, straight, left, right);
        addNodeToTree(treeWidget, parentItem, node->right, straight, left, right);
        if (parentItem)
            item = new QTreeWidgetItem(parentItem);
        else
            item = new QTreeWidgetItem(treeWidget);
        item->setText(0, QString("%1: %2").arg(node->key).arg(node->name));
    }
}

void AdvancedBinTree::addToTreeWidget(QTreeWidget* treeWidget, bool straight, bool left, bool right) {
    addNodeToTree(treeWidget, nullptr, root, straight, left, right);
}

