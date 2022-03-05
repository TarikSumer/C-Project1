//============================================================================
// Name        : Ass1.cpp
// Author      : Tarik Sumer
// Version     :
// Copyright   : 
// Description : Assignment1 in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;

int linkCount; //link count we have in each step
std::vector<vector<int>> links; //array for keeping the coordinates of links to reach after checking all links
std::vector<std::vector<int>> grid;
int temp[] = {-1,-1}; //temporary arrays to keep first caller coordinates
int callerCell[] = {-1,-1};
int point;
int gridSize;

void printGrid(vector<vector<int>> & grid, int size){ //print grid vector function for n x n vectors
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout << grid[i][j] << " ";
		}
	cout << endl;
	}
}
// ----------------------------------------------

bool ifContain(int x, int y){ // checks if a link is in the 2d links vector
	for(vector<int> i : links){
		if(i[0] == x && i[1] == y){
			return true;
		}
	}
	return false;
}

// ----------------------------------------------

//checkCells function gets the id & coordinates and size of the balloon to be placed and check around cells
void checkCells(int x, int y, int id, int gridSize, vector<vector<int>> & grid){

//------------------------------------------------------------
	if(x == gridSize - 1){ //bottom cell check
		//do nothing
	}else {
		if(grid[x+1][y] == id && !ifContain(x+1, y)){ //south cell check
			links.push_back({x+1,y});
			linkCount++;
			checkCells(x+1, y, id, gridSize, grid);
		}
	}
//------------------------------------------------------------
	if(y == 0){ //leftmost cell check
		//do nothing
	}else {
		if(grid[x][y-1] == id && !ifContain(x, y-1)){ //west cell check
			links.push_back({x,y-1});
			linkCount++;
			checkCells(x, y-1, id, gridSize, grid);
		}
	}
//------------------------------------------------------------
	if(x == 0){ //top cell check
		//do nothing
	}else {
		if(grid[x-1][y] == id && !ifContain(x-1, y)){ //north cell check
			links.push_back({x-1,y});
			linkCount++;
			checkCells(x-1, y, id, gridSize, grid);
		}
	}
//------------------------------------------------------------
	if(y == gridSize - 1){ //rightmost cell check
		//do nothing
	}else {
		if(grid[x][y+1] == id && !ifContain(x, y+1)){ //east cell check
			links.push_back({x,y+1});
			linkCount++;
			checkCells(x, y+1, id, gridSize, grid);
		}
	}
} //end of function checkCells

void popBalloons(int x, int y, int id, int gridSize, vector<vector<int>> & grid){
	for(int i=0;i<gridSize;i++){//north to south popping
		if(grid[i][y] == id){
			point += id;
			grid[i][y] = 0;
		}
	}
	//------------------------------------------------------
	for(int i=0;i<gridSize;i++){//west to east popping
		if(grid[x][i] == id){
			point += id;
			grid[x][i] = 0;
		}
	}
	//------------------------------------------------------
	int temp_x = x; //temp variables to keep first coordinates passed in for diagonal popping
	int temp_y = y;

	while(temp_x >= 0 && temp_y >= 0){ //northwest direction
		if(grid[temp_x][temp_y] == id){
			point += id;
			grid[temp_x][temp_y] = 0;
		}
		temp_x = temp_x - 1;
		temp_y = temp_y - 1;
	}

//++++++++++++++++++++
	temp_x = x;
	temp_y = y;
//++++++++++++++++++++

	while(temp_x < gridSize && temp_y < gridSize){ //southeast direction
		if(grid[temp_x][temp_y] == id){
			point += id;
			grid[temp_x][temp_y] = 0;
		}
		temp_x = temp_x + 1;
		temp_y = temp_y + 1;
	}

//++++++++++++++++++++
	temp_x = x;
	temp_y = y;
//++++++++++++++++++++

	while(temp_x < gridSize && temp_y >= 0){ //southwest direction
		if(grid[temp_x][temp_y] == id){
			point += id;
			grid[temp_x][temp_y] = 0;
		}
		temp_x = temp_x + 1;
		temp_y = temp_y - 1;
	}

//++++++++++++++++++++
	temp_x = x;
	temp_y = y;
//++++++++++++++++++++

	while(temp_x >= 0 && temp_y < gridSize){
		if(grid[temp_x][temp_y] == id){
			point += id;
			grid[temp_x][temp_y] = 0;
		}
		temp_x = temp_x - 1;
		temp_y = temp_y + 1;
	}
}//end of popBalloons function

int main(int argc, char *argv[]) { // M A I N

	fstream new_file;//reading first parts's file
	ofstream output_file;
	new_file.open(argv[1], ios::in);
	string line;
	std::getline(new_file, line);
	gridSize = std::stoi(line); //getting grid size
	std::vector<std::vector<int>> grid(gridSize, std::vector<int>(gridSize)); //initialising grid

	      while(std::getline(new_file, line)){ //placing the balloons while reading the file at the same time
	    	  std::stringstream test(line);
	    	  std::string segment;
	    	  std::vector<std::string> seglist;
	    	  while(std::getline(test, segment, ' ')){
	    		  	  seglist.push_back(segment);
	    	  	  }
	    	  grid[std::stoi(seglist[1])][std::stoi(seglist[2])] = std::stoi(seglist[0]); //placing the balloon
	    	  linkCount++; // add current cell to link count
	    	  links.push_back({std::stoi(seglist[1]),std::stoi(seglist[2])}); //add current cell to links vector
	    	  checkCells(std::stoi(seglist[1]), std::stoi(seglist[2]), std::stoi(seglist[0]), gridSize, grid); // send the information to check function
	    	  while(linkCount >= 3){
	    		  for(vector<int> i : links){ //replacing cell id's other than called cell with 0 and making called cell id+1 afterwards
	    			  if(i==links[0]){
	    				  grid[i[0]][i[1]] += 1; //id + 1
	    				  temp[0] = i[0];
	    				  temp[1] = i[1];
	    				  callerCell[0] = i[0];
	    				  callerCell[1] = i[1];
	    				  continue;
	    			  }
	    			  grid[i[0]][i[1]] = 0;
	    		  }
	    		  links.resize(0); //emptying the links vector
	    		  linkCount = 0;
	    		  if(temp[0] == callerCell[0] && temp[1] == callerCell[1]){
	    			  linkCount ++;
		    		  links.push_back({callerCell[0], callerCell[1]});
		    		  checkCells(temp[0], temp[1], grid[temp[0]][temp[1]], gridSize, grid);
		    	  }
	    	  }//end of inner while
	    	  linkCount = 0; //if !>=3 is the case
    		  links.resize(0);
	      } //end of while

	output_file.open(argv[3], ios::out);  // performing write operation to file//
	output_file << "PART 1:" << endl;
	for(int i=0;i<gridSize;i++){
		for(int j=0;j<gridSize;j++){
			output_file << grid[i][j] << " ";
		}
		output_file << endl;
	}
                                        ////////////////// ^^ FIRST PART COMPLETED ^^ //////////////////
	fstream second_file;
	second_file.open(argv[2], ios::in);//reading second part's file
	std::getline(second_file, line);
	gridSize = std::stoi(line);//size of the grid

	for(int i=0;i<gridSize;i++){
		std::getline(second_file, line);//reading line by line to construct grid
		std::stringstream test(line);
		std::string segment;
		std::vector<std::string> seglist;
		while(std::getline(test, segment, ' ')){
			seglist.push_back(segment);
		}
		for(int j=0;j<gridSize;j++){
			grid[i][j] = std::stoi(seglist[j]);
		}
	}
	while(std::getline(second_file, line)){ //placing bombs
		std::stringstream test(line);
		std::string segment;
		std::vector<std::string> seglist;
		while(std::getline(test, segment, ' ')){
			seglist.push_back(segment);
		}
		if(grid[std::stoi(seglist[0])][std::stoi(seglist[1])] == 0){ //if cell id is 0, continue to next bomb
			continue;
		}else {
			popBalloons(std::stoi(seglist[0]), std::stoi(seglist[1]), grid[std::stoi(seglist[0])][std::stoi(seglist[1])], gridSize, grid);
		}
	}

	output_file << endl <<  "PART 2:" << endl;
	for(int i=0;i<gridSize;i++){
		for(int j=0;j<gridSize;j++){
			output_file << grid[i][j] << " ";
		}
		output_file << endl;
	}
	output_file << "Final Point: " << point << "p";

	new_file.close();
	output_file.close();
	second_file.close();
	return 0;
}
