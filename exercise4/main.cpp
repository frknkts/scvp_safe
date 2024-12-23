#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO

SC_MODULE(toplevel) {
    // Declare places and transitions
    place<1,1> IDLE;
    place<1,1> ACTIVE;

    transition<1,1> ACT;
    transition<1,1> WR;
    transition<1,1> PRE;
    transition<1,1> RD;

    SC_CTOR(toplevel) 
        : IDLE(1), ACTIVE(0), ACT("ACT"), WR("WR"), PRE("PRE"), RD("RD") {
        
        ACT.in.bind(IDLE);
        ACT.out.bind(ACTIVE);

        WR.in.bind(ACTIVE);
        WR.out.bind(ACTIVE);

        RD.in.bind(ACTIVE);
        RD.out.bind(ACTIVE);

        PRE.in.bind(ACTIVE);
        PRE.out.bind(IDLE);

        // Define the test process
        SC_THREAD(process);
    }

    void process() {

        while (true)
        {
            wait(10, SC_NS);
            ACT.fire();

            wait(10, SC_NS);
            ACT.fire();

            wait(10, SC_NS);
            RD.fire();

            wait(10, SC_NS);
            WR.fire();

            wait(10, SC_NS);
            PRE.fire();

            wait(10, SC_NS);
            ACT.fire();
            
            sc_stop();
        }
    }
};

int sc_main(int, char**)
{
    // TODO
    toplevel t("t");

    sc_start();
    return 0;
}
