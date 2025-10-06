#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

// Here i created this class to represent each single node in Huffman tree
class HuffNode {
public:
    char symbol;             
    int freq;                
    HuffNode *leftChild;     
    HuffNode *rightChild;   

    // Here is the constructor used to initialize node data
    HuffNode(char s, int f) : symbol(s), freq(f), leftChild(nullptr), rightChild(nullptr) {}
};

// This function will help to give new parent node with combination of two small nodes
HuffNode* mergeNodes(HuffNode* first, HuffNode* second) {
    HuffNode* newNode = new HuffNode('#', first->freq + second->freq); // '#' marks an internal node
    newNode->leftChild = first;
    newNode->rightChild = second;
    return newNode;
}

// This function helps to create Huffman tree from given characters and ferquency values
HuffNode* createHuffmanTree(const string& chars, const vector<int>& freqList) {
    vector<HuffNode*> treeNodes;

    // Step 1: Here we are creating separate node for each character
    for (size_t i = 0; i < chars.size(); ++i) {
        treeNodes.emplace_back(new HuffNode(chars[i], freqList[i]));
    }

    // Step 2: Here we need to Keep on combining two least frequency nodes until only one root node remains
    while (treeNodes.size() > 1) {
        // Sort nodes in ascending order of frequency
        sort(treeNodes.begin(), treeNodes.end(),
             [](HuffNode* a, HuffNode* b) { return a->freq < b->freq; });

 
        HuffNode* left = treeNodes.front();
        HuffNode* right = *(treeNodes.begin() + 1);

        // Here i created a new internal node with the combination of their frequencies
        HuffNode* parentNode = mergeNodes(left, right);

        // In this line iam trying to remove the two smallest nodes and adding the new parent node
        treeNodes.erase(treeNodes.begin(), treeNodes.begin() + 2);
        treeNodes.push_back(parentNode);
    }

    // After the whole process last remaining node will be considered root of the Huffman tree
    return treeNodes.front();
}

// Here i created recursive function which is used to generate Huffman codes using preorder traversal
void displayCodes(HuffNode* root, const string& prefix, vector<pair<char, string>>& codes) {
    if (!root) return; // Base condition for recursion

    // If it's a leaf node, we should store both character and it's code
    if (root->symbol != '#') {
        codes.emplace_back(root->symbol, prefix);
    }

    // we should Add '0' for left child and '1' for right child
    displayCodes(root->leftChild, prefix + "0", codes);
    displayCodes(root->rightChild, prefix + "1", codes);
}

int main() {
    // Here is given input characters and their frequencies
    string inputChars = "abcdef";
    vector<int> freqList = {5, 9, 12, 13, 16, 45};

    cout << "Given Data:\n";
    cout << "Characters: " << inputChars << "\n";
    cout << "Frequencies: ";
    for (auto f : freqList) cout << f << " ";
    cout << "\n\n";

    // Step 3: Building the Huffman Tree
    HuffNode* rootNode = createHuffmanTree(inputChars, freqList);

    // Step 4: Generating Huffman codes
    vector<pair<char, string>> codeList;
    displayCodes(rootNode, "", codeList);

    // Step 5: Finally this line is to display the final Huffman codes
    cout << "Huffman Codes (Preorder Traversal):\n";
    for (auto& entry : codeList) {
        cout << entry.first << " : " << entry.second << endl;
    }

    return 0;
}
