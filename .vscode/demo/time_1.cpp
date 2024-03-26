#include <iostream>
#include <string>
#include <cstring>
#include <ctime>
#include <cmath>

using namespace std;

void setTime(struct tm &I) {
    cout << "Enter deadline date (DDMMYYYY): \n";
    string d; 
    cin >> d;
    char arr[d.length() + 1];
    strcpy(arr, d.c_str());
    I.tm_sec = 0;
    I.tm_min = 0; 
    I.tm_hour = 0; 
    I.tm_mday = int(arr[0] - '0') * 10 + int(arr[1] - '0');
    I.tm_mon = int(arr[2] - '0') * 10 + int(arr[3] - '0') - 1; 
    I.tm_year = (int(arr[4] - '0') * 1000) + (int(arr[5] - '0') * 100) + (int(arr[6] - '0') * 10) + (int(arr[7] - '0')) - 1900;
    cout << "Day is: " << I.tm_mday << " " << I.tm_mon + 1 << " " << I.tm_year + 1900 << endl;
}

int main() {
    time_t now;
    struct tm tp, ip;

    now = time(NULL);
    tp = *localtime(&now);
    tp.tm_sec = 0; 
    tp.tm_min = 0; 
    tp.tm_hour = 0;
    cout << "Today is: " << tp.tm_mday << " " << tp.tm_mon + 1 << " " << tp.tm_year + 1900 << endl;

    setTime(ip);
    
    time_t now_seconds = mktime(&tp);
    time_t ip_seconds = mktime(&ip);

    double seconds_difference = difftime(ip_seconds, now_seconds);
    int days_difference = (seconds_difference) / (60 * 60 * 24);

    cout << "Remaining days: " << days_difference << endl;

    return 0;
}
