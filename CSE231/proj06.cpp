#include<iostream>
#include<string>
using std::string;
#include<vector>
using std::vector;
using std::cout;
#include<sstream>
using std::stringstream;
#include<math.h>
using std::endl;
#include<algorithm>
using std::reverse;
/*Name: NumberToString
* return type: String
* parameters: 1 template
* purpose: Converts any number value to string*/
template <typename T>
string NumberToString(T Number)
{
	//initializes a stringstream object to store the given value
	stringstream ss;
	//stores the given value in the sstream object
	ss << Number;
	//returns the object (which can be stored as any type)
	return ss.str();
}

/*Name: vec_2_str
* return type: string
* parameters: 1 const vector<long>
* purpose: Converts a vector of longs to a string with values seperated by commas*/
string vec_2_str(const vector<long>& v)
{
	string str = "";
	//itterates through the vector
	for (unsigned int i = 0; i<v.size(); i++)
	{
		//initializes string object of the number at position i in vector
		string num = NumberToString(v.at(i));
		//checks to see if it is last num
		if ((i + 1) == v.size())
		{
			str += num;
		}
		//if not it adds a comma after
		else
		{
			str += num + ',';
		}
	}
	return str;
}
/*Name: stringtonum
* return type: long
* parameters: 1 str
* purpose: converts strings into longs*/
long stringtonum(string str) {
    //initializes stream
	stringstream buffer; 
	//adds string to the streams buffer
	buffer << str;
	long value;
	//puts the stream buffer into a long
	buffer >> value;
	return value;
}
/*Name: seqIndex
* return type: long
* parameters: 1 long
* purpose: returns the value of sequence at desired index*/
long seqIndex(long index)
{
	return pow(2, index);
}
/*Name: vecSum
* return type: long
* parameters: 1 long, 1 vector
* purpose: takes the sum of a vector*/
long vecSum(long steps, vector<long> vec)
{
	long sum = 0;
	//itterates through vector
	for (unsigned int i = vec.size() - (steps); i< vec.size(); i++)
	{
	    //adds each component to the long, sum
		sum += vec[i];
	}
	return sum;
}
/*Name: gen_nstep_vector
* return type: vector<long>
* parameters: 2 longs
* purpose: generates a vector of the desired fibbonocci sequence*/
vector<long> gen_nstep_vector(long limit, long nstep)
{
	vector<long> vec;
	vec.push_back(1);
	//loop that adds all the values of the nstep sequence vector
	for (unsigned int i = 0; i < nstep - 1; i++)
	{
		vec.push_back(seqIndex(i));
	}
	//loop that calculates the remaining sequence up to the limit
	while (vecSum(nstep, vec) <= limit)
	{
		long sum = vecSum(nstep, vec);
		vec.push_back(sum);
	}
	return vec;
}

/*Name: vectorsumR
* return type: long
* parameters: 1 int, 1 vecor<long>
* purpose: adds vector starting at specific index*/
long vectorsumR(int begin, vector<long> c)
{
    long sum=0;
    //itterates through vector c
    for(int i=begin; i<c.size(); ++i)
    {
        //adds value to sum
        sum+=c[i];
    }
    return sum;
}
/*Name: num_to_nstep_coding
* return type: string
* parameters: 2 longs
* purpose: converts number to nstep binary encoding*/
string num_to_nstep_coding(long num, long nstep)
{
	const vector<long> fibnums = gen_nstep_vector(num, nstep);
	vector<long> selectednums;
	//counts down the vector fibnums
	for (auto i=fibnums.size()-1; i!= 0 && num > 0; --i) 
	{
	    //if the difference between num and fibnums is posotive
		if ((num - fibnums[i]) >= 0) 
		{
		    //takes away fibnums at index i from num
			num -= fibnums[i];
			//puts into selected nums vector
			selectednums.push_back(i);
		}
	}
	string encodedstr="";
	//counts doown selected nums elements
	for(int i=selectednums.size()-1; i>=0; --i){
	    selectednums[i]-=vectorsumR(i+1, selectednums);
	    //adds 0's until it finds element, then adds 1
	    for(int x=0;; ++x )
	    {
	        //end of loop statement
	        if((x+1)==selectednums[i])
	        {
	            encodedstr+="1";
	            break;
	        }
	        else
	        {
	            encodedstr+="0";
	        }
	    }

	}
	return encodedstr;
}

/*Name: num_to_nstep_coding
* return type: string
* parameters: 2 longs
* purpose: converts number to nstep binary encoding*/
long nstep_coding_to_num(const string& coding, const vector<long>& nstep_sequence)
{
	long num =0;
	//adds a 0 to the beggining or coding string
	string binary = '0'+coding; 
	//itterates through binary string
	for(int i=0; i<binary.length(); i++)
	{
	    //if it finds a 1
	    if(binary.at(i)=='1')
	    {
	        //it adds the value at that location in seq vector
	        num+=nstep_sequence[i];
	    }
	}
	return num;
}
