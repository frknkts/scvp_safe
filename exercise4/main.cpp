#include <systemc.h>

#include "place.h"
#include "transition.h"
#include "subnet.h"

// Toplevel:
// TODO

SC_MODULE(toplevel) {
    // Declare places and transitions
    place p1;         // First place
    place p2;         // Second place
    place p3;         // Third place
    place p4;         // Fourth place 

    transition<1,2> t1;    // Transition from p1 to p2
    transition<2,1> t2;    // Transition from p2 to p1
    transition<1,1> t3;    // Transition from p2 to p1

    SC_CTOR(toplevel) 
        : p1(1), p2(0), p3(0), p4(0), t1("t1"), t2("t2"), t3("t3") {
        // Connect ports for t1
        t1.in.bind(p1);
        t1.out(p2);
        t1.out(p3);

        // Connect ports for t2
        t2.in.bind(p2);
        t2.in.bind(p4);
        t2.out.bind(p1);

        // Connect ports for t3
        t3.in.bind(p3);
        t3.out.bind(p4);

        // Define the test process
        SC_THREAD(process);
    }

    void process() {

        while (true)
        {
            wait(10, SC_NS);
            t1.fire();

            wait(10, SC_NS);
            t2.fire();

            wait(10, SC_NS);
            t3.fire();

            wait(10, SC_NS);
            t2.fire();

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
