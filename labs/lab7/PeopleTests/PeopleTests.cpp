#define CATCH_CONFIG_MAIN
#include <memory>
#include <vector>
#include "../../../catch2/catch.hpp"
#include "../People/Pupil.h"
#include "../People/Teacher.h"
#include "../People/Student.h"
#include "../People/AdvancedStudent.h"
#include "../People/Worker.h"
#include "../People/IPerson.h"


TEST_CASE("People")
{
	SECTION("Pupil")
	{
		auto pupil = Pupil("name", "surname", "middleName", "address", "schoolName", "className");

		REQUIRE(pupil.GetFirstName() == "name");
		REQUIRE(pupil.GetLastName() == "surname");
		REQUIRE(pupil.GetMiddleName() == "middleName");
		REQUIRE(pupil.GetAddress() == "address");
		REQUIRE(pupil.GetSchoolName() == "schoolName");
		REQUIRE(pupil.GetClassName() == "className");
	}

	SECTION("Teacher")
	{
		auto teacher = Teacher("name", "surname", "middleName", "address", "math");

		REQUIRE(teacher.GetFirstName() == "name");
		REQUIRE(teacher.GetLastName() == "surname");
		REQUIRE(teacher.GetMiddleName() == "middleName");
		REQUIRE(teacher.GetAddress() == "address");
		REQUIRE(teacher.GetSubjectName() == "math");
	}

	SECTION("Student")
	{
		auto student = Student("name", "surname", "middleName", "address", "iSpring", "01");

		REQUIRE(student.GetFirstName() == "name");
		REQUIRE(student.GetLastName() == "surname");
		REQUIRE(student.GetMiddleName() == "middleName");
		REQUIRE(student.GetAddress() == "address");
		REQUIRE(student.GetUniversityName() == "iSpring");
		REQUIRE(student.GetStudentID() == "01");
		
	}

	SECTION("Advinced student")
	{
		auto advancedStudent = AdvancedStudent("name", "surname", "middleName", "address", "iSpring", "02", "oop");

		REQUIRE(advancedStudent.GetFirstName() == "name");
		REQUIRE(advancedStudent.GetLastName() == "surname");
		REQUIRE(advancedStudent.GetMiddleName() == "middleName");
		REQUIRE(advancedStudent.GetAddress() == "address");
		REQUIRE(advancedStudent.GetUniversityName() == "iSpring");
		REQUIRE(advancedStudent.GetStudentID() == "02");
		REQUIRE(advancedStudent.GetDissertationTopic() == "oop");
	}

	SECTION("Worker")
	{
		auto worker = Worker("name", "surname", "middleName", "address", "tech");

		REQUIRE(worker.GetFirstName() == "name");
		REQUIRE(worker.GetLastName() == "surname");
		REQUIRE(worker.GetMiddleName() == "middleName");
		REQUIRE(worker.GetAddress() == "address");
		REQUIRE(worker.GetSpecialty() == "tech");
	}
}

TEST_CASE("IPerson")
{
	SECTION("std::vector<std::unique_ptr<IPerson>>")
	{
		auto pupil = std::make_unique<Pupil>("pupil", "surname", "middleName", "address", "schoolName", "className");
		auto worker = std::make_unique<Worker>("worker", "surname", "middleName", "address", "tech");
		auto advancedStudent = std::make_unique<AdvancedStudent>("advinced student", "surname", "middleName", "address", "iSpring", "02", "oop");
		auto student = std::make_unique<Student>("student", "surname", "middleName", "address", "iSpring", "01");
		auto teacher = std::make_unique<Teacher>("teacher", "surname", "middleName", "address", "math");

		std::vector<std::unique_ptr<IPerson>> persons;

		persons.push_back(std::move(pupil));
		persons.push_back(std::move(worker));
		persons.push_back(std::move(advancedStudent));
		persons.push_back(std::move(student));
		persons.push_back(std::move(teacher));
		
		REQUIRE(persons[0]->GetFirstName() == "pupil");
		REQUIRE(persons[1]->GetFirstName() == "worker");
		REQUIRE(persons[2]->GetFirstName() == "advinced student");
		REQUIRE(persons[3]->GetFirstName() == "student");
		REQUIRE(persons[4]->GetFirstName() == "teacher");
	}
}

TEST_CASE("IStudent")
{
	SECTION("std::vector<std::unique_ptr<IStudent>>")
	{

		auto advancedStudent = std::make_unique<AdvancedStudent>("advinced student", "surname", "middleName", "address", "iSpring", "02", "oop");
		auto student = std::make_unique<Student>("student", "surname", "middleName", "address", "iSpring", "01");
		
		std::vector<std::unique_ptr<IStudent>> persons;

		persons.push_back(std::move(advancedStudent));
		persons.push_back(std::move(student));

		REQUIRE(persons[0]->GetFirstName() == "advinced student");
		REQUIRE(persons[1]->GetFirstName() == "student");
	}
}	
