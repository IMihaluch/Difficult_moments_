#pragma once

#include <iostream>
#include <iterator>
#include <string>
#include <unordered_set>
#include <vector>
#include <list>
#include <deque>

template<typename IT>
void printWords(IT it, IT end)
{
    std::unordered_set<std::string> countWords(it, end);
    std::copy(countWords.begin(), countWords.end(), std::ostream_iterator<std::string>(std::cout, "; "));
}

void exercise_1()
{
    std::vector<std::string> v{ "one", "two", "three", "five", "one", "five", "six", "two", "two", "one", "seven", "nine" };
    std::cout << "Vector output:" << std::endl;
    printWords(v.begin(), v.end());

    std::list<std::string> l(v.begin(), v.end());
    std::cout << "\nOutput of the sheet:" << std::endl;
    printWords(l.begin(), l.end());

    std::deque<std::string> d(v.begin(), v.end());
    std::cout << "\nDeck output:" << std::endl;
    printWords(d.begin(), d.end());
}
