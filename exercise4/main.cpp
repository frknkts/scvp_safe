#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO

SC_MODULE(toplevel) {
    // Declare places and transitions
    // Has Weights on the arcs of 1, but holds 2 tokens at the beginning
    place<1,1> IDLE;

    subnet s1, s2;

    SC_CTOR(toplevel) 
        : IDLE(2), s1("s1"), s2("s2") {
        
        s1.in.bind(IDLE);
        s1.out.bind(IDLE);
        
        s2.in.bind(IDLE);
        s2.out.bind(IDLE);

        // Define the test process
        SC_THREAD(process);
    }

    void process() {

        while (true)
        {
            wait(10, SC_NS);
            s1.ACT.fire();

            wait(10, SC_NS);
            s1.ACT.fire();

            wait(10, SC_NS);
            s1.RD.fire();

            wait(10, SC_NS);
            s1.WR.fire();

            wait(10, SC_NS);
            s1.PRE.fire();

            wait(10, SC_NS);
            s1.ACT.fire();

            wait(10, SC_NS);
            s2.ACT.fire();

            wait(10, SC_NS);
            s2.ACT.fire();

            wait(10, SC_NS);
            s1.PRE.fire();

            wait(10, SC_NS);
            s2.PRE.fire();

            wait(10, SC_NS);
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
