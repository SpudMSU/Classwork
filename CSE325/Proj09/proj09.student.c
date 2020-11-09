/*
 Spencer D Cassetta

 Cse 325

 Project 7
 
*/


#include <iomanip>
#include <iostream>
#include <vector> // std::cout
#include <fstream>
#include <sstream> 
#include <string.h>
#include <stdio.h>
#include <bitset>
//variables
#define page_size 16
#define data_size 16
using namespace std;

//prints out each element on a single line with a space between elements
//agr::input is the string elements to print
//agr::size is the size of the input
void printlnOut(int *input, int size)
{
  for(int i=0; i<size; i++)
  {
    if(i !=0)
    {
      cout << " ";
    }
    cout << hex << input[i];
  }
}//struct for the PageTable

struct PageTable
{
  struct Page{
    int frame =0;
    struct Entry{
      int index = 0x0;
      int V = 0;
      int R = 0;
      int M = 0;
    };
    Entry *data = new Entry[8];
  };
  Page mem;
};
//function to initialize the ram

void initPT(PageTable *p)
{
    p->mem.frame = 0x0000;
    for(int j=0x0; j<0x08; j+=0x01)
    {    
      p->mem.data[j].index = j;
    }
}

string hitos(int input)
{
  std::stringstream ss;
  ss << input;
  return ss.str();
}

void PrintPT(PageTable *p)
{
  cout << "\n";
  cout <<"\n";
  cout << "<Page Table>";
    cout <<"\n" << "  V R M FRMN";
    cout <<"\n";
    for(int j=0x0; j<0x08; j+=0x01)
    {
      cout << "\n";
      int *s = new int[4];
      s[0] = p->mem.data[j].index;
      s[1] = p->mem.data[j].V;
      s[2] = p->mem.data[j].R;
      s[3] = p->mem.data[j].M;
      printlnOut(s, 4);     
      cout << " " << setfill('0') << setw(4) <<p->mem.frame;
    }
    cout << "\n";
}
//split function to split by spaces
//arg::str is the string to split
vector<string> Split(string str)
{

  //returns a vector
  vector<string> res;

  //uses streams to get rid of spaces
  istringstream iss(str);
  for(string s; iss >> s; )
  {
    res.push_back(s);
  }
  return res;
}



string getOffset(string hexAdd)
{
  string s = hexAdd;
  stringstream ss;
  ss << hex << s;
  unsigned n;
  ss >> n;
  bitset<16> b(n);
  bitset<11> a;
  for(int i=0; i<11; i++)
  {
    a[i] = b[i];
  }
  stringstream res;
  res << hex << uppercase << a.to_ulong();
  return res.str();

}
string getPageNumber(string input)
{
  string s = input;
  stringstream ss;
  ss << hex << s;
  unsigned n;
  ss >> n;
  bitset<16> b(n);
  bitset<3> a;
  for(int i=11, j=0; i<14; i++,j++)
  {
    a[j] = b[i];
  }
  stringstream res;
  res << hex << uppercase << a.to_ulong();
  return res.str();

}

int main( int argc, char **argv )
{
    cout << hex;
    PageTable ourPT;
    initPT(&ourPT);
    //initialize and print cache
    string filename;
    bool debug = false;
    //process the arguments and set variables accordingly 
    for(int i= 1; i<argc;i++)
    {
      string op = argv[i];
      if(op == "-debug")
      {     
        debug = true;
      }
      else if(op == "-refs")
      {
        i++;
        filename = argv[i]; 
      }
      else{
        cout << "\nInvalid Opperation or arguments, ignoring";
      }
    } 
    if(debug)
    {
      PrintPT(&ourPT);
      //print book
    }    //open the given file and process each line accordingly
    ifstream file;
    if(filename != "")
    {
       file.open(filename, ios::in);
    }
    int memRefs =0;
    int writeRefs = 0;
    int readRefs = 0;
    if(filename != "" && file)
    {
      string input = "";
      while(getline(file, input))
      {

        vector<string> args = Split(input);//uses split function
        string address = args[0];
        string fOp = args[1];
        string pageNum = getPageNumber(args[0]);
        string off = getOffset(args[0]);

        //print out the data members
        cout << "\n" << address;
        cout << " " << fOp[0];
        cout << " " << pageNum;
        cout << " " <<off;
        //have to cout the page number and page offset
        memRefs++;
        switch(fOp[0])
        {//switch statement for read/write
        case 'R':
          readRefs++;
          break;
        case 'W':
          {
            writeRefs++;
          } 
        default:
          break;
        }
        if(debug)
        {//if debug is set then print cache before every operation
          PrintPT(&ourPT);
        }
      }
    }
    else{
      cout << "\nError: filename not found";
    }
    PrintPT(&ourPT);
    cout << "\nMemory references: " << memRefs;
    cout << "\nRead operations: " << readRefs;
    cout << "\nWrite operations: " << writeRefs;
    //print the cache after the final operation
    //print the book
}
