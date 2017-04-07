/**
 *  lineCount.cpp
 *
 *  @brief  this program takes one command line argument, which should be
 *          the file title
 *  @author Joseph Londre
 *  @date   4/6/17
 */
#include <iostream>
#include<string.h>
#include<sstream>
#include<fstream>
#include<vector>
#include<limits.h>
#include<map>
using namespace std;
void MERGE(vector<int>&data,int,int,int);
void MERGESORT(vector<int>&data,int,int);

void MERGESORT( vector<int> &data, int p,int r  ){
  if(p < r)
  {
    int q = (p+r)/2;
    MERGESORT(data,p,q);
    MERGESORT(data,q+1,r);
    MERGE(data,p,q,r);
  }
}

void MERGE( vector<int> &data,int p, int q, int r ){
  int n1 = q - p + 1 ;
  int n2 = r - q;
  vector<int> L;
  vector<int> R;
  for(int i = 0;i < n1;i++)
  {
    L.push_back(data[p + i]);
  }
  for(int j = 0;j < n2;j++)
  {
    R.push_back(data[q + j + 1]);
  }

  //sentinal
  int sentinal = INT_MAX;
  L.push_back(sentinal);
  R.push_back(sentinal);

  int i = 0;
  int j = 0;
  for(int k = p;k <= r; k++)
  {
    if(L[i] <= R[j])
    {
      data[k] = L[i];
      i = i + 1;
    }else{
      data[k] = R[j];
      j = j + 1;
    }
  }
}

int main(int argc, char* argv[])
{

  if(argc != 2)
  {
    cerr << "invalid number of arguments" << endl;
    return 0;
  }

  int charCount = 0;
  int lineCount = 0;
  char line1[256];
  vector<int> comparisons;
  vector<int> withspaces;
  map<int,int> MAP;

  ifstream fs;
  fs.open(argv[1]);

  int lineNumber = 0;
  while(fs.getline(line1,256))
  {
    lineNumber++;

    //used for ommitting spaces
    int gcount = fs.gcount();
    for(unsigned int i = 0; i < strlen(line1); i++)
    {
      if(isspace(line1[i]))
        gcount--;
    }
    gcount--;

    //use map to link line number and size
    MAP[gcount] = lineNumber;

    //entering vectors
    comparisons.push_back(gcount);
    withspaces.push_back(fs.gcount());

    //counters
    charCount = charCount + gcount;
    lineCount++;
  }

  MERGESORT(comparisons,0,comparisons.size()-1);
  MERGESORT(withspaces,0,withspaces.size()-1);

  cout << "Number of lines in file = " << lineCount << endl;
  cout << "Number of characters in file = " << charCount << endl;
  cout << endl;
  cout << "Longest line location = line " << MAP[comparisons[comparisons.size()-1]]<< endl;
  cout << "Characters in longest line (with spaces) = " 
    << withspaces[withspaces.size()-1]<< endl;
  cout << "Characters in longest line (without spaces) = " 
    << comparisons[comparisons.size()-1]<< endl;
  return 0;
}
