#include <log.h>
#include <iostream>
#include <vector>

using namespace std;

const unsigned N = 10;

int main()
{
    Log log1;
    for (unsigned i = 0; i < N; i++)
        log1.writeLog("test log");
    auto  vec1 = log1.getLog();
    for (unsigned i = 0; i < N; i++)
        cout << vec1[i]<<endl;
    return 0;
}

