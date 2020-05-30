//Gerald Torrijos
//gxt170002

#include "../include/theaterseats.h"
#include <iostream>
#include <iomanip>

theaterseats::theaterseats(int a, char b, char c) : basenode(a, b, c) //sets pointers in node to null
{
}

theaterseats::theaterseats() : basenode() //sets pointers in node to null
{
}

int theaterseats::get_row()
{
    return row;
}
char theaterseats::get_seat()
{
    return col;
}
bool theaterseats::is_reserved()
{
    if (ticket == '.')
        return false;
    return true;
}
char theaterseats::get_ticket()
{
    return ticket;
}

void theaterseats::set_row(int input)
{
    row = input;
}
void theaterseats::set_seat(char input)
{
    col = input;
}

// A=Adult, C=Child, S=Senior, .=Empty
void theaterseats::set_ticket(char input)
{
    if (input == 'A' || input == 'C' || input == 'S' || input == '.')
        ticket = input;
}
