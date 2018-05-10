#include "variant.hh"

#include <iostream>

//
// ###############################################################
//

struct T
{
    T(int value) : value_(value) { std::cout << "construct\n"; }
    T(const T& t): value_(t.value_) { std::cout << "copy\n"; }
    T(T&& t): value_(t.value_) { std::cout << "move\n"; }
    ~T() { std::cout << "deconstruct\n"; }

    void print() const { std::cout << "value is: " << value_ << "\n"; }

    int value_;
};

//
// ###############################################################
//

using my_variant = variant<T, std::string, double>;

my_variant generate_variant()
{
    my_variant res;
    res = T(12);
    std::cout << "res set!\n";
    return res;
}

struct visitor
{
    void operator()(const T& t) { std::cout << "T visited\n"; };
    void operator()(const std::string& t) { std::cout << "string visited\n"; };
    void operator()(const double& t) { std::cout << "double visited\n"; };
};

int main()
{
    my_variant v = generate_variant();

    v.get<T>().print();

    v = std::string("test_value");

    std::cout << "new variant: " << v.get<std::string>() << "\n";

    v.apply_visitor<visitor>();

    v.get<double>();
}
