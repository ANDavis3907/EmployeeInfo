#include <iostream>
#include <string>
#include <vector>
#include <fstream>

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
        cout << "Username: " << username << endl;
        cout << "Password: " << password << endl;
        cout << "Employee Type: " << employeeType << endl;
    }

    virtual ~Employee() = default;
};

// HR_Employee class
class HR_Employee : public Employee {
public:
    HR_Employee(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "HR") {}

    void viewEmployees(const vector<Employee*>& employees) const {
        for (const auto& employee : employees) {
            employee->displayInfo();
            cout << "--------------------" << endl;
        }
    }

    void searchEmployee(const vector<Employee*>& employees, int searchId) const {
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
                string newFirstName, newLastName, newUsername, newPassword, newEmployeeType;
                int newUserId;
                cout << "Enter new first name: ";
                cin >> newFirstName;
                cout << "Enter new last name: ";
                cin >> newLastName;
                cout << "Enter new user ID: ";
                cin >> newUserId;
                cout << "Enter new username: ";
                cin >> newUsername;
                cout << "Enter new password: ";
                cin >> newPassword;
                cout << "Enter new employee type (HR, Manager, Employee): ";
                cin >> newEmployeeType;

                employee->firstName = newFirstName;
                employee->lastName = newLastName;
                employee->userId = newUserId;
                employee->username = newUsername;
                employee->password = newPassword;
                employee->employeeType = newEmployeeType;
                cout << "Employee information updated." << endl;
                return;
            }
        }
        cout << "Employee not found." << endl;
    }

    void deleteEmployee(vector<Employee*>& employees, int deleteId) {
        for (auto it = employees.begin(); it != employees.end(); ++it) {
            if ((*it)->userId == deleteId) {
                delete *it; // Free the memory
                employees.erase(it); // Remove the pointer from the vector
                cout << "Employee deleted." << endl;
                return;
            }
        }
        cout << "Employee not found." << endl;
    }
};

// Manager class
class Manager : public Employee {
public:
    Manager(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "Manager") {}

    void viewEmployees(const vector<Employee*>& employees) const {
        for (const auto& employee : employees) {
            employee->displayInfo();
            cout << "--------------------" << endl;
        }
    }

    void searchEmployee(const vector<Employee*>& employees, int searchId) const {
        for (const auto& employee : employees) {
            if (employee->userId == searchId) {
                employee->displayInfo();
                return;
            }
        }
        cout << "Employee not found." << endl;
    }
};

// GeneralEmployee class
class GeneralEmployee : public Employee {
public:
    GeneralEmployee(string firstName, string lastName, int userId, string username, string password) 
        : Employee(firstName, lastName, userId, username, password, "Employee") {}

    void viewOwnInfo() const {
        displayInfo();
    }
};

// Function to create sample employees
void createSampleEmployees(vector<Employee*>& employees) {
    employees.push_back(new HR_Employee("John", "Doe", 101, "hr1", "hr123"));
    employees.push_back(new Manager("Jane", "Smith", 102, "manager1", "manager123"));
    employees.push_back(new GeneralEmployee("David", "Lee", 103, "employee1", "employee123"));
    employees.push_back(new GeneralEmployee("Mary", "Johnson", 104, "employee2", "employee234"));
    employees.push_back(new Manager("Michael", "Brown", 105, "manager2", "manager456"));
    employees.push_back(new HR_Employee("Sarah", "Williams", 106, "hr2", "hr456"));
    employees.push_back(new GeneralEmployee("James", "Wilson", 107, "employee3", "employee567"));
    employees.push_back(new GeneralEmployee("Emily", "Davis", 108, "employee4", "employee678"));
    employees.push_back(new Manager("Robert", "Jones", 109, "manager3", "manager789"));
    employees.push_back(new GeneralEmployee("Christopher", "Anderson", 110, "employee5", "employee890"));
}

// Function to save employees to a file
void saveEmployees(const vector<Employee*>& employees, const string& filename) {
    ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& employee : employees) {
            outFile << employee->firstName << " "
                    << employee->lastName << " "
                    << employee->userId << " "
                    << employee->username << " "
                    << employee->password << " "
                    << employee->employeeType << endl;
        }
        outFile.close();
    } else {
        cout << "Unable to open file for saving." << endl;
    }
}

// Function to load employees from a file
void loadEmployees(vector<Employee*>& employees, const string& filename) {
    ifstream inFile(filename);
    if (inFile.is_open()) {
        string firstName, lastName, username, password, employeeType;
        int userId;
        while (inFile >> firstName >> lastName >> userId >> username >> password >> employeeType) {
            if (employeeType == "HR") {
                employees.push_back(new HR_Employee(firstName, lastName, userId, username, password));
            } else if (employeeType == "Manager") {
                employees.push_back(new Manager(firstName, lastName, userId, username, password));
            } else if (employeeType == "Employee") {
                employees.push_back(new GeneralEmployee(firstName, lastName, userId, username, password));
            }
        }
        inFile.close();
    } else {
        // File does not exist, create a new file
        ofstream outFile(filename);
        if (outFile.is_open()) {
            cout << "Created new file: " << filename << endl;
            outFile.close();
        } else {
            cout << "Unable to create file: " << filename << endl;
        }
    }
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
void hrMenu(HR_Employee* hr, vector<Employee*>& employees, bool& restart) {
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
                restart = true;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 6);
}

// Manager menu function
void managerMenu(Manager* manager, const vector<Employee*>& employees, bool& restart) {
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
                cout << "Enter user ID to search: ";
                cin >> searchId;
                manager->searchEmployee(employees, searchId);
                break;
            }
            case 3:
                cout << "Exiting Management Menu." << endl;
                restart = true;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 3);
}

// General employee menu function
void generalEmployeeMenu(GeneralEmployee* employee, bool& restart) {
    int choice;
    do {
        cout << "\nGeneral Employee Menu:" << endl;
        cout << "1. View Own Info" << endl;
        cout << "2. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                employee->viewOwnInfo();
                break;
            case 2:
                cout << "Exiting General Employee Menu." << endl;
                restart = true;
                break;
            default:
                cout << "Invalid choice." << endl;
        }
    } while (choice != 2);
}

int main() {
    vector<Employee*> employees;
    const string filename = "employees.txt";

    // Load employees from file or create a new file if it doesn't exist
    loadEmployees(employees, filename);

    bool restart = false;
    do {
        string username, password;
        cout << "Enter username (or type 'quit' to exit): ";
        cin >> username;
        if (username == "quit") {
            cout << "Exiting program..." << endl;
            break;
        }
        cout << "Enter password: ";
        cin >> password;
        if (password == "quit") {
            cout << "Exiting program..." << endl;
            break;
        }

        Employee* user = nullptr;

        if (login(username, password, employees, user)) {
            if (user->employeeType == "HR") {
                hrMenu(static_cast<HR_Employee*>(user), employees, restart);
            } else if (user->employeeType == "Manager") {
                managerMenu(static_cast<Manager*>(user), employees, restart);
            } else if (user->employeeType == "Employee") {
                generalEmployeeMenu(static_cast<GeneralEmployee*>(user), restart);
            }
        } else {
            cout << "Invalid login credentials." << endl;
        }

    } while (restart);

    // Save employees to file
    saveEmployees(employees, filename);

    // Cleanup
    for (Employee* employee : employees) {
        delete employee;
    }
    employees.clear();

    return 0;
}