#ifndef DISCRETE_RANDOM_SURFACE_HPP_KJS
#define DISCRETE_RANDOM_SURFACE_HPP_KJS

#include <vector>

#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>

template<class T, class U, class V>
class discrete_random_surface: public std::vector<U>{
public:
    typedef T index_t;
    typedef U height_t;
    typedef V sequence_idx_t;
    discrete_random_surface(const index_t nr_sites_, const height_t nr_levels_, const sequence_idx_t seed_index_)
    :std::vector<height_t>(nr_sites_,0)
    ,nr_sites(nr_sites_)
    ,nr_levels(nr_levels_)
    ,seed_index(seed_index_)
    ,gen(seed_index_)
    ,dist(0,nr_levels_-1)
    {}
    void generate_heights(){
        for (index_t i = 0; i < nr_sites; ++i){this->at(i) = random_height();}
    }
private:
    height_t random_height(){return dist(gen);}
    const index_t nr_sites;
    const height_t nr_levels;
    const sequence_idx_t seed_index;
    boost::random::mt19937 gen;
    boost::random::uniform_int_distribution<> dist;
};

#endif//#ifndef DISCRETE_RANDOM_SURFACE_HPP_KJS

