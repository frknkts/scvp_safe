#ifndef EXOR_H
#define EXOR_H

#include <systemc.h>

#include "nand.h"

// TODO: Insert your code here
SC_MODULE(exor){
public: 
    sc_in<bool> A;
    sc_in<bool> B;
    sc_out<bool> Z;

    nand n_a, n_b, n_c, n_d;

    sc_signal<bool> h1, h2, h3;

    SC_CTOR(exor): n_a("n_a"), n_b("n_b"), n_c("n_c"), n_d("n_d"), A("A"), B("B") ,Z("Z"), h1("h1"), h2("h2"), h3("h3"){ 
        // SC_METHOD(exor);
        
        n_a.A.bind(A);
        n_a.B.bind(B);
        n_a.Z.bind(h1);

        n_c.A.bind(A);
        n_c.B.bind(h1);
        n_c.Z.bind(h2);

        n_b.A.bind(h1);
        n_b.B.bind(B);
        n_b.Z.bind(h3);

        n_d.A.bind(h2);
        n_d.B.bind(h3);
        n_d.Z.bind(Z);
    }
};
#endif // EXOR_H
