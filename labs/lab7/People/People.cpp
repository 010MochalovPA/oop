#include <iostream>
#include "Student.h"
#include "Teacher.h"

int main()
{
    auto student = Student("student", "lastname", "middleName", "address", "universityName", "studentId");

	std::cout << std::endl;
	std::cout << student.GetFirstName() << std::endl;
	std::cout << student.GetLastName() << std::endl;
	std::cout << student.GetMiddleName() << std::endl;
	std::cout << student.GetAddress() << std::endl;
	std::cout << student.GetStudentID() << std::endl;
	std::cout << student.GetUniversityName() << std::endl;

	auto teacher = Teacher("teacher", "lastname", "middleName", "address", "subjectName");

	std::cout << std::endl;
	std::cout << teacher.GetFirstName() << std::endl;
	std::cout << teacher.GetLastName() << std::endl;
	std::cout << teacher.GetMiddleName() << std::endl;
	std::cout << teacher.GetAddress() << std::endl;
	std::cout << teacher.GetSubjectName() << std::endl;
}
