#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Task {
    int id;
    string title;
    string category;
    bool done;
};

vector<Task> tasks;
int nextId = 1;
const string FILE_NAME = "tasks.txt";

// ---------------- SAVE ----------------
void saveTasks() {
    ofstream file(FILE_NAME);

    for (int i = 0; i < tasks.size(); i++) {
        file << tasks[i].id << "\n";
        file << tasks[i].title << "\n";
        file << tasks[i].category << "\n";
        file << tasks[i].done << "\n";
    }
}

// ---------------- LOAD ----------------
void loadTasks() {
    ifstream file(FILE_NAME);

    if (!file.is_open()) return;

    tasks.clear();

    Task t;

    while (file >> t.id) {
        file.ignore();
        getline(file, t.title);
        getline(file, t.category);
        file >> t.done;
        file.ignore();

        tasks.push_back(t);

        if (t.id >= nextId)
            nextId = t.id + 1;
    }
}

// ---------------- ADD TASK ----------------
void addTask() {
    Task t;

    cin.ignore();
    t.id = nextId++;
    t.done = false;

    cout << "Enter title: ";
    getline(cin, t.title);

    cout << "Enter category: ";
    getline(cin, t.category);

    tasks.push_back(t);
    saveTasks();

    cout << "Task added successfully!\n";
}

// ---------------- MARK DONE ----------------
void markDone() {
    int id;
    cout << "Enter task ID: ";
    cin >> id;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) {
            tasks[i].done = true;
            saveTasks();
            cout << "Task marked as done!\n";
            return;
        }
    }

    cout << "Task not found!\n";
}

// ---------------- VIEW ----------------
void viewTasks(int mode) {
    cout << "\nID   Title                Category       Status\n";
    cout << "------------------------------------------------\n";

    bool found = false;

    for (int i = 0; i < tasks.size(); i++) {

        if (mode == 1 && tasks[i].done) continue;
        if (mode == 2 && !tasks[i].done) continue;

        cout << setw(4) << tasks[i].id << " "
            << setw(20) << tasks[i].title.substr(0, 18) << " "
            << setw(14) << tasks[i].category.substr(0, 12) << " "
            << (tasks[i].done ? "Done" : "Pending") << "\n";

        found = true;
    }

    if (!found)
        cout << "No tasks found.\n";
}

// ---------------- DELETE ----------------
void deleteTask() {
    int id;
    cout << "Enter ID to delete: ";
    cin >> id;

    for (int i = 0; i < tasks.size(); i++) {
        if (tasks[i].id == id) {
            tasks.erase(tasks.begin() + i);
            saveTasks();
            cout << "Task deleted!\n";
            return;
        }
    }

    cout << "Task not found!\n";
}

// ---------------- MAIN ----------------
int main() {
    loadTasks();

    int choice;

    do {
        cout << "\n===== TO DO APP =====\n";
        cout << "1. Add Task\n";
        cout << "2. Mark Done\n";
        cout << "3. View Pending\n";
        cout << "4. View Completed\n";
        cout << "5. View All\n";
        cout << "6. Delete Task\n";
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1: addTask(); break;
        case 2: markDone(); break;
        case 3: viewTasks(1); break;
        case 4: viewTasks(2); break;
        case 5: viewTasks(0); break;
        case 6: deleteTask(); break;
        }

    } while (choice != 0);

    cout << "Goodbye!\n";

    return 0;
}