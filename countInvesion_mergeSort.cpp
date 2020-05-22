#include<fstream>
#include<vector> 
#include <iostream>
using namespace std;
size_t inv_count=0;
vector<int> divCountInv(vector<int> arr){

    if(arr.size() < 2)
        return arr;
    if(arr.size() == 2){
        if(arr[0] > arr[1]){
            inv_count += 1;
            return {arr[1], arr[0]};
        }
        
        return arr;
    }

    auto resultL = divCountInv(vector<int>(arr.begin(), arr.begin()+arr.size()/2));
    auto resultR = divCountInv(vector<int>(arr.begin()+arr.size()/2, arr.end()));

    int li = 0;
    int ri = 0;
    vector<int> result;
    while(li < resultL.size()  && ri < resultR.size()){
        if(resultL[li] > resultR[ri]){
            inv_count += resultL.size()-li;
            result.push_back(resultR[ri]);
            ++ri;
        }
        else {
            result.push_back(resultL[li]);
            ++li;
        }
    }
    while(li < resultL.size()){
        result.push_back(resultL[li]);
        ++li;
    }
    while(ri < resultR.size()){
        result.push_back(resultR[ri]);
        ++ri;
    }
    
    

    return result;

}

int main(){
    vector<int> arr;
    ifstream f;
    f.open("test.txt");
    int i; 
    while(f>>i){
        
        arr.push_back(i);
    }

    arr  = divCountInv(arr);
    cout << inv_count << endl;
    ofstream f2("result.txt", ios::out);

    for(int a: arr)
        f2 << a << endl;
    
    f2.close();
    f.close();

    return 0;

}