#include <iostream>
using namespace std;
#include <string>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>

struct Tnode{
	string word;
	int count;
	Tnode* left;
	Tnode* right;
};
vector <Tnode> v; //keeps track of all nodes.


void printTnodes(Tnode* node){
	cout << "string is: " << node->word << endl;
	cout << "count is: " << node->count << endl;
	cout << node->left << " LEFT\n";
	cout << node->right << " RIGHT\n";
	if (node->left==0 && node->right==0) //sterile
		return;
	else { //DFS searching for left first.
		if (node->left!=0)
			printTnodes(node->left);
		if (node->right!=0)
			printTnodes(node->right);
		return;
	}
}

//helper function for qsort to print nodes in alphabetical order.
bool compareStr(Tnode node1, Tnode node2){
	return node1.word < node2.word;
}


void printTnodesAlpha(){
	sort(v.begin(),v.end(),compareStr);
	vector<Tnode> vcopy = v;
	cout << "sorted vector contains:\n";
	for (vector<Tnode>::iterator it=vcopy.begin(); it!=vcopy.end(); ++it) {
		cout << it->count << " as COUNT\n";
		cout << it->word << " as WORD\n";
		cout << it->left << " as LEFT\n";
		cout << it->right << " as RIGHT\n";
	}
}


void pushTnode(Tnode* root, string wrd, int cnt){
	//Tnode* node = new Tonode{wrd,cnt,0,0} doesn't work. works in c++11 apparently?
	//example of workaround:
	//Tnode* test = new Tnode;
	//test->count=cnt;
	//test->word=wrd;
	//test->left=0;
	//test->right=0;
	//delete test;
	Tnode node = {wrd, cnt, 0, 0};
	v.push_back(node); //lol what c++03?
	//TODO: find appropriate place to push this by using root.
	//empty
	if (root->word==""){
		root->word= v.back().word;
		root->count=v.back().count;
		return;
	}
	//push to right
	if (root->count < v.back().count){
		if (root->right==0)
			root->right=&v.back();
		else {
			v.pop_back();
			pushTnode(root->right,wrd,cnt);
		}
	//push to left
	} else {
		if (root->left==0)
			root->left=&v.back();
		else{
			v.pop_back();
			pushTnode(root->left,wrd,cnt);
		}
	}

}

void basicEncryption(char* argv[]){
	ostringstream message;
	char* pargv = argv[1];
	char* reset = argv[1];
	char ch;
	cout << "\n\n";
	do {
		if (!cin.get(ch)) return; //this instead of cin >> ch; b/c 
		//this gets one char at a time where as the latter keeps going until
		//EOF or something weird
		if (*pargv == 0)
			pargv = reset;
		if (ch=='\n') {
			cout << message.str();
			return;
		}
		message << (ch ^ (*pargv));
		pargv++;
	} while (ch!='\n');

}

void print(int num, int base=10){
	ostringstream output;
	string y;
	switch (base){
	case 10:
		cout << num << endl;
		return;

	case 2: 
		while (num!=0){
			output << num%2;
			num/=2;
		}
		y = output.str();
		reverse(y.begin(),y.end());
		y = "0b" + y;
		cout << y << endl;
		return;
	case 16:
		while(num!=0){
			if (num%16 >= 10){
				output << char(num%16 + 55);
			} else {
				output << num%16;
			}
			num/=16;
		}
		y = output.str();
		reverse(y.begin(),y.end());
		y = "0x" + y;
		cout << y << endl;
		return;
	}
}

int main(int argc, char* argv[]){
	//#3
	//for (int i=1; i<argc; ++i){
	//	cout << "Hello, " << argv[i] << "!" << endl;
	//}

	//#7
	//v.reserve(100);
	//Tnode root = {"",0,0,0}; //doesn't count as a "node".
	////this does.
	//string wrd;
	//int cnt;
	//ostringstream convert;

	//for (int i = 0; i<50; i+=5){
	//	convert << i;
	//	wrd = "should be " + convert.str();
	//	//convert.clear() clears error status
	//	//convert.empty() asks if it is empty
	//	//below reassigns stream to an empty string.
	//	convert.str("");
	//	cnt = i;
	//	pushTnode(&root,wrd,cnt);
	//}
	//for (int i = 60; i>10; i-=3){
	//	convert << i;
	//	wrd = "should be " + convert.str();
	//	convert.str("");
	//	cnt = i;
	//	pushTnode(&root,wrd,cnt);
	//}
	//printTnodes(&root);
	//printTnodesAlpha();

	//9
	//basicEncryption(argv);
	//16
	print(125);
	print(125,10);
	print(125,2);
	print(125,16);
	//17: add functions such as sqrt(), log(), sin() to the desk calculator.  Predefine
	//the names and call the functions through an array of pointers to functions.  Don't forget to
	//check the arguments in a function call. doitl8r


	return 0;
}