#include <systemc.h>

#include "stim.h"
#include "exor.h"
#include "mon.h"

int sc_main(int, char**)
{
    sc_signal<bool> sigA, sigB, sigZ;

    stim Stim1("Stimulus");
    Stim1.A(sigA);
    Stim1.B(sigB);

    exor DUT("exor");
    DUT.A(sigA);
    DUT.B(sigB);
    DUT.Z(sigZ);

    Monitor mon("Monitor");
    mon.A(sigA);
    mon.B(sigB);
    mon.Z(sigZ);

    // Setup Waveform Tracing:
    sc_trace_file *wf = sc_create_vcd_trace_file("traceFile");
    sc_trace(wf, sigA, "A");
    sc_trace(wf, sigB, "B");
    sc_trace(wf, sigZ, "Z");

    sc_start();  // run forever

    // Close Trace File:
    sc_close_vcd_trace_file(wf);

    return 0;
}
