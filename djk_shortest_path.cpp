#include <fstream>
#include <iostream>
#include <map>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

map<int, vector<pair<int,int>>> read_graph( ){
    fstream fileObj;
    fileObj.open("djk_graph.txt");
    if(!fileObj.is_open()){
        cout << "file open failure " << endl;
        return {};
    }
    map<int, vector<pair<int,int>>> graph;
    int i;
    while(!fileObj.eof() ){
        string str, temp;
        getline(fileObj, str);
        stringstream ss(str);
        int node;
        
        ss >> node;
        
        while(ss >> temp){
            auto it = temp.find(',');
            int u = stoi(temp.substr(0, it));
            int v = stoi(temp.substr(it+1));
            graph[node].push_back({u,v});
            

        }
        
    }
    
     return graph;   

}
void shortestDistance( int start, int dest, map<int, vector<pair<int, int>>> &graph, vector<int> A, string B, vector<int> &result){

set<int> X;
X.insert(1);
A[start] = 0;

auto greedyScore = [](int A_v, int lvw){ return A_v + lvw; };

while(X.find(dest) == X.end()){

    int minNeighbor=0;
    int minScore  = 100000;
    for(auto v : X){
        for(auto w : graph[v]){
            if(X.find(w.first) != X.end())   // Only arks from X to V-X
                continue;
            if( greedyScore(A[v], w.second) < minScore ){
                minNeighbor = w.first;
                minScore = greedyScore(A[v], w.second);
            }
        }
    }
    A[minNeighbor] = minScore;
    X.insert(minNeighbor);    
    B += "->"+to_string(minNeighbor);

}

cout << "Shortest Distance : " << A[dest] << " : Path : " << B << endl;
result.push_back(A[dest]);
}
int main(){

    auto graph = read_graph();
    /*
    map<int, vector<pair<int, int>>> graph ;
    graph[1] = { {2,1}, {3,4} };
    graph[2] = { {4,6}, {3,2} };
    graph[3] = { {4,3} };
    graph[4]={};
    */
    cout << "Size of the graph " << graph.size() << endl;
    auto destVertex = {7,37,59,82,99,115,133,165,188,197};
    //auto destVertex = {4};
    vector<int> result;
    for(int dest : destVertex){
        cout << "From: " << 1 << " Dest " << dest << endl;
        vector<int> A(graph.size()+2, 0);

        shortestDistance(1, dest, graph, A, "1", result);
        cout << " *************** " << endl;
    }

    for(int res : result){
        cout << res << " : ";
        }
    cout << endl;
    
// 2599 : 2610 : 2947 : 2052 : 2367 : 2399 : 2029 : 2442 : 2505 : 3068 : 
    return 0;
}