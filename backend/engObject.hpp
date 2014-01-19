#ifndef ENGOBJECT_HPP
#define ENGOBJECT_HPP
#include <vector>

struct engData
{
    std::vector<double> vertices;
};

class engObject
{
public:
    engObject();
private:
    engData data;
    bool staticdraw;
};

#endif // ENGOBJECT_HPP
