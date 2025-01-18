#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//Employee base class
class Employee {
    public:
    string name;
    int userId;

    Employee(string name, int userId) : name(name), userId(userId) {}

    virtual void displayInfo() const {
        cout << "Name: " << name << endl;
        cout << "User Id: " << userId << endl;
    }
};

//Human Resources Employee Class
class HR_Employee : public Employee {
    public:
    HR_Employee(string name, int userId) : Employee(name, userId) {}

    void addEmployee(vector<Employee*>& employees) {
        string newEmployeeName;
        int newUserId;

        cout << "Enter new employee name: ";
        cin >> newEmployeeName;
        cout << "Enter new employee user ID: ";
        cin >> newUserId;

        employees.push_back(new Employee(newEmployeeName, newUserId));
    }

    void viewEmployees(const vector<Employee*>& employees) {
        for (const auto& employee : employees) {
            employee->displayInfo();
            cout << "-------------------" << endl;
        }
    }

    void searchEmployee(const vector<Employee*>& employees, int searchId) {
        for (const auto& employee : employees) {
            if (employee->userId == searchId) {
                employee->displayInfo();
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void modifyEmployee(vector<Employee*>& employees, int modifyId) {
        for (auto& employee : employees) {
            if (employee->userId == modifyId) {
                string newName;
                cout << "Enter new name: ";
                cin >> newName;
                employee->name = newName;
                cout << "Employee modified." << endl;
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void deleteEmployee(vector<Employee*>& employees, int deleteId) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->userId == deleteId) {
                employees.erase(it);
                cout << "Employee deleted." << endl;
                return;
            }
        }
        cout << "Employee not found." << endl;
    }
};

//Management Employee Class
class Manager : public Employee {
    public:
    Manager(string name, int userId) : Employee(name, userId) {}

    void searchEmployee(const vector<Employee*>& employees, int searchId) {
        for (const auto& employee : employees) {
            if (employee->userId == searchId) {
                employee->displayInfo();
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void viewEmployees(const vector<Employee*>& employees) {
        for (const auto& employee : employees) {
            employee->displayInfo();
            cout << "-------------------" << endl;
        }
    }
};

// General Employee Class
class GeneralEmployee : public Employee {
    public:
    GeneralEmployee(string name, int userId) : Employee(name, userId) {}

    void viewOwnInfo() {
        displayInfo();
    }
};

//Login Function
bool login(string username, string password, Employee*& user) {
    if (username == "hr" && password == "hr123") {
        user = new HR_Employee("HR User", 1);
        return true;
    } else if (username == "manager" && password == "manager123") {
        user = new Manager("Manager User", 2);
        return true;
    } else if (username == "employee" && password == "employee123") {
        user = new GeneralEmployee("Employee User", 3);
        return true;
    } else {
        cout << "Invalid username or password." << endl;
        return false;
    }
}

//HR Menu
void hrMenu(HR_Employee* hr, vector<Employee*>& employees) {
    int choice;
    do {
        cout << "\nHR Menu" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View Employees" << endl;
        cout << "3. Search Employee" << endl;
        cout << "4. Modify Employee" << endl;
        cout << "5. Delete Employee" << endl;
        cout << "6. Exit & Logout" << endl;
        cout << "Select Menu Option: ";
        cin >> choice;

        switch (choice) {
            case 1:
            hr->addEmployee(employees);
            break;
            case 2:
            hr->viewEmployees(employees);
            break;
            case 3: {
                int searchId;
                cout << "Enter user ID to search: ";
                cin >> searchId;
                hr->searchEmployee(employees, searchId);
                break;
            }
            case 4: {
                int modifyId;
                cout << "Enter user ID to modify: ";
                cin >> modifyId;
                hr->modifyEmployee(employees, modifyId);
                break;
            }
            case 5: {
                int deleteId;
                cout << "Enter user ID to delete: ";
                cin >> deleteId;
                hr->deleteEmployee(employees, deleteId);
                break;
            }
            case 6:
                cout << "Exiting HR Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);
}

//Manager Menu
void managerMenu(Manager* manager, const vector<Employee*>& employees) {
    int choice;
    do {
        cout << "\nManager Menu" << endl;
        cout << "1. View Employees" << endl;
        cout << "2. Search Employee" << endl;
        cout << "3. Exit & Logout" << endl;
        cin >> choice;

        switch (choice) {
            case 1:
                manager->viewEmployees(employees);
                break;
            case 2: {
                int searchId;
                cout << "Enter user ID to search: ";
                cin >> searchId;
                manager->searchEmployee(employees, searchId);
                break;
            }
            case 3:
                cout << "Exiting Manager Menu..." << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 3);
}

//General Employee Menu
void generalEmployeeMenu(GeneralEmployee* employee) {
    cout << "\nGeneral Employee Menu" << endl;
    employee->viewOwnInfo();
}

int main() {
    vector<Employee*> employees;

    //Sample initial data
    employees.push_back(new Employee("John Doe", 1001));
    employees.push_back(new Employee("Jane Smith", 1002));

    string username, password;
    Employee* user = nullptr;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (login(username, password, user)) {
        if (dynamic_cast<HR_Employee*>(user)) {
            hrMenu(dynamic_cast<HR_Employee*>(user), employees);
        } else if (dynamic_cast<Manager*>(user)) {
            generalEmployeeMenu(dynamic_cast<GeneralEmployee*>(user));
        }
    }

    //Clean up memory
    for (auto& employee : employees) {
        delete employee;
    }
    delete user;

    return 0;
}
