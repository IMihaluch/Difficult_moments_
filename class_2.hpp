#pragma once

#include <iostream>
#include <numeric>
#include <fstream>
#include "protoclasses.pb.h"

void class_2()
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

    protoclasses::StudentsGroup sg;
    *sg.add_students() = s;

    std::ofstream out("student.bin", std::ios_base::binary);
    sg.SerializeToOstream(&out);
    out.close();

    protoclasses::StudentsGroup new_sg;
    std::ifstream in("student.bin", std::ios_base::binary);
    if (new_sg.ParseFromIstream(&in))
    {
        std::cout << new_sg.students(0).name().surname() << std::endl;
        std::cout << new_sg.students(0).average_score() << std::endl;
    }
    else
    {
        std::cout << "Error!" << std::endl;
    }
    in.close();
}
