#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

struct Student {
    std::string name;
    int marks[3]; // Assuming 3 subjects
    int totalMarks;
    int schoolRank;
    int classRank;
};

const int NUM_CLASSES = 3; // Number of classes in each stream
const int NUM_STUDENTS_PER_CLASS = 40; // Number of students in each class
const int NUM_SUBJECTS = 3; // Number of subjects

std::vector<Student> students;

void calculateRanks() {
    std::sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.totalMarks > b.totalMarks;
    });

    int currentRank = 1;
    students[0].schoolRank = 1;

    for (size_t i = 1; i < students.size(); ++i) {
        if (students[i].totalMarks < students[i - 1].totalMarks) {
            currentRank = i + 1;
        }
        students[i].schoolRank = currentRank;
    }

    // Assuming students are already grouped by class
    for (size_t i = 0; i < students.size(); ++i) {
        students[i].classRank = i % NUM_STUDENTS_PER_CLASS + 1;
    }
}

int main() {
    // Read student data from file or input
    // For simplicity, let's assume you read the student data and marks here
    
    // Calculate total marks
    for (auto& student : students) {
        student.totalMarks = 0;
        for (int i = 0; i < NUM_SUBJECTS; ++i) {
            student.totalMarks += student.marks[i];
        }
    }
    
    // Calculate ranks
    calculateRanks();

    // Print and write ranks to file
    std::ofstream outputFile("rank_results.txt");
    for (const auto& student : students) {
        std::cout << "Student: " << student.name
                  << " | School Rank: " << student.schoolRank
                  << " | Class Rank: " << student.classRank << std::endl;

        outputFile << "Student: " << student.name
                   << " | School Rank: " << student.schoolRank
                   << " | Class Rank: " << student.classRank << std::endl;
    }
    
    outputFile.close();
    return 0;
}
