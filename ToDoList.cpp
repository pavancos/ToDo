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

void setTime(struct tm &I)
{
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
    cout << "\nTask ID: " << task.id << endl;
    cout << "Task: " << task.task << endl;
    cout << "Deadline: " << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << endl;
    cout << "Remaining Days: " << task.remDays << endl;
}

void readData()
{
    if (tasks.empty())
    {
        cout << "\nNo tasks available.\n";
        return;
    }

    priority_queue<todo> temp = tasks;
    cout << "\nTasks List:\n";
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
        cout << "\nNo tasks available.\n";
        return -1;
    }

    int NoOfDays;
    cout << "\nEnter the number of days: ";
    cin >> NoOfDays;

    priority_queue<todo> temp = tasks;
    bool found = false;
    while (!temp.empty())
    {
        if (temp.top().remDays < NoOfDays)
        {
            print(temp.top());
            found = true;
        }
        temp.pop();
    }

    if (!found)
    {
        cout << "\nNo tasks with remaining days less than " << NoOfDays << " found.\n";
    }
    return -1;
}

void deleteData()
{
    if (tasks.empty())
    {
        cout << "\nNo tasks available.\n";
        return;
    }

    int id;
    cout << "\nEnter task ID to delete: ";
    cin >> id;

    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty())
    {
        if (tasks.top().id == id)
        {
            found = true;
            cout << "\nDeleting Task " << id << ":\n";
            tasks.pop(); // Discard the task to delete
        }
        else
        {
            temp.push(tasks.top());
        }
        tasks.pop();
    }

    tasks = temp;
    if (!found)
    {
        cout << "\nTask with ID " << id << " not found.\n";
    }
}

void updateData()
{
    if (tasks.empty())
    {
        cout << "\nNo tasks available.\n";
        return;
    }

    int id;
    cout << "\nEnter task ID to update: ";
    cin >> id;

    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty())
    {
        if (tasks.top().id == id)
        {
            found = true;
            cout << "\nUpdating Task " << id << ":\n";
            addtodo();
        }
        else
        {
            temp.push(tasks.top());
        }
        tasks.pop();
    }

    tasks = temp;
    if (!found)
    {
        cout << "\nTask with ID " << id << " not found.\n";
    }
}

int main()
{
    while (true)
    {
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. Display Tasks";
        cout << "\n\t3. Search Task by Remaining Days";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";
        cout << "\n\t6. Exit";
        int choice;
        cout << "\n\n\tEnter choice: ";
        cin >> choice;
        switch (choice)
        {
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
            updateData();
            break;
        case 6:
            cout << "\n\tExiting program...";
            return 0;
        default:
            cout << "\n\tInvalid choice. Please enter a valid option.";
        }
    }
}
