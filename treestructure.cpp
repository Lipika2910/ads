#include <iostream>
using namespace std;

class TreeNode {
    int data;
    TreeNode* left;
    TreeNode* right;

public:
    TreeNode(int value) {
        data = value;
        left = right = nullptr;
    }

    TreeNode* insert(TreeNode* root, int value) {
        if (!root) return new TreeNode(value);
        if (value < root->data) root->left = insert(root->left, value);
        else root->right = insert(root->right, value);
        return root;
    }

    bool search(TreeNode* root, int value) {
        if (!root) return false;
        if (root->data == value) return true;
        if (value < root->data) return search(root->left, value);
        return search(root->right, value);
    }

    void inorder(TreeNode* root) {
        if (root) {
            inorder(root->left);
            cout << root->data << " ";
            inorder(root->right);
        }
    }

    friend class BinaryTree;
};

class BinaryTree {
    TreeNode* root;

public:
    BinaryTree() {
        root = nullptr;
    }

    void insert(int value) {
        root = root ? root->insert(root, value) : new TreeNode(value);
    }

    bool search(int value) {
        return root ? root->search(root, value) : false;
    }

    void display() {
        cout << "In-order Traversal: ";
        if (root) root->inorder(root);
        else cout << "Tree is empty.";
        cout << endl;
    }
};

int main() {
    BinaryTree tree;

    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);

    tree.display();

    int key = 7;
    if (tree.search(key)) cout << "Key " << key << " found in the tree.\n";
    else cout << "Key " << key << " not found in the tree.\n";

    return 0;
}
