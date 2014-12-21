#ifndef MT_WRAPPER_HPP_KJS
#define MT_WRAPPER_HPP_KJS

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_01.hpp>

class mt_wrapper{
public:
    mt_wrapper():uni01(rng){}
    mt_wrapper(const unsigned int R):rng(R),uni01(rng){}
    void seed(const unsigned int R){rng.seed(R);}
    double operator()(){return uni01();}
private:
    boost::random::mt19937 rng;
    boost::random::uniform_01<boost::random::mt19937&> uni01;
};
#endif//MT_WRAPPER_HPP_KJS

