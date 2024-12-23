#ifndef PLACE_H
#define PLACE_H

#include <systemc.h>

// Place Interface:
// TODO
class placeInterface: public sc_interface{

public:
    // Virtual functions which need to be implemented by the class inheriting them
    virtual void addTokens(unsigned int n) = 0;
    virtual void removeTokens(unsigned int n) = 0;
    virtual unsigned int testTokens() = 0;

    virtual ~placeInterface() {}
};

// Place Channel:
// TODO

class place : public placeInterface {
    private:

    unsigned int tokens; // Number of tokens in this place

    public:

    // Constructor to initialize the tokens
    place(unsigned int initial_tokens = 0) : tokens(initial_tokens) {}

    void addTokens(unsigned int n) override 
    {
        // tokens = tokens + n;
        tokens += n;
    }

    void removeTokens(unsigned int n) override 
    {
        if (tokens >= n)
        {
            // tokens = tokens - n;
            tokens -= n;
        }
        // else 
        // {
        //     SC_REPORT_WARNING("place", "Attempt to remove more tokens than available.");
        // }
    }

    unsigned int testTokens() override 
    {
        return tokens;
    }
};

#endif // PLACE_H
