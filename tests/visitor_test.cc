#include "variant.hh"

#include <assert.h>
#include <string>
#include <iostream>

using my_variant = variant<double, std::string>;

struct visitor
{
    void operator()(const double& d, std::string& s)
    {
        s += std::to_string(d);
    }

    void operator()(const std::string& d, std::string& s)
    {
        s += d;
    }
};

int main()
{
    std::cout << "Running!\n";

    std::string total_string;

    my_variant v;
    v = std::string("test_string");
    v.apply_visitor<visitor, std::string&>(total_string);
    v.apply_visitor<visitor, std::string&>(total_string);

    assert(total_string == "test_stringtest_string");

    std::cout << "Passed!\n";
}
