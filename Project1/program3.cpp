#include <ctime>
#include <string>
#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

int memRecursiveLCS(string x, string y, int i, int j, int** mem_table){

	if(mem_table[i][j] == -1){
		if(i == 0 || j == 0){
			mem_table[i][j] = 0;
		}else if(x[i] == y[j]){
			mem_table[i][j] = memRecursiveLCS(x, y, i-1, j-1, mem_table) + 1;
		}else{
			mem_table[i][j] =  max( memRecursiveLCS(x, y, i-1, j, mem_table), memRecursiveLCS(x, y, i, j-1, mem_table) );
		}
	}
	return mem_table[i][j];
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
	
	//int **mem_table;
	//int mem_table = new int *[str1.size()+1];
	int str1_size = str1.size()+1;
	int str2_size = str2.size()+1;
	
	int ** mem_table;
	mem_table = new int*[str1_size];
	
	clock_t beg_time = clock();
	
	for(int i = 0; i < str1_size; i++){
		mem_table[i] = new int[str2_size];
	}

	for(int i = 0; i < str1.size()+1; i++){
		for(int j = 0; j < str2.size()+1; j++){
			if(i == 0 || j == 0){
				mem_table[i][j] = 0;
			}else{
				mem_table[i][j] = -1;
			}
		}
	}

	int LCSlen = memRecursiveLCS(str1, str2, str1.size(), str2.size(), mem_table);
	clock_t end_time = clock();
	fp_o << LCSlen << endl;
	fp_o << float(end_time-beg_time)/CLOCKS_PER_SEC << endl;

	fp_o.close();	

	return 0;
}

