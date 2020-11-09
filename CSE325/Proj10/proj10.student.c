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

string algo = "";
int simParams = 0;
int faults = 0;
int writeBacks = 0;
bool fault = false;
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
struct Entry{
    int frame =0;
    int index = 0x0;
    int V = 0;
    int R = 0;
    int M = 0;
};
struct Page{
  int valid = 0;
  Entry *data = new Entry[8];
};
vector<int> FreeFrames;
vector<Entry> PageQ;
bool writeBack = false;
Page ourP;
//function to initialize the ram


void initP(Page *p)
{
    for(int j=0x0; j<0x08; j+=0x01)
    {    
      p->data[j].index = j;
    }
}
string hitos(int input)
{
  std::stringstream ss;
  ss << input;
  return ss.str();
}

void PrintP(Page *p)
{
  cout <<"\n" << "  V R M FRMN";
  cout <<"\n";
  for(int j=0x0; j<0x08; j+=0x01)
  {
    cout << "\n";
    int *s = new int[4];
    s[0] = p->data[j].index;
    s[1] = p->data[j].V;
    s[2] = p->data[j].R;
    s[3] = p->data[j].M;
    printlnOut(s, 4);     
    cout << " " << setfill('0') << setw(4) <<p->data[j].frame;
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
{ //I manually did the bit shifting because I forgot about bitwise functions
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
int GetFreeFrame()
{
  return -1;
}
bool IsInRam(int index, Page *p)
{
  int i = p->data[index].V;
  if( i == 1)
  {
      return true;
  }
  return false;
}
int GetVictim() 
{
  //if m set too 1, copy from ram to disk
  return 0;
}
void PageReplacement(int i)
{
    int frame = 0;
    if(algo == "FIFO")
    {//fifo algorithm
        Entry temp = PageQ[0];
        frame = temp.frame;
        PageQ.erase(PageQ.begin());
    }
    else//perform clock algorithm
    {
       for(size_t i=0; i<PageQ.size(); i++)
       {
           if(PageQ[i].R == 0)
           {
               frame = PageQ[i].frame;
               PageQ.erase(PageQ.begin() + i);
               break;
           }
           PageQ[i].R = 0;
       }
       if(frame == 0)
       {
           frame = PageQ[0].frame;
       }
    }

    for(int i=0; i<8; i++)
    {//perform the writeback
        if (ourP.data[i].V && ourP.data[i].frame == frame)
        {
            //writeback
            if(ourP.data[i].M == 1)
            {
                writeBack = true;
            }//set the bits
            ourP.data[i].M = 0;
            ourP.data[i].V = 0;
        }
    }
    ourP.data[i].frame = frame;
    ourP.data[i].V = 1;

}
void PageFault(Page *p, int pNum)
{
  faults++;
  fault = true;

  //set the bits
  p->data[pNum].V = 1;
  p->data[pNum].R = 0;
  if(FreeFrames.size() > 0)
  {//if available frames then add frame to Q
      int frame = FreeFrames[0];
      FreeFrames.erase(FreeFrames.begin());
      p->data[pNum].frame = frame;
      PageQ.push_back(p->data[pNum]);
  }
  else
  {//otherwise perform page replacement
    PageReplacement(pNum);
  }

}

int main( int argc, char **argv )
{
    ifstream file;
    int pageNumber =0;
    string frameStrList="";
    file.open("config", ios::in);
    if(file)
    {//gets info from config file
      string StrPageNum ="";
      getline(file,algo);
      getline(file,StrPageNum);
      getline(file, frameStrList);
      vector<string> framelist = Split(frameStrList);

      for(size_t i=0; i<framelist.size();i++)
      {
        FreeFrames.push_back(stoi(framelist[i]));
      }
      pageNumber = stoi(StrPageNum);

      file.close();
      file.clear();
      
    }
    //tells cout to output all numbers in hex
    cout << hex;

    //initialize our page
    initP(&ourP);
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
      PrintP(&ourP);
      //print book
    }    //open the given file and process each line accordingly 
    if(filename != "")
    {
       file.open(filename, ios::in);
    }
    int memRefs =0;
    int writeRefs = 0;
    int readRefs = 0;
    if(filename != "" && file)
    {//process all memory references
      string input = "";
      while(getline(file, input))
      {
        vector<string> args = Split(input);//uses split function
        memRefs++;
        string address = args[0];
        string fOp = args[1];
        int pageNum = stoi(getPageNumber(args[0]));
        int off = stoi(getOffset(args[0]), 0, 16);

        //print out the data members
        cout << "\n" << address;
        cout << " " << fOp[0];
        cout << " " << pageNum;
        cout << " " << off;
        //have to cout the page number and page offset

        if(!IsInRam(pageNum, &ourP))
        {
          PageFault(&ourP, pageNum);
        }
        else
        {
            fault = false;
            writeBack = false;
        }
        if(fault)
        {
            cout << " F";
        }
        else
        {
            cout << "  ";
        }
        if(writeBack)
        {
            writeBacks++;
            cout << " B";
        }
        else
        {
            cout << "  ";
        }

        int PhysicalAdd = (ourP.data[pageNum].frame << 13) | off;

        cout << " " << hex << setw(6) << setfill('0') << PhysicalAdd << endl;
        switch(fOp[0])
        {//switch statement for read/write
        case 'R':
          readRefs++;
          break;
        case 'W':
          {
            ourP.data[pageNum].M = 1;
            writeRefs++;
          } 
        default:
          break;
        }
        if(debug)
        {//if debug is set then print cache before every operation
          PrintP(&ourP);
        }
      }
    }
    else{
      cout << "\nError: filename not found";
    }
    PrintP(&ourP);
    cout << std::dec;
    cout << "\nSimulation Parameters: " << algo << " " << pageNumber << " " << frameStrList ;
    cout << "\nMemory references: " << memRefs;
    cout << "\nRead operations: " << readRefs;
    cout << "\nWrite operations: " << writeRefs;
    cout << "\nPage Faults: " << faults;
    cout << "\nWrite Backs: " << writeBacks;
    //print the cache after the final operation
    //print the book
}
