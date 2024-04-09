#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <functional>

using namespace std;

float operator"" _Fahrenheit(const char* x)
{
    int value = 0;
    while ((*x) != 0)
    {
        value = value * 10 + (*x) - '0';
        x++;
    }
    return (value - 32) / 1.8;
}

float operator"" _Kelvin(const char* x)
{
    int value = 0;
    while ((*x) != 0)
    {
        value = value * 10 + (*x) - '0';
        x++;
    }
    return value - 273.15;
}


template<typename T>
class TreeNode {
public:
    T value;
    TreeNode<T>* nextSibling;
    TreeNode<T>* firstChild;
    TreeNode<T>* parent;

    TreeNode(T val) : value(val), nextSibling(nullptr), firstChild(nullptr), parent(nullptr) {}

    ~TreeNode() {
        while (firstChild != nullptr) {
            TreeNode<T>* temp = firstChild;
            firstChild = firstChild->nextSibling;
            delete temp;
        }
    }
};

template<typename T>
class Tree {
public:
    TreeNode<T>* root;

    Tree() : root(nullptr) {}

    void addNode(T value, TreeNode<T>* parentNode = nullptr) {
        TreeNode<T>* newNode = new TreeNode<T>(value);
        if (parentNode == nullptr) {
            root = newNode;
        }
        else
        {
            newNode->nextSibling = parentNode->firstChild;
            parentNode->firstChild = newNode;
            newNode->parent = parentNode;
        }
    }

    TreeNode<T>* find_node(TreeNode<T>* node, function<bool(T)> compare)
    {
        if (node == nullptr) return nullptr;
        if (compare(node->value)) return node;

        TreeNode<T>* result = find_node(node->firstChild, compare);
        if (result != nullptr) return result;

        return find_node(node->nextSibling, compare);
    }

    int CountNodes(TreeNode<T>* node) {
        if (node == nullptr)
            return 0;

        int count = 1;

        for (TreeNode<T>* child = node->firstChild; child != nullptr; child = child->nextSibling) {
            count += CountNodes(child);
        }

        return count;
    }
    TreeNode<T>* PrevChild(TreeNode<T>* node, TreeNode<T>* nodnecesar)
    {
        for (TreeNode<T>* child = node->firstChild; child != nullptr; child = child->nextSibling) {
            if (child->nextSibling == nodnecesar) return child;
            PrevChild(child,nodnecesar);
        }
        return nullptr;
    }
    void DeleteNode(TreeNode<T>* node) {
        if (node == nullptr)
            return;
        if (node != root)
        {
            TreeNode<T>* prev = PrevChild(root, node);
            if (prev != nullptr) 
            {
                prev->nextSibling = node->nextSibling;
            }
            else
            {
                node->parent->firstChild = node->nextSibling;
            }
        }
        delete node;

    }

    TreeNode<T>* GetNode(TreeNode<T>* parentNode , int index) {
        int i = 1;
        TreeNode<T>* current = parentNode->firstChild;
        while (i != index)
        {
            i++;
            current = current->nextSibling;
        }
        return current;
    }

    void insertAtIndex(TreeNode<T>* parent, int val, int index)
    {
        TreeNode<T>* newNode = new TreeNode<T>(val);
        if (index == 0)
        {
            newNode->nextSibling = parent->firstChild;
            parent->firstChild = newNode;
            return;
        }

        TreeNode<T>* current = parent->firstChild;
        int current_index = 0;

        while (current_index < index - 1 and current != nullptr)
        {
            current = current->nextSibling;
            current_index++;
        }

        if (current != nullptr)
        {
            newNode->nextSibling = current->nextSibling;
            current->nextSibling = newNode;
        }
    }

    void sortChildren(TreeNode<T>* node, function<bool(const T&, const T&)> compareFunc)
    {
        if (node == nullptr or node->firstChild == nullptr)
            return;

        bool swapped;
        do {
            swapped = false;
            TreeNode<T>* current = node->firstChild;
            TreeNode<T>* prev = nullptr;
            while (current && current->nextSibling) {
                TreeNode<T>* next = current->nextSibling;
                bool shouldSwap = false;

                if (compareFunc != nullptr) {
                    shouldSwap = compareFunc(current->value, next->value);
                }
                else {
                    shouldSwap = current->value < next->value;
                }

                if (shouldSwap)
                {
                    if (prev) {
                        prev->nextSibling = next;
                    }
                    else {
                        node->firstChild = next;
                    }
                    current->nextSibling = next->nextSibling;
                    next->nextSibling = current;
                    prev = next;
                    swapped = true;
                }
                else {
                    prev = current;
                    current = next;
                }
            }
        } while (swapped);
    }
};
int main() {
    
    float a = 300_Kelvin;
    float b = 120_Fahrenheit;
    cout << a << " " << b << endl;
    cout << "-----------------------------------------";
    cout << std::endl;
    
    Tree<int> RealTree;

    RealTree.addNode(10);

    RealTree.addNode(5, RealTree.root);
    RealTree.addNode(15, RealTree.root);
    RealTree.addNode(30, RealTree.root);

    int nr_noduri = RealTree.CountNodes(RealTree.root);
    cout << "Numarul de noduri: " << nr_noduri << endl;
    TreeNode<int>* foundNode = RealTree.find_node(RealTree.root, [](int value) { return value == 15; });
    if (foundNode) {
        cout << "Found Node: " << foundNode->value << endl;
    }
    else {
        cout << "Node not found." << endl;
    }
    TreeNode<int>* special_node = RealTree.root->firstChild;
    special_node = special_node->nextSibling;
    //special_node = special_node->nextSibling;
    RealTree.DeleteNode(RealTree.root->firstChild);
    RealTree.sortChildren(RealTree.root, [](const int& a, const int& b) { return a < b; });

    cout << "Sorted Children: ";
    TreeNode<int>* child = RealTree.root->firstChild;
    while (child != nullptr) {
        cout << child->value << " ";
        child = child->nextSibling;
    }
    cout << endl;
    special_node = RealTree.root->firstChild;

    RealTree.addNode(1979, special_node);             
    RealTree.addNode(9000000, special_node);
    RealTree.addNode(2, special_node);
    RealTree.addNode(171, special_node);
 
    RealTree.insertAtIndex(special_node, 6, 2);


    RealTree.sortChildren(special_node, [](const int& a, const int& b) { return a < b; });

    cout << "Sorted Children: ";
    child = special_node->firstChild;
    while (child != nullptr) {
        cout << child->value << " ";
        child = child->nextSibling;
    }
    cout << endl;

    cout << RealTree.CountNodes(RealTree.root);                

    return 0;
}