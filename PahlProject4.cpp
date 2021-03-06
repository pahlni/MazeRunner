#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

int bruteForceMazeSolver(int i, int j);
int backtrackingMazeSolver(int i, int j);
int greedyMazeSolver(int i, int j);
int divideAndConquerMazeSolver(int i, int j);
int dynamicProgrammingMazeSolver(int i, int j);
int randomizedMazeSolver(int i, int j);

struct maze
{
  int rows;
  int cols;
  char matrix [100][100];
};

maze myMaze;

int main()
{
  //seed random number generator
  srand(time(NULL));
  
  //required variables
  ifstream in;
  in.open("maze.txt");
  char line;
  
  //read the matrix using plain c code, character by character
  in >> myMaze.rows;
  in >> line;
  in >> myMaze.cols;
  cout << "Reading a " << myMaze.rows << " by " << myMaze.cols << " matrix." << endl;
  //Burn the end of line character
  in.ignore(200,'\n');
  for(int i=0; i<myMaze.rows; i++)
    {
      for(int j=0; j<myMaze.cols; j++)
	{
	  in.get( myMaze.matrix[i][j] );
	}
      //Burn the end of line character
      in.ignore(200,'\n');
    }
  
  //Print the empty maze
  for(int i=0; i<myMaze.rows; i++)
    {
      for(int j=0; j<myMaze.cols; j++)
			cout << myMaze.matrix[i][j];
      cout << endl;
    }
  int x=1,y=1;
  
  //Find starting coordinates
  for(int i=0; i<myMaze.rows; i++)
    for(int j=0; j<myMaze.cols; j++)
      if( myMaze.matrix[i][j] == 'S' ){
	x=i;
	y=j;
      }
  
  //Call a recursive mazeSolver

  //store temp maze for next algorithm
  maze temp = myMaze;
  
  int bfDistance = bruteForceMazeSolver(x,y);     //brute force? dnc?
  
  cout << "Brute force distance: " << bfDistance << " units away!" << endl;
  
  //Print solved maze
  for(int i=0; i<myMaze.rows; i++)
    {
      for(int j=0; j<myMaze.cols; j++)
	cout << myMaze.matrix[i][j];
      cout << endl;
    }
  
  
  //get uncomplete maze
  myMaze=temp;
  int rDistance = randomizedMazeSolver(x,y);
  cout << "Randomized distance: " << rDistance << " units away!" << endl;
  
  //Print solved maze
  for(int i=0; i<myMaze.rows; i++)
    {
      for(int j=0; j<myMaze.cols; j++)
	cout << myMaze.matrix[i][j];
      cout << endl;
    }
  
  return 0;
}

int bruteForceMazeSolver(int i, int j)
{
  int ret;
  
  //return 0 if F is found
  if(myMaze.matrix[i-1][j]=='F'||myMaze.matrix[i+1][j]=='F'||
     myMaze.matrix[i][j-1]=='F'||myMaze.matrix[i][j+1]=='F'){
    return 0;
  }

  //move through all open spaces with an opening
  if(myMaze.matrix[i-1][j]==' '){
    //place a . when visited
    myMaze.matrix[i-1][j]='.';
    //move to space
    ret = bruteForceMazeSolver(i-1, j);
    //if the space has more spaces to travel add to the return
    if(ret != -1){
      return 1 + ret;
    }
  }
  if(myMaze.matrix[i+1][j]==' '){
    myMaze.matrix[i+1][j]='.';
    ret = bruteForceMazeSolver(i+1, j);
    if(ret != -1){
      return 1 + ret;
    }
  }
  if(myMaze.matrix[i][j-1]==' '){
    myMaze.matrix[i][j-1]='.';
    ret = bruteForceMazeSolver(i, j-1);
    if(ret != -1){
      return 1 + ret;
    }
  }
  if(myMaze.matrix[i][j+1]==' '){
    myMaze.matrix[i][j+1]='.';
    ret = bruteForceMazeSolver(i, j+1);
    if(ret != -1){
      return 1 + ret;
    }
  }

  //return -1 when there are no open spaces
  return -1;
}
int backtrackingMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int greedyMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int divideAndConquerMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int dynamicProgrammingMazeSolver(int i, int j)
{
    //algorithm goes here
    return -1;
}
int randomizedMazeSolver(int i, int j)
{
  int ret;
  //find the direction to go
  int dir = rand() % 4;

  //return 0 when F is found
  if(myMaze.matrix[i-1][j]=='F'||myMaze.matrix[i+1][j]=='F'||
     myMaze.matrix[i][j-1]=='F'||myMaze.matrix[i][j+1]=='F'){
    return 0;
  }

  //direction up to rand function
  switch(dir){
  case 0:
    //process same as bruteForce
    if(myMaze.matrix[i-1][j]==' '){
      myMaze.matrix[i-1][j]='.';
      ret = randomizedMazeSolver(i-1, j);
      if(ret != -1){
	return 1 + ret;
      }
    }
    break;
  
  case 1:
    if(myMaze.matrix[i+1][j]==' '){
      myMaze.matrix[i+1][j]='.';
      ret = randomizedMazeSolver(i+1, j);
      if(ret != -1){
	return 1 + ret;
      }
    }
    break;

  case 2:
    if(myMaze.matrix[i][j-1]==' '){
      myMaze.matrix[i][j-1]='.';
      ret = randomizedMazeSolver(i, j-1);
      if(ret != -1){
	return 1 + ret;
      }
    }
    break;

  case 3:
    if(myMaze.matrix[i][j+1]==' '){
      myMaze.matrix[i][j+1]='.';
      ret = randomizedMazeSolver(i, j+1);
      if(ret != -1){
	return 1 + ret;
      }
    }
    break;
  }  
  
  //if there are no open spaces go back to the last open space
  if(myMaze.matrix[i-1][j]!=' '&&myMaze.matrix[i+1][j]!=' '&&
     myMaze.matrix[i][j-1]!=' '&&myMaze.matrix[i][j+1]!=' '){
    return -1;
  }
  
  //if there is still somewhere to go try again
  return randomizedMazeSolver(i, j);

}

//recursion!!
//Mark current location
//Base Case: Look north, south, east, west for victory!
//Mark our path
//Try going south if it is open
//Try going north if it is open
//Try going east if it is open
//Try going west if it is open
