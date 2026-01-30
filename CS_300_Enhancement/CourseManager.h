#ifndef COURSE_MANAGER_H
#define COURSE_MANAGER_H

#include <string>
#include <vector>

struct Course {
    std::string courseNumber;
    std::string courseName;
    std::vector<std::string> prerequisites;
};

class CourseManager {
private:
    std::vector<Course> courses;

public:
    void readFile(const std::string& filename);
    void printCourses() const;
    void courseSearch(const std::string& courseNumber) const;
};

#endif // COURSE_MANAGER_H

