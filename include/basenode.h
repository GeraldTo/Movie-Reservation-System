//Gerald Torrijos
//gxt170002

#ifndef BASENODE_H
#define BASENODE_H

class basenode
{
protected:
    int row;
    char col;
    char ticket;

public:
    basenode();
    basenode(int, char, char);
    virtual int get_row() = 0;
    virtual char get_seat() = 0;
    virtual char get_ticket() = 0;
    virtual ~basenode() {}
};

#endif // BASENODE_H
