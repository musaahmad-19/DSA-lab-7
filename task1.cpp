
#include <iostream>
#include <stack>
#include <string>
#include <vector>
using namespace std;

struct Node {
    char data;
    Node* left;
    Node* right;

    Node(char value) {
        data = value;
        left = right = NULL;
    }
};

Node* buildTree(string s, int& i) {
    if (i >= s.length() || s[i] == ',' || s[i] == ')')
        return NULL;

    Node* root = new Node(s[i++]);

    if (i < s.length() && s[i] == '(') {
        i++;

        if (i < s.length() && s[i] != ',')
            root->left = buildTree(s, i);

        if (i < s.length() && s[i] == ',')
            i++;

        if (i < s.length() && s[i] != ')')
            root->right = buildTree(s, i);

        if (i < s.length() && s[i] == ')')
            i++;
    }

    return root;
}

void preorder(Node* root) {
    if (root == NULL)
        return;

    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

void inorderIterative(Node* root) {
    stack<Node*> s;
    Node* current = root;

    while (current != NULL || !s.empty()) {
        while (current != NULL) {
            s.push(current);
            current = current->left;
        }

        current = s.top();
        s.pop();

        cout << current->data << " ";
        current = current->right;
    }
}

void postorderIterative(Node* root) {
    if (root == NULL)
        return;

    stack<Node*> s1, s2;
    s1.push(root);

    while (!s1.empty()) {
        Node* current = s1.top();
        s1.pop();
        s2.push(current);

        if (current->left != NULL)
            s1.push(current->left);

        if (current->right != NULL)
            s1.push(current->right);
    }

    while (!s2.empty()) {
        cout << s2.top()->data << " ";
        s2.pop();
    }
}

bool validateTree(string s) {
    if (s.empty())
        return false;

    int balance = 0;
    int n = s.length();

    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            balance++;
        else if (s[i] == ')') {
            balance--;
            if (balance < 0)
                return false;
        }
    }

    if (balance != 0)
        return false;

    int i = 0;
    Node* root = buildTree(s, i);

    return root != NULL && i == n;
}

int height(Node* root) {
    if (root == NULL)
        return 0;

    int leftHeight = height(root->left);
    int rightHeight = height(root->right);

    return 1 + max(leftHeight, rightHeight);
}

void printDepth(Node* root, int depth) {
    if (root == NULL)
        return;

    cout << root->data << ": " << depth << endl;

    printDepth(root->left, depth + 1);
    printDepth(root->right, depth + 1);
}

Node* insertBST(Node* root, int value) {
    if (root == NULL)
        return new Node(char(value));

    if (value < root->data)
        root->left = insertBST(root->left, value);
    else if (value > root->data)
        root->right = insertBST(root->right, value);

    return root;
}

void inorderBST(Node* root) {
    if (root == NULL)
        return;

    inorderBST(root->left);
    cout << int(root->data) << " ";
    inorderBST(root->right);
}

int main() {
    string treeString = "a(b(d,e),c(,f(g,)))";
    int index = 0;

    Node* root = buildTree(treeString, index);

    cout << "Preorder: ";
    preorder(root);

    cout << "\nInorder: ";
    inorderIterative(root);

    cout << "\nPostorder: ";
    postorderIterative(root);

    cout << "\nValid Tree String: "
         << (validateTree(treeString) ? "Yes" : "No");

    cout << "\nHeight: " << height(root);

    cout << "\nNode Depths:\n";
    printDepth(root, 0);

    int values[] = {50, 30, 70, 20, 40, 60, 80};
    Node* bst = NULL;

    for (int value : values)
        bst = insertBST(bst, value);

    cout << "\nBST Inorder: ";
    inorderBST(bst);

    cout << endl;
    return 0;
}
