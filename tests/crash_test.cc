#include "variant.hh"

#include <map>
#include <iostream>

struct T
{
    static int counter;

    T() : value_(counter++) { std::cout << "construct! " << value_ << "\n"; }
    T(const T& t): value_(counter++) { std::cout << "copy! old: " << t.value_ << " new: " << value_ << "\n"; }
    ~T() { std::cout << "deconstruct " << value_ << "\n"; }

    void print() const { std::cout << "value is: " << value_ << "\n"; }

    int value_;
};

int T::counter = 0;

struct test_type
{
    using map_type = std::map<std::string, test_type>;

    test_type()
        : v()
    {
    }

    ~test_type() { std::cout << "destruct test_type!\n"; }

    test_type& operator=(const test_type& rhs)
    {
        v = rhs.v;
        return *this;
    }

    test_type& operator[](const std::string& s)
    {
        map_type& m = v.get<map_type>();
        std::cout << "operator[] (" << s << ")\n";
        return m[s];
    };

    test_type(const test_type& rhs)
    {
        std::cout << "copying test_type\n";
        v = rhs.v;
    }

    //void operator=(const std::string& s) { v.set<std::string>(s); }
    void operator=(const T& t) { v.set<T>(t); }
    void operator=(const map_type& t) { v.set<map_type>(t); }

    variant<T, map_type> v;
};

//
// ############################################################################
//

struct print_helper
{
void operator()(const T& t)
{
    std::cout << "t value: " << t.value_ << "\n";
}

void operator()(const test_type::map_type& v)
{
    for (const auto& pair : v)
    {
        std::cout << pair.first << ": ";
        pair.second.v.apply_visitor<print_helper>();
    }
    std::cout << "\n";
}
};

//
// ############################################################################
//

int main()
{
    std::cout << "Start running!\n";


    test_type t;
    test_type t2;

    t = test_type::map_type{};
    t2 = test_type::map_type{};

    std::cout << "setting T\n";
    t2["test2"] = T();

    std::cout << "copying t2 into t\n";
    t["test"] = t2;

    const auto& t2_test = t["test"].v.get<test_type::map_type>();
    std::cout << "t2 test size: " << t2_test.size() << "\n";

    std::cout << "applying visitor\n";
    t.v.apply_visitor<print_helper>();

    std::cout << "destruct t2\n";
    t2.~test_type();
    std::cout << "destruct t1\n";
    t.~test_type();

    std::cout << "Done running!\n";
}
