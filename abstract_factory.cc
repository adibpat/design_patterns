#include <iostream>

class toppings {

};

class preparation {

};

class beverage {
public:
    virtual void make(void) = 0;
    virtual ~beverage() = 0;
};

class beverageFactory {
public:
    virtual beverage* getBeverage(void) = 0;
};

class coffee : public beverage {
private:
    toppings *_t;
    preparation *_p;
public:
    coffee() {}
    ~coffee() {}
    virtual void make() {
    }
};

class coffeeFactory : public beverageFactory {
public:
    virtual beverage* getBeverage() {
        return new coffee();
    }
};