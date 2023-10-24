#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct todolist
{
    int id;
    string task;
};

int ID;
void banner();
void addTask();
void showTask();
int searchTask();
void deleteTask();
void updateTask();

int main()
{
    printf("\033c");

    while (true)
    {
        banner();
        cout << "\n\t1. Add Task";
        cout << "\n\t2. Show Task";
        cout << "\n\t3. Search Task";
        cout << "\n\t4. Delete Task";
        cout << "\n\t5. Update Task";

        int choice;
        cout << "\n\tEnter Choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            addTask();
            break;
        case 2:
            showTask();
            break;
        case 3:
            searchTask();
            break;
        case 4:
            deleteTask();
            break;
        case 5:
            updateTask();
            break;

        default:
            break;
        }
    }

    return 0;
}

void banner()
{
    cout << "_______________________________\n"
         << endl;
    cout << "\t    My Todo" << endl;
    cout << "_______________________________" << endl;
}

void addTask()
{
    printf("\033c");
    banner();
    todolist todo;
    cout << "Enter new task: " << endl;
    cin.get();
    getline(cin, todo.task);
    char save;
    cout << "Save? (y/n): ";
    cin >> save;
    if (save == 'y')
    {
        ID++;
        ofstream fout;
        fout.open("todo.txt", ios::app);
        fout << "\n"
             << ID;
        fout << "\n"
             << todo.task;
        fout.close();

        char more;
        cout << "Add more task? (y/n): ";
        cin >> more;

        if (more == 'y')
        {
            addTask();
        }
        else
        {
            printf("\033c");
            cout << "Added Successfully!" << endl;
            return;
        }
    }
    printf("\033c");
}

void showTask()
{
    printf("\033c");
    banner();
    todolist todo;
    ifstream fin;
    fin.open("todo.txt");
    cout << "Task: " << endl;

    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.task != "")
        {
            cout << "\t" << todo.id << ": " << todo.task << endl;
        }
        else
        {
            cout << "\tEmpty!" << endl;
        }
    }

    fin.close();
    char exit;
    cout << "Exit? (y/n): ";
    cin >> exit;
    if (exit != 'y')
    {
        showTask();
    }
    printf("\033c");
}

int searchTask()
{
    printf("\033c");
    banner();
    int id;
    cout << "Enter task id: ";
    cin >> id;
    todolist todo;
    ifstream fin("todo.txt");
    while (!fin.eof())
    {
        fin >> todo.id;
        fin.ignore();
        getline(fin, todo.task);
        if (todo.id == id)
        {
            printf("\033c");
            cout << "\t" << todo.id << ": " << todo.task << endl;
            return id;
        }
    }

    printf("\033c");
    cout << "Not found\n";
    return 0;
}

void deleteTask()
{
    printf("\033c");
    int id = searchTask();

    if (id != 0)
    {
        char del;
        cout << "\n\tDelete? (y/n): ";
        cin >> del;
        if (del == 'y')
        {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;
            while (!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id)
                {
                    tempFile << "\n"
                             << index;
                    tempFile << "\n"
                             << todo.task;
                    index++;
                    ID--;
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            printf("\033c");
            cout << "\n\tDeleted Successfully!" << endl;
        }
        else
        {
            printf("\033c");
            cout << "Not deleted" << endl;
        }
    }
}

void updateTask()
{
    printf("\033c");
    int id = searchTask();

    if (id != 0)
    {
        char update;
        cout << "\n\tUpdate? (y/n): ";
        cin >> update;
        if (update == 'y')
        {
            todolist todo;
            ofstream tempFile;
            tempFile.open("temp.txt");
            ifstream fin;
            fin.open("todo.txt");
            int index = 1;
            while (!fin.eof())
            {
                fin >> todo.id;
                fin.ignore();
                getline(fin, todo.task);
                if (todo.id != id)
                {
                    tempFile << "\n"
                             << index;
                    tempFile << "\n"
                             << todo.task;
                    index++;
                    ID--;
                }
                else
                {
                    printf("\033c");
                    cout << "Enter updated task: " << endl;
                    cin.get();
                    getline(cin, todo.task);
                    char save;
                    cout << "Save? (y/n): ";
                    cin >> save;
                    if (save == 'y')
                    {

                        tempFile << "\n"
                                 << index;

                        tempFile << "\n"
                                 << todo.task;
                    }
                }
            }
            fin.close();
            tempFile.close();
            remove("todo.txt");
            rename("temp.txt", "todo.txt");
            printf("\033c");
            cout << "\n\tDeleted Successfully!" << endl;
        }
        else
        {
            printf("\033c");
            cout << "Not deleted" << endl;
        }
    }
}