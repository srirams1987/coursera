#include <fstream> 
#include <iostream>
#include <map>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
//#include <pair>
using namespace std;
bool rev = false;
void dfsForward(map<int, vector<int>> &graph,
                    vector<bool> &explored, 
                    int currNode,
                    int s, 
                    int &t, 
                    vector<int> & f, 
                    map<int, int> &leaderMap){

            if(graph.count(currNode) == 0){  // no out going nodes 
                // end
                return;

            }
            if(graph.find(currNode) == graph.end()){
                return ;
            }
            if(explored[currNode]){
                return;
            }
            //cout << currNode << "  , " << endl;  ;
            //cout <<(int) graph[currNode].size() << endl;
            auto &neighbors = graph[currNode];
            explored[currNode] = true;
            for(auto &neighbor: neighbors){
               //cout << currNode << " neighbor " << neighbor << endl;
                if(explored[neighbor]) {
                    continue;
                }
                //explored[neighbor]=true;
                dfsForward(graph, explored, neighbor, s, t,  f, leaderMap);
            }
            ++t;                         // increment finishing time 
           // cout << "times " <<t << endl;
            f[currNode] = t;             //finishing time of node
            if(rev)
                leaderMap[currNode] = s;     // leader node of currNode
            //cout << " completed Node " << currNode << " leader " << s  << endl;

    }
void dfsLoop_forward(map<int, vector<int>> &graph,
                    vector<bool> &explored, 
                    vector<int> &f, 
                    map<int, int> &leaderMap,
                    int totalNumberOfNodes){
        
        int t =0;
        for(int i = totalNumberOfNodes; i>=1 ; --i){
            //cout << "exploring node " << i << endl;
            if(explored[i])
                continue;
            int s = i;
            dfsForward(graph, explored, i, s, t, f, leaderMap);
        }


}



void createGraph(map<int, vector<int>> &graph){
fstream fileobj;
    fileobj.open("/Users/srirams/Documents/coursera/algos/scc.txt");
    
    int from , to;
    if(!fileobj.is_open()){
        cout << "Not Open " << endl;
        return;
        
    }
    while(!fileobj.eof()){
        //from;
        //int to;
        fileobj>> from;
        fileobj>> to;
        graph[from].push_back( to );
       // cout << from<< " " << to << endl;
    }
        //1   to 875714
    //vector<bool> explored(875714, false);
    cout << "graph stats " << graph.size() << endl;
    fileobj.close();

}
int main(){
    map<int, vector<int>> directed_graph ;
    map<int, vector<int>> rev_directed_graph ;
    createGraph(directed_graph);
    
    int nNodes = 875714;
    int sizevec = nNodes + 1;
    vector<bool> explored(sizevec, false);
    
    vector<int> finishingTimes(sizevec, 0);
    map<int, int> leaderMap;
    dfsLoop_forward(directed_graph, explored, finishingTimes, leaderMap, nNodes);

    cout << " *** RESULT *** " << endl;
    //for(auto e : explored)
    //    cout << e << " , ";
//    cout << endl << "finishing times :";

/*
    for(auto f : finishingTimes)
        cout << f << " , ";
/*    cout << endl << "leadermap : " << endl;

    for(auto l : leaderMap)
        cout << l.first << ", " << l.second << endl;
*/
    for(auto i: directed_graph){
        for(auto n : i.second)
        rev_directed_graph[finishingTimes[n]].push_back(finishingTimes[i.first]);
    }

  //  cout << "reversed graph " << endl;
    rev = true;
    /*
    for(auto n : rev_directed_graph){
        cout << n.first << " : ";
        for(auto k : n.second)
            cout << k << ", ";
        cout << endl;
    }
    */
    vector<bool> explored_rev(875714+1, false);
    int t_rev =0;
    vector<int> finishingTimes_rev(875714+1, 0);
    map<int, int> leaderMap_rev;
    
    dfsLoop_forward(rev_directed_graph, explored_rev, finishingTimes_rev, leaderMap_rev, 875714);

    //set<int> leaders(leaderMap_rev.begin(), leaderMap_rev.end());
    map<int,int> leadersCount;
    cout << "leaders " << endl;
    for( auto l : leaderMap_rev){
        //cout << l.first << " " << l.second << endl;
        //auto it = find(finishingTimes.begin(), finishingTimes.end(), l.second) ;
        //leadersCount[(int) std::distance(finishingTimes.begin(), it)]++;
        leadersCount[l.second]++;
        //cout << " ** "<<(int) std::distance(finishingTimes.begin(), it) << endl;;
        }
        auto comp = [](pair<int,int> a, pair<int,int> b){return a.second < b.second;}; 
    priority_queue<pair<int,int>, vector<pair<int,int>>, decltype(comp)> pq(comp);
    cout << "PQ  "<< endl;
    for(auto p :leadersCount){
        pq.push(p);
        }
    cout << "Top 5 " << pq.size()  << endl;
    int top5 = 5;
    while(top5--){
        auto p = pq.top();
        cout<< p.first << " " << p.second << endl;
        pq.pop();//
    }
    return 0;

}
