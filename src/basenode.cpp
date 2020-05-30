//Gerald Torrijos
//gxt170002

#include "../include/basenode.h"

basenode::basenode()
{
    row = 0;
    col = 0;
    ticket = 0;
}
basenode::basenode(int a, char b, char c) //info in node
{
    row = a;
    col = b;
    ticket = c;
}
