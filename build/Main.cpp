#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

// Employee base class
class Employee {
public:
    string firstName;
    string lastName;
    int userId;
    string username;
    string password;
    string employeeType;

    Employee(string firstName, string lastName, int userId, string username, string password, string employeeType) 
        : firstName(firstName), lastName(lastName), userId(userId), username(username), password(password), employeeType(employeeType) {}

    virtual void displayInfo() const {
        cout << "Name: " << firstName << " " << lastName << endl;
        cout << "User ID: " << userId << endl;
        cout << "Employee Type: " << employeeType << endl;
    }
};

// Human Resources employee class
class HR_Employee : public Employee {
public:
    HR_Employee(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "HR") {}
};

// Management employee class
class Manager : public Employee {
public:
    Manager(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "Manager") {}
};

// General employee class
class GeneralEmployee : public Employee {
public:
    GeneralEmployee(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "Employee") {}
};

// Function to create sample employees
void createSampleEmployees(vector<Employee*>& employees) {
    employees.push_back(new HR_Employee("John", "Doe", 101, "hr1", "hr123", "HR"));
    employees.push_back(new Manager("Jane", "Smith", 102, "manager1", "manager123", "Manager"));
    employees.push_back(new GeneralEmployee("David", "Lee", 103, "employee1", "employee123", "Employee"));
    employees.push_back(new GeneralEmployee("Mary", "Johnson", 104, "employee2", "employee234", "Employee"));
    employees.push_back(new Manager("Michael", "Brown", 105, "manager2", "manager456", "Manager"));
    employees.push_back(new HR_Employee("Sarah", "Williams", 106, "hr2", "hr456", "HR"));
    employees.push_back(new GeneralEmployee("James", "Wilson", 107, "employee3", "employee567", "Employee"));
    employees.push_back(new GeneralEmployee("Emily", "Davis", 108, "employee4", "employee678", "Employee"));
    employees.push_back(new Manager("Robert", "Jones", 109, "manager3", "manager789", "Manager"));
    employees.push_back(new GeneralEmployee("Christopher", "Anderson", 110, "employee5", "employee890", "Employee"));
}

// Login function
bool login(string username, string password, vector<Employee*>& employees, Employee*& user) {
    for (auto& employee : employees) {
        if (employee->username == username && employee->password == password) {
            user = employee;
            return true;
        }
    }
    cout << "Invalid username or password." << endl;
    return false;
}

// HR menu
void hrMenu(HR_Employee* hr, vector<Employee*>& employees) {
    int choice;
    do {
        cout << "\nHR Menu:" << endl;
        cout << "1. Add Employee" << endl;
        cout << "2. View All Employees" << endl;
        cout << "3. Search Employee" << endl;
        cout << "4. Modify Employee" << endl;
        cout << "5. Delete Employee" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string firstName, lastName, employeeType;
                int userId;
                string username, password;

                cout << "Enter new employee first name: ";
                cin >> firstName;
                cout << "Enter new employee last name: ";
                cin >> lastName;
                cout << "Enter new employee user ID: ";
                cin >> userId;
                cout << "Enter employee type (HR, Manager, Employee): ";
                cin >> employeeType;
                cout << "Enter new employee username: ";
                cin >> username;
                cout << "Enter new employee password: ";
                cin >> password;

                if (employeeType == "HR") {
                    employees.push_back(new HR_Employee(firstName, lastName, userId, username, password));
                } else if (employeeType == "Manager") {
                    employees.push_back(new Manager(firstName, lastName, userId, username, password));
                } else if (employeeType == "Employee") {
                    employees.push_back(new GeneralEmployee(firstName, lastName, userId, username, password));
                } else {
                    cout << "Invalid employee type." << endl;
                    continue; // Skip to next iteration of the loop
                }

                cout << "Employee added successfully." << endl;
                break;
            }
            case 2:
                hr->viewEmployees(employees); 
                break;
            case 3: {
                int searchId;
                cout << "Enter employee ID to search: ";
                cin >> searchId;
                hr->searchEmployee(employees, searchId);
                break;
            }
            case 4: {
                int modifyId;
                cout << "Enter employee ID to modify: ";
                cin >> modifyId;
                hr->modifyEmployee(employees, modifyId);
                break;
            }
            case 5: {
                int deleteId;
                cout << "Enter employee ID to delete: ";
                cin >> deleteId;
                hr->deleteEmployee(employees, deleteId);
                break;
            }
            case 6:
                cout << "Exiting HR Menu." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 6);
}

// Management menu
void managerMenu(Manager* manager, const vector<Employee*>& employees) {
    int choice;
    do {
        cout << "\nManagement Menu:" << endl;
        cout << "1. View All Employees" << endl;
        cout << "2. Search Employee" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manager->viewEmployees(employees); 
                break;
            case 2: {
                int searchId;
                cout << "Enter employee ID to search: ";
                cin >> searchId;
                manager->searchEmployee(employees, searchId);
                break;
            }
            case 3:
                cout << "Exiting Management Menu." << endl;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 3);
}

// General employee menu
void generalEmployeeMenu(GeneralEmployee* employee) {
    cout << "\nGeneral Employee Menu:" << endl;
    employee->viewOwnInfo();
}

// HR_Employee methods
void HR_Employee::viewEmployees(const vector<Employee*>& employees) {
    for (const auto& employee : employees) {
        employee->displayInfo();
        cout << "--------------------" << endl;
    }
}

void HR_Employee::searchEmployee(const vector<Employee*>& employees, int searchId) {
    for (const auto& employee : employees) {
        if (employee->userId == searchId) {
            employee->displayInfo();
            return;
        }
    }
    cout << "Employee not found." << endl;
}

void HR_Employee::modifyEmployee(vector<Employee*>& employees, int modifyId) {
    for (auto& employee : employees) {
        if (employee->userId == modifyId) {
            string newName;
            cout << "Enter new name: ";
            cin >> newName;
            employee->name = newName; 
            cout << "Employee information updated." << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

void HR_Employee::deleteEmployee(vector<Employee*>& employees, int deleteId) {
    for (auto it = employees.begin(); it != employees.end(); ++it) {
        if ((*it)->userId == deleteId) {
            delete *it; // Delete the Employee object before erasing from vector
            employees.erase(it);
            cout << "Employee deleted." << endl;
            return;
        }
    }
    cout << "Employee not found." << endl;
}

// Manager methods
void Manager::viewEmployees(const vector<Employee*>& employees) {
    for (const auto& employee : employees) {
        employee->displayInfo();
        cout << "--------------------" << endl;
    }
}

void Manager::searchEmployee(const vector<Employee*>& employees, int searchId) {
    for (const auto& employee : employees) {
        if (employee->userId == searchId) {
            employee->displayInfo();
            return;
        }
    }
    cout << "Employee not found." << endl;
}

int main() {
    vector<Employee*> employees; 

    createSampleEmployees(employees); 

    string username, password;
    Employee* user = nullptr;

    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (login(username, password, employees, user)) {
        if (dynamic_cast<HR_Employee*>(user)) {
            hrMenu(dynamic_cast<HR_Employee*>(user), employees);
        } else if (dynamic_cast<Manager*>(user)) {
            managerMenu(dynamic_cast<Manager*>(user), employees);
        } else if (dynamic_cast<GeneralEmployee*>(user)) {
            generalEmployeeMenu(dynamic_cast<GeneralEmployee*>(user));
        }
    }

    // Clean up memory
    for (auto& employee : employees) {
        delete employee;
    }
    delete user;

    return 0;
}