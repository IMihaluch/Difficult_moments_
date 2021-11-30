#include <iostream>
#include <iomanip>
#include "task_3.hpp"
#include "task_2.hpp"

using namespace std;

void task_3()
{
    Matrix m(4);
    m.fillRandom();

    for (const double& i : m)
    {
        cout << setw(5) << i;
    }

    cout << endl;
}
