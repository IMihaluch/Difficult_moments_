#include "interfaces.hpp"
#include <numeric>

void interfaces()
{
    protoclasses::FullName fn;
    fn.set_name("Ivan");
    fn.set_surname("Petrov");
    fn.set_patronymic("Mikhailovich");

    protoclasses::Student s;
    *s.mutable_name() = fn;
    s.add_grades(5);
    s.add_grades(2);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.add_grades(4);
    s.add_grades(3);
    s.set_average_score(std::accumulate(s.grades().begin(), s.grades().end(), 0) / s.grades().size());

    StG::StudentsGroup sg;
    sg.add_student(s);
    sg.Save();

    StG::StudentsGroup new_sg;
    new_sg.Open();
    std:: cout << new_sg.GetAllInfo(fn) << std::endl;
}
