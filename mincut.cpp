
#include <fstream>
#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>      // std::stringstream
#include <stdlib.h>     /* srand, rand */
#include <set>
#include <numeric>
#include <algorithm>

using namespace std;

size_t getNumberNodes(vector<pair<int,int>> edges){
    
    set<int> nodes;
    for(auto p : edges){
        nodes.insert(p.first);
        nodes.insert(p.second);
        //if(nodes.size()>10)
         //   break;
    }
    return nodes.size();
    
}
vector<pair<int,int>> mincut(vector<pair<int,int>> edges){
    ///cout << edges.size() << endl;
    while(getNumberNodes(edges) > 2){
    
        srand (time(NULL));
        //cout << edges.size() << " * " << endl;;
    
        int rnd =rand()%(edges.size());
        int fnode = edges[rnd].first;
        int snode = edges[rnd].second;
        //remove edge
        edges.erase(edges.begin()+rnd);
    
        //remove snode
        for(auto &p : edges){
           
            if(p.first == snode)
                    p.first = fnode;
            if(p.second == snode)
                    p.second = fnode;
        }
        

        //remove self edges
        edges.erase(remove_if(edges.begin(), edges.end(), [&](pair<int,int> &in){return in.first == in.second;}), edges.end());
    
    }
    
    return edges;
}



int main(){
    
    ifstream f1; f1.open("/Users/srirams/Documents/algosPractice/git/typeracer/algo/graph.txt");
    string str;
    cout << f1.is_open() << endl;
    vector<pair<int,int>> edges;
    while(getline(f1, str)){
        //cout << str << endl;
        stringstream ss(str);
        int val;
        string s1; int key;
        ss >> key;
        
        while(ss >> val){
            pair<int,int> p = {val,key};
            pair<int,int> p1 = {key, val};
            if((find(edges.begin() , edges.end() , p) == edges.end()) && (find(edges.begin() , edges.end() , p1) == edges.end()))
                edges.push_back({key,val});
        }
        
    }
    int minc = 100000;
    cout << edges.size() <<  endl;
    vector<pair<int,int>> a;
    for(int i =0 ;i < 100; ++i){
        a = mincut(edges);
        int k = a.size();
        minc = (minc<k)?minc:k;
        cout << k << endl;
    }
    cout << "********" << minc << endl;
    return 0;
}
