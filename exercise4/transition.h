#ifndef TRANSITION_H
#define TRANSITION_H

#include <systemc.h>

#include "place.h"

// Transition:
// TODO

template<unsigned int N = 1, unsigned int M = 1, unsigned int L = 0>
SC_MODULE(transition) 
{
    public:
    sc_port<placeInterface, N, SC_ALL_BOUND> in;
    sc_port<placeInterface, M, SC_ALL_BOUND> out;
    sc_port<placeInterface, L, SC_ZERO_OR_MORE_BOUND> inhibitors;

    SC_CTOR(transition){
    };

    void fire()
    {

        // 1. Check if all input places have at least one token or one token in inhibitors
        // 2. Remove one token from every input place 
        // 3. Add one token for every output place 

        // Ugly test of inhibitor ports 
        // Tested before in since typically less ports of this type
        for ( unsigned int j = 0 ; j < L ; j++)
        {
            if ( inhibitors[j]->testTokens() != 0)
            {
                std::cout << this->name() << ": NOT Fired" << std::endl;
                return;
            }
        }

        // Test if all input places have at least one token
        for ( unsigned int i = 0 ; i < N; i++ )
        {
            if ( in[i]->testTokens() == 0)
            {
                std::cout << this->name() << ": NOT Fired" << std::endl;
                return;
            }
        }   

        // Remove tokens from input port 
        for ( unsigned int i=0 ; i < N; i++ )
        {
            in[i]->removeTokens();
        }
        
        // Add tokens to output port 
        for ( unsigned int i=0 ; i < M; i++ )
        {
            out[i]->addTokens();
        }
        
        std::cout << this->name() << ": Fired" << std::endl;

    }

};

#endif // TRANSITION_H
