#include "proj08_market.h"
#include <set>
using std::set;
#include<sstream>
using std::stringstream;
#include<iostream>
using std::cout; using std::endl;
#include <fstream>
using std::ifstream;using std::string;using std::boolalpha;using std::getline;


bool Player::buy(Market &m, string stock, long date, long quantity) 
{// buy function for player
	if (cash >= (quantity*m.get_price(stock, date)) && m.get_price(stock, date) != -1.0) 
	{//if date is valid and enough cash is owned, deduct the cash and add the stock
		cash -= quantity*m.get_price(stock, date);
		stocks[stock] += quantity;
		return true;
	}
	return false; 
}
bool Player::sell(Market &m, string stock, long date, long quantity) 
{//Player sell function
    long year = stringtonum(NumberToString(date).substr(0,4));
	bool isinlist = false;
	for(string i: m.symbol_list)
	{//finds symbol in list
		if (stock == i)
			isinlist = true;
	}
	if (!isinlist || year > 2012 || year < 2001)
		return false;//error case
	if (stocks[stock] >= quantity && m.get_price(stock, date) !=-1.00)
	{// if enough stock is owned and stock and date is valid, add the cash and deduct the stock
		cash += quantity * m.get_price(stock, date);
		stocks[stock] -= quantity;
		return true;
	}
	return false; //returns false otherwise
}
string Player::to_str() 
{//puts player to a formatted string
	stringstream out;
	out << fixed << setprecision(2);
	out << cash << ','; //prints cash
	for (auto i : stocks) 
	{//itterates through stock stl map
		if (i.second > 0)
		{ //if part of stock is owned, report it
			out << i.first << ':' << i.second << ",";
		}
	}
	return out.str().substr(0, out.str().length()-1); //return stringstreams string
}
Player Player::combine(Player& p2) 
{//combines two players
	Player c_p;

	c_p.cash = p2.cash + cash; //adds cash
	p2.cash = 0, cash = 0; //sets both players to 00
	for (auto i : p2.stocks)
	{ //itterates through player 2's owned stocks
		if (i.second > 0)
		{//if stock is owned, add to c_p stocks
			c_p.stocks[i.first] += i.second;
		}
	}
	for (auto i : stocks)
	{//itterates through current players stocks
		if (i.second > 0)
		{ //if stock is owned, add it to c_p stocks
			c_p.stocks[i.first] += i.second;
		}
	}
	return c_p; //return new player
}

template <typename T>
string NumberToString(T Number)
{//borrowed from previous project
	//initializes a stringstream object to store the given value
	stringstream ss;
	//stores the given value in the sstream object
	ss << Number;
	//returns the object (which can be stored as any type)
	return ss.str();
}
double stringtonum(string str) 
{ //borrowed from previous project

	stringstream buffer;
	buffer << str;
	double value;
	buffer >> value;
	return value;
}
Market::Market(string fname) {
	file_name = fname; string line;
	ifstream file(file_name);
	while (getline(file, line)) 
	{ //itterates through file line by line
		string date = line.substr(0, 8); 
		string vecdata = line.substr(13); 
		while (!vecdata.empty()) 
		{ // repeats until str is empty
			while(vecdata.at(0) == ' ') 
			{//erases all spaces at begining
				vecdata.erase(0,1);
			}
			int i = vecdata.find(' '); //finds first instance of space
			stocks[stringtonum(date)].push_back(stringtonum(vecdata.substr(0, i))); //adds the begining up to the first space to the map
			vecdata.erase(0, i); //erases data after it has been added
		}
	}
}
double Market::get_price(string stock, long date) const{
	cout << boolalpha;
	string date_s = NumberToString(date);
	string year = date_s.substr(0, 4); string month = date_s.substr(4, 2); string day = date_s.substr(6); //formats str
	bool validstock = false; int i = 0; //so we can use i outside of loop
	while (i < symbol_list.size()) 
	{ //itterates through the symbol list
		if (symbol_list[i] == stock) 
		{//if found it stops and is a valid stock
			validstock = true;
			break;
		}
		else 
		{//otherwise it goes onto next element
			++i;
		}
	}
	if (!validstock || stringtonum(year) > 2012 || stringtonum(year) < 2001 || stringtonum(month) > 12 || stringtonum(day) > 31)
		return -1.0;//error case
	else 
	{//if not an error
		for (auto iter : stocks) 
		{//itterates through stocks map
			if (iter.first == date) 
			{ //finds correct date
				return iter.second.at(i); //returns the data in same index as the company
			}
		}
	}
	return -1.0; //error case
		
}
pair<double, double> Market::high_low_year(long year, string symbol) {
	bool v_year = false, v_symbol = false; int i = 0; double high = 0.0; double low = 999999.00;
	while (i < symbol_list.size()) 
	{ //itterates through symbol list to find company
		if (symbol_list[i] == symbol) 
		{//if found it stops
			v_symbol = true;
			break;
		}
		else 
		{//otherwise it increments
			++i;
		}
	}
	if (!v_symbol)
		return { -1.0, -1.0 }; //error case
	for (auto itter :stocks) 
	{//itterates through stock map
		if (stringtonum(NumberToString(itter.first).substr(0, 4)) == year)
		{ //if the year is in the key
			v_year = true; //then the year is valid
			if (itter.second.at(i) > high) //if higher than the high, it is new high
				high = itter.second.at(i);
			if (itter.second.at(i) < low) 
			{//if lower than the low, it is new low
				low = itter.second.at(i);
			}
		}
	}
	if(!v_year) //error case
		return { -1.0, -1.0 };
	return { high, low };
}
