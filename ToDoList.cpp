#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include <chrono>
#include <cstring>
#include <cmath>
using namespace std::chrono;
using namespace std;
int ID = 0;
bool isValidDate(int day, int month, int year)
{
    if (year < 0 || month < 1 || month > 12 || day < 1 || year < 0 && month < 1 && day < 1)
        return false;
    if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
            return (day <= 29);
        else
            return (day <= 28);
    }
    if (month == 4 || month == 6 || month == 9 || month == 11)
        return (day <= 30);
    else
        return (day <= 31);
}
void setTime(struct tm &I)
{
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    cout << "\tEnter deadline date (DD/MM/YYYY): ";
    string d;
    cin >> d;
    int day, month, year;
    sscanf(d.c_str(), "%d/%d/%d", &day, &month, &year);
    if (!isValidDate(day, month, year))
    {
        cout << "\tInvalid date format or out of range! Please enter a valid date in DD/MM/YYYY format.\n";
        return;
    }
    if (year < currentTime->tm_year + 1900 ||
        (year == currentTime->tm_year + 1900 && month < currentTime->tm_mon + 1) ||
        (year == currentTime->tm_year + 1900 && month == currentTime->tm_mon + 1 && day < currentTime->tm_mday))
    {
        cout << "\tInvalid date! Please enter a future date.\n";
        return;
    }
    I.tm_sec = 0;
    I.tm_min = 0;
    I.tm_hour = 0;
    I.tm_mday = day;
    I.tm_mon = month - 1;
    I.tm_year = year - 1900;
}
struct todo
{
    int id;
    string task;
    struct tm dedLine;
    int remDays;
    bool operator<(const todo &other) const
    {
        return remDays > other.remDays;
    }
};
priority_queue<todo> tasks;
void addtodo()
{
    cout << "\n\tEnter new task: ";
    string task;
    cin.ignore();
    getline(cin, task);
    struct tm Ded;
    setTime(Ded);
    if (!isValidDate(Ded.tm_mday, Ded.tm_mon + 1, Ded.tm_year + 1900))
    {
        cout << "\n\tInvalid date! Task not added.\n";
        return;
    }
    time_t now;
    struct tm tp;
    now = time(NULL);
    tp = *localtime(&now);
    tp.tm_sec = 0;
    tp.tm_min = 0;
    tp.tm_hour = 0;
    time_t now_seconds = mktime(&tp);
    time_t ip_seconds = mktime(&Ded);
    double seconds_difference = difftime(ip_seconds, now_seconds);
    int Rem = (seconds_difference) / (60 * 60 * 24);
    ID++;
    tasks.push({ID, task, Ded, Rem});
    cout << "\n\tTask has been added successfully";
}

void print(const todo &task)
{
    cout << "\n\tTask ID: " << task.id << endl;
    cout << "\tTask: " << task.task << endl;
    cout << "\tDeadline: " << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << endl;
    cout << "\tRemaining Days: " << task.remDays << endl;
}
void readData()
{
    if (tasks.empty())
    {
        cout << "\n\tNo tasks available.\n";
        return;
    }
    priority_queue<todo> temp = tasks;
    cout << "\n\tTasks List:\n";
    while (!temp.empty())
    {
        print(temp.top());
        temp.pop();
    }
}
int searchData()
{
    if (tasks.empty())
    {
        cout << "\n\tNo tasks available.\n";
        return -1;
    }
    int NoOfDays;
    cout << "\n\tEnter the number of days: ";
    cin >> NoOfDays;
    priority_queue<todo> temp = tasks;
    bool found = false;
    while (!temp.empty())
    {
        if (temp.top().remDays <= NoOfDays)
        {
            print(temp.top());
            found = true;
        }
        temp.pop();
    }

    if (!found)
    {
        cout << "\n\tNo tasks with remaining days less than " << NoOfDays << " found.\n";
    }
    return -1;
}
void deleteData()
{
    if (tasks.empty())
    {
        cout << "\n\tNo tasks available.\n";
        return;
    }

    string task;
    cout << "\n\tEnter task name to delete: ";
    cin.ignore();
    getline(cin, task);
    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty())
    {
        if (tasks.top().task == task)
        {
            found = true;
            cout << "\n\tDeleting Task \"" << task << "\":\n";
            tasks.pop();
        }
        else{
            temp.push(tasks.top());
            tasks.pop();
        }
    }
    tasks = temp;
    if (!found)
    {
        cout << "\n\tTask with name \"" << task << "\" not found.\n";
    }
}
int main()
{
    while (true)
    {
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. Display Tasks";
        cout << "\n\t3. Search Task by Remaining Days";
        cout << "\n\t4. Delete Task by Name";
        cout << "\n\t5. Exit";
        int choice;
        cout << "\n\n\tEnter choice: ";
        cin >> choice;
        switch (choice){
        case 1:
            addtodo();
            break;
        case 2:
            readData();
            break;
        case 3:
            searchData();
            break;
        case 4:
            deleteData();
            break;
        case 5:
            cout << "\n\tExiting program...\n";
            return 0;
        default:
            cout << "\n\tInvalid choice. Please enter a valid option.";
        }
    }
}