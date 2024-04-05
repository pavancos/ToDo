#include <iostream>
#include <string>
#include <queue>
#include <ctime>
#include <chrono>
#include <fstream>
#include <cstring>
#include <cmath>
#include <cstdlib> // Include library for exit()
using namespace std::chrono;
using namespace std;

const string FILE_NAME = "tasks.txt";

int ID = 0;

// Check if the date is valid
bool isValidDate(int day, int month, int year) {
    if (year < 0 || month < 1 || month > 12 || day < 1 || year < 0 && month < 1 && day < 1)
        return false;
    if (month == 2) {
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

// Convert string to lowercase
string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

// Set deadline time
void setTime(struct tm &I) {
    time_t now = time(0);
    tm *currentTime = localtime(&now);
    cout << "\tEnter deadline date (DD/MM/YYYY): ";
    string d;
    cin >> d;
    int day, month, year;
    sscanf(d.c_str(), "%d/%d/%d", &day, &month, &year);
    if (!isValidDate(day, month, year)) {
        cout << "\tInvalid date format or out of range! Please enter a valid date in DD/MM/YYYY format.\n";
        return;
    }
    if (year < currentTime->tm_year + 1900 ||
        (year == currentTime->tm_year + 1900 && month < currentTime->tm_mon + 1) ||
        (year == currentTime->tm_year + 1900 && month == currentTime->tm_mon + 1 && day < currentTime->tm_mday)) {
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

// Task structure
struct todo {
    int id;
    string task;
    struct tm dedLine;
    int remDays;
    bool operator<(const todo &other) const {
        return remDays > other.remDays;
    }
};

priority_queue<todo> tasks;

// Write task to file
void writeTaskToFile(const todo &task) {
    ofstream outfile(FILE_NAME, ios::app);
    if (outfile.is_open()) {
        outfile << task.task << "\n";
        outfile << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << "\n";
        outfile << task.remDays << "\n";
        outfile.close();
    } else {
        cout << "\n\tUnable to open file to write task.\n";
    }
}

// Remove task from file
void removeTaskFromFile(const string &taskName) {
    ifstream infile(FILE_NAME);
    ofstream outfile("temp.txt");
    if (infile.is_open() && outfile.is_open()) {
        string line;
        bool found = false;
        while (getline(infile, line)) {
            if (line == taskName) {
                for (int i = 0; i < 3; ++i) {
                    getline(infile, line);
                }
                found = true;
            } else {
                outfile << line << "\n";
            }
        }
        infile.close();
        outfile.close();
        remove(FILE_NAME.c_str());
        rename("temp.txt", FILE_NAME.c_str());
        if (!found) {
            cout << "\n\tTask with name \"" << taskName << "\" not found.\n";
        }
    } else {
        cout << "\n\tUnable to open file to delete task.\n";
    }
}

// Read tasks from file
void readTasksFromFile(priority_queue<todo> &tasks) {
    ifstream infile(FILE_NAME);
    if (infile.is_open()) {
        while (!infile.eof()) {
            int id, remDays;
            string task, deadline;
            getline(infile, task);
            if (task.empty()) {
                break;
            }
            getline(infile, deadline);
            infile >> remDays;
            infile.ignore();
            struct tm dedLine;
            sscanf(deadline.c_str(), "%d/%d/%d", &dedLine.tm_mday, &dedLine.tm_mon, &dedLine.tm_year);
            dedLine.tm_mon--; // Adjust month since tm_mon ranges from 0 to 11
            dedLine.tm_year -= 1900; // Adjust year since tm_year is years since 1900
            tasks.push({id, task, dedLine, remDays});
        }
        infile.close();
    } else {
        cout << "\n\tUnable to open tasks file.\n";
    }
}

// Add new task
void addtodo() {
    cout << "\n\tEnter new task: ";
    string task;
    cin.ignore();
    getline(cin, task);
    task = toLower(task);
    struct tm Ded;
    setTime(Ded);
    if (!isValidDate(Ded.tm_mday, Ded.tm_mon + 1, Ded.tm_year + 1900)) {
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
    writeTaskToFile({ID, task, Ded, Rem}); // Write new task to file
}

// Print task information
void print(const todo &task) {
    cout << "\n\tTask ID: " << task.id << endl;
    cout << "\tTask: " << task.task << endl;
    cout << "\tDeadline: " << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << endl;
    cout << "\tRemaining Days: " << task.remDays << endl;
}

// Display all tasks
void readData() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return;
    }
    priority_queue<todo> temp = tasks;
    cout << "\n\tTasks List:\n";
    while (!temp.empty()) {
        print(temp.top());
        temp.pop();
    }
}

// Search tasks by number of days
int searchDataByDays() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return -1;
    }
    int NoOfDays;
    cout << "\n\tEnter the number of days: ";
    cin >> NoOfDays;
    priority_queue<todo> temp = tasks;
    bool found = false;
    while (!temp.empty()) {
        if (temp.top().remDays <= NoOfDays) {
            print(temp.top());
            found = true;
        }
        temp.pop();
    }
    if (!found) {
        cout << "\n\tNo tasks with remaining days less than " << NoOfDays << " found.\n";
    }
    return -1;
}

// Search tasks by date
void searchDataByDate() {
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

// Delete task by name
void deleteData() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return;
    }
    string task;
    cout << "\n\tEnter task name to delete: ";
    cin.ignore();
    getline(cin, task);
    task = toLower(task);
    removeTaskFromFile(task); // Remove task from file
    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty()) {
        if (tasks.top().task == task) {
            found = true;
            cout << "\n\tDeleting Task \"" << task << "\"\n";
            tasks.pop();
        } else {
            temp.push(tasks.top());
            tasks.pop();
        }
    }
    tasks = temp;
    if (!found) {
        cout << "\n\tTask with name \"" << task << "\" not found.\n";
    }
}

// Update task deadline
void update() {
    if (tasks.empty()) {
        cout << "\n\tNo tasks available.\n";
        return;
    }
    string taskName;
    cout << "\n\tEnter the name of the task to update deadline: ";
    cin.ignore();
    getline(cin, taskName);
    taskName = toLower(taskName);
    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty()) {
        todo currentTask = tasks.top();
        tasks.pop();
        if (currentTask.task == taskName) {
            found = true;
            struct tm newDeadline;
            setTime(newDeadline);
            currentTask.dedLine = newDeadline;
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
            writeTaskToFile(currentTask); // Write updated task to file
        }
        temp.push(currentTask);
    }
    tasks = temp;
    if (!found) {
        cout << "\n\tTask with name \"" << taskName << "\" not found.\n";
    }
}

int main() {
    // Check if tasks.txt exists, if not, create it
    ifstream file(FILE_NAME);
    if (!file.good()) {
        ofstream outfile(FILE_NAME);
        if (!outfile) {
            cerr << "Unable to create tasks file!" << endl;
            return EXIT_FAILURE;
        }
        outfile.close();
    }

    readTasksFromFile(tasks); // Read tasks from file
    while (true) {
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. Display Tasks";
        cout << "\n\t3. Search Task by Date";
        cout << "\n\t4. Search Task by Days";
        cout << "\n\t5. Delete Task by Name";
        cout << "\n\t6. Update Task";
        cout << "\n\t7. Exit";

        int choice;
        cout << "\n\n\tEnter choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addtodo();
                break;
            case 2:
                readData();
                break;
            case 3:
                searchDataByDate();
                break;
            case 4:
                searchDataByDays();
                break;
            case 5:
                deleteData();
                break;
            case 6:
                update();
                break;
            case 7:
                cout << "\n\tExiting program...";
                return 0;
            default:
                cout << "\n\tInvalid choice. Please enter a valid option.";
        }
    }
}
