#include <iostream>
#include <string>
#include <queue>
#include<ctime>
#include<chrono>
using namespace std::chrono;
using namespace std;
int main(){
    //getting local time of mach
    time_t now;
    struct tm tp;
    now=time(NULL);
    tp=*localtime(&now);
    cout<<"Today is: "<<tp.tm_mday<<" "<<tp.tm_mon+1<<" "<<tp.tm_year+1900<<endl;
    cout<<"Time now is: "<<tp.tm_hour<<":"<<tp.tm_min<<":"<<tp.tm_sec<<endl;
    
    return 0;

}