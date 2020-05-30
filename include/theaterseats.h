//Gerald Torrijos
//gxt170002

#ifndef THEATERSEATS_H
#define THEATERSEATS_H
#include "basenode.h"

class theaterseats : public basenode
{
public:
    theaterseats();
    theaterseats(int, char, char);
    virtual ~theaterseats() {}
    int get_row();
    char get_seat();
    bool is_reserved();
    char get_ticket();
    void set_row(int);
    void set_seat(char);
    void set_ticket(char);
};

#endif // THEATERSEATS_H
