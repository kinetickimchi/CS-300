// Name: Kyunghoon Lee
// Professor: Dr. Adamo
// CS-300
// 16 August 2024

#include <iostream>
#include <fstream>  // to load from filesystem
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Define Course structure to hold course data
struct Course {
    string courseNumber;
    string name;
    vector<string> prerequisites;
};

// Forward declarations of functions
void loadCourses(vector<Course>& courses, string filename);  // Load data from csv
void sortCourses(vector<Course>& courses);  // Alphanumerically sort courses
void printCourseList(vector<Course>& courses);  // after sorting
string toUpper(const string& str);  // Ensures correct formatting of courseNumber input
void searchCourse(vector<Course>& courses, const string& courseNumber);  // Return information for a single course


int main() {
    vector<Course> courses;
    string filename;  // file to import goes here
    int choice;

    cout << "Welcome to the course planner." << endl << endl;

    // Menu display
    while (true) {
        cout << "  1. Load Data Structure." << endl;
        cout << "  2. Print Course List." << endl;
        cout << "  3. Print Course." << endl;
        cout << "  9. Exit" << endl << endl;
        cout << "What would you like to do? ";
        cin >> choice;  // Get input from user for menu choice
        cout << endl;


        switch (choice) {
            case 1:
                cout << "Note: file to import must be in the correct directory." << endl;
                cout << "Enter filename: ";
                cin.ignore();  // Clear input buffer
                getline(cin, filename);  // Accounts for spaces in filename
                cout << "Importing file " << filename << "..." << endl;

                loadCourses(courses, filename);  // Call loadCourses function to import
                break;

            case 2:
                printCourseList(courses);
                cout << endl;
                break;

            case 3: {
                string courseNumber;

                cout << "What course do you want to know about? Please enter the course number: ";
                cin >> courseNumber;
                searchCourse(courses, courseNumber);

                break;
            }
            case 9:
                cout << "Thank you for using the course planner!" << endl;
                return 0;  // end program

            default:  // for any input other than a valid menu option
                cout << choice << " is not a valid option." << endl;
                cout << endl;

        }
    }

}

// Function to load course data from csv file
void loadCourses(vector<Course>& courses, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ',')) {  // Split line into tokens by commas
            tokens.push_back(token);  // Add to end of tokens vector
        }

        // Check if line format is correct
        if (tokens.size() < 2) {
            cerr << "Error: Formatting error at line: " << line << endl;
            continue;  // Move on to next line
        }

        // Create course object and enter details
        Course course;
        course.courseNumber = tokens[0];
        course.name = tokens[1];

        // Add prerequisites to end if they exist, check if token is empty
        for (size_t i = 2; i < tokens.size(); ++ i) {
            if (!tokens[i].empty()) {
                course.prerequisites.push_back(tokens[i]);
            }
        }

        // Add to end of courses vector
        courses.push_back(course);
    }

    file.close(); // Close file

    cout << "Course data loaded successfully." << endl;
    cout << endl;
}

// Function to sort original courses vector
void sortCourses(vector<Course>& courses) {
    sort(courses.begin(), courses.end(), [](Course& a, Course& b) {
        return a.courseNumber < b.courseNumber;
    });
}

// Function to sort courses, then display sorted list
void printCourseList(vector<Course>& courses) {
    sortCourses(courses);  // Sort courses before displaying

    cout << "Here is a sample schedule:" << endl;
    cout << endl;

    for (auto course : courses) {
        cout << course.courseNumber << ", " << course.name << endl;
    }
}

// Function to ensure courseNumber input is capitalized to match formatting
string toUpper(const string& str) {
    string upperStr = str;
    std::transform(upperStr.begin(), upperStr.end(), upperStr.begin(), [](unsigned char c)
        { return std::toupper(c); });
    return upperStr;
}

// Function to search for passed courseNumber and display information
void searchCourse(vector<Course>& courses, const string& courseNumber) {
    string upperCourseNumber = toUpper(courseNumber);  // Call toUpper() to ensure input format matches
    bool found = false;  // Checks if courseNumber input was found

    for (auto course : courses) {
        if (toUpper(course.courseNumber) == upperCourseNumber) {
            cout << course.courseNumber << ", " << course.name << endl;
            if (!course.prerequisites.empty()) {
                cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    cout << course.prerequisites[i];
                    if (i < course.prerequisites.size() - 1) {
                        cout << ", ";
                    }
                }
                cout << endl;
                cout << endl;

            } else {
                cout << "No prerequisites" << endl;
                cout << endl;
            }
            found = true;  // Course found
            break;

        }
    }
    if (!found) {
        cout << "Course " << upperCourseNumber << " not found." << endl;
        cout << endl;
    }

}