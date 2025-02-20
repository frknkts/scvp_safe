#pragma once
#include <systemc.h>

SC_MODULE(RSLatch)
{
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> D;

    sc_signal<bool> C; // Auxiliary signal

    SC_CTOR(RSLatch) : A("A"), B("B"), D("D"), C("C")
    {
        SC_METHOD(process);
        //sensitive << A << B;
        sensitive << A << B << C <<D;
    }

    void process()
    {
        D.write(!B.read() && C.read()); // Nor Gate
        C.write((A.read() || D.read())); // Nor Gate
    }
};