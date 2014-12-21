#ifndef PARAMETER_HPP_KJS
#define PARAMETER_HPP_KJS

#include <iostream>
#include <stdexcept>

template <class T>
class parameter {
public:
    parameter(const std::string name__) : name_(name__), set_(false) {}
    parameter(const std::string name__, std::istream& stm, std::ostream& ostm)
        : name_(name__),
          set_(false)
    {
        read(stm, ostm);
    }
    parameter(const std::string name__, const T input) : name_(name__), set_(true), value_(input) {}
    void read(std::istream& stm, std::ostream& ostm)
    {
        ostm << "provide parameter " << name() << std::endl;
        stm >> value_;
        set_ = true;
    }
    void print(std::ostream& stm) const
    {
        stm << "value of parameter " << name() << std::endl;
        stm << value() << std::endl;
    }
    bool set() const { return set_; }
    void set(const T input)
    {
        if (set()) throw std::runtime_error("parameter: illegal attempt to reset value");
        value_ = input;
        set_ = true;
    }
    std::string name() const { return name_; }
    T value() const
    {
        if (!set()) throw std::runtime_error("parameter: illegal attempt to read empty value: name: "+name());
        return value_;
    }
    T operator()() const { return value(); }
private:
    const std::string name_;
    bool set_;
    T value_;
};

#endif // #ifndef PARAMETER_HPP_KJS

