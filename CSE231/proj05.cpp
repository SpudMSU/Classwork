#include <iostream>
#include <string>
#include <stdio.h>
#include <ctype.h>
using std::string;
//creates global constant variable alphabet without q
const string alphabet = "abcdefghijklmnoprstuvwxyz";

/*Name:removeDups
Type:string
params:1 string
purpose: function that removes duplicates*/
string removeDups(string str)
{
    //itterates through string
    for(unsigned int i=0; i< str.length(); ++i)
    {
        //itterates through string inside of itterating through string
        for(unsigned int j= i+1; j < str.length(); ++j)
        {
            if(str[i]==str[j] && i != j)
            {
                //removes if it finds another copy within itself
                str.erase(j, 1);
                //resets the nested loop
                j=i+1;
            }
        }
    }
    //returns final product (string)
    return str;
    
}

/*Name: clean_string
Type: string
params: 1 string
purpose:removes all on alphabetical objects and returns all lowercase as well as removes 'q'*/
string clean_string(string s)
{
    //creates loop to itterate through string
    for(unsigned int i=0; i< s.length(); ++i)
    {
        if(!isalpha(s.at(i)) || s[i]=='q')
        { 
        //removes if not alphabetical or if letter q
            s.erase(i, 1); 
            --i;
        }
        else
        {
            //puts it to lowercase if it is alphabetical
            s[i]= tolower(s[i]); 
        }
    } 
    // returns modified string after loop
    return s;
}
/*Name: create_encoding
Type: string
params: 1 string
purpose:creates encoding block used to encrypt messages*/
string create_encoding(string key)
{
    //cleans key
    key = clean_string(key);
    //removes duplicates
    key=removeDups(key); 
    //itterates through alphabet
    for(char alpha = 'a'; alpha <= 'z'; alpha++)
    {
        if(key.find(alpha) == string::npos && alpha != 'q')
        {
            //if letter is not in key and is not q add it to key
            key+= alpha;
        }
    }
    //returns modified key
    return key;
}

/*Name: row
Type: long
params: 1 long
purpose:function to calculate row*/
long row(long index)
{ 
    return index/5;
}
/*Name: col
Type: long
params: 1 long
purpose: function to calculate column*/
long col(long index)
{
    return index%5;
}
/*Name:charAtCords
Type: char
params: 1 string, 2 longs
purpose:  returns character at specific location*/
char charAtCords(string str, long roww, long coll)
{
	return str[(roww*5+coll)];
}

/*Name: encode_digraph
Type: string
params: 3 strings
purpose: encodes message*/
string encode_digraph(string dg, string block1, string block2)
{
    //creates string to store encrypted string
    string encrypted =""; 
    //itterates through dg
    for(unsigned int i=0; i< dg.length(); i+=2)
    {
        //finds row and column of next 2 chars
       long row1 = row(alphabet.find(dg[i])); 
       long col1 = col(alphabet.find(dg[i+1])); 
       long row2 = row(alphabet.find(dg[i+1]));
       long col2 = col(alphabet.find(dg[i]));
       //adds char at coordinates in block 1 to encrypted variable
       encrypted+= charAtCords(block1, row1, col1);
       //adds char at coordinates in block 2 to encrypted variable
       encrypted+=charAtCords(block2, row2, col2);
    }
    //returns encrypted variable
    return encrypted;
}

/*Name: decode_digraph
Type: string
params: 3 strings
purpose:decodes message*/
string decode_digraph(string msg, string key1, string key2)
{
    //creates string to store decrypted string
    string decrypted =""; 
    //itterates through dg
    for(unsigned int i=0; i< msg.length(); i+=2)
    {
         //finds row and column of next 2 chars
       long row1 = row(key1.find(msg[i])); 
       long col1 = col(key2.find(msg[i+1])); 
       long row2 = row(key2.find(msg[i+1])); 
       long col2 = col(key1.find(msg[i]));
       //adds char at coordinates in alphabet to decrypted variable
       decrypted+= charAtCords(alphabet, row1, col1);
       //adds char at coordinates in alphabet to decrypted variable
       decrypted+=charAtCords(alphabet, row2, col2);
    }
    //returns decrypted value
    return decrypted;
}

/*Name: encode
Type: string
params: 3 strings
purpose:performs full encoding process*/
string encode(string msg, string key1, string key2)
{
    //cleans msg
    msg = clean_string(msg);
  	//checks if msg is evenly divisible (factor of 2)
    if((msg.length)()%2 > 0)
    {
        //if not it adds an x
        msg+= 'x';
    }
    //creates encoding for key1 and key2
    key1 = create_encoding(key1);
    key2 = create_encoding(key2);
    //returns final product
    return encode_digraph(msg, key1, key2);
}
/*Name: decode
Type: string
params: 3 strings
purpose:performs full decoding process*/
string decode(string msg, string key1, string key2)
{
    //creates encoding for key1 and key2
    key1 = create_encoding(key1);
    key2= create_encoding(key2);
    //returns final product
    return decode_digraph(msg, key1, key2); 
}

int main(){
    cout << create_encoding("squarespace");
}
