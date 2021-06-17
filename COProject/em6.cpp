#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

// employee class is designed for storing data of employees
class employee
{
private:
    string name;
    string employee_id;
    string contact_number;
    char email_id[35];
    double salary;

public:
    employee();
    void setdata();
    void display();
    bool Emp_ID_Check(string);
    void Increment_Salary(int);
    double get_CTC();
};

int main()
{
    char repeat;
    // Code is written in do while so that program can work in continuation
    do
    {
        system("cls");
        repeat = 'y';
        int choice = 0;

        // Main Menu

        cout << "\t\t\t\tWelcome to Employee Managment Software\n"
             << endl
             << endl
             << "\t1) Enter Employee Data\n"
             << "\t2) Search Employee Data\n"
             << "\t3) Modify / Delete Employee Records \n"
             << "\t4) Increment Employee Salary \n"
             << "\t5) Expense Tracker \n"
             << "\t6) Exit \n"
             << "\tEnter your Choice : ";
        cin >> choice;

        ifstream Employee("Employee.dat", ios ::binary); // Linking Binary File Employee.dat
        Employee.seekg(0, ios ::end); // Seeking File Pointer at the end of File
        int no_of_employees = Employee.tellg() / sizeof(employee); // Getting Number of Employee Records 
        Employee.close(); // Closing of Input stream from Employee.dat

        employee Employee_Data;
        
        // For Entering Employee Data
        if (choice == 1)
        {
            fstream Employee_Stream;
            Employee_Stream.open("Employee.dat", ios ::app | ios :: out | ios ::binary); // Linking Binary File Employee.dat in output, binary and append mode
            
            cout << "Enter data of Employee : " << endl;
            Employee_Data.setdata(); // Call of setdata function to set data in Employee_Data object
            Employee_Stream.write((char *)&Employee_Data, sizeof(employee)); // Write data of Employee_Data object in Employee.dat using Employee_Stream Object of fstream

            cout << "Detials of Entered Employee is sucessfully stored" << endl;

            Employee_Stream.close(); // Closing stream with Employee.dat
        }

        // For Searching Employee Data
        else if (choice == 2)
        {
            fstream Employee_Stream("Employee.dat", ios ::binary | ios :: in); // Linking Binary File Employee.dat in input, binary mode
            
            // Checking if no_of_employees records is 0 or Employee_Stream object of Fstream failed to link with Employee.dat 
            if (!Employee_Stream || no_of_employees == 0) 
            {
                cout << "No Records Available" << endl;
            }
            else
            {
                int i = 0;
                string Emp_ID;
                
                bool flag = 0;
                cout << "Enter Employee ID : ";
                cin >> Emp_ID; // Getting input of Employee ID to be searched in Binary File

                // Iterating to check every record for giving Employee ID
                while (i < no_of_employees)
                {
                    Employee_Stream.read((char *)&Employee_Data, sizeof(employee)); // Reading data from Employee.dat in Employee_Data

                    // Checking Employee ID in every record and if the Emp_ID match then break the loop
                    if (Employee_Data.Emp_ID_Check(Emp_ID))
                    {
                        flag = 1;
                        break;
                    }
                    i++;
                }

                // Checking if Record was found and if found then display that record
                if (flag)
                {
                    Employee_Data.display();
                }
                else
                    cout << "No Employee Found with Employee ID " << Emp_ID << endl;
            }
            
            Employee_Stream.close();
        }

        // For Appending / Deleting the Record
        else if (choice == 3)
        {
            fstream Employee_Stream_Original("Employee.dat", ios ::binary | ios :: in); // Linking Binary File Employee.dat in binary and input mode

            // Checking if no_of_employees records is 0 or Employee_Stream object of Fstream failed to link with Employee.dat
            if (!Employee_Stream_Original || no_of_employees == 0)
            {
                cout << "No Records Available" << endl;
                Employee_Stream_Original.close();
            }

            else
            {
                int i = 0;
                string Emp_ID;

                bool flag = 0;
                cout << "Enter Employee ID : ";
                cin >> Emp_ID; // Getting input of Employee ID to be searched in Binary File

                // Iterating to check every record for giving Employee ID
                while (i < no_of_employees)
                {
                    Employee_Stream_Original.read((char *)&Employee_Data, sizeof(employee)); // Reading data from Employee.dat in Employee_Data

                    // Checking Employee ID in every record and if the Emp_ID match then break the loop
                    if (Employee_Data.Emp_ID_Check(Emp_ID))
                    {
                        flag = 1;
                        break;
                    }
                    i++;
                }

                // Checking if Record was found and if found then display that record
                if (flag)
                {
                    Employee_Data.display();
                    int subchoice;

                    // Menu for Modify / Deleting the Record
                    cout << "\nThis is the Employee Record corresponding to Employee ID " << Emp_ID << endl;
                    cout << "1. Modify the Record" << endl;
                    cout << "2. Delete the Record" << endl;
                    cout << "Enter your Choice : ";
                    cin >> subchoice;

                    if (subchoice == 1 || subchoice == 2)
                    {
                        fstream Employee_Stream_Temp("NewEmployee.dat", ios ::binary | ios :: out); // Creating new file NewEmployee.dat file in binary and output mode
                        i = 0;
                
                        Employee_Stream_Original.seekg(0, ios ::beg); // Bringing File Pointer at the beggining of File
                        
                        // Iterating Employee.dat and copying all the records in NewEmployee.dat excluding given Emp_ID record
                        while (i < no_of_employees)
                        {
                            Employee_Stream_Original.read((char *)&Employee_Data, sizeof(employee));

                            // Checking Emp_ID to prevent copying of the given record
                            if (!Employee_Data.Emp_ID_Check(Emp_ID))
                            {
                                Employee_Stream_Temp.write((char *)&Employee_Data, sizeof(employee));
                            }
                            
                            i++;
                        }
                        
                        Employee_Stream_Original.close(); // Closing input stream with Employee.dat

                        // In case of Modifying the record we shall take input and add it in NewEmployee.dat
                        if (subchoice == 1)
                        {
                            cout << "Enter New Employee Data which is to be Modified : - " << endl;
                            Employee_Data.setdata();
                            Employee_Stream_Temp.write((char *)&Employee_Data, sizeof(employee)); // Writing modified record in NewEmployee.dat
                        }

                        Employee_Stream_Temp.close(); // Closing stream with NewEmployee.dat

                        remove("Employee.dat"); // Removing / Deleting Employee.dat file
                        rename("NewEmployee.dat", "Employee.dat"); // Renaming NewEmployee.dat as Employee.dat

                        if (subchoice == 1)
                            cout << "Record is succesfully Modified" << endl;
                        else
                            cout << "Record is successfully Deleted" << endl;
                    }
                    else
                    {
                        cout << "Invalid choice" << endl;
                    }
                }
                else
                    cout << "No Employee Found with Employee ID " << Emp_ID << endl;
            }
        }

        else if (choice == 4)
        {
            ifstream Employee_Stream_read("Employee.dat", ios ::binary); // Linking Employee.dat in binary mode
            int i = 0;

            // Checking if no_of_employees records is 0 or Employee_Stream object of Fstream failed to link with Employee.dat
            if (!Employee_Stream_read || no_of_employees == 0)
            {
                cout << "No Records Available" << endl;
                Employee_Stream_read.close();
            }
            else
            {
                int increment_percentage = 0;
                cout << "Enter Percentage by which you want to Increment the Salary of Employees : ";
                cin >> increment_percentage; // Getting Input of percentage by which salary is to be incremented

                ofstream Employee_Stream_writer("NewEmployee.dat", ios ::binary); // Creating New File NewEmployee.dat in binary mode

                // Iterating Employee.dat to get the records and after incrementing salary adding them into NewEmployee.dat
                while (i < no_of_employees)
                {
                    Employee_Stream_read.read((char *)&Employee_Data, sizeof(employee)); 
                    Employee_Data.Increment_Salary(increment_percentage); // Calling of Increment_salary Function to Increment salary
                    Employee_Stream_writer.write((char *)&Employee_Data, sizeof(employee)); 
                    i++;
                }

                Employee_Stream_writer.close(); // Closing Output Stream with NewEmployee.dat
                Employee_Stream_read.close();   // Closing Input Stream with Employee.dat

                remove("Employee.dat"); // Removing / Deleting Employee.dat
                rename("NewEmployee.dat", "Employee.dat"); // Renaming NewEmployee.dat as Employee.dat

                cout << "Salary of all the Employees is incremented by " << increment_percentage << " %" << endl;
            }
        }

        // Expense Tracker to track expense of Human Resource and get an average expense per employee
        else if (choice == 5)
        {
            ifstream Employee_Stream("Employee.dat", ios ::binary); // Linking Employee.dat in binary mode

            // Checking if no_of_employees records is 0 or Employee_Stream object of Fstream failed to link with Employee.dat
            if (!Employee_Stream || no_of_employees == 0)
            {
                cout << "No Records Available" << endl;
                Employee_Stream.close();
            }
            else
            {
                int i = 0;
                double total_CTC = 0;
                double average_CTC = 0;
                
                // Traversing through all the record and getting the total expense
                while (i < no_of_employees)
                {
                    Employee_Stream.read((char *)&Employee_Data, sizeof(employee));

                    total_CTC += Employee_Data.get_CTC();

                    i++;
                }

                average_CTC = total_CTC / no_of_employees;

                cout << "Total Cost to Company on Employees is : " << total_CTC << endl;
                cout << "Total Number of Employees : " << no_of_employees << endl;
                cout << "Average Salary per Employee : " << average_CTC << endl;
            }

            Employee_Stream.close();
        }

        // For returning to main menu
        if (choice == 6)
        {
            cout << "\tAre you sure you want to exit : ";
            cin >> repeat;
            tolower(repeat);
            if (repeat == 'n')
                repeat = 'y';
            else if (repeat == 'y')
                repeat = 'n';
        }
        else
        {
            cout << "Do you want to return to Main Menu : ";
            cin >> repeat;
            tolower(repeat);
        }

    } while (repeat == 'y');

    return 0;
}

// Definition of setdata function of employee class
void employee ::setdata()
{
    cout << "Enter employee name: ";
    cin >> name;
    cout << "Enter employee id: ";
    cin >> employee_id;
    cout << "Enter salary: ";
    cin >> salary;
    cout << "Enter contact information:  ";
    cin >> contact_number;
    cout << "Enter email id: ";
    cin>>email_id;    
}

// Definition of display function of employee class
void employee ::display()
{
    cout << "Employee Name : " << name << endl;
    cout << "Employee ID : " << employee_id << endl;
    cout << "Employee Salary : " << salary << endl;
    cout << "Contact Number : " << contact_number << endl;
    cout << "Email ID : " << email_id << endl;
}

// Definition of Emp_ID_Check function of employee class
bool employee ::Emp_ID_Check(string Emp_ID)
{
    if (Emp_ID == this->employee_id)
    {
        return true;
    }
    return false;
}

// Definition of Increment_Salary function of employee class
void employee ::Increment_Salary(int increment_percentage)
{
    salary = salary + (increment_percentage * salary) / 100;
}

// Definition of get_CTC function of employee class
double employee ::get_CTC()
{
    return salary;
}

// Definition of constructor of emmpployee class
employee :: employee()
{
    name = "NULL";
    employee_id = "NULL";
    contact_number = "NULL";
    strcpy(email_id, "NULL\0");
    salary = 0;
}