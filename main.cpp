#include <iostream>
#include "to_string.h"

using namespace std;

int main()
{
    queue<int> s;
    s.push(3);
    s.push(2);
    cout << to_string(s) << endl;
    return 0;
}