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

void setTime(struct tm &I){
    cout << "\tEnter deadline date (DDMMYYYY): ";
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

// Function to convert a string to lowercase
string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

struct todo{
    int id;
    string task;
    struct tm dedLine;
    int remDays;

    bool operator<(const todo &other) const{
        return remDays > other.remDays;
    }
};

priority_queue<todo> tasks;

void addtodo(){
    cout << "\n\tEnter new task: ";
    string task;
    cin.ignore();
    getline(cin, task);

     // Convert task to lowercase
    task = toLower(task);

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

void print(const todo &task){
    cout << "\n\tTask ID: " << task.id << endl;
    cout << "\tTask: " << task.task << endl;
    cout << "\tDeadline: " << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << endl;
    cout << "\tRemaining Days: " << task.remDays << endl;
}

void readData(){
    if (tasks.empty()){
        cout << "\n\tNo tasks available.\n";
        return;
    }

    priority_queue<todo> temp = tasks;

    cout << "\n\tTasks List:\n";
    while (!temp.empty()){
        print(temp.top());
        temp.pop();
    }
}

void searchData() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return;
    }

    struct tm input_date;
    setTime(input_date);

    struct tm input_date_copy = input_date;
    time_t input_time = mktime(&input_date_copy);

    priority_queue<todo> temp = tasks;

    bool found = false;
    while (!temp.empty()) {
       struct tm task_deadline = temp.top().dedLine;
       time_t task_time = mktime(&task_deadline);
    if (task_time != -1 && task_time <= input_time) {
        print(temp.top());
        found = true;
       }
    temp.pop();
    }

    if (!found) {
        cout << "\n\tNo tasks found with deadlines on or before the specified date.\n";
    }
}

void deleteData(){
    if (tasks.empty()){
        cout << "\n\tNo tasks available.\n";
        return;
    }

    string task;
    cout << "\n\tEnter task name to delete: ";
    cin.ignore();
    getline(cin, task);

     // Convert task to lowercase
    task = toLower(task);

    priority_queue<todo> temp;

    bool found = false;
    while (!tasks.empty()){
        if (tasks.top().task == task){
            found = true;
            cout << "\n\tDeleting Task \""<< task << "\"\n";
            tasks.pop(); // Discard the task to delete
        }
        else{
            temp.push(tasks.top());
            tasks.pop();
        }
    }
    tasks = temp;
    if (!found){
        cout << "\n\tTask with name \"" << task << "\" not found.\n";
    }
}

void update() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return;
    }

    string taskName;
    cout << "\n\tEnter the name of the task to update deadline: ";
    cin.ignore();
    getline(cin, taskName);

     // Convert taskName to lowercase
    taskName = toLower(taskName);

    priority_queue<todo> temp;

    bool found = false;
    while (!tasks.empty()) {
        todo currentTask = tasks.top(); // Get a copy of the top task
        tasks.pop(); // Remove the top task from the original queue
        if (currentTask.task == taskName) {
            found = true;
            struct tm newDeadline;
            setTime(newDeadline);
            currentTask.dedLine = newDeadline; // Modify the deadline of the copy

            // Recalculate remaining days based on the new deadline
            time_t now;
            struct tm tp;
            now = time(NULL);
            tp = *localtime(&now);
            tp.tm_sec = 0;
            tp.tm_min = 0;
            tp.tm_hour = 0;
            time_t now_seconds = mktime(&tp);
            time_t ip_seconds = mktime(&newDeadline);
            double seconds_difference = difftime(ip_seconds, now_seconds);
            int Rem = (seconds_difference) / (60 * 60 * 24);
            currentTask.remDays = Rem;
            cout << "\n\tDeadline updated successfully for Task \"" << taskName << "\"" << endl;
        }
        temp.push(currentTask); // Push the modified or unmodified task into the temporary queue
    }
    tasks = temp; // Assign the modified queue back to the original

    if (!found) {
        cout << "\n\tTask with name \"" << taskName << "\" not found.\n";
    }
}



int main(){
    while (true){
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. Display Tasks";
        cout << "\n\t3. Search Task by Remaining Days";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";
        cout << "\n\t6. Exit";
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
            update();
            break;
        case 6:
            cout << "\n\tExiting program...";
            return 0;
        default:
            cout << "\n\tInvalid choice. Please enter a valid option.";
        }
    }
}
