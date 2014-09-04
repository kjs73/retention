#ifndef WRC_GC_DISCRETE_INVASION_HPP_KJS
#define WRC_GC_DISCRETE_INVASION_HPP_KJS

#include "progress.hpp"
#include "precise_output.hpp"
#include "parameter.hpp"
#include "variable.hpp"
#include "discrete_random_surface.hpp"
#include "retention_finder.hpp"

class wrc_gc_discrete_invasion{
public:
	typedef unsigned int index_t;
	typedef unsigned int sample_nr_t;
	typedef unsigned int sequence_idx_t;
	typedef double output_t;
	wrc_gc_discrete_invasion()
	:L("lattice size",std::cin,std::cout)
	,M("number of samples",std::cin,std::cout)
	,R("random number sequence index",std::cin,std::cout)
	,n("number of levels",std::cin,std::cout)
	,height(L()*L(),n(),R())
	,retention(L(),height)
	{std::cout.precision(std::numeric_limits<output_t>::digits10);}
	void run(){
		progress stat(M());
		for (sample_nr_t i = 0; i < M(); ++i){
			simulate_sample();
			stat.next(i);
		}
		print_output();
	}
	void simulate_sample(){
		sample_reset();
		find_sample_retention();
		sample_accumulate();
	}
	void sample_reset(){
		height.generate_heights();
		retention.reset_and_initialize();
	}
	void find_sample_retention(){
		retention.find();
	}
	void sample_accumulate(){
		mean_retention.Add(retention.retained_volume());
	}
	void print_output(){
		std::cout << "discrete grand-canonical water retention model on square lattice" << std::endl;
		std::cout << "total retained volume" << std::endl;
		std::cout << "L\tn\tM\tR\tmean\terror\tstd" << std::endl;
		std::cout << L() << "\t" << n() << "\t" << M() << "\t" << R() << "\t" << mean_retention.Mean() << "\t" << mean_retention.Error() << "\t" << mean_retention.Std() << std::endl;
	}
private:
	parameter<index_t> L;
	parameter<sample_nr_t> M;
	parameter<sequence_idx_t> R;
	parameter<index_t> n;
	
	discrete_random_surface<index_t,index_t,sequence_idx_t> height;
	retention_finder< index_t, index_t, discrete_random_surface<index_t,index_t,sequence_idx_t> > retention;
	
	Variable<> mean_retention;
};

#endif//#ifndef WRC_GC_DISCRETE_INVASION_HPP_KJS

