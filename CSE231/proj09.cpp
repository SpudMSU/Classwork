#include <algorithm>
using std::distance;using std::lower_bound;
#include <string>
using std::string;
#include<sstream>
using std::stringstream;
#include "proj09_mapset.h"
vector<pair<string, long>>::iterator MapSet::find_key(string key) 
{//uses lowerbound to return itterator to first element equal to or greater than passed element
    return lower_bound(v_.begin(), v_.end(), key, [](pair<string, long> p, string key) {return p.first <= key; });;
}
bool MapSet::add(pair<string, long> pair) 
{//adds elements to map in an organized fasion
    if (v_.empty()) 
    {//if the vector is empty then nothing matters, just insert the pair
        v_.insert(v_.begin(), pair);
        return true;
    }
    for (auto i : v_)
    {//checks for duplicates, if found returns false
        if (i.first == pair.first) { return false; }
    }//if not a duplicate use findkey to determine where to insert pair to keep vector organized
    v_.insert(find_key(pair.first), pair);
    return true;
}
MapSet::MapSet(initializer_list<pair<string, long>> list) 
{//initialiser for mapset given a list
    for (auto i : list)
    {//itterates through list and adds elements in an organized fasion
        add(i);
    }
}
size_t MapSet::size() { return v_.size(); } //accessor to private variable
pair<string, long> MapSet::get(string str) 
{//finds a specific pair
    for (auto i : v_)
    {//itterates through vector
        if (i.first == str)
        {//returns pair its looking for
            return i;
        }
    }//returns the default if pair could not be found
    return { "",0 };
}
bool MapSet::update(string str, long val)
{//updates value of a key
    for (auto &i : v_)
    {//itterates through vector (referenced i so we can change the memory value)
        if (i.first == str)
        {//finds the correct key and updates value
            i.second = val;
            return true;
        }
    }//returns false if key could not be found
    return false;
}
bool MapSet::remove(string key)
{//removes key from vector
    for (auto i = v_.begin(); i != v_.end(); ++i)
    {//itterates through vector
        if (i->first == key)
        {//finds the key, then erases it
            v_.erase(i);
            return true;
        }
    }//returns false if key could not be found
    return false;
}
int MapSet::compare(MapSet &map)
{//returns 0, -1, or 1 depending on comparison evaluation
    size_t s;int v;
    if(size() < map.size())
    {//size is smaller and therefore is limit
        s=size();
        v=-1;
    }
    else if(map.size()<size())
    {// mapsize is smaller
        s=map.size();
        v=1;
    }
    else
    {// they are equal
        s=size();
        v=0;
    }
    for (int i = 0; i<s; ++i)
    {//itterate up to the size of smaller map
        if (map.v_.at(i).first > v_.at(i).first) 
        {//if args key is bigger returns -1
            return -1;
        }
        else if (v_.at(i).first>map.v_.at(i).first)
        {//if this key is bigger then returns 1
            return 1;
        }
    }//returns v defined during the defenition of size if all the keys are equal
    return v;
}
MapSet MapSet::mapset_union(MapSet &map)
{
    for (auto i : map.v_)
    {//itterates through passed map and adds it
        add(i);
    }//this works because we only want to add if its not a duplicate
    return *this;
}
MapSet MapSet::mapset_intersection(MapSet &map)
{
    MapSet intersection; MapSet testmap(map);
    for (auto i : v_)
    {//itterates through vector
        if (!testmap.add(i))
        {//if it fails to add to testmap then its a intersection
            intersection.add(i);
        }
    }
    return intersection;
}
ostream& operator<<(ostream &os, MapSet &map) 
{//overloading << to deal with mapsets
    stringstream ss;
    for (auto i : map.v_)
    {//itterates and prints elements of mapset
        ss << i.first << ":" << i.second << ", ";
    }
    return os << ss.str().substr(0, ss.str().length() - 2);
}
