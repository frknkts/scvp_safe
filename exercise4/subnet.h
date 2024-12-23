#ifndef SUBNET_H
#define SUBNET_H

#include <systemc.h>

#include "place.h"
#include "transition.h"

// Subnet:
// TODO

// Based on toplevel from previous Task
SC_MODULE(subnet) {
    // Declare places and transitions
    place<1,1> ACTIVE;

    // Literal initialization of transitions even if default values
    transition<1,1,1> ACT; // Has inhibitor port from ACTIVE
    transition<1,1,0> WR;
    transition<1,1,0> PRE;
    transition<1,1,0> RD;

    SC_CTOR(subnet) 
        : ACTIVE(0), ACT("ACT"), WR("WR"), PRE("PRE"), RD("RD") {
        
        // ACT.in.bind(IDLE); <- Is connected in toplevel
        ACT.out.bind(ACTIVE);
        ACT.inhibitors.bind(ACTIVE);

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        // PRE.out.bind(IDLE); <- Is connected in toplevel
    }

};

#endif // SUBNET_H
