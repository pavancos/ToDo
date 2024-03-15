#include <iostream>
#include <string>
#include <queue>
#include<ctime>
#include<chrono>
using namespace std::chrono;
using namespace std;
int ID = 0;
struct todo {
    int id;
    string task;
    int priority;
    bool operator<(const todo& other) const {
        return priority > other.priority;
    }
};
priority_queue<todo> tasks;
void addtodo() {
    cout << "\n\tEnter new task: ";
    string task;
    cin.ignore();
    getline(cin, task);
    int priority;
    cout << "\tEnter priority (1-High, 2-Medium, 3-Low): ";
    cin >> priority;
    ID++;
    tasks.push({ID, task, priority});
    cout << "\n\tTask has been added successfully";
}
void print(const todo& task) {
    string priorityStr;
    switch (task.priority) {
        case 1:
            priorityStr = "High";
            break;
        case 2:
            priorityStr = "Medium";
            break;
        case 3:
            priorityStr = "Low";
            break;
        default:
            priorityStr = "NA";
    }
    cout << "\n\tID: " << task.id;
    cout << "\n\tTask: " << task.task;
    cout << "\n\tPriority: " << priorityStr;
}
void readData() {
    cout << "\n\t------------------Your current Tasks in the list--------------------";
    priority_queue<todo> temp = tasks;
    while (!temp.empty()) {
        print(temp.top());
        temp.pop();
    }
}
int searchData() {
    int id;
    cout << "\n\tEnter task id: ";
    cin >> id;
    priority_queue<todo> temp = tasks;
    while (!temp.empty()) {
        if (temp.top().id == id) {
            print(temp.top());
            return id;
        }
        temp.pop();
    }
    return -1;
}
void deleteData() {
    int id = searchData();
    if (id != -1) {
        priority_queue<todo> newTasks;
        while (!tasks.empty()) {
            if (tasks.top().id != id) {
                newTasks.push(tasks.top());
            }
            tasks.pop();
        }
        tasks = newTasks;
        cout << "\n\tTask deleted successfully";
    } else {
        cout << "\n\tTask not found";
    }
}
void updateData() {
    int id = searchData();
    if (id != -1) {
        cout << "\n\tEnter updated task: ";
        string updatedTask;
        cin.ignore();
        getline(cin, updatedTask);
        todo updatedTodo;
        while (!tasks.empty()) {
            if (tasks.top().id == id) {
                updatedTodo = tasks.top();
                updatedTodo.task = updatedTask;
                tasks.pop();
            } else {
                tasks.pop();
            }
        }
        tasks.push(updatedTodo);
        cout << "\n\tTask updated successfully";
    } else {
        cout << "\n\tTask not found";
    }
}
int main() {
    while (true) {
        cout << "\n\n\t1. Add Task";
        cout << "\n\t2. Display Tasks";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";
        cout << "\n\t6. Exit";
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
