#ifndef PROGRESS_HPP_KJS
#define PROGRESS_HPP_KJS

#include <ctime>
#include <utility>
#include <iostream>

class progress{
public:
    typedef size_t index_t;
    typedef double float_t;
    typedef long long int long_t;

    progress(const index_t totalin):oom(1.0/static_cast<float_t>(totalin)),m(totalin),curr(0),prev(0){}

    void next(const index_t idx, std::ostream& stm = std::cout){
        curr = static_cast<index_t>(static_cast<float_t>(idx+1)*oom*100);
        if (curr!=prev){
            TimePercentage(idx,stm);
        }
    }

    void TimePercentage(const index_t smp, std::ostream& stm){
        // percentage done
        stm << "---" << std::endl;
        stm << "percentage done" << std::endl;
        stm << curr << " %" << std::endl;
        prev = curr;
        stm << "---" << std::endl;
        // time elapsed
        stm << "time elapsed" << std::endl;
        PrintTime(stm);
        // estimated time to completion
        stm << "---" << std::endl;
        stm << "estimated time to completion" << std::endl;
        IntToTime(((float_t)(m-smp-1)/(float_t)(smp+1))*(float_t)clock(), stm);
        // estimated total time
        stm << "---" << std::endl;
        stm << "estimated total run time" << std::endl;
        IntToTime(((float_t)m/(float_t)(smp+1))*(float_t)clock(), stm);
        stm << "---" << std::endl;
        // estimated completion time in local time
        stm << "estimated completion local time" << std::endl;
        time_t timer = time(NULL);
        timer+=(((float_t)(m-smp-1)/(float_t)(smp+1))*(float_t)clock())/CLOCKS_PER_SEC;
        stm << ctime(&timer);
        stm << "---" << std::endl;
    }

    void PrintTime(std::ostream& stm){
        long_t tm = clock();
        long_t days = tm/((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60*(long_t)24);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60*(long_t)24);
        long_t hours = tm/((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60);
        long_t minutes = tm/((long_t)CLOCKS_PER_SEC*(long_t)60);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60);
        long_t seconds = tm/((long_t)CLOCKS_PER_SEC);
        if (days){
            if (days>1) stm << days << " days  ";
            else stm << days << " day  ";
        }
        if (hours){
            if (hours>1) stm << hours << " hours  ";
            else stm << hours << " hour  ";
        }
        if (minutes){
            if (minutes>1) stm << minutes << " minutes  ";
            else stm << minutes << " minute  ";
        }
        if (seconds){
            if (seconds>1) stm << seconds << " seconds";
            else stm << seconds << " second";
        }
        stm << std::endl;
    }

    void IntToTime(const long_t inp, std::ostream& stm){
        long_t tm = inp;
        long_t days = tm/((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60*(long_t)24);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60*(long_t)24);
        long_t hours = tm/((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60*(long_t)60);
        long_t minutes = tm/((long_t)CLOCKS_PER_SEC*(long_t)60);
        tm%=((long_t)CLOCKS_PER_SEC*(long_t)60);
        long_t seconds = tm/((long_t)CLOCKS_PER_SEC);
        if (days){
            if (days>1) stm << days << " days  ";
            else stm << days << " day  ";
        }
        if (hours){
            if (hours>1) stm << hours << " hours  ";
            else stm << hours << " hour  ";
        }
        if (minutes){
            if (minutes>1) stm << minutes << " minutes  ";
            else stm << minutes << " minute  ";
        }
        if (seconds){
            if (seconds>1) stm << seconds << " seconds";
            else stm << seconds << " second";
        }
        stm << std::endl;
    }

private:
    const float_t oom;
    const index_t m;
    index_t curr;
    index_t prev;
};

#endif//#ifndef PROGRESS_HPP_KJS
