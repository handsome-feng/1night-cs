#include <iostream>
uning namespace std;

class Factory {
public:
    Factory();
    virtual ~Factory();

    static Product* createProduct (string proname);
};

int main (int argc, char *argv[])
{
    Product *prod = Factory::createProduct("A");
    prod->Use();

    delete prod;

    return 0;
}
