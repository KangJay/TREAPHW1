#include "DictBST.h"
#include <iostream> 
#include <fstream> 
#include <string> 
#include <ctime>

using namespace std;

void print(pair<string, int> pair) {
	cout << pair.second << " " << pair.first << endl;
}

int main() { 
	BST<string, int> tree;
	string word;
	while (cin >> word) {
		tree[word]++;
	}
	tree.displayTree();
	return 0;
}
