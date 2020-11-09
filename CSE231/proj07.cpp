#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <fstream>
using std::string; using std::set; using std::ostream; using std::ifstream; using std::cout; using std::endl; using std::vector;
using ServerName = const std::string &; using UserName = const std::string &; using ServerData = std::map<string, std::set<string>>;

string EraseNonAlpha(string str) {
	for (unsigned int i = 0; i < str.length(); ++i)
	{
		if (!isalnum(str[i]))
		{//if not alphabetical/numerical, element gets erased
			str.erase(i);
		}
	}
	return str;
}
bool AddConnection(ServerData &sd, ServerName sn, UserName un)
{
	unsigned int size = sd[sn].size();
	sd[sn].insert(un);
	if (size < sd[sn].size())
	{//compares size before/after to determine if successful
		return true;
	}
	return false;
}
bool DeleteConnection(ServerData &sd, ServerName sn, UserName un)
{
	bool result = sd[sn].erase(un);	
	//erases then returns bool value from erase function
	return result;
}
ServerData ParseServerData(const string &fname)
{
	ifstream f(fname); ServerData server; string str;
	if (f.fail())
	{//if failure exception
		throw std::invalid_argument("invalid_argument");
	}
	while (getline(f, str)) 
	{//itterates line by line through file f
		//finds first space character
		int i = str.find(' '); 
		if (str.at(i + 1) == ' ')
		{//adds 1 if next is also a space
			++i; 
		}
		if (EraseNonAlpha(str.substr(i + 1, i + 5)) == "join")
		{//finds the word join, which is always 1 char after the last space 
			AddConnection(server, EraseNonAlpha(str.substr(i + 6)), EraseNonAlpha(str.substr(0, i))); 
		}
		else if (EraseNonAlpha(str.substr(i + 1, i + 6)) == "leave")
		{//different case if leave b/c leave is 5 chars
			DeleteConnection(server, EraseNonAlpha(str.substr(i + 7)), EraseNonAlpha(str.substr(0, i)));
		}
		else
		{//cmd wasnt join or leave
			throw std::domain_error("domain_error"); 
		}
	}
	return server;
}
void PrintAll(std::ostream &out, const ServerData &sd)
{
	for (auto server : sd)
	{
		//prints server name
		out << server.first << " :";
		for (auto username : server.second) 
		{ //prints all usernames within said server
			out << " " << username;
		}
		out << endl;
	}
}
set<string> AllServers(const ServerData &sd)
{
	set<string> servers;
	for (auto server : sd)
	{//itterates through sd
		servers.insert(server.first); 
		//inserts all keys
	}
	return servers;
}
set<string> AllUsers(const ServerData &sd)
{
	set<string> users;
	for (auto server : sd)
	{//itterates through sd
		for (auto user : server.second)
		{//itterates through set within value of map
			users.insert(user);
		}
	}
	return users;
}
set<string> HasConnections(const ServerData &sd, UserName un)
{
	set<string> ServersC;
	for (auto server : sd)
	{//itterates through sd
		for (auto user : server.second)
		{//set within map 
			if (user == un)
			{//finds username
				ServersC.insert(server.first); 
				//adds server to list
			}
		}
	}
	return ServersC;
}
set<string> HasUsers(const ServerData &sd, ServerName sn) {
	set<string> users;
	for (auto server : sd)
	{//itterates through sd
		if (server.first == sn)
		{//finds server name
			return server.second; 
			//returns the set containing all users
		}
	}
	return users;
}
void BalanceServers(ServerData &sd, ServerName sn1, ServerName sn2) {
	set<string> userSN1 = HasUsers(sd, sn1); 
	//gets all users from both servers
	set<string> userSN2 = HasUsers(sd, sn2);
	for (auto user : userSN2) 
	{//itterates through 2nd server users
		if (userSN1.find(user) != userSN1.end()) 
		{//if it is in other server as well, erase both
			userSN2.erase(user);
			userSN1.erase(user);
		}
		else 
		{//otherwise put it all into sn1
			userSN1.insert(user);
			userSN2.erase(user);
		}
	}
	//easier to find halfway between the elements if its in a vector instead of a set
	vector<string> servVec; 
	for (auto user : userSN1)
	{ //puts all elements in the already alphabetized set into a vector
		servVec.push_back(user);
	}
	int num = 0;
	if (servVec.size() % 2) 
	{//if not even
		num = servVec.size() / 2 + 1;
	}
	else
	{
		num = servVec.size() / 2;
	}
	for (int i = 0; i < servVec.size(); ++i) 
	{//itterates through vector
		if (i < num)
		{ //if element is in first half, erase from server 2 and insert into server 1
			sd[sn1].insert(servVec.at(i));
			sd[sn2].erase(servVec.at(i));
		}
		else 
		{//if second half, erase from server 1 and insert into server 2
			sd[sn2].insert(servVec.at(i));
			sd[sn1].erase(servVec.at(i));
		}
	}
}
void CleanAndBalance(ServerData &sd) {
	set<string> users; set<string> serverList = AllServers(sd);
	for (auto server : sd) 
	{ //itterates through all server data
		set<string> userL = server.second;
		for (string user : userL) 
		{ //itterates through the user list
			bool erased = false;
			for (auto serverIter : sd) 
			{ //itterates through server data again
				if (serverIter.first == server.first) 
				{//if its the same server do nothing
				}
				else if (serverIter.second.find(user) != serverIter.second.end()) 
				{ //if this username is found in other servers erase it from both
					serverIter.second.erase(user);
					if (!erased) 
					{
						server.second.erase(user);
						erased = true;
					}
				}
			}
		}
	}
	users = AllUsers(sd);
	sd.clear();
	while (!users.empty()) 
	{ //runs while there are elements inside of users
		for (auto server : serverList)
		{
			string firstuser;
			for (string user : users) 
			{ //gets the first user 
				firstuser = user;
				break;
			}
			if (!firstuser.empty())  
			{ //checks too see if string is empty. Fix to bug that caused last hidden to fail.
				sd[server].insert(firstuser);
			}
			//erases first element after insertion into sd
			users.erase(firstuser); 
		}
	}
}
