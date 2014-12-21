#ifndef PRECISE_OUTPUT_HPP_KJS
#define PRECISE_OUTPUT_HPP_KJS

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <stdexcept>
#include <limits.h>

template <class F>
class precise_output: public std::ofstream{
public:
    precise_output(std::string name)
    :std::ofstream(name.c_str())
    {
        if (name.size() > NAME_MAX) throw std::runtime_error("precise_output: filename too long");
        stream_setup();
    }
    precise_output(const char* name)
    :std::ofstream(name)
    {stream_setup();}
    precise_output()
    {stream_setup();}
    void open(const std::string& file_name){std::ofstream::open(file_name.c_str());}
private:
    void stream_setup(){
        if (this->fail()) throw std::runtime_error("precise_output: failed to open file");
        this->precision(std::numeric_limits<F>::digits10);
    }
};

#endif//PRECISE_OUTPUT_HPP_KJS

