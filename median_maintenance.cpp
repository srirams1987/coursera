#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<int> read_file(){

    string file = "median_maintenance.txt";
    fstream fileObj ;
    fileObj.open(file);
    if(!fileObj.is_open()){
        cout << "Failed " << endl;
        return {};
    }
    int val ;
    vector<int> result;
    while(fileObj >> val)
        result.push_back(val);
    
    return result;

}

int main(){

    auto unsorted_array = read_file();
    auto comp = [](int a, int b){return a > b;};
    priority_queue<int, vector<int>,decltype(comp)> min_heap(comp);
    priority_queue<int> max_heap;
    int size = 0;
    int64_t sum_medians = 0;
    int median = 0;
    for(int i =0;i < unsorted_array.size() ; ++i){
    
            int val  = unsorted_array[i];

            if(i % 2 == 0){  // size is even adding val will make the size odd.
                 if(max_heap.empty())
                    max_heap.push(val);
                else if(val < max_heap.top())
                    max_heap.push(val);
                else{
                    min_heap.push(val);
                    int min_top = min_heap.top();
                    min_heap.pop();
                    max_heap.push(min_top);
                }
            }else{              // size is odd  adding val will make the size even.
               
                if(val > max_heap.top()){
                    min_heap.push(val);
                }else{
                    max_heap.push(val);
                    min_heap.push(max_heap.top());
                    max_heap.pop();
                    
                    }
            }
            cout << val << " max_heap.top() " << max_heap.top() << " min size " << min_heap.size() << " max size " << max_heap.size() << endl;
            sum_medians += max_heap.top();
        
    }
    cout << sum_medians%unsorted_array.size() << endl;

    return 0;
}