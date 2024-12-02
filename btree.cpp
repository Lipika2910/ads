#include <iostream>
#include <vector>
using namespace std;

class BTreeNode {
    int minDegree;                // Minimum degree (defines range for keys)
    vector<int> keys;             // Keys in the node
    vector<BTreeNode*> children;  // Child pointers
    bool isLeaf;                  // True if the node is a leaf

public:
    BTreeNode(int degree, bool leaf) {
        minDegree = degree;
        isLeaf = leaf;
    }

    void traverse() {
        for (int i = 0; i < keys.size(); i++) {
            if (!isLeaf) children[i]->traverse();
            cout << keys[i] << " ";
        }
        if (!isLeaf) children[keys.size()]->traverse();
    }

    BTreeNode* search(int key) {
        int i = 0;
        while (i < keys.size() && key > keys[i]) i++;

        if (i < keys.size() && keys[i] == key) return this;

        if (isLeaf) return nullptr;

        return children[i]->search(key);
    }

    void insertNonFull(int key) {
        int i = keys.size() - 1;

        if (isLeaf) {
            keys.insert(keys.end(), key);
            while (i >= 0 && keys[i] > key) {
                keys[i + 1] = keys[i];
                i--;
            }
            keys[i + 1] = key;
        } else {
            while (i >= 0 && keys[i] > key) i--;
            if (children[i + 1]->keys.size() == 2 * minDegree - 1) {
                splitChild(i + 1, children[i + 1]);
                if (keys[i + 1] < key) i++;
            }
            children[i + 1]->insertNonFull(key);
        }
    }

    void splitChild(int i, BTreeNode* child) {
        BTreeNode* newNode = new BTreeNode(child->minDegree, child->isLeaf);
        for (int j = 0; j < minDegree - 1; j++) {
            newNode->keys.push_back(child->keys[j + minDegree]);
        }

        if (!child->isLeaf) {
            for (int j = 0; j < minDegree; j++) {
                newNode->children.push_back(child->children[j + minDegree]);
            }
        }

        child->keys.resize(minDegree - 1);
        children.insert(children.begin() + i + 1, newNode);
        keys.insert(keys.begin() + i, child->keys[minDegree - 1]);
    }

    friend class BTree;
};

class BTree {
    BTreeNode* root;
    int minDegree;

public:
    BTree(int degree) {
        root = nullptr;
        minDegree = degree;
    }

    void traverse() {
        if (root) root->traverse();
    }

    BTreeNode* search(int key) {
        return root ? root->search(key) : nullptr;
    }

    void insert(int key) {
        if (!root) {
            root = new BTreeNode(minDegree, true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * minDegree - 1) {
                BTreeNode* newNode = new BTreeNode(minDegree, false);
                newNode->children.push_back(root);
                newNode->splitChild(0, root);

                int i = 0;
                if (newNode->keys[0] < key) i++;
                newNode->children[i]->insertNonFull(key);

                root = newNode;
            } else {
                root->insertNonFull(key);
            }
        }
    }
};

int main() {
    BTree tree(3); // Minimum degree 3

    tree.insert(10);
    tree.insert(20);
    tree.insert(5);
    tree.insert(6);
    tree.insert(12);
    tree.insert(30);
    tree.insert(7);
    tree.insert(17);

    cout << "Traversal of the B-Tree:\n";
    tree.traverse();

    int key = 6;
    if (tree.search(key)) cout << "\nKey " << key << " found in the tree.";
    else cout << "\nKey " << key << " not found in the tree.";

    return 0;
}
