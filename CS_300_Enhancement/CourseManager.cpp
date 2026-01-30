#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "CourseManager.h"


void CourseManager::readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cout << "Error opening file.\n\n";
        return;
    }

    courses.clear();

    std::string line;
    while (getline(file, line)) {
        Course course;

        size_t pos = line.find(',');
        course.courseNumber = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        course.courseName = line.substr(0, pos);
        line.erase(0, pos + 1);

        while ((pos = line.find(',')) != std::string::npos) {
            course.prerequisites.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }

        if (!line.empty()) {
            course.prerequisites.push_back(line);
        }

        courses.push_back(course);
    }

    std::cout << "Data loaded successfully.\n\n";

    // Sort courses once loaded
    std::sort(courses.begin(), courses.end(),
        [](const Course& a, const Course& b) {
            return a.courseNumber < b.courseNumber;
        });
}

/*
 * Prints courses in vector
 */
void CourseManager::printCourses() const {
    if (courses.empty()) {
        std::cout << "Course data not loaded.\n\n";
        return;
    }

    std::cout << "Here is a sample schedule:\n\n";
    for (const auto& course : courses) {
        std::cout << course.courseNumber << ", "
            << course.courseName << std::endl;
    }
    std::cout << std::endl;
}

/*
 * Searches for a course and prints details
 */
void CourseManager::courseSearch(const std::string& courseNumber) const {
    if (courses.empty()) {
        std::cout << "Course data not loaded.\n\n";
        return;
    }

    for (const auto& course : courses) {
        if (course.courseNumber == courseNumber) {
            std::cout << course.courseNumber << ", "
                << course.courseName << '\n';

            if (course.prerequisites.empty()) {
                std::cout << "Prerequisites: None\n\n";
            }
            else {
                std::cout << "Prerequisites: ";
                for (size_t i = 0; i < course.prerequisites.size(); ++i) {
                    if (i > 0) std::cout << ", ";
                    std::cout << course.prerequisites[i];
                }
                std::cout << "\n\n";
            }
            return;
        }
    }

    std::cout << "Course not found.\n\n";
}
