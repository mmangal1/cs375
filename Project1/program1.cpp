#include <ctime>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

enum Arrow{
	UP, LEFT, DIAGONAL, BLANK
};

typedef struct elements{
	int val;
	enum Arrow arrow;
}elements;

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
	
	int rows = str1.size()+1;
	int cols = str2.size()+1;

	//create table for storing values and directions
	elements table[rows][cols];


	clock_t beg_time = clock();
	//initialize table to all 0 and no arrow
	for(int i = 0; i < rows; i++){
		for(int j = 0; j < cols; j++){
			table[i][j].val = 0;
			table[i][j].arrow = BLANK;
		}
	}

	//update table according to characters of strings provided
	//must start from index 1 since table also holds base values of 0 in first row and column
	for(int i = 1; i < rows; i++){
		for(int j = 1; j < cols; j++){
			if(str1[i-1] == str2[j-1]){ //same character, update arrow to diagonal, and increase value+1 from diagonal value
				table[i][j].val = table[i-1][j-1].val + 1;
				table[i][j].arrow = DIAGONAL;	
			}else if(table[i][j-1].val > table[i-1][j].val){	//left value is greater than value above
				table[i][j].val = table[i][j-1].val;
				table[i][j].arrow = LEFT;
			}else{	//above value is greater or equal to the left value
				table[i][j].val = table[i-1][j].val;
				table[i][j].arrow = UP;
			}
		}
	}

	//if input x and y string are less than or equal to 10, print the table to output file, print LCS
	//else just print length of LCS
	if(str1.size() <= 10 && str2.size() <= 10){
		//print LCS table
		for(int i = 0; i < rows; i++){
			for(int j = 0; j < cols; j++){
				fp_o << table[i][j].val << " ";
			}
			fp_o << endl;
		}
		//find the LCS of the problem
		int i_row = rows-1;
		int j_col = cols-1;
		string LCS = "";
		while(i_row > 0 && j_col > 0){
			if(table[i_row][j_col].arrow == DIAGONAL){
				LCS = str1[i_row-1] + LCS;
				i_row--;
				j_col--;
			}else if(table[i_row][j_col].arrow == UP){
				i_row--;
			}else{
				j_col--;
			}
		}
	
		clock_t end_time = clock();
		fp_o << float(end_time-beg_time)/CLOCKS_PER_SEC << endl;

	}else{
		fp_o << table[rows-1][cols-1].val << endl;
	
		clock_t end_time = clock();
		fp_o << float(end_time-beg_time)/CLOCKS_PER_SEC << endl;
	}

	fp_o.close();	
	return 0;
}
