#pragma once

#include <gtest/gtest.h>
#include "Work1.hpp"

class TestBook: public testing::Test
{
protected:
    PhoneBook *book;

    void SetUp() override
    {
        std::stringstream src_stream;
        src_stream << "Ilin;Petr;Artemovich;7;17;4559767;;\n"
                << "Egorov;Savelii;Stanislavovich;77;4521;8880876;99;\n"
                << "Egorov;Timofei;;7;273;5699819;5542;\n"
                << "Zaitsev;Zakhar;Artemovich;125;44;4164751;;\n";

        book = new PhoneBook(src_stream);
    }

    void TearDown() override
    {
        delete book;
    }
};

TEST_F(TestBook, GetPhoneNumber_notFound)
{
    std::string lastname = "Aleksandrov";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestBook, GetPhoneNumber_foundOne)
{
    std::string lastname = "Ilin";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "");
}

TEST_F(TestBook, GetPhoneNumber_foundMore)
{
    std::string lastname = "Egorov";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "found more than 1");
}

TEST_F(TestBook, GetPhoneNumber_empty)
{
    std::string lastname = "";

    auto answer = book->GetPhoneNumber(lastname);
    EXPECT_EQ(std::get<0>(answer), "not found");
}

TEST_F(TestBook, ChangePhoneNumber)
{
    std::string lastname = "Ilin";

    ASSERT_EQ(std::get<0>(book->GetPhoneNumber(lastname)).empty(), true);

    PhoneNumber answer = std::get<1>(book->GetPhoneNumber(lastname))[0];
    EXPECT_EQ(answer.number, "4559767");

    book->ChangePhoneNumber(Person { "Ilin", "Petr", "Artemovich" }, PhoneNumber { 7, 222, "27345558", std::nullopt });

    answer = std::get<1>(book->GetPhoneNumber(lastname))[0];
    EXPECT_EQ(answer.country_code, 7);
    EXPECT_EQ(answer.city_code, 222);
    EXPECT_EQ(answer.number, "27345558");
    EXPECT_EQ(answer.additional_number, std::nullopt);
}

TEST_F(TestBook, sortByName)
{
    std::stringstream src_stream;
    src_stream << "    Egorov      Savelii     Stanislavovich   +77(4521)8880876 99\n"
            << "    Egorov     Timofei                   +7(273)5699819 5542\n"
            << "      Ilin        Petr      Artemovich   +7(17)4559767\n"
            << "   Zaitsev      Zakhar      Artemovich   +125(44)4164751\n";

    book->SortByName();

    std::stringstream dst_stream;
    dst_stream << *book;

    while (!dst_stream.eof())
    {
        std::string str_src;
        std::string str_dst;

        src_stream >> str_src ;
        dst_stream >> str_dst;

        EXPECT_EQ(str_dst, str_src);
    }
}

TEST_F(TestBook, sortByPhone)
{
    std::stringstream src_stream;
    src_stream << "    Zaitsev      Zakhar     Artemovich     +125(44)4164751\n"
            << "         Ilin        Petr      Artemovich   +7(17)4559767\n"
            << "       Egorov     Timofei                   +7(273)5699819 5542\n"
            << "       Egorov     Savelii  Stanislavovich   +77(4521)8880876 99\n";

    book->SortByPhone();

    std::stringstream dst_stream;
    dst_stream << *book;

    while (!dst_stream.eof())
    {
        std::string str_src;
        std::string str_dst;

        src_stream >> str_src ;
        dst_stream >> str_dst;

        EXPECT_EQ(str_dst, str_src);
    }
}
