#include <iostream>
#include <string>
using namespace std;
std::string num1 = "3141592653589793238462643383279502884197169399375105820974944592";

std::string num2 = "2718281828459045235360287471352662497757247093699959574966967627";

std::string add(std::string num1, std::string num2){
    int c =0;
    std::string result = "";
    auto r1 = num1.rbegin();
    auto r2 = num2.rbegin();
    while(r1!=num1.rend() && r2!=num2.rend()){
        //cout <<*r1 << *r2 << endl;
        int r = *r1-'0'+ *r2-'0' + c;
        result = std::to_string(r%10) + result;
        c = r/10;
        ++r1;++r2;
    }
    while(r1!=num1.rend()){
        int r = *r1-'0' + c;
        result = std::to_string(r%10) + result;
        c = r/10;
        ++r1;
        }
    while(r2!=num2.rend()){
        int r = *r2-'0' + c;
        result = std::to_string(r%10) + result;
        c = r/10;
        ++r2;
        }
        
   // std::cout << "adding "<<result << std::endl;
    if(c)
    result = to_string(c)+result;
    
    return result;
    
}
std::string recur(std::string num1, std::string num2){
    int n = num1.length();
    if(n == 1){
        return std::to_string(stoi(num1) * stoi(num2));
        }
    std::string a = num1.substr(0, n/2);
    std::string b = num1.substr( n/2, std::string::npos);
    std::string c = num2.substr(0, n/2);
    std::string d = num2.substr(n/2, std::string::npos);
    
    //std::cout << a << " " << b << " " << c << " " << d <<" " << std::endl;
    std::string ac = recur(a, c) + std::string( n, '0') ;
    std::string bd = recur(b, d) ;
    
    std::string ad = recur(a, d);
    std::string bc = recur(b, c);
    std::string ad_p_bc = add(ad, bc) + std::string(n/2,'0' );
    // std::cout << ac << " " << bd << " " << ad << " " << bc <<" " << std::endl;
    return add(add(ac, ad_p_bc), bd);
    
    
    
}

int main(){

    std::cout << recur(num1, num2) << std::endl;
    
    
    return 0;
}