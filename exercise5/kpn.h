#ifndef KPN_H
#define KPN_H

#include <systemc.h>

SC_MODULE(kpn)
{
private:
    // ADD THINGS HERE
    sc_fifo<unsigned int> a;
    sc_fifo<unsigned int> b;
    sc_fifo<unsigned int> c;
    sc_fifo<unsigned int> d;

    sc_signal<unsigned int> e;

    void add();
    void split();
    void delay();

public:
    SC_CTOR(kpn) // : ADD THINGS HERE
    : a(10), b(10), c(10), d(10)
    {
        // ADD THINGS HERE

        b.write(1);
        c.write(0);

        SC_THREAD(add);
        SC_THREAD(delay);
        SC_THREAD(split);

        // sensitive   << a.data_read_event() << a.data_written_event() 
        //             << b.data_read_event() << b.data_written_event() 
        //             << c.data_read_event() << c.data_written_event() 
        //             << d.data_read_event() << d.data_written_event();
    }

};

#endif // KPN_H
