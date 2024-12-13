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
#include <fstream>
#include <map>

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

// TODO:
void ConvertCodeHelper(Node* root, string str /*map 참조*/) // 실제 압축 변환 재귀
{
	if (!root)
		return;

	if (!root->left && !root->right)
		// map에 저장

	ConvertCodeHelper(root->left, str + "0");
	ConvertCodeHelper(root->right, str + "1");

}

void ConvertCode(Node* root, string str /*content 참조*/) // 압축 변환 실행
{
	// std::map 생성
	// ConvertCodeHelper -> map 반환
	// map을 이용해 실제 content를 변환
}

void HuffmanCoding(vector<char> data, vector<int> freq /*content 참조*/)
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
	// TODO: ConvertCode()
	// TODO: WriteFile()
}

int main()
{
	// 파일 입력 처리
	string filename = "The game of life and how to play it by Florence Scovel Shinn.txt";
	ifstream ifs(filename);

	if (!ifs)
	{
		cerr << "File open ERROR" << endl;
		exit(1);
	}

	map<char, int, greater<int>> char_count;

	string content;
	char ch;
	while (ifs.get(ch))
	{
		content += ch;
		if (char_count.find(ch) == char_count.end()) // 없으면
			char_count[ch] = 1;
		else
			char_count[ch] += 1;
	}

	std::cout << "File content:\n" << content << std::endl;

	ifs.close();

	// 허프만코딩
	vector<char> data;
	vector<int> freq;

	for (auto p : char_count)
	{
		data.push_back(p.first);
		freq.push_back(p.second);
	}


	HuffmanCoding(data, freq);

	return 0;
}
