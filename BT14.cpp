#include <iostream>
#include <string>
#include <vector>
#include <limits>

using namespace std;

class Student
{
private:
    int id;
    string name;
    int age;
    float gpa;
public:
    // Constructor
    Student(int input_id, string input_name, int input_age, float input_gpa)
    {
        this -> id = input_id;
        this -> name = input_name;
        this -> age = input_age;
        this -> gpa = input_gpa;
    }
    
    // Constructor withou parameters
    Student ()
    {
        id = -1;
        name = "";
        age = -1;
        gpa = -1;
    }

    int get_id(void)
    {
        return id;
    }
    
    string get_name(void)
    {
        return name;
    }

    void print_info (void)
    {
        cout << "The information of the student:" << endl
             << "- ID: " << id << endl
             << "- NAME: " << name << endl
             << "- AGE: " << age << endl
             << "- GPA: " << gpa << endl; 
    }
};

class StudentDirectory
{
private:
    vector <Student> student_list;
public:
    int add_student_to_list(int input_id, string input_name, int input_age, float input_gpa)
    {
        // 1. Input validation
        if (input_id < 0 || input_age < 0 || input_gpa < 0.0f || input_name[0] == '\0')
        {
            cout << "Invalid input for add student addition!" << endl;
            return -1;
        }

        // 2. Add student to vector
        Student tmp(input_id, input_name, input_age, input_gpa);
        student_list.push_back(tmp);
        return 0;
    }

    vector<Student> :: iterator find_student_with_id (int find_id)
    {
        if (find_id < 0)
        {
            cout << "Invalid ID" << endl;
            return student_list.end();
        }

        int student_count = 0;
        vector<Student> :: iterator it_1 = student_list.begin();
        vector<Student> :: iterator it_2 = student_list.begin();


        // Use linear search for searching
        for (it_1; it_1 != student_list.end(); it_1 ++)
        {
            if (it_1->get_id() == find_id)
            {
                it_1->print_info();
                cout << endl;

                if (student_count == 1)
                    it_2 = it_1;
            }
        }

        if (student_count == 0)
        {
            cout << "Does not have any corresspond student in the list" << endl << endl;
            return student_list.end();
        }
        return it_2;
    }
    
    vector<Student> :: iterator find_student_with_name (string find_name)
    {
        if (find_name[0] == '\0')
        {
            cout << "Invalid Name!" << endl;
            return student_list.end();
        }

        int student_count = 0;
        vector<Student> :: iterator it_1 = student_list.begin();
        vector<Student> :: iterator it_2 = student_list.begin();

        // Use linear search for searching
        for (it_1; it_1 != student_list.end(); it_1 ++)
        {
            if (it_1->get_name() == find_name)
            {
                it_1->print_info();
                cout << endl;

                if (student_count == 1)
                    it_2 = it_1;
            }
        }

        if (student_count == 0)
        {
            cout << "Does not have any corresspond student in the list" << endl << endl;
            return student_list.end();
        }
        return it_2;
    }

    void print_list (void)
    {
        for (auto it = student_list.begin(); it != student_list.end(); it ++)
        {
            it->print_info();
            cout << endl;
        }
    }
};

StudentDirectory list;


/**
* @brief Function for adding student to the list
*/
void adding_student_input (void)
{
    Student tmp;
    int input_id, input_age;
    string input_name;
    float input_gpa;


while (true)
{
    cout << "Please input student's ID: ";
    try
    {
        cin >> input_id;
        cin.ignore();    // discard leftover newline
        
        if (!cin)
            throw runtime_error("Invalid input type. Please enter an integer for ID.");

        if (input_id < 0)
            throw invalid_argument("ID cannot be negative. Please try again.");

        break; // Valid input, exit the loop
    }
    catch (const exception& error)
    {
        cout << error.what() << endl;
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
}

while (true)
{
    cout << "Please input student's Name: ";
    try
    {
        if(!getline(cin, input_name))
        {
            throw runtime_error("Input error. Please try again.");
        }
        if (input_name.empty())
            throw invalid_argument("Name cannot be empty. Please try again.");
        break; // Valid input, exit the loop
    }
    catch (const exception& error)
    {
        cout << error.what() << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
}

while (true)
{
    cout << "Please input student's Age: ";
    try
    {
        cin >> input_age;
        if (!cin)
            throw runtime_error("Invalid input type. Please enter an integer for age.");
        if (input_age < 0)
            throw invalid_argument("Age cannot be negative. Please try again.");
        break;
    }
    catch (const exception& error)
    {
        cout << error.what() << endl;
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
}


while (true)
{
    cout << "Please input student's GPA: ";
    try
    {
        cin >> input_gpa;
        if (!cin)
            throw runtime_error("Invalid input type. Please enter a float for GPA.");
        if (input_gpa < 0)
            throw invalid_argument("GPA cannot be negative. Please try again.");
        break;
    }
    catch (const exception& error)
    {
        cout << error.what() << endl;
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
    }
}

    // 2. Create a new student
    list.add_student_to_list(input_id, input_name, input_age, input_gpa);
    cout << endl << "Added student succesfully!" << endl << endl;
}

/**
* @brief Function for searching student with ID or Name
*/
void searching_student_input (void)
{
    int find_id;
    string find_name;
    int searching_method;

    cout << "Please choose searching method: " << endl
         << "1. Search with ID." << endl
         << "2. Search with Name." << endl << endl;
input_again:
    cout << "Your decision: ";
    cin >> searching_method;
    cout << endl;

    if (!cin)
    {
        cout << endl << "Invalid input, please try again!" << endl;
        cin.clear(); // clear the error flag
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
        goto input_again;
    }
    else if (searching_method < 1 || searching_method > 2)
    {
        cout << endl << "Invalid input, please try again!" << endl;
        goto input_again;
    }


    if (searching_method == 1)
    {
        // 1. Input ID
        while (true)
        {
            cout << "Please input the ID you want to find: ";
            try
            {
                cin >> find_id;
                if (!cin)
                    throw runtime_error("Invalid input type. Please enter an integer for ID.");
                if (find_id < 0)
                    throw invalid_argument("ID cannot be negative. Please try again.");
            }
            catch (const exception& error)
            {
                cout << error.what() << endl;
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            break; // Valid input, exit the loop
        }
        // 2. Find student with ID
        list.find_student_with_id(find_id);
    }
    else if (searching_method == 2)
    {
        // 1. Input Name
        while (true)
        {
            cout << "Please input the Name you want to find: ";
            try
            {
                cin.ignore();
                if (!getline(cin, find_name))
                    throw runtime_error("Input error. Please try again.");
                if (find_name.empty())
                    throw invalid_argument("Name cannot be empty. Please try again.");
            }
            catch (const exception& error)
            {
                cout << error.what() << endl;
                cin.clear(); // clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            }
            break;
        }
        // 2. Find student with Name
        list.find_student_with_name(find_name);
    }
}

void input_menu(void)
{
    while (true)
    {
        int decision = 0;
        cout << "Please enter follow these instructions, if you want to: " << endl
             << "1. For adding student to the list." << endl
             << "2. For searching for student (with id or name)." << endl
             << "3. See every student in the list." << endl 
             << "4. Exit the program." << endl << endl;
        
        input_again:
             cout << "Your decision: ";
        
        cin >> decision;
        cout << endl;
    
        if (!cin)
        {
            cout << endl << "Invalid input, please try again!" << endl;
            cin.clear(); // clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard invalid input
            goto input_again;
        }
        else if (decision < 1 || decision > 4)
        {
            cout << endl << "Invalid input, please try again!" << endl;
            goto input_again;
        }
    
        if (decision == 1)
        {
            adding_student_input();
        }
        else if (decision == 2)
        {
            searching_student_input();
        }
        else if (decision == 3)
        {
            list.print_list();
        }
        else if (decision == 4)
        {
            cout << "Exiting the program..." << endl;
            return;
        }
    }
}

int main()
{
    input_menu();
    return 0;
}



