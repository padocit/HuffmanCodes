/* 
*  <Greedy Algorithms>
*  Huffman Codes (instead of ASCII)
*  https://en.wikipedia.org/wiki/Huffman_coding
*  https://stanford-cs161.github.io/winter2024/assets/files/lecture14-notes.pdf
*/

#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

struct Node
{
	string data;
	int freq;
	Node* left = nullptr;
	Node* right = nullptr;
};

// Greater: min_priority_queue(min_heap)
struct Compare
{
	bool operator()(Node* l, Node* r)
	{
		return l->freq > r->freq;
	}
};

void PrintCodes(Node* root, string str)
{
	if (!root)
		return;

	if (!root->left && !root->right) 
		cout << root->data << ": " << str << "\n";

	PrintCodes(root->left, str + "0");
	PrintCodes(root->right, str + "1");
}

void HuffmanCoding(vector<char> data, vector<int> freq)
{
	// priority: less freq
	priority_queue<Node*, vector<Node*>, Compare> heap;

	for (int i = 0; i < data.size(); ++i)
		heap.push(new Node{ string(1, data[i]), freq[i] });

	while (heap.size() != 1)
	{
		Node* left, * right, * top;

		left = heap.top(); heap.pop();
		right = heap.top(); heap.pop();

		top = new Node{ string(left->data + right->data), left->freq + right->freq };
		top->left = left;
		top->right = right;
		heap.push(top); // TODO: Improve? (How to decrease the inner swim of minHeap)

		cout << "(" << left->data << ", " << left->freq << ") + (" << right->data << ", " << right->freq << ") -> ";
		cout << "(" << top->data << ", " << top->freq << ")" << endl;
	}
	PrintCodes(heap.top(), "");
}

int main()
{
	vector<char> data = { 'a', 'b', 'c', 'd', 'e', 'f' };
	vector<int> freq = { 45, 13, 12, 16, 9, 5 };

	HuffmanCoding(data, freq);

	return 0;
}
