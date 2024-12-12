# HuffmanCodes

*  <Greedy Algorithms>
*  Huffman Codes (instead of ASCII)
*  https://en.wikipedia.org/wiki/Huffman_coding
*  https://stanford-cs161.github.io/winter2024/assets/files/lecture14-notes.pdf

## 특징

- **Greedy**
  - **정렬** 대신 **우선순위 큐**
  - 진행 정도에 따라 순서가 바뀌는 구조이기 때문
- **Prefix free**
  - **고정 너비**가 아닌 **가변 너비** bit
    - ASCII:         8bit 고정
    - Huffman Codes: bit수 가변
  - 따라서 압축form 혼동 가능
    - Ex) a: 0, b: 1, c: 10 => 10은 'c'인가 'ba'인가?

## 구조

![image](https://github.com/user-attachments/assets/1a756d0d-fcf7-494a-99a1-39267e68b859)
(출처: cs161)

- 우선순위: 낮은 빈도 수
- 우선순위대로 tree 결합 (greedy)
- (주의) 트리의 불균형이 핵심 (prefix free)

## 예제: TODO

`TODO: 실제 고전 문서 txt 파일을 압축했다가 풀어보기`

## 보완할 점

```cpp
		Node* left, * right, * top;

		left = heap.top(); heap.pop();
		right = heap.top(); heap.pop();

		top = new Node{ string(left->data + right->data), left->freq + right->freq };
		top->left = left;
		top->right = right;
		heap.push(top); // TODO: Improve? (How to decrease the inner swim of minHeap)
```

- 현재: top Node를 heap에 바로 삽입 -> heap 내부에서 불필요한 swim (어차피 다음 차례에 우선순위대로 Node 2개를 뺄 예정)
- 보완: 우선순위대로 다음 left, right를 정한다 -> top Node를 heap에 삽입

> 하지만 코드가 더 지저분해질 가능성이 있어서 현재로서는 현상 유지
