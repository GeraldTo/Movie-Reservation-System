//Gerald Torrijos
//gxt170002

#include "../include/auditorium.h"
#include "../include/theaterseats.h"
#include <fstream>
#include <iostream>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <cmath>

auditorium::auditorium(string input) //done
{
    rows = 0;
    cols = 0;
    room_name = input;
    total_adults = 0;
    total_childs = 0;
    total_seniors = 0;
    bestrow = 0;
    bestcol = 0;
    create_audi();
}

auditorium::~auditorium() //done
{
    delete[] room;
}

void auditorium::create_audi()
{
    // initiallizes rows and columns by looping get line and counting line length
    ifstream roomsize(room_name);
    string row_line = "";
    while (getline(roomsize, row_line))
    {
        rows++;
        cols = (int)row_line.length(); //gets length of row
    }
    roomsize.close();
    room = new theaterseats *[rows];
    for (int i = 0; i < rows; i++)
    {
        room[i] = new theaterseats[cols];
    }
    ifstream audi(room_name);
    for (int i = 1; i <= rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            char current_seat = (char)(j + 65);
            char current_ticket;
            audi >> current_ticket;    //gets ticket type from file
            if (current_ticket != '.') //checks if current seat is reserved
            {
                if (current_ticket == 'A') //adds to number sold, adults tickets, and total sales
                {
                    total_adults++;
                }
                else if (current_ticket == 'C') //adds to number sold, child tickets, and total sales
                {
                    total_childs++;
                }
                else if (current_ticket == 'S') //adds to number sold, senior tickets, and total sales
                {
                    total_seniors++;
                }
            }
            theaterseats *current_node = new theaterseats(i, current_seat, current_ticket); //creates a new node
            room[i - 1][j] = *current_node;
        }
    }
    audi.close();
}

string auditorium::customer_auditorium() //done
{
    char start = 65;
    string letter_row = "   ";
    while (start < 65 + cols) //loop that prints letters of each columns from A to seats in row
    {
        letter_row += string(1, start); //adds next letter to letter_row
        start++;
    }
    string eachrow = "";
    for (int i = 0; i < rows; i++) //loop to print out each row of  seats
    {
        if (i < 9) //this is to line up the rows with the row number
            eachrow += (to_string(i + 1)) + "  ";
        else
            eachrow += (to_string(i + 1)) + " ";
        for (int j = 0; j < cols; j++) //goes to specific columns
        {
            if (room[i][j].get_ticket() != '.') //if reserved it replaces letter with #
            {
                eachrow += '#';
            }
            else
            {
                eachrow += room[i][j].get_ticket();
            }
        }
        eachrow += "\n";
    }
    return letter_row + "\n" + eachrow;
}

bool auditorium::is_reserved(int r, char c, int sum) //done
{
    int row = r - 1;
    int col = int(c) - 65;
    if (col + sum > cols)
    {
        return true;
    }
    for (int i = 0; i < sum; i++) //loops to check if current seat is reserved starting at the row and column desired
    {
        if (room[row][col + i].is_reserved())
        {
            return true;
        }
    }
    return false;
}

void auditorium::reserve_tickets(int r, char c, int adult, int child, int senior) //done
{
    int row = r - 1;
    int col = int(c) - 65;

    int sum = adult + child + senior;
    total_adults += adult;
    total_childs += child;
    total_seniors += senior;
    for (int i = 0; i < sum; i++) // goes from starring position to sum
    {
        if (adult > 0) //if there are still adult tickets then write it into linked list
        {
            room[row][col + i].set_ticket('A');
            adult--;
        }
        else if (child > 0) //if there are still child tickets then write it into linked list
        {
            room[row][col + i].set_ticket('C');
            child--;
        }
        else if (senior > 0) //if there are still adult tickets then write it into linked list
        {
            room[row][col + i].set_ticket('S');
            senior--;
        }
    }
    write_back();
}

void auditorium::write_back() //done
{
    ofstream audi(room_name);
    for (int i = 0; i < rows; i++) //loop to print out each row of  seats
    {
        for (int j = 0; j < cols; j++) //goes to specific columns
        {
            audi << (room[i][j].get_ticket()); //writes ticket type into file
        }
        if (i != rows - 1) //this is to prevent an extra line being written back into file
        {
            audi << "\n";
        }
    }
    audi.close();
}

void auditorium::remove_seats(char c, int r)
{
    int row = r - 1;
    int col = int(c) - 65;
    if (room[row][col].get_ticket() == 'A') //adds to number sold, adults tickets, and total sales
    {
        total_adults--;
    }
    else if (room[row][col].get_ticket() == 'C') //adds to number sold, child tickets, and total sales
    {
        total_childs--;
    }
    else if (room[row][col].get_ticket() == 'S') //adds to number sold, senior tickets, and total sales
    {
        total_seniors--;
    }
    room[row][col].set_ticket('.');
    write_back();
}


double auditorium::distance_formula(double x, double y) //done
{
    double current_row = ((double)(rows + 1)) / 2.0;  //middle row
    double current_seat = ((double)(cols + 1)) / 2.0; //middle seat
    double distancexy = 0.0;
    distancexy = sqrt(pow((current_row - y), 2.0) + pow((current_seat - x), 2.0)); //distance from middle
    return distancexy;
}


void auditorium::best_available(int sum) //done
{
    double distance_from_mid = 1000000000.0;
    double distance_temp = 0.0;
    char temp_seat = 0;
    int temp_row = 0;

    int mid_row = 0;
    if(rows%2==1)
    {
        mid_row = rows/2;
    }
    else
    {
        mid_row = rows/2-1;
    }
    int mid_col = 0;
    if(cols%2==1)
    {
        mid_col = cols/2;
    }
    else
    {
        mid_col = cols/2-1;
    }
    for (int i = 0; i < rows; i++) //loop to print out each row of  seats
    {
        for (int j = 0; j < cols; j++) //goes to specific columns
        {
            if (is_reserved(room[i][j].get_row(), room[i][j].get_seat(), sum) == false) //if seats starting at current node to sum are not reserved then it checks distance
            {
                distance_temp = abs(i-mid_row)+abs(j-mid_col); //uses distance formula on current node
                if (distance_temp < distance_from_mid)                                                                               //if current distance is smaller than previous smallest disance then it changes the best available
                {
                    temp_row = room[i][j].get_row();
                    temp_seat = room[i][j].get_seat();
                    distance_from_mid = distance_temp;
                }
            }
        }
    }
    bestrow = temp_row;  //alters best available
    bestcol = temp_seat; //alters best available
}

char auditorium::best_available_col() //done
{
    return bestcol;
}

int auditorium::best_available_row() //done
{
    return bestrow;
}
