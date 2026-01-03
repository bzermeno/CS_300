/* ProjectTwo.cpp : This program reads a file of course data and stores it 
 * in a vector of courses. The user can then print the list of courses 
 * or search for a specific course. The program will continue to run until 
 * the user chooses to exit.
 * Author: Beau Zermeno
 * Date: February 23, 2025
 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;

// Initialize the struct Course
struct Course {
    string courseNumber;
	string courseName;
	vector<string> prerequisites;
};

/*
 * Funtion to read the file and store the data in the vector of courses
 * @param string filename
 * @param vector<Course>& courses
*/
void readFile(string filename, vector<Course>& courses) {
	ifstream file(filename);
	if (!file) {
		cout << "Error opening file." << endl << endl;
		return;
	}
	string line;
	while (getline(file, line)) {
		Course course;
		string prereq;
		int pos = 0;
		pos = line.find(",");
		course.courseNumber = line.substr(0, pos);
		line.erase(0, pos + 1);
		pos = line.find(",");
		course.courseName = line.substr(0, pos);
		line.erase(0, pos + 1);
		while ((pos = line.find(",")) != string::npos) {
			prereq = line.substr(0, pos);
			course.prerequisites.push_back(prereq);
			line.erase(0, pos + 1);
		}
		course.prerequisites.push_back(line);
		courses.push_back(course);
	}
	cout << "Data loaded successfully." << endl << endl;
	file.close();
}

/*
 * Function to print the courses
 * @param vector<Course>& courses
*/
void printCourses(vector<Course>& courses) {
	cout << "Here is a sample schedule:" << endl << endl;

	for (int i = 0; i < courses.size(); i++) {
		cout << courses[i].courseNumber << ", ";
		cout << courses[i].courseName << endl;
	}
	cout << endl;
}

/*
 * Function to sort the courses
 * @param vector<Course>& courses
 * @param int left
 * @param int right
*/ 
void quickSort(vector<Course>& courses, int left, int right) {
	int i = left, j = right;
	Course tmp;
	string pivot = courses[(left + right) / 2].courseNumber;
	
	// Partition
	while (i <= j) {
		while (courses[i].courseNumber < pivot)
			i++;
		while (courses[j].courseNumber > pivot)
			j--;
		if (i <= j) {
			tmp = courses[i];
			courses[i] = courses[j];
			courses[j] = tmp;
			i++;
			j--;
		}
	}

	// Recursion
	if (left < j)
		quickSort(courses, left, j);
	if (i < right)
		quickSort(courses, i, right);
}

/*
 * Function to search for a course
 * @param vector<Course>& courses
 * @param string courseNumber
*/
void courseSearch(vector<Course>& courses, string courseNumber) {
	for (const auto& course : courses) {
		if (course.courseNumber == courseNumber) {
			cout << course.courseNumber << ", " << course.courseName << endl;

			// Check if the course has prerequisites
			if (course.prerequisites[0].length() < 2) {
				cout << "Prerequisites: None" << endl << endl;
			}
			else {
				// Print the prerequisites
				cout << "Prerequisites: ";
				cout << course.prerequisites[0];

				for (int j = 1; j < course.prerequisites.size(); j++) {
					if (course.prerequisites[j].length() > 1) {
						cout << ", " << course.prerequisites[j];
					}
				}
				cout << endl << endl;
			}
			return;
		}
	}

	// Print error message if course is not found
	cout << "Course not found." << endl << endl;
}

/*
 * Main function
*/
int main() {
	// Initialize the variables
	string filename;
	vector<Course> courses;
	string choice;
	string courseNumber;

	cout << "Welcome to the course planner." << endl << endl;

	while (true) {
		// Display the menu
		cout << "    1. Load Data Structure." << endl;
		cout << "    2. Print Course List." << endl;
		cout << "    3. Print Course." << endl;
		cout << "    9. Exit" << endl << endl;
		
		cout << "What would you like to do? ";
		getline(cin, choice);

		if (choice == "1") {
			// Load the data
			cout << "What file do you want to load? ";
			getline(cin, filename);
			readFile(filename, courses);	
		}
		else if (choice == "2") {
			// Sort and print the courses
			quickSort(courses, 0, courses.size() - 1);
			printCourses(courses);
		}
		else if (choice == "3") {
			// Search for a course
			cout << "What course do you want to know about? ";
			getline(cin, courseNumber);
			transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
			courseSearch(courses, courseNumber);
		}
		else if (choice == "9"){
			// Exit the program
			cout << "Thank you for using the course planner!" << endl;
			break;
		}
		else {
			// Invalid option
			cout << choice << " is not a valid option." << endl << endl;
		}
	}
}


