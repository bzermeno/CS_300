/* 
 * CS_300_Enhancement.cpp
 * 
 * This program reads a file of course data and stores it in a vector 
 * of courses. The user can then print the list of courses or search
 * for a specific course. The program will continue to run until the 
 * user chooses to exit.
 * Author: Beau Zermeno
 * Date: January 26, 2026
 */


#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "CourseManager.h"

/*
 * Main function
 */
int main() {
	// Initialize the variables
	CourseManager manager;
	std::string filename;
	std::string choice;
	std::string courseNumber;

	std::cout << "Welcome to the course planner.\n\n";

	while (true) {
		// Display the menu
		std::cout << "    1. Load Data Structure.\n";
		std::cout << "    2. Print Course List.\n";
		std::cout << "    3. Print Course.\n";
		std::cout << "    9. Exit\n";
		
		std::cout << "What would you like to do? ";
		getline(std::cin, choice);

		if (choice == "1") {
			// Load the data
			std::cout << "What file do you want to load? ";
			getline(std::cin, filename);
			manager.readFile(filename);
		}
		else if (choice == "2") {
			// Print course list	
			manager.printCourses();
		}
		else if (choice == "3") {
			// Search for a course
			std::cout << "What course do you want to know about? ";
			getline(std::cin, courseNumber);
			transform(courseNumber.begin(), courseNumber.end(), courseNumber.begin(), ::toupper);
			manager.courseSearch(courseNumber);
		}
		else if (choice == "9"){
			// Exit the program
			std::cout << "Thank you for using the course planner!\n";
			break;
		}
		else {
			// Invalid option
			std::cout << choice << " is not a valid option.\n\n";
		}
	}
}

