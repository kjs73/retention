#ifndef RETENTION_FINDER_HPP_KJS
#define RETENTION_FINDER_HPP_KJS

#include <algorithm>

#include "discrete_random_surface.hpp"
#include "lattice_strip_square_2d.hpp"
#include "maximum_acc.hpp"
#include "ranking_uniform_selection.hpp"

template<class T, class U, class SURF>
class retention_finder{
public:
    typedef T index_t;
    typedef U height_t;
    typedef ranking_uniform_selection<height_t,index_t> ranking_t;
    typedef lattice_strip_square_2d lattice_t;
    typedef SURF surface_t;
    retention_finder(const index_t L_, const surface_t& height_)
    :lattice(L_,L_)
    ,visited(L_*L_,false)
    ,height(height_)
    {
        visited.swap(visited);
    }
    void reset_and_initialize(){
        std::fill(visited.begin(),visited.end(),false);
        front.clear();
        retention = 0;
    }
    void find(){
        initial_conditions();
        for (index_t i = 0; i < lattice.NumberSites(); ++i){
            invade_next_site();
        }
    }
    index_t retained_volume()const{return retention;}
private:
    lattice_t lattice;
    std::vector<bool> visited;
    ranking_t front;
    index_t retention;
    const surface_t& height;
    maximum_acc<height_t> maximum_height; // "flooding level"
    
    void initial_conditions(){
        const index_t L = lattice.Lx();
        // set up initial status of invasion information
        // bottom, open
        for (index_t i = 1; i < L-1; ++i){
            add_to_front(i);
        }
        // top, open
        for (index_t i = lattice.NumberSites()-L+1; i < lattice.NumberSites()-1; ++i){
            add_to_front(i);
        }
        // left, closed
        for (index_t i = 0; i < lattice.NumberSites(); i += L){
            add_to_front(i);
        }
        // right, closed
        for (index_t i = L-1; i < lattice.NumberSites(); i += L){
            add_to_front(i);
        }
        // set up maximum height accordingly
        maximum_height.reset(front.minimum_key());
    }
    void add_to_front(const index_t site){
        if (visited.at(site)) throw std::runtime_error("retention_finder: label mismatch");
        visited.at(site) = true;
        front.insert(height.at(site),site);
    }
    void invade_next_site(){
        maximum_height.check(front.minimum_key());
        const index_t next_site = front.next_value_erase_multimap();
        update_retention(next_site);
        update_front(next_site);
    }
    void update_retention(const index_t next_site){
        if (lattice.site_at_boundary(next_site)) return; // water drains irrespective of site height
        const height_t delta_retention = (maximum_height()-height.at(next_site));
        if (delta_retention<0){
            std::cout << delta_retention << std::endl;
            throw std::runtime_error("retention_finder: height mismatch");
        }
        else if (delta_retention>0){
            retention += delta_retention;
        }
    }
    void update_front(const index_t next_site){
        for (index_t i = 0; i < lattice.NumberNeighbors(); ++i){
            if ( lattice.BulkConnection(next_site,i) ){
                const index_t nbr = lattice.neighbor(next_site,i);
                if (visited.at(nbr)==false){
                    add_to_front(nbr);
                }
            }
        }
    }
};

#endif//#ifndef RETENTION_FINDER_HPP_KJS

