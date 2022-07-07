#include <iostream>

using namespace std;

// abstract pizza class
class abstract_pizza {
public:
    virtual float getPrice() const = 0;
};

// abstract decorator class for abstract_pizza
class abstract_pizza_decorator : public abstract_pizza {
private:
    abstract_pizza *_pizza;
    float _price;
public:
    abstract_pizza_decorator(abstract_pizza *pizza, float price) : _pizza(pizza), _price(price) {}
    float getPrice() const {
        return _price + _pizza->getPrice();
    }
};

// concrete implementation of margarita pizza
class Margarita : public abstract_pizza {
private:
    float _price;
public:
    Margarita() : _price(10.99) {}
    float getPrice() const {
        return _price;
    }
};

// concrete implementation of gourmet pizza
class Gourmet : public abstract_pizza {
private:
    float _price;
public:
    Gourmet() : _price(12.99) {}
    float getPrice() const {
        return _price;
    }
};

class OliveTopping : public abstract_pizza_decorator {
public:
    OliveTopping(abstract_pizza *pizza) : abstract_pizza_decorator(pizza, 3.99) {}
};

class PineappleTopping : public abstract_pizza_decorator {
public:
    PineappleTopping(abstract_pizza *pizza) : abstract_pizza_decorator(pizza, 3.99) {}
};

int main (void) {
    abstract_pizza *p = new Margarita();
    abstract_pizza_decorator *o = new OliveTopping(p);
    abstract_pizza_decorator *pa = new PineappleTopping(o);
    cout << "Pizza price " << p->getPrice() << endl;
    cout << "Olive and Pineapple topping pizza " << pa->getPrice() << endl;
    return 0;
}
