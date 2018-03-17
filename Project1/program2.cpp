#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

int recursiveLCS(string x, string y, int i, int j){

	if(i <= 0 || j <= 0){
		return 0;
	}else if(x[i] == y[j]){
		return recursiveLCS(x, y, i-1, j-1) + 1;
	}else{
		return max( recursiveLCS(x, y, i-1, j), recursiveLCS(x, y, i, j-1) );
	}
}

int main(int argc, char *argv[]){

	//input files -- filex.txt and filey.txt
	ifstream fp_x, fp_y;
	fp_x.open(argv[1]);
	fp_y.open(argv[2]);
	
	//output file -- output.txt
	ofstream fp_o;
	fp_o.open(argv[3]);
	
	string str1; //for filex.txt string
	string str2; //for filey.txt string

	if(!fp_x){
		cerr << "Error opening filex.txt" << endl; 
		exit(1);
	}else if(!fp_y){
		cerr << "Error opening filey.txt" << endl; 
		exit(1);
	}else if(!fp_o){
		cerr << "Error opening output.txt" << endl;
		exit(1);
	}

	fp_x >> str1; //stores the contents from filex into str1
	fp_y >> str2; //stores the contents from filey into str2

	fp_x.close();
	fp_y.close();
	
	clock_t beg_time = clock();
	int LCSlen = recursiveLCS(str1, str2, str1.size(), str2.size());
	clock_t end_time = clock();
	fp_o << LCSlen << endl;
	fp_o << float(end_time-beg_time)/CLOCKS_PER_SEC << endl;

	fp_o.close();	

	return 0;
}
