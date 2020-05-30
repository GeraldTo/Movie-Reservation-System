//Gerald Torrijos
//gxt170002

#ifndef AUDITORIUM_H
#define AUDITORIUM_H
#include <string>
#include "theaterseats.h"

class auditorium
{
private:
    theaterseats** room;
    std::string room_name;
    int rows;
    int cols;
    int bestrow;
    char bestcol;
    int total_adults;
    int total_childs;
    int total_seniors;
    

public:
    auditorium(std::string);
    virtual ~auditorium();
    std::string customer_auditorium();
    void create_audi();
    void print_audi();
    void best_available(int);
    char best_available_col();
    void remove_seats(char, int);
    int best_available_row();
    bool is_reserved(int, char, int);
    void reserve_tickets(int, char, int, int, int);
    void write_back();
    double distance_formula(double, double);
    std::string getreport();

    //getters
    int get_rows(){return rows;}
    int get_cols(){return cols;}
    int get_total_adults() { return total_adults; }
    int get_total_childs() { return total_childs; }
    int get_total_seniors() { return total_seniors; }
    int get_total_seats() { return rows*cols; }
    int get_seats_sold() { return total_adults+total_childs+total_seniors; }
    int get_open_seats() { return get_total_seats() - get_seats_sold(); }
    double get_a_sales(){return (total_adults * 10);}
    double get_c_sales(){return (total_childs * 5);}
    double get_s_sales(){return (total_seniors * 7.5);}
    double get_sales() { return get_a_sales() + get_c_sales() + get_s_sales(); }
};

#endif // AUDITORIUM_H
