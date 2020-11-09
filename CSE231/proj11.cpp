#ifndef MAP_SET
#define MAP_SET

#include<iostream>
using std::ostream;
#include<string>
using std::string;
#include<utility>
#include<initializer_list>
using std::initializer_list;
#include<sstream>

using std::stringstream;
using std::ostringstream;


//
// Node
//
template<typename K, typename V>
struct Node {
    K first;
    V second;
    Node *next = nullptr;

    Node() = default;
    Node(K, V);
    bool operator<(const Node&) const;
    bool operator==(const Node&) const;
    friend ostream& operator<<(ostream &out, const Node &n) {
        out << n.first << ":" << n.second;
        return out;
    }
};

template<typename K, typename V>
Node<K, V>::Node(K key, V value) {
    first = key;
    second = value;
}

template<typename K, typename V>
bool Node<K, V>::operator<(const Node &n) const {
    return (first<n.first);
}

template<typename K, typename V>
bool Node<K, V>::operator==(const Node &n) const {
    return (first == n.first);
}


//
// MapSet
//
template<typename K, typename V>
class MapSet {
private:
    Node<K, V>* head_ = nullptr;
    Node<K, V>* tail_ = nullptr;
    size_t sz_ = 0;
    Node<K,V>* find_key(K);

public:
    MapSet() = default;
    MapSet(initializer_list< Node<K, V> >);
    MapSet(const MapSet&);
    MapSet operator=(MapSet);
    Node<K,V>& at(long);
    ~MapSet();
    size_t size();
    bool remove(K);
    bool add(Node<K, V>);
    Node<K, V> get(K);
    bool update(K, V);
    int compare(MapSet&);
    MapSet mapset_union(MapSet&);
    MapSet mapset_intersection(MapSet&);

    friend ostream& operator<<(ostream &out, const MapSet &ms) {
        stringstream ss;
        for (Node<K,V>* i=ms.head_; i!= nullptr; i=i->next)
        {//uses node << overload
            ss << *i << ", ";
        }
        out << ss.str().substr(0, ss.str().length() - 2);
        return out;
    }

};
template<typename K, typename V>
Node<K,V>& MapSet<K,V>::at(long index) 
{//used to solve odd remove seg fault
    Node<K,V> *rPtr = head_;
    for (int i = 0; i<index; i++) {
        rPtr = rPtr->next;
    }//finds element at specified index
    return *rPtr;
}

template<typename K, typename V>
MapSet<K, V>::MapSet(initializer_list< Node<K, V> > il) {
    for(auto i:il)
    {//goes through list and adds them
        add(i);
    }
}

template<typename K, typename V>
MapSet<K, V>::MapSet(const MapSet &ms) 
{//used from single link example code
    if (ms.head_ == nullptr)
    {//if ms is empty them so is this instance
        head_ = nullptr;
        tail_ = nullptr;
    }
    else {//otherwise copy the nodes with different addresses
        head_ = new Node<K,V>(ms.head_->first,ms.head_->second);
        tail_ = head_;
        Node<K,V>* sl_ptr = ms.head_->next;
        Node<K,V>* new_node;
        while (sl_ptr != nullptr){
            new_node = new Node<K,V>(sl_ptr->first, sl_ptr->second);
            tail_->next = new_node;
            sl_ptr = sl_ptr->next;
            tail_ = new_node;
        }
    }
}

template<typename K, typename V>
MapSet<K, V> MapSet<K, V>::operator=(MapSet ms) 
{//used from singlelink example code
    swap(head_, ms.head_);
    swap(tail_, ms.tail_);
    return *this;
}//swaps addresses then returns this

// walk down the list, moving head_ but remember it in to_del
// delete each node in turn, the set head_ and tail_
template<typename K, typename V>
MapSet<K, V>::~MapSet() 
{//destructor from singlelink example code
    Node<K,V>* to_del = head_;
    while (to_del !=nullptr){//while there are nodes left
        head_ = head_->next;//increments the head
        delete to_del;//deletes value that was the head
        to_del = head_;//targets the value at the new head
    }//then sets tail and head to null
    head_ = nullptr;
    tail_ = nullptr;
}

template<typename K, typename V>
size_t MapSet<K, V>::size() 
{//accessor for private variable sz_
    return sz_;
}

template<typename K, typename V>
Node<K,V>* MapSet<K,V>::find_key(K key)
{//returns pointer to node that is >=
    for (Node<K,V>* i=head_; i != nullptr; i=i->next)
    {
        if (i->first>=key) 
        {//if it finds the node return it
            return i;
        }
    }//if no nodes were >= then return null
    return nullptr;
}

template<typename K, typename V>
bool MapSet<K, V>::add(Node<K, V> n) 
{// adds node to liked list
    Node<K,V>* pn = new Node<K,V>(n.first,n.second); //created pointer copy of node n to solve for seg faults I got when I used &n
    if(head_== nullptr)
    {//if head_ is null then list is empty
        head_=pn;
        tail_=pn;
        sz_++;
        return true;
    }
    auto pos = find_key(n.first);
    if(pos== nullptr)
    {//if pos is null then it belongs on the very end
        tail_->next=pn;
        tail_=pn;
        sz_++;
        return true;
    }
    else if(pos->first==pn->first)//if it returns something already in there then no need to add
        return false;
    pn->next=pos;//sets pns next to pos
    for (Node<K, V>* i=head_; i!= nullptr ; i=i->next) 
    {//increments linked list to find the node before pos
        if(i==pos)
        {//if it finds pos first then it is the first element in linked list
            head_=pn;
            sz_++;
            return true;
        }
        if(i->next==pos)
        {//otherwise sets it next equal to pn
            i->next=pn;
            sz_++;
            return true;
        }
    }
}

template<typename K, typename V>
bool MapSet<K, V>::remove(K key) 
{//removes node with same key
    int j=0;
    for (Node<K,V>* i = head_; i != nullptr ; i=i->next, ++j) 
    {//increments through linked list to find key
        if(i->first==key)
        {//if it finds it it deletes it and returns true
            delete i;
            --sz_;
            this->at(j-1).next=i->next;
            return true;
        }
    }//if it couldnt find it then it returns false
    return false;
}

template<typename K, typename V>
Node<K, V> MapSet<K, V>::get(K key) 
{//returns node with key
    for (auto i = head_; i != nullptr; i=i->next) 
    {//itterates to find node with key
        if(i->first==key)
        {//returns it
            return *i;
        }
    }
    return {"",0};
}
template<typename K, typename V>
bool MapSet<K, V>::update(K key, V value) {//updates node to new value
    for (auto i = head_; i != nullptr; i=i->next)
    {//itterates through ary_
        if (i->first == key)
        {//if it finds the correct key it updates the node
            i->second=value;
            return true;
        }
    }//returns false if node not found
    return false;
}

template<typename K, typename V>
int MapSet<K, V>::compare(MapSet &ms) {
    {//returns 0, -1, or 1 depending on comparison evaluation
        size_t s;
        int v;
        if (size() < ms.size())
        {//size is smaller and therefore is limit
            v = -1;
        }
        else if (ms.size() < size())
        {
            v = 1;
        }
        else
        {
            v = 0;
        }
        for (auto i = head_, j=ms.head_; i != nullptr &&j!= nullptr; i=i->next, j=j->next)
        {//itterate up to the size of smaller map
            if (j->first > i->first)
            {//if args key is bigger returns -1
                return -1;
            }
            else if (j->first<i->first)
            {//if this key is bigger then returns 1
                return 1;
            }
        }//returns v defined during the defenition of size if all the keys are equal
        return v;
    }
}

template<typename K, typename V>
MapSet<K, V> MapSet<K, V>::mapset_union(MapSet<K, V> &ms) 
{//creates a union between two mapsets
    MapSet<K,V> h=*this;
    for (auto i = ms.head_;  i!= nullptr ; i=i->next) 
    {//adds all elements to h
        h.add(*i);
    }//this works because if value is in both we keep the one from this MapSet
    return h;
}

template<typename K, typename V>
MapSet<K, V> MapSet<K, V>::mapset_intersection(MapSet<K, V> &ms) 
{//creates intersection between two mapsets
    MapSet<K,V> intersection, testmap(ms);
    for (auto i = head_; i != nullptr; i=i->next)
    {//itterates through ary_
        if(!testmap.add(*i))
        {//if it is already in map add to MapSet
            intersection.add(*i);
        }
    }
    return intersection;
}

int main(){
    cout <<1;
    MapSet<string,long> ms;
    cout <<2;
    bool result;
    cout <<3;
    result = ms.add({"bill", 1});
    cout << result;
    result = ms.add({"bill", 2});   
    cout << result;
}
