// CMakeProject1.cpp: определяет точку входа для приложения.
//

#include "HuffmanCoding.h"

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <string>

using namespace std;

struct Node {
    char symbol;
    double probability;
    Node* left, * middle, * right;

    Node(char symbol, double probability) : symbol(symbol), probability(probability), left(nullptr), middle(nullptr), right(nullptr) {}
};

struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->probability > r->probability;
    }
};

Node* buildHuffmanTree(vector<char>& symbols, vector<double>& probabilities) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (int i = 0; i < symbols.size(); ++i) {
        pq.push(new Node(symbols[i], probabilities[i]));
    }

    while (pq.size() > 1) {
        if (pq.size() < 3) {
            Node* left = pq.top();
            pq.pop();

            Node* right = pq.top();
            pq.pop();

            double sumProb = left->probability + right->probability;
            Node* newNode = new Node('$', sumProb);
            newNode->left = left;
            newNode->right = right;

            pq.push(newNode);
        }
        else {
            Node* left = pq.top();
            pq.pop();

            Node* middle = pq.top();
            pq.pop();

            Node* right = pq.top();
            pq.pop();

            double sumProb = left->probability + middle->probability + right->probability;
            Node* newNode = new Node('$', sumProb);
            newNode->left = left;
            newNode->middle = middle;
            newNode->right = right;

            pq.push(newNode);
        }
    }

    return pq.top();
}

void generateHuffmanCodes(Node* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    if (root->left == nullptr && root->middle == nullptr && root->right == nullptr) {
        huffmanCodes[root->symbol] = code;
    }

    if (root->left) generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    if (root->middle) generateHuffmanCodes(root->middle, code + "1", huffmanCodes);
    if (root->right) generateHuffmanCodes(root->right, code + "2", huffmanCodes);
}

int main() {
    cout << "Enter num of symblos in alphabet: " << endl;
    int size;
    cin >> size;

    vector<char> symbols(size);
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter " << i + 1 << " symbol: ";
        cin >> symbols[i];
        cout << endl;
    }
    vector<double> probabilities(size);
    for (int i = 0; i < size; ++i)
    {
        cout << "Enter probability of symbol " << symbols[i] << " : ";
        cin >> probabilities[i];
        cout << endl;
    }

    Node* root = buildHuffmanTree(symbols, probabilities);

    map<char, string> huffmanCodes;
    generateHuffmanCodes(root, "", huffmanCodes);

    for (auto& pair : huffmanCodes) {
        cout << "Symbol: " << pair.first << ", Huffman Code: " << pair.second << endl;
    }

    return 0;
}
