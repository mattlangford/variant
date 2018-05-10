# variant
c++11 variant since my compiler is apparently old

# Usage
I think this is pretty compliant with a real variant with a few different function names probably

## Define the variant
```
using my_variant = variant<std::string, double, T>;
```

## Set the variant
```
my_variant v;
v = std::string();
```

## Change it maybe
```
double value = 12;
v = value;
```

## Get value
```
double new_value = v.get<double>();

// It's not a string, so this will throw
std::string thats_not_a_string = v.get<std::string>();
```

## Apply a visitor
```
struct my_visitor
{
    void operator()(const std::string&);
    void operator()(const double&);
    void operator()(T&);
}

v.apply_visitor<my_visitor>()
```
