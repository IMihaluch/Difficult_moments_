#pragma once

#include <iostream>
#include <vector>
#include <fstream>
#include "protoclasses.pb.h"

namespace StG
{
    class IRepository
    {
    public:
        virtual void Open() = 0; // бинарная десериализация в файл
        virtual void Save() = 0; // бинарная сериализация в файл
        virtual ~IRepository() {};
    };

    class IMethods
    {
    public:
        virtual double GetAverageScore(const protoclasses::FullName &name) = 0;
        virtual std::string GetAllInfo(const protoclasses::FullName &name) = 0;
        virtual std::string GetAllInfo() = 0;
        virtual ~IMethods() {};
    };

    class StudentsGroup: public IRepository, public IMethods
    {
    private:
        std::vector<protoclasses::Student> m_students;
    public:
        void add_student(const protoclasses::Student &s)
        {
            m_students.push_back(s);
        }

        double GetAverageScore(const protoclasses::FullName &name)
        {
            auto it = std::find_if(m_students.begin(), m_students.end(), [&](const protoclasses::Student &s)
            {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                tie(name.name(), name.surname(), name.patronymic());
            });

            if (it == m_students.end())
            {
                return 0.0;
            }

            return it->average_score();
        }

        std::string GetAllInfo(const protoclasses::FullName &name)
        {
            auto it = std::find_if(m_students.begin(), m_students.end(), [&](const protoclasses::Student &s)
            {
                return tie(s.name().name(), s.name().surname(), s.name().patronymic()) ==
                tie(name.name(), name.surname(), name.patronymic());
            });

            if (it == m_students.end())
            {
                return {};
            }

            std::string temp = "Name: " + it->name().name() + ' ' + it->name().surname() + ' ' + it->name().patronymic() + '\n';
            temp += "Evaluations: ";
            for (int i = 0; i < it->grades().size(); ++i)
            {
                temp += std::to_string(it->grades(i)) + "; ";
            }
            temp += '\n';
            temp += "Average score: " + std::to_string(it->average_score()) + "\n\n";

            return temp;
        }

        std::string GetAllInfo()
        {
            std::string temp;

            std::for_each(m_students.begin(), m_students.end(), [&](const protoclasses::Student &s)
            {
                temp += GetAllInfo(s.name());
            });

            return temp;
        }

        void Save()
        {
            std::ofstream out("data.bin", std::ios_base::binary);
            auto size = m_students.size();
            out.write(reinterpret_cast<char*>(&size), sizeof(size));
            std::for_each(m_students.begin(), m_students.end(), [&](const protoclasses::Student &s)
            {
                s.SerializeToOstream(&out);
            });
            out.close();
        }

        void Open()
        {
            std::ifstream in("data.bin", std::ios_base::binary);
            size_t size = 0;
            in.read(reinterpret_cast<char*>(&size), sizeof(size));
            while (size--)
            {
                protoclasses::Student s;
                s.ParseFromIstream(&in);
                m_students.push_back(std::move(s));
            }
            in.close();
        }

        virtual ~StudentsGroup() {};
    };
}

void interfaces();
