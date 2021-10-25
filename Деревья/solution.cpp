#pragma comment(linker, "/STACK:67108864")

#include <fstream>
#include <memory> 
#include <cmath>
#include <set>
#include <algorithm>
#include <vector>
#include <iostream>

long long myMax(long long a, long long b)
{
    return a > b ? a : b;
}

long long myMin(long long a, long long b)
{
    return a < b ? a : b;
}

class Node
{
public:
    long long key;
    long long min_child;
    std::pair<long long, long long> info;
    Node* left;
    Node* right;
    bool isLeaf() {
        return left == nullptr && right == nullptr;
    }
    int subtreesCount() {
        if (left != nullptr && right != nullptr) {
            return 2;
        }
        if (isLeaf()) {
            return 0;
        }
        return 1;
    }
    Node(long long key)
    {
        this->key = key;
        left = nullptr;
        right = nullptr;
        min_child = key;
        info = std::make_pair(0, 0);
    }
};

class BinTree
{
public:
    Node* root;
    long long max_path = 0;
    std::vector<Node*> roots;
    long long size = 0;
    BinTree()
    {
        this->root = nullptr;
    }
    void insert(long long value) {
        this->root = insert(value, root);
    }
    Node* insert(long long value, Node* node) {
        if (node == nullptr) {
            size++;
            return new Node(value);
        }
        if (value < node->key) {
            node->left = insert(value, node->left);
        }
        else if (value > node->key) {
            node->right = insert(value, node->right);
        }
        return node;
    }
    void findRoots(Node* node) {
        if (node != nullptr) {
            findRoots(node->left);
            findRoots(node->right);
            if (!node->isLeaf()) {
                long long height;
                long long semipath;
                if (node->left == nullptr) {
                    height = node->right->info.first + 1;
                    semipath = node->right->info.first + 1;
                    node->min_child = node->right->min_child;
                }
                else if (node->right == nullptr) {
                    height = node->left->info.first + 1;
                    semipath = node->left->info.first + 1;
                    node->min_child = node->left->min_child;
                }
                else
                {
                    height = myMax(node->right->info.first, node->left->info.first) + 1;
                    semipath = node->right->info.first + node->left->info.first + 2;
                    if (node->left->info.first > node->right->info.first) {
                        node->min_child = node->left->min_child;
                    }
                    else if (node->left->info.first < node->right->info.first) {
                        node->min_child = node->right->min_child;
                    }
                    else {
                        node->min_child = myMin(node->left->min_child, node->right->min_child);
                    }
                }
                node->info = std::make_pair(height, semipath);
                if (node->info.second == max_path) {
                    roots.push_back(node);
                }
                if (node->info.second > max_path) {
                    max_path = node->info.second;
                    roots.clear();
                    roots.push_back(node);
                }
            }
        }
    }
    void findRoots() {
        findRoots(this->root);
    }
    void deleteNode() {
        long long key = -1;
        long long min_sum = LLONG_MAX;
        for (int i = 0; i < roots.size(); i++) {
            long long sum;
            if (roots[i]->left != nullptr && roots[i]->right != nullptr) {
                sum = roots[i]->left->min_child + roots[i]->right->min_child;
            }
            else if (roots[i]->left == nullptr) {
                sum = roots[i]->key + roots[i]->right->min_child;
            }
            else {
                sum = roots[i]->key + roots[i]->left->min_child;
            }
            if (sum < min_sum) {
                min_sum = sum;
                key = roots[i]->key;
            }
        }
        deleteNode(key);
    }
    void deleteNode(long long value) {
        root = deleteNode(value, root);
    }
    Node* deleteNode(long long value, Node* node) {
        if (node == nullptr) return nullptr;
        if (value < node->key) {
            node->left = deleteNode(value, node->left);
            return node;
        }
        else if (value > node->key) {
            node->right = deleteNode(value, node->right);
            return node;
        }
        if (node->left == nullptr) return node->right;
        if (node->right == nullptr) return node->left;
        long long minKey = findMinNode(node->right)->key;
        node->key = minKey;
        node->right = deleteNode(minKey, node->right);
        return node;
    }
    Node* findMinNode(Node* node) {
        if (node->left != nullptr) {
            return findMinNode(node->left);
        }
        return node;
    }
    static void DestroyNode(Node* node) {
        if (node) {
            DestroyNode(node->left);
            DestroyNode(node->right);
            delete node;
        }
    }
    ~BinTree()
    {
        DestroyNode(this->root);
    }
};

class TreeReader
{
public:
    BinTree* tree;
    std::string fileName;

    TreeReader(std::string fileName)
    {
        this->fileName = fileName;
        tree = new BinTree();
    }

    ~TreeReader()
    {
        delete tree;
    }

    void readTree() {
        std::ifstream fin(fileName);
        int x;
        while (fin >> x) {
            tree->insert(x);
        }
    }
};

class Writer
{
public:
    BinTree* tree;
    std::string fileName;

    Writer(std::string fileName, BinTree* tree)
    {
        this->fileName = fileName;
        this->tree = tree;
    }

    void preorderLeftTraversalWithPrint(Node* node, std::ofstream* fout) {
        if (node != nullptr) {
            *fout << node->key << std::endl;
            preorderLeftTraversalWithPrint(node->left, fout);
            preorderLeftTraversalWithPrint(node->right, fout);
        }
    }
    void preorderLeftTraversalWithPrint() {
        std::ofstream* fout = new std::ofstream(this->fileName);
        preorderLeftTraversalWithPrint(tree->root, fout);
        delete fout;
    }
};

int main()
{
    TreeReader* reader = new TreeReader("in.txt");
    reader->readTree();
    reader->tree->findRoots();
    reader->tree->deleteNode();
    Writer* writer = new Writer("out.txt", reader->tree);
    writer->preorderLeftTraversalWithPrint();
    delete reader;
    delete writer;
    return 0;
}