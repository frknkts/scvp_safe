#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO

template<unsigned int N = 1, unsigned int M = 1>
SC_MODULE(transition) 
{
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;

    SC_CTOR(transition){
    };

    void fire(){

    // 1. Check if all input places have at least one token
    // 2. Remove one token from every input place 
    // 3. Add one token for every output place 

        for ( unsigned int i=0 ; i < N; i++ )
        {
            if ( in[i]->testTokens() == 0)
            {
                std::cout << this->name() << ": NOT Fired" << std::endl;
                return;
            }
        }   
                
        for ( unsigned int i=0 ; i < N; i++ )
        {
            in[i]->removeTokens(1);
        }
                
        for ( unsigned int i=0 ; i < M; i++ )
        {
            out[i]->addTokens(1);
        }
        
        std::cout << this->name() << ": Fired" << std::endl;

    }

};

#endif // TRANSITION_H
