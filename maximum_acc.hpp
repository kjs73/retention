#ifndef MAXIMUM_ACC_HPP_KJS
#define MAXIMUM_ACC_HPP_KJS
template <class T>
class maximum_acc{
public:
    maximum_acc(const T initial_value=0){reset(initial_value);}
    void check(const T input){
        if (input>this_value) this_value = input;
    }
    T get()const{return this_value;}
    T operator()()const{ return get(); }
    void reset(const T input){this_value = input;}
private:
    T this_value;
};
#endif//MAXIMUM_ACC_HPP_KJS

