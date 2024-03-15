#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include<ctime>
#include<chrono>
using namespace std::chrono;
using namespace std;
void setTime(struct tm &I){
    cout<<"Enter deadline date(DDMMYYYY): \n";
    string d; cin>>d;
    char arr[d.length()+1];
    strcpy(arr, d.c_str());
    I.tm_mday= int(arr[0]-'0')*10+int(arr[1]-'0');
    I.tm_mon= int(arr[2]-'0')*10+int(arr[3]-'0');
    I.tm_year= int(arr[4]-'0')*1000+int(arr[5]-'0')*100+int(arr[6]-'0')*10+int(arr[7]-'0');
    cout<<"Day is: "<<I.tm_mday<<" "<<I.tm_mon<<" "<<I.tm_year<<endl;
}

int main(){
    //getting local time of mach
    time_t now;
    struct tm tp;
    now=time(NULL);
    tp=*localtime(&now);
    cout<<"Today is: "<<tp.tm_mday<<" "<<tp.tm_mon+1<<" "<<tp.tm_year+1900<<endl;
    cout<<"Time now is: "<<tp.tm_hour<<":"<<tp.tm_min<<":"<<tp.tm_sec<<endl;
    struct tm ip;
    setTime(ip);
    return 0;
}