#ifndef RANKING_UNIFORM_SELECTION_HPP_KJS
#define RANKING_UNIFORM_SELECTION_HPP_KJS

#include <map>
#include <cassert>

#include "mt_wrapper.hpp"

namespace{

template<class K, class M>
class ranking_uniform_selection: public std::multimap<K,M>{
public:
	M  next_value_erase(){ // select uniformly among lowest-key elements
		typename std::multimap<K,M>::iterator it = this->begin();
		const K this_key = it->first;
		const unsigned int number_values_same_key = this->count(this_key);
		assert(number_values_same_key>=1);
		if (number_values_same_key>1){
			const unsigned int position = static_cast<unsigned int>( number_values_same_key*uni01() );
			assert( position < number_values_same_key );
			std::advance( it, position );
		}
		const M result = it->second;
		this->erase(it);
		return result;
	}
	M next_value_erase_multimap(){ // select multimap-style among lowest-key elements
		typename std::multimap<K,M>::iterator it = this->begin();
		const M result = it->second;
		this->erase(it);
		return result;
	}
	M uniform_next_value_erase(){ // select uniformly, ignoring key values
		typename std::multimap<K,M>::iterator it = this->begin();
		const unsigned int position = static_cast<unsigned int> ( this->size()*uni01() );
		std::advance( it, position );
		const M result = it->second;
		this->erase(it);
		return result;
	}
	K minimum_key()const{return (this->begin())->first;}
	void insert(const K key_input, const M mapped_input){std::multimap<K,M>::insert(std::make_pair<K,M>(key_input,mapped_input));}
	void insert(const std::pair<K,M>& inp){std::multimap<K,M>::insert(inp);}
private:
	static mt_wrapper uni01;
};

template<class K, class M>
mt_wrapper ranking_uniform_selection<K,M>::uni01;

} //namespace
#endif//RANKING_UNIFORM_SELECTION_HPP_KJS

