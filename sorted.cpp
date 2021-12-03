#include <vector>
#include <list>
#include <math.h>
#include <algorithm>

#include "heading.hpp"
#include "templates.hpp"

using namespace std;

void sorted_1()
{
    const unsigned int size = 10;
    int newIntValue = -3;
    double newDoubleValue = 2.2;

    vector<int> v(size);
    generator(v, -10, 10);
    sort(v.begin(), v.end());
    print(v);                             
    insert_sorted(v, newIntValue);
    print(v);                             

    cout << endl;

    list<double> l(size);
    generator(l, -10.0, 10.0);
    l.sort();
    print(l);                             
    insert_sorted(l, newDoubleValue);
    print(l);                             

    cout << endl;
}

void vector_2()
{
    vector<double> v(100);

    double error = 0;
    generator(v, -1000.0, 1000.0);

    print(v);                                                          
    copy(v.begin(), v.end(), ostream_iterator<int> { cout, " " });     

    cout << endl;

    for_each(v.begin(), v.end(), [&](const double& i)
        {
            error += pow(i - static_cast<int>(i), 2);
        });

    cout << endl << "The error between the digital and analog signal is equal to" << error << endl;
}
