#include<iostream>
#include <string>
#include <windows.h>
using namespace std;

const int ALPHABET_SIZE = 26;

// trie node 
struct TrieNode
{
	struct TrieNode *children[ALPHABET_SIZE];

	// isEndOfWord is true if the node represents 
	// end of a word 
	bool isEndOfWord;
	string meaning;
};

// Returns new trie node (initialized to NULLs) 
struct TrieNode *getNode(void)
{
	struct TrieNode *pNode = new TrieNode;

	pNode->isEndOfWord = false;

	for (int i = 0; i < ALPHABET_SIZE; i++)
		pNode->children[i] = NULL;

	return pNode;
}

// If not present, inserts key into trie 
// If the key is prefix of trie node, just 
// marks leaf node 
void insert(struct TrieNode *root, string key, string meaningkey)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index])
			pCrawl->children[index] = getNode();

		pCrawl = pCrawl->children[index];
	}

	// mark last node as leaf and add meaning
	if (pCrawl->isEndOfWord){
		cout << key << " was exist, do you want redefinition?\n0.No\n1.Yes\n";
		int a;
		cin >> a;
		if (a){
			pCrawl->meaning = meaningkey;
		}
	}
	else{
		pCrawl->isEndOfWord = true;
		pCrawl->meaning = meaningkey;
	}
}


void search(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index]){
			cout <<key<< " is not exist";
			return;
		}

		pCrawl = pCrawl->children[index];
	}

	if (pCrawl != NULL && pCrawl->isEndOfWord){
		cout <<key<<": "<< pCrawl->meaning;
	}
	else cout << key << " is not exist";
}

void remove(struct TrieNode *root, string key)
{
	struct TrieNode *pCrawl = root;

	for (int i = 0; i < key.length(); i++)
	{
		int index = key[i] - 'a';
		if (!pCrawl->children[index]){
			cout << key << " is not exist";
			return;
		}
		pCrawl = pCrawl->children[index];
	}

	// unmark last node

	if (pCrawl->isEndOfWord){
		pCrawl->isEndOfWord = false;
		cout << key << " has been removed!";
	}
	else cout << key << " is not exist";
}

// Driver 
int main()
{
	// Input keys (use only 'a' through 'z' 
	// and lower case) 
	string keys[] = { "add", "bee", "can", "cat", "catch", "category", "dog", "end", "feed", "goodbye", "high", "just", "ink", "knee", "light",
		"mom", "night", "organization", "program", "quit", "rest", "sit", "ton", "unit", "viper", "xray", "yes", "zero", "address", "cannon" };

	string meaningkeys[] = { "Them / Cong", "Con Ong", "Co the", "Con meo", "Bat lay", "The loai", "Con cho", "Ket thuc", "Cho an", "Tam biet",
		"Cao", "Vua moi", "Muc", "Dau goi", "Anh sang", "Me", "Ban dem", "To chuc", "chuong trinh", "thoat", "Nghi ngoi", "ngoi", "Tan", "Don vi",
		"Ran luc", "Tia X", "Co", "So 0", "Dia chi", "Sung than cong" };



	int n = sizeof(keys) / sizeof(keys[0]);

	// Construct trie 
	struct TrieNode *root = getNode();

	
	for (int i = 0; i < n; i++)
		insert(root, keys[i], meaningkeys[i]);

	// Search for different keys 
	cout << "------------WELCOME TO DICTIONARY TRIE------------";
	
	int a = 0;
	string key;
	string meaningkey;
	while (a != 4){
		cout << "\nList command:\n1.Search a word\n2.Add a new word\n3.Remove a word\n4.Exit\n";
		cin >> a;

		//Search
		if (a == 1){
			cout << "Type word: ";
			cin >> key;
			search(root, key);
		}

		//Add
		if (a == 2){
			cout << "Type word and meaning: ";
			cin >> key;
			getline(cin, meaningkey);
			insert(root, key, meaningkey);
		}

		//Remove
		if (a == 3){
			cout << "Type word: ";
			cin >> key;
			remove(root, key);
		}
		Sleep(1000);
		cout << endl;
	}
	return 0;
}
