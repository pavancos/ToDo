
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <ctime>
#include <chrono>
#include <cstring>
#include <cmath>
#include<algorithm>

using namespace std::chrono;
using namespace std;

const string FILENAME = "tasks.txt"; // File name to store tasks

int ID = 0;

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

string toLower(const string& str) {
    string result = str;
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}

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

void addToFile(const todo &task) {
    ofstream file(FILENAME, ios::app);
    if (file.is_open()) {
        file << task.id << "|" << task.task << "|" << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << "|" << task.remDays << endl;
        file.close();
    } else {
        cout << "Unable to open file.";
    }
}

void deleteFromFile(const string &taskName) {
    ifstream fin(FILENAME);
    ofstream fout("temp.txt");
    if (!fin || !fout) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        string name = line.substr(line.find('|') + 1, line.find('|', line.find('|') + 1) - line.find('|') - 1);
        if (name != taskName) {
            fout << line << endl;
        }
    }

    fin.close();
    fout.close();

    remove(FILENAME.c_str());
    rename("temp.txt", FILENAME.c_str());
}

void updateFile(const todo &updatedTask) {
    ifstream fin(FILENAME);
    ofstream fout("temp.txt");
    if (!fin || !fout) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        int id = stoi(line.substr(0, line.find('|')));
        if (id == updatedTask.id) {
            fout << updatedTask.id << "|" << updatedTask.task << "|" << updatedTask.dedLine.tm_mday << "/" << updatedTask.dedLine.tm_mon + 1 << "/" << updatedTask.dedLine.tm_year + 1900 << "|" << updatedTask.remDays << endl;
        } else {
            fout << line << endl;
        }
    }

    fin.close();
    fout.close();

    remove(FILENAME.c_str());
    rename("temp.txt", FILENAME.c_str());
}

void readFromFile() {
    ifstream file(FILENAME);
    if (file.is_open()) {
        todo task;
        char separator; // To capture '|' character
        while (file >> task.id >> separator) {
            getline(file, task.task, '|');
            file >> task.dedLine.tm_mday >> separator >> task.dedLine.tm_mon >> separator >> task.dedLine.tm_year >> separator >> task.remDays;
            file.ignore(numeric_limits<streamsize>::max(), '\n');
            task.dedLine.tm_mon -= 1; // Adjust month to 0-indexed format
            task.dedLine.tm_year -= 1900; // Adjust year to year since 1900
            tasks.push(task);
        }
        file.close();
    } else {
        cout << "Unable to open file.";
    }
}


bool isDuplicateTask(const string& taskName, const struct tm& deadline) {
    priority_queue<todo> temp = tasks;
    while (!temp.empty()) {
        // Compare task names ignoring case and spaces
        string existingTaskName = temp.top().task;
        if (toLower(existingTaskName) == toLower(taskName) &&
            temp.top().dedLine.tm_mday == deadline.tm_mday &&
            temp.top().dedLine.tm_mon == deadline.tm_mon &&
            temp.top().dedLine.tm_year == deadline.tm_year) {
            return true; // Duplicate task found
        }
        temp.pop();
    }
    return false; // No duplicate task found
}

void addtodo() {
    cout << "\n\tEnter new task: ";
    string task;
    cin.ignore();
    getline(cin, task);
    task = toLower(task); // Convert task name to lower case
    // Remove spaces from task name
    task.erase(remove_if(task.begin(), task.end(), ::isspace), task.end());

    struct tm Ded;
    setTime(Ded);
    if (!isValidDate(Ded.tm_mday, Ded.tm_mon + 1, Ded.tm_year + 1900)) {
        cout << "\n\tInvalid date! Task not added.\n";
        return;
    }

    if (isDuplicateTask(task, Ded)) {
        cout << "\n\tThis task already exists with the same name and deadline.\n";
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
    addToFile({ID, task, Ded, Rem});
    cout << "\n\tTask has been added successfully";
}

void print(const todo &task) {
    cout << "\n\tTask ID: " << task.id << endl;
    cout << "\tTask: " << task.task << endl;
    cout << "\tDeadline: " << task.dedLine.tm_mday << "/" << task.dedLine.tm_mon + 1 << "/" << task.dedLine.tm_year + 1900 << endl;
    cout << "\tRemaining Days: " << task.remDays << endl;
}

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
    priority_queue<todo> temp;
    bool found = false;
    while (!tasks.empty()) {
        if (tasks.top().task == task) {
            found = true;
            cout << "\n\tDeleting Task \"" << task << "\"\n";
            deleteFromFile(task);
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
            updateFile(currentTask);
        }
        temp.push(currentTask);
    }
    tasks = temp;
    if (!found) {
        cout << "\n\tTask with name \"" << taskName << "\" not found.\n";
    }
}

int main() {
    readFromFile(); // Load tasks from file when the program starts
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
    return 0;
}
