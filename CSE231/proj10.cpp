#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<vector>
using std::vector;
#include<utility>
using std::pair;
#include<initializer_list>
using std::initializer_list;
#include<algorithm>
using std::sort; using std::lower_bound;using std::distance;using std::swap;using std::copy;
#include<sstream>
using std::ostringstream;
//
// Node
//
template<typename K, typename V>
struct Node {//structure for a node
    K first;
    V second;
    Node() = default;
    Node(K,V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    friend ostream& operator<<(ostream &out, const Node &n){
        out << n.first <<":" << n.second;
        return out;
    }
};

template<typename K, typename V>
Node<K,V>::Node(K key, V value)
{//node constructor
    first=key;
    second=value;
}

template<typename K, typename V>
bool Node<K,V>::operator<(const Node &n) const
{//< overload
    return (first>n.first);
}

template<typename K, typename V>
bool Node<K,V>::operator==(const Node &n) const
{//== overload
    return (first==n.first);
}
//MapSet
template<typename K, typename V>
class MapSet {//MapSet class structure
private:
    Node<K, V> *ary_;
    size_t capacity_;
    int sz;
    Node<K, V> *find_key(K);
    void cleanarr(); 
    void grow();
public:
    MapSet( int sz=2);
    MapSet(initializer_list<Node<K, V> >);
    MapSet(const MapSet &);
    MapSet operator=(MapSet);
    ~MapSet();
    size_t size();
    bool remove(K);
    bool add(Node<K, V>);
    Node<K, V> get(K);
    bool update(K, V);
    int compare(MapSet &);
    MapSet mapset_union(MapSet &);
    MapSet mapset_intersection(MapSet &);
    friend ostream &operator<<(ostream &out, const MapSet &ms)
    {//overloads output operator to properly print MapSet Items
        ostringstream oss;
        for (int i = 0; i < ms.capacity_; ++i) 
        {
            if(isalpha(ms.ary_[i].first[0]))//if it is alphabetical, print
                oss << ms.ary_[i].first << ":" << ms.ary_[i].second << ", ";

        }
        out << oss.str().substr(0, oss.str().length() - 2);
        return out;
    }
};
template<typename K, typename V>
MapSet<K, V>::MapSet(int size)
{//class constructor
    ary_ = new Node<K, V>[size];
    capacity_ = size;
    sz=0;
}
template<typename K, typename V>
void MapSet<K, V>::grow()
{//doubles capacity
    Node<K, V> *nArr=new Node<K, V>[capacity_ * 2];
    copy(ary_,ary_+size(), nArr);
    delete[] ary_;
    swap(ary_, nArr);
    capacity_*=2;
}

template<typename K, typename V>
void MapSet<K, V>::cleanarr()
{//removes any empty spaces from ary_
    Node<K, V> *Arr = new Node<K,V>[sz];//creates new array
    int j=0;//to track # of elements added
    for (int i = 0; i < capacity_; ++i)
    {//if key is alphabetical, it adds it to the new array
        if((ary_[i].first[0]) >= 'a' && ary_[i].first[0] <= 'z'){
            Arr[j] = ary_[i];
            ++j;
        }
    }//deletes ary_ and swaps Arrs memory address with it
    delete[] ary_;
    swap(ary_, Arr);
    capacity_=sz;
    sz=j;
}

template<typename K, typename V>
Node<K, V> *MapSet<K, V>::find_key(K key)
{//finds correct place to put value
    return lower_bound(ary_, ary_ + sz, key, [](Node<K, V> n, K key ) { return key>=n.first;});;
}

template<typename K, typename V>
bool MapSet<K, V>::add(Node<K, V> n) 
{
    for (int i = 0; i < capacity_; ++i) 
    {//returns false if item is in array
        if (n == ary_[i]) { return false; }
    }
    if((sz+1)>=capacity_)
    {//we need atleast 1 extra space for shifting elements 
        grow();
    }
    auto pos = distance(ary_, find_key(n.first));
    if(ary_[pos].first!="")
    {//if position is taken,
        for (int i = sz-1; i >= pos ; --i)
        {//shifts the Nodes to place new node in correct position
            ary_[i+1]=ary_[i];
        }
    }//increments size and cleans the array when complete
    ary_[pos] = n;
    sz++;
    cleanarr();
    return true;
}

template<typename K, typename V>
MapSet<K, V>::MapSet(initializer_list<Node<K, V> > il) 
{//constructor for MapSet given a list
    ary_ = new Node<K, V>[il.size()];
    capacity_=il.size();
    sz = il.size();
    for (auto i: il) {
        add(i);
    }
}


template<typename K, typename V>
MapSet<K, V>::MapSet(const MapSet &ms) 
{//constructor for mapset given a mapset
    ary_ = new Node<K,V> [ms.sz];
    copy(ms.ary_, ms.ary_ + ms.sz, ary_);
    sz=ms.sz;
    capacity_ = ms.capacity_;
}

template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::operator=(MapSet<K,V> ms)
{//= operator overload
    delete [] ary_;
    capacity_ = ms.capacity_;
    ary_= new Node<K,V> [ms.sz];
    copy(ms.ary_, ms.ary_ + ms.sz, ary_);
    return *this;
}

template<typename K, typename V>
MapSet<K, V>::~MapSet() 
{//MapSet destructor
    delete[] ary_;
}

template<typename K, typename V>
size_t MapSet<K, V>::size() 
{//size accessor
    return sz;
}

template<typename K, typename V>
bool MapSet<K, V>::remove(K key) 
{//removes element from ary_
    bool isin = false; int index = 0;
    for (int i = 0; i < capacity_; ++i) 
    {//finds element in std::array<T, N> ;
        if (key == ary_[i].first) { isin = true, index = i; }
    }
    if (!isin) { return false; } //returns false if not in ary_
    ary_[index].second = 0;//sets value to defualt
    ary_[index].first="";
    cleanarr();// then cleans array
    return true;
}

template<typename K, typename V>
Node<K, V> MapSet<K, V>::get(K key) 
{//retrieves specified node from ary_
    for (int i = 0; i < size(); ++i) 
    {//itterates through ary_
        if (ary_[i].first == key) 
        {//finds the key, then returns node
            return ary_[i];
        }
    }//returns defualt if not found
    Node<K, V> def("", 0);
    return def;
}

template<typename K, typename V>
bool MapSet<K, V>::update(K key, V value) 
{//updates node to new value
    for (int i = 0; i < size(); ++i) 
    {//itterates through ary_
        if (ary_[i].first == key) 
        {//if it finds the correct key it updates the node
            ary_[i]={ary_[i].first, value};
            return true;
        }
    }//returns false if node not found
    return false;
}

template<typename K, typename V>
int MapSet<K, V>::compare(MapSet &ms) 
{//returns an int based on coparing two different nodes
    {//returns 0, -1, or 1 depending on comparison evaluation
        size_t s;
        int v;
        if (size() < ms.size()) 
        {//size is smaller and therefore is limit
            s = size();
            v = -1;
        } 
        else if (ms.size() < size()) 
        {// mapsize is smaller
            s = ms.size();
            v = 1;
        } 
        else 
        {// they are equal
            s = size();
            v = 0;
        }
        for (int i = 0; i < s; ++i) 
        {//itterate up to the size of smaller map
            if (ms.ary_[i].first > this->ary_[i].first)
            {//if args key is bigger returns -1
                return -1;
            }
            else if (ms.ary_[i].first < this->ary_[i].first)
            {//if this key is bigger then returns 1
                return 1;
            }
        }//returns v defined during the defenition of size if all the keys are equal
        return v;
    }
}

template<typename K, typename V>
MapSet <K, V> MapSet<K, V>::mapset_union(MapSet <K, V> &ms) 
{//creates a union between two maps
    for (int i = 0; i <ms.sz ; ++i) 
    {//if it is already in ary_ value will not be added
        add(ms.ary_[i]);
    }//this works because if value is in both we keep the one from this MapSet
    return *this;
}
template<typename K, typename V>
MapSet<K,V> MapSet<K,V>::mapset_intersection(MapSet<K,V> &ms) 
{//returns a MapSet of nodes that were in both maps
    MapSet<K,V> intersection, testmap(ms);
    for (int i = 0; i < sz; ++i)
    {//itterates through ary_
        if(!testmap.add(ary_[i]))
        {//if it is already in map add to MapSet
            intersection.add(ary_[i]);
        }
    }
    return intersection;
}

int main (){
    MapSet<string,long> ms1({ {"bill",1},{"alan",2},{"abby",3} });
    MapSet<string, long> ms2({ {"alan",4},{"abby", 5},{"john",7} });
    MapSet<string, long> ms3({ {"abby",5}, {"alan",17} });
    MapSet<string,long> ms_union = ms1.mapset_union(ms2);
    ostringstream oss;
    oss << ms_union;
    string result1 = oss.str();
    string ans1 = "abby:3, alan:2, bill:1, john:7";
    cout<<(result1==ans1);
    MapSet<string,long> m =ms2.mapset_union(ms1);
    oss.str("");
    oss << m;
    string result2 = oss.str();
    string ans2 = "abby:5, alan:4, bill:1, john:7";
    cout<<(ans2==result2);

}
