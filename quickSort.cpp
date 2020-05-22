#include <fstream> 
#include <iostream> 
#include <vector>
#include <chrono>
using namespace std;
void p1(vector<int> &arr){
for(auto a : arr)
    cout << a << " " ;
    cout << endl;

}
int totalComp=0;

int partition(vector<int> &arr, int start, int end, int pivot){
    int startind = start;
    swap(arr[start], arr[pivot]);
    ++start;
    int i = start;
    while(start <= end){
        if(arr[start] < arr[startind]){
            swap(arr[start], arr[i]);
            i+=1;
        }
        ++start; 
        //printArr(arr);

    }
    int k;
    //cin >> k;
    swap(arr[i-1], arr[startind]);
    return i-1;
}
void quickSort(vector<int> &arr, int start, int end){
    if( start >= end)
        return ;
    if(arr.empty())
        return ;

    vector<int> median = {start, end, start+((end-start)/2)};
    sort(median.begin(), median.end(), [arr](int a, int b){ return arr[a]<arr[b];});
    //printArr(median);
    
    totalComp += end - start;
    //cout << end - start << endl;

    
    //int res = partition(arr, start, end, start);
    //int res = partition(arr, start, end, end);
    int res = partition(arr, start, end, median[1]);
    
    //cout << arr[res] <<" " <<  res << endl;
    quickSort(arr, start, res-1);
    quickSort(arr, res+1, end);


}
int main(){

    fstream f2;

    f2.open("testQ.txt", ios::in);
    int i;
    vector<int> arr;
    while(f2>>i)
        arr.push_back(i);
    
    //vector<int> arr = {7,6,5,4,3,2,1};
    //arr = {3,8,2,5,1,4,7,6};
    
    //printArr(arr);
    auto tic = chrono::system_clock::now();
    quickSort(arr, 0, arr.size()-1);
    auto toc = chrono::system_clock::now();
    auto timetaken = chrono::duration_cast<chrono::microseconds>(toc - tic);
    cout << " " << totalComp << endl;
    //printArr(arr);


}