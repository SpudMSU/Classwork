/*
 Spencer D Cassetta

 Cse 325

 Project 7
 
*/



#include <iostream>
#include <vector> // std::cout
#include <fstream>
#include <sstream> 
#include <string.h>
#include <stdio.h>

//variables
#define mem_size 16
#define data_size 16
using namespace std;


//struct for the ram
struct RAM
{
  struct line
  {
    int address;
    int bytes[16][2];
  };
  line *mem = new line[65536];
};

//function to initialize the ram
void InitializeRAM(RAM *ram)
{
  //initialize all 65536 lines
  for(int i=0x00000,j=0; j<65536; i+=0x00010, j++)
  {
    ram ->mem[j].address = i;
    for(int x=0; x<16; x++)
    {
      //set all the bytes to 0
      ram->mem[j].bytes[x][1] = 0x0;
      ram->mem[j].bytes[x][0] = 0x0;
    }
  } 
}

//Prints the ram
void PrintRAM(RAM ram)
{
  cout <<"--------------------------RAM-------------------------";
  for(int i=0x000000; i<0x100000; i+=0x10)
  {
    //only print values between 0x020000 - 0x0200f0
    if(i>=0x020000 && i<= 0x0200f0)
    {
      cout <<"\n";
      cout << ram.mem[i/0x10].address;
      cout << ":";
      for(int j=0; j<16; j++)
      {
        cout << " " << ram.mem[i/0x10].bytes[j][0];
        cout<<ram.mem[i/0x10].bytes[j][1];
      }
    }
  }
  cout << "\n";
}
//defining the cache
struct cache
{
  struct line
  {
    int valid =0;
    int mod = 0;
    string tag = "000";
    string *data = new string[data_size];
  };
  line *mem = new line[mem_size];
};

//reads the cache
void ReadCache(cache c, string index, int offset)
{

  int i = stoi(index,0,16);
  for(int x=0; x<4; x++)
  {
    //read in the first 4 bits at the given address
    cout << " ";
    cout << c.mem[i].data[offset];
    offset++;
  }
}

//write to the cache
void WriteCache(cache *c, string index, int offset, string *bytes)
{
  int i = stoi(index,0,16);
  for(int x=0; x<4; x++)
  {
    //write the data at the address
    c->mem[i].data[offset] = bytes[x];
    offset++;
  }
  //set modifier bit to 1
  c->mem[i].mod = 1;
}
//convertrts hex int to string
string convert_int(int n)
{
  std::stringstream ss;
  ss << hex << n;
  return ss.str();
}

//copies value from ram back to the cache
void RamToCache(cache *c,  RAM *r, string address)
{
  string in(1, address[3]);
  int cacheI = stoi(in,0,16); //cache index
  int rAdd = (stoi(address, 0, 16))/0x10; //ram address
  for(int i=0; i<16; i++)
  {
    //copy the ram address over to cache index
    string newByte = convert_int((r->mem[rAdd].bytes[i][0])) +
      convert_int(r->mem[rAdd].bytes[i][1]);
    c->mem[cacheI].data[i] = newByte;
  }
  //set bits appropriately
  c->mem[cacheI].valid = 1;
  c->mem[cacheI].mod = 0;
  c->mem[cacheI].tag = address.substr(0,3);
}

//check for hit or miss and modifier bits
int CheckCache(cache c, string index, string tag)
{
  int i = stoi(index, 0, 16);
  if(c.mem[i].valid == 0)
  {
    //valid bit not set, its a miss
    return -1;
  }
  if(i>=0x10)
  {
    //invalid input
    return -1;
  }
  if(c.mem[i].tag == tag)
  {
    //hit
    return 1;
  }
  if (c.mem[i].mod == 1)
  {
    //miss and modifier bit is set
    return 0;
  }
  //normal miss
  return -1;
}

//writes back data from the cache to the ram
void WriteBack(RAM *r, cache c, string index)
{
  //get appropriate index's
  int i = stoi(index, 0, 16);
  int address = stoi((c.mem[i].tag+index),0,16);
  for(int x=0; x<16; x++)
  {
    char y =c.mem[i].data[x][0];//get the hex from the data

    //convert the char to a hex int
    int v = (y >= 'A') ? (y >= 'a') ? (y - 'a' + 10) : (y - 'A' + 10) : (y -
        '0');
    r->mem[address].bytes[x][0] = v; //set value;

    //then repeat for other hex value
    y =c.mem[i].data[x][1];
    v = (y >= 'A') ? (y >= 'a') ? (y - 'a' + 10) : (y - 'A' + 10) : (y -
                    '0');
    r->mem[address].bytes[x][1] = v;
  }
}
//sets the cache to null
//arg::c pointer to the cahe to set null
void SetNull(cache *c)
{
  for(int i=0; i<16; i++)
  {
    c->mem[i].valid =0;
    c->mem[i].mod = 0;
    c->mem[i].tag = "000";
    for(int x=0; x<16; x++)
    {
      c->mem[i].data[x] = "00";
    }
  }
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

//prints out each element on a single line with a space between elements
//agr::input is the string elements to print
//agr::size is the size of the input
void printlnOut(string *input, int size)
{
  for(int i=0; i<size; i++)
  {
    if(i !=0)
    {
      cout << " ";
    }
    cout << input[i];
  }
}

//prints out the contents of the cache
//agrs:: c is a cache
void printCache(cache c)
{
  cout << "\n     ---------------------------Cache--------------------------\n";
  cout << "\n     V M    Tag ------------------Data-------------------------\n";
  for(int i=0; i<mem_size; i++)
  {
    cout << "["<<i<<"]: ";
    string in[3];
    in[0] = to_string(c.mem[i].valid);
    in[1] = to_string(c.mem[i].mod);
    in[2] = "000"+c.mem[i].tag;
    printlnOut(in, 3);
    cout << " ";
    printlnOut(c.mem[i].data, data_size);
    cout << "\n";
  }
}
int main( int argc, char **argv )
{
    cout << hex;
    //initialize and print cache
    cache ourCache;
    SetNull(&ourCache);
    RAM myRam;
    InitializeRAM(&myRam);
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
      printCache(ourCache);
    }    //open the given file and process each line accordingly
    ifstream file;
    if(filename != "")
    {
       file.open(filename, ios::in);
    }

    if(filename != "" && file)
    {
      string input = "";
      while(getline(file, input))
      {

        vector<string> args = Split(input);//uses split function
        string address = args[0];
        string fOp = args[1];
        string tag = address.substr(0,3);
        string index(1, address[3]);
        string offset(1,address[4]);
        //print out the data members
        cout << "\n" << address;
        cout << " " << fOp[0];
        cout << " " << index;
        cout << " " << tag;
        cout << " " << offset;
        int hit = CheckCache(ourCache, index, tag);
        if(hit != 1)
        {//if miss,
          cout << " M";
          if(hit == 0)
          {//write back if M is set
            WriteBack(&myRam, ourCache, index);
          }
          //write the cache to the ram
          RamToCache(&ourCache, &myRam, address); 
        }
        else{
          //otherwise its a hit
          cout << " H";
        }
        switch(fOp[0])
        {//switch statement for read/write
        case 'R':
          //perform read
          ReadCache(ourCache, index, stoi(offset,0,16));
          break;
        case 'W':
          {
            //process arguments and perform write
            string *bytes = new string[4];
            bytes[0] = args[2];
            bytes[1] = args[3];
            bytes[2] = args[4];
            bytes[3] = args[5];
            for(int i=0; i<4; i++)
            {
              cout << " " << bytes[i];
            }
            WriteCache(&ourCache, index, stoi(offset,0,16), bytes);
            break;
          } 
        default:
          break;
        }
        if(debug)
        {//if debug is set then print cache before every operation
          printCache(ourCache);
        }
      }
    }
    else{
      cout << "\nError:filename not found";
    }

    //print the cache after the final operation
    printCache(ourCache);

    PrintRAM(myRam);
}
