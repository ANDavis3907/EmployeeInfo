EmployeeManagementSystem
A C++ command-line application that implements a multi-tiered employee management hierarchy. The system utilizes Object-Oriented Programming (OOP) principles to manage different employee roles (HR, Manager, General Employee) with specific access permissions and data persistence.

Technical Highlights
Object-Oriented Architecture: Uses a base Employee class with virtual functions to support Polymorphism, allowing the system to handle diverse employee types through a unified interface.

Class Inheritance: Implements specific derived classes (HR_Employee, Manager, GeneralEmployee) that inherit core attributes while providing unique functional overrides for role-based tasks.

Data Persistence: Features a custom file-handling engine that loads employee records from employees.txt at runtime and serializes the updated state back to the disk upon exit.

Access Control Logic: Includes a secure login system that routes users to specific menus based on their employeeType.

HR: Full CRUD capabilities (View/Search/Manage all staff).

Manager: Performance review and oversight capabilities.

Employee: Self-service profile management.

Memory Management: Demonstrates clean memory practices by using a std::vector of pointers with a manual cleanup routine to prevent memory leaks during runtime.

Technical Specifications
Language: C++ (C++11 or higher)

Key Concepts: Inheritance, Polymorphism, Virtual Destructors, File I/O (fstream), Pointer Management.

Storage: Flat-file database (employees.txt).
