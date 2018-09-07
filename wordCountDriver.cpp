#include "Treap.h"
#include <iostream> 
#include <fstream> 
#include <string> 

using namespace std;

void print(pair<string, int> pair) {
	cout << pair.second << " " << pair.first << endl;
}

int main() {
	Treap<string, int> tree;
	string word;

	while (cin >> word) {
		tree.insert(word);
	} 
	for (Treap<string, int>::Iterator it = tree.begin(); it != tree.end(); ++it) {
		print(*it);
	}
	//tree.isValidHeap();
	//tree.dump(); 
	return 0;
}
