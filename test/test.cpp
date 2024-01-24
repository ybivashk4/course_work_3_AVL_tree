#include <fstream>
#include <iostream>
using namespace std;
int main(){
	ofstream out;
	out.open("../saves/large.txt");
	for (int i=1; i<10000000;i++){
		out << i << " ";
	}
}
