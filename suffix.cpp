#include <iostream>
#include <unordered_map>
using namespace std;

class SuffixTreeNode {
public:
    unordered_map<char, SuffixTreeNode*> children;

    // Function to insert a suffix into the tree
    void insertSuffix(const string& suffix) {
        SuffixTreeNode* current = this;
        for (int i = 0; i < suffix.length(); i++) {
            char ch = suffix[i];
            if (current->children.find(ch) == current->children.end()) {
                current->children[ch] = new SuffixTreeNode();
            }
            current = current->children[ch];
        }
    }

    // Recursive function to display the tree
    void display(const string& prefix = "") {
        for (auto it = children.begin(); it != children.end(); ++it) {
            cout << prefix << it->first << endl;
            it->second->display(prefix + it->first);
        }
    }
};

int main() {
    SuffixTreeNode root;

    string text = "banana";

    // Insert all suffixes of the string into the tree
    for (int i = 0; i < text.length(); ++i) {
        root.insertSuffix(text.substr(i));
    }

    cout << "Suffix tree constructed successfully for the string: " << text << endl;
    cout << "Displaying Suffix Tree:\n";

    // Display the suffix tree structure
    root.display();

    return 0;
}
