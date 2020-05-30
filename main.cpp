#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cmath>
#include "src/hashMap.cpp"
#include "src/auditorium.cpp"
#include "src/theaterseats.cpp"
#include "src/basenode.cpp"

using namespace std;

hashMap test;

int menu(string);               //main menu and asks for input
int admin_menu();               //admin menu
void audi_menu(string, string); //submenu for reservation
int input_int();                //does cin and sees if its an actual int then returns it
void setUsers();
void login_menu();

int main()
{
    setUsers();
    //test.printMap();
    login_menu();

    return 0;
}

void setUsers()
{
    ifstream file("userdb.dat"); //reads file and puts it into hashmap
    while (!file.eof())
    {
        string line;
        getline(file, line);
        istringstream ss(line);
        string user;
        string pass;
        getline(ss, user, ' ');
        getline(ss, pass, ' ');
        test.set_index(user, pass);
    }
}

int input_int() //check if input is int and returns it
{
    int input = 0;
    cin >> input;
    while (true)
    {
        if (!cin.fail()) //verifies input
        {
            break;
        }
        else //otherwise loop
        {
            cout << "\nPlease enter a valid input" << endl;
            cin.clear();
            cin.ignore(100000, '\n');
            cin >> input;
        }
    }
    return input;
}

void login_menu()
{
    while (1) //breaks out once admin exits
    {         //otherwise loops login
        string user = "";
        string pass = "";
        cout << "Enter username: ";
        cin >> user;
        int pass_attempt = 0;
        int exit = 0;
        while (pass_attempt < 3) //increments as long as password is wrong
        {
            cout << "Enter Password: ";
            cin >> pass;
            if (test.pass_correct(user, pass) && user != "admin") //checks if user and password exists
            {
                cout << "\nWelcome Back\n"
                     << endl;
                exit = menu(user);
                break;
            }
            else if (test.pass_correct(user, pass)) //checks to see if login belongs to an admin
            {                                       //to know if it should go to an admin menu
                cout << "\nHello admin\n"
                     << endl;
                exit = admin_menu();
                break;
            }
            else
                cout << "\nError. Retry\n"
                     << endl;
            pass_attempt++;
        }
        if (exit != 0) //exit is only if admin exits
            break;
    }
}

int admin_menu()
{
    int input = 0;
    while (true) //loops menu until exits or or logs out
    {
        cout << "1. Print Report\n2. Logout\n3. Exit" << endl;
        cout << "\nWhat can we do for you today? ";
        while (true) //verifies input
        {
            input = input_int(); //gets input and sees if its in valid range
            if (input >= 1 && input <= 3)
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        if (input == 1) //gets report for admin
        {
            cout << "\nHere is the report\n"
                 << endl;
            cout << "Auditoriums  | " << setw(10) << left << "Open seats" << setw(10) << left << " Reserved" << setw(10) << left
                 << "Adult" << setw(10) << left << "Children" << setw(10) << left << "Seniors" << setw(10) << left << "Sales" << endl;

            auditorium room1("A1.txt");
            auditorium room2("A2.txt");
            auditorium room3("A3.txt");
            cout << "Auditorium 1 | " << setw(11) << left << room1.get_open_seats() << setw(9) << left << room1.get_seats_sold()
                 << setw(10) << left << room1.get_total_adults() << setw(10) << left << room1.get_total_childs()
                 << setw(10) << left << room1.get_total_seniors() << "$" << fixed << setprecision(2) << room1.get_sales() << endl;

            cout << "Auditorium 2 | " << setw(11) << left << room2.get_open_seats() << setw(9) << left << room2.get_seats_sold()
                 << setw(10) << left << room2.get_total_adults() << setw(10) << left << room2.get_total_childs()
                 << setw(10) << left << room2.get_total_seniors() << "$" << fixed << setprecision(2) << room2.get_sales() << endl;

            cout << "Auditorium 3 | " << setw(11) << left << room3.get_open_seats() << setw(9) << left << room3.get_seats_sold()
                 << setw(10) << left << room3.get_total_adults() << setw(10) << left << room3.get_total_childs()
                 << setw(10) << left << room3.get_total_seniors() << "$" << fixed << setprecision(2) << room3.get_sales() << endl;

            cout << "Total        | " << setw(11) << left << (room3.get_open_seats()) + (room2.get_open_seats()) + (room1.get_open_seats())
                 << setw(9) << left << room1.get_seats_sold() + room2.get_seats_sold() + room3.get_seats_sold()
                 << setw(10) << left << room1.get_total_adults() + room2.get_total_adults() + room3.get_total_adults()
                 << setw(10) << left << room3.get_total_childs() + room2.get_total_childs() + room1.get_total_childs()
                 << setw(10) << left << room1.get_total_seniors() + room2.get_total_seniors() + room3.get_total_seniors()
                 << "$" << room1.get_sales() + room2.get_sales() + room3.get_sales() << endl;

            cout << endl;
        }
        else if (input == 2) //logs out
        {
            cout << "\nBye\n"
                 << endl;
            return 0;
        }
        else if (input == 3) //exits program
        {
            cout << "\nExiting Program\nBye" << endl;
            return 1;
        }
    }
    return 0;
}

int menu(string user)
{
    while (true)
    {
        cout << "1. Reserve Seats\n2. View Orders\n3. Update Order\n4. Display Receipt\n5. Log Out" << endl;
        cout << "\nWhat can we do for you today? ";
        int input = 0;
        while (true) //needs to loop to verify if input is in correct range
        {
            input = input_int();
            if (input >= 1 && input <= 5)
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        if (input == 1) //leads to sub menu to reserve seats in auditorium and creat new order
        {
            int room = 0;
            cout << "\n1. Auditorium 1\n2. Auditorium 2\n3. Auditorium 3\n\nWhich auditorium do you want? ";
            while (true)
            {
                room = input_int();
                if (room >= 1 && room <= 3)
                    break;
                cout << "\nPlease enter a valid input" << endl;
            }
            if (room == 1)
                audi_menu(user, "A1.txt");
            else if (room == 2)
                audi_menu(user, "A2.txt");
            else if (room == 3)
                audi_menu(user, "A3.txt");
        }
        else if (input == 2) // displays all orders
        {
            cout << "\nHere is your current order.\n"
                 << endl;
            test.get_all_orders(user, "View");
        }
        else if (input == 3) //update the orders
        {
            cout << endl;
            test.get_all_orders(user, "View"); //displays orders
            int order_num = 0;
            if (test.getOrder(user, 1) != "no orders yet") //only runs if there is an order
            {
                while (true) //prompts to choose which order to edit
                {
                    cout << "\nWhich order do you want to change? " << endl;
                    order_num = input_int();
                    if (order_num > 0 && test.getOrder(user, order_num) != "no orders yet")
                    {
                        cout << "\nWhat do you want to do with your order?\n"
                             << endl;
                        cout << "\n1. Add tickets to order\n2. Delete tickets from order\n3. Cancel Order\n\nWhat do you want to change? ";
                        int order = 0;
                        while (true) //gets a valid input in range
                        {
                            order = input_int();
                            if (order >= 1 && order <= 3)
                                break;
                            cout << "\nPlease enter a valid input" << endl;
                        }
                        string current_order = test.getOrder(user, order_num); // gets a string that represents the order
                        string audi = "";
                        if (current_order.substr(0, 1) == "1") //first oart of string is the auditorium it comes from
                            audi = "A1.txt";
                        else if (current_order.substr(0, 1) == "2")
                            audi = "A2.txt";
                        else if (current_order.substr(0, 1) == "3")
                            audi = "A3.txt";
                        auditorium room(audi);
                        int rows = 0;
                        int seats = 0;
                        string useless = "";
                        fstream file(audi);
                        while (!file.eof())
                        {
                            getline(file, useless); //gets each line and counts every time it can get another line
                            rows++;
                            if (rows == 1)
                                seats = (int)useless.length(); //gets length of row
                        }
                        file.clear();
                        file.close();
                        current_order.erase(0, 1);
                        if (order == 1)
                        {
                            cout << "Where do you want to add? " << endl;
                            int input_row = 0;
                            char input_seat = 0;
                            int input_adults = 0;
                            int input_child = 0;
                            int input_seniors = 0;
                            cout << room.customer_auditorium() << endl; //shows customer the seats available and which ones are full by looping through each node and returning the tickets
                            cout << "\nWhat row do you want?:" << endl;
                            while (true) //asks which row that desired seat is in to be added
                            {
                                input_row = input_int();
                                if (input_row <= rows && input_row > 0)
                                    break;
                                cout << "\nPlease enter a valid input" << endl;
                            }
                            cout << "\nWhat column do you want?:" << endl;
                            cin >> input_seat;
                            while (1) //asks which seat wanted to be added
                            {

                                if ((input_seat >= 'A' && input_seat <= (char)(65 + seats)) || (input_seat >= 'a' && input_seat <= (char)(97 + seats)))
                                {
                                    input_seat = (char)toupper(input_seat);
                                    break;
                                }
                                else
                                {
                                    cout << "Please enter a valid input" << endl;
                                    cin.clear();
                                    cin.ignore(1000000000, '\n');
                                    cin >> input_seat;
                                }
                            }
                            cout << "\nHow many adult tickets do you want?:" << endl; //basically does get audi_menu() but without best available
                            while (true)
                            {
                                input_adults = input_int();
                                if (input_adults >= 0)
                                    break;
                                cout << "\nPlease enter a valid input" << endl;
                            }
                            cout << "\nHow many children tickets do you want?:" << endl;
                            while (true)
                            {
                                input_child = input_int();
                                if (input_child >= 0)
                                    break;
                                cout << "\nPlease enter a valid input" << endl;
                            }
                            cout << "\nHow many senior tickets do you want?:" << endl;
                            while (true)
                            {
                                input_seniors = input_int();
                                if (input_seniors >= 0)
                                    break;
                                cout << "\nPlease enter a valid input" << endl;
                            }
                            if (room.is_reserved(input_row, input_seat, input_adults + input_child + input_seniors)) //goes to specified part of the grid and loops each seat until it hits the sum of tickets
                                cout << "\n\nLooks like you can't reserve the seats you want\n"
                                     << endl;
                            else
                            {
                                room.reserve_tickets(input_row, input_seat, input_adults, input_child, input_seniors); //reserves the desired seats if they are all available
                                cout << "\nYour tickets are now reserved. Thank you\n"
                                     << endl;
                                int incre = 0;
                                int tempA = input_adults;
                                int tempC = input_child;
                                int tempS = input_seniors;
                                char tempseat = input_seat;
                                while (incre < input_adults + input_child + input_seniors) //edits order by adding orders to the end of the old order string
                                {
                                    if (tempA > 0)
                                    {
                                        string s(1, tempseat);
                                        string k(1, 'A');
                                        current_order += (to_string(input_row) + s + k);
                                        tempseat++;
                                        tempA--;
                                    }
                                    else if (tempC > 0)
                                    {
                                        string s(1, tempseat);
                                        string k(1, 'C');
                                        current_order += (to_string(input_row) + s + k);
                                        tempseat++;
                                        tempC--;
                                    }
                                    else if (tempS > 0)
                                    {
                                        string s(1, tempseat);
                                        string k(1, 'S');
                                        current_order += (to_string(input_row) + s + k);
                                        tempseat++;
                                        tempS--;
                                    }
                                    incre++;
                                }
                                test.change_order(user, current_order, order_num);
                            }
                        }
                        else if (order == 2) //removes a seat from order
                        {
                            int input_row = 0;
                            char input_seat = 0;
                            while (true)
                            {
                                cout << "\nWhat row do you want to delete from?:" << endl;
                                while (true)
                                {
                                    input_row = input_int();
                                    if (input_row <= rows && input_row > 0)
                                        break;
                                    cout << "\nPlease enter a valid input" << endl;
                                }
                                cout << "\nWhat seat do you want?:" << endl;
                                cin >> input_seat;
                                while (1)
                                {
                                    if ((input_seat >= 'A' && input_seat <= (char)(65 + seats)) || (input_seat >= 'a' && input_seat <= (char)(97 + seats)))
                                    {
                                        input_seat = (char)toupper(input_seat);
                                        break;
                                    }
                                    else
                                    {
                                        cout << "Please enter a valid input" << endl;
                                        cin.clear();
                                        cin.ignore(1000000000, '\n');
                                        cin >> input_seat;
                                    }
                                }
                                string sea(1, input_seat);
                                string pos = to_string(input_row) + sea;
                                if (current_order.find(pos) != string::npos) //if order exists in order string it removes it otherwise it loops again
                                {
                                    room.remove_seats(input_seat, input_row);
                                    current_order.erase(current_order.find(pos), 3);
                                    test.change_order(user, current_order, order_num);
                                    break;
                                }
                                cout << "Invalid seats try again" << endl;
                            }
                            cout << room.customer_auditorium() << endl; //displays new auditorium
                        }
                        else if (order == 3)
                        {
                            cout << "We're going to clear it then.\n"
                                 << endl;
                            for (int i = 0; i < (int)current_order.length(); i += 3)
                            {
                                int row = stoi(current_order.substr(i, i + 1));
                                char seat = current_order[i + 1];
                                room.remove_seats(seat, row);
                            }
                            current_order = "";
                            test.change_order(user, current_order, order_num);
                        }
                        break;
                    }
                    else
                        cout << "Invalid order number" << endl;
                }
            }
        }
        else if (input == 4) //displays all orders and the total cost
        {
            cout << "\nHere is your current receipt.\n"
                 << endl;
            test.get_all_orders(user, "Receipt");
        }
        else if (input == 5) //logs out
            break;
    }

    cout << "\nBye\n"
         << endl;
    return 0;
}

void audi_menu(string user, string audi)
{
    fstream file(audi);
    if (file)
    {
        auditorium room(audi);
        int rows = room.get_rows();
        int seats = room.get_cols();
        int input_row = 0;
        char input_seat = 0;
        int input_adults = 0;
        int input_child = 0;
        int input_seniors = 0;

        
        cout << room.customer_auditorium() << endl; //shows customer the seats available and which ones are full by looping through each node and returning the tickets

        cout << "\nWhat row do you want?:" << endl;
        while (true) //gets row input to know where to reserve
        {
            input_row = input_int();
            if (input_row <= rows && input_row > 0) //checks range to not go over existing rows
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        cout << "\nWhat column do you want?:" << endl;
        cin >> input_seat;
        while (1) //gets seat to know where to go in the columns
        {
            if ((input_seat >= 'A' && input_seat <= (char)(65 + seats)) || (input_seat >= 'a' && input_seat <= (char)(97 + seats))) //checks range to not go over existing columns
            {
                input_seat = (char)toupper(input_seat);
                break;
            }
            else
            {
                cout << "Please enter a valid input" << endl;
                cin.clear();
                cin.ignore(1000000000, '\n');
                cin >> input_seat;
            }
        }
        cout << "\nHow many adult tickets do you want?:" << endl;
        while (true) //asks for nums of desired seats of adults
        {
            input_adults = input_int();
            if (input_adults >= 0)
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        cout << "\nHow many children tickets do you want?:" << endl;
        while (true) //asks for nums of desired seats of children
        {
            input_child = input_int();
            if (input_child >= 0)
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        cout << "\nHow many senior tickets do you want?:" << endl;
        while (true) //asks for nums of desired seats of seniors
        {
            input_seniors = input_int();
            if (input_seniors >= 0)
                break;
            cout << "\nPlease enter a valid input" << endl;
        }
        {                                                                                            //reserves seats
            if (room.is_reserved(input_row, input_seat, input_adults + input_child + input_seniors)) //goes to specified part of the grid and loops each seat until it hits the sum of tickets
            {
                char yesorno = 0;
                cout << "\n\nLooks like you can't reserve the seats you want\n"
                     << endl;
                
                room.best_available(input_adults + input_child + input_seniors);        //uses distance formula to find closest seat to the middle
                if (room.best_available_col() != '@' || room.best_available_row() != 0) //these values change if there is a best available seat
                {
                    cout << room.customer_auditorium() << endl;
                    cout << "\nClosest seats to middle is " << room.best_available_row() //found a best available
                         << room.best_available_col() << "\n\nWant best available?\nY/N" << endl;
                    while (yesorno != 'N') //loops until valid answer
                    {
                        cin >> yesorno;
                        if (yesorno == 'Y')
                        {
                            room.reserve_tickets(room.best_available_row(), room.best_available_col(), input_adults, input_child, input_seniors); //reserves best available by using the new seats found instead

                            string temp = ""; //generates a string using sum of desired seats and starting position of best available seats
                            int incre = 0;    //to get an order string formatted as (row seat ticket type)
                            int tempA = input_adults;
                            int tempC = input_child;
                            int tempS = input_seniors;
                            char tempseat = room.best_available_col();
                            while (incre < input_adults + input_child + input_seniors)
                            {
                                if (tempA > 0)
                                {
                                    string s(1, tempseat);
                                    string k(1, 'A');
                                    temp += (to_string(room.best_available_row()) + s + k);
                                    tempseat++;
                                    tempA--;
                                }
                                else if (tempC > 0)
                                {
                                    string s(1, tempseat);
                                    string k(1, 'C');
                                    temp += (to_string(room.best_available_row()) + s + k);
                                    tempseat++;
                                    tempC--;
                                }
                                else if (tempS > 0)
                                {
                                    string s(1, tempseat);
                                    string k(1, 'S');
                                    temp += (to_string(room.best_available_row()) + s + k);
                                    tempseat++;
                                    tempS--;
                                }
                                incre++;
                            }
                            test.setOrders(user, audi, temp); //creates new order

                            cout << "\nThank you\n"
                                 << endl;
                            break;
                        }
                        else if (yesorno == 'N')
                            cout << "\nThanks anyways!\n"
                                 << endl;
                        else //invalid input
                            cout << "Please enter a valid input" << endl;
                    }
                }
                else
                    cout << "There are no available seats for you. Sorry\n"
                         << endl;
                
            }
            else
            {
                room.reserve_tickets(input_row, input_seat, input_adults, input_child, input_seniors); //reserves the desired seats if they are all available
                cout << room.customer_auditorium();
                cout << "\nYour tickets are now reserved. Thank you\n"
                     << endl;
                string temp = ""; //generates a string using sum of desired seats and starting position inputed
                int incre = 0;    //to get an order string formatted as (row seat ticket type)
                int tempA = input_adults;
                int tempC = input_child;
                int tempS = input_seniors;
                char tempseat = input_seat;
                while (incre < input_adults + input_child + input_seniors)
                {
                    if (tempA > 0)
                    {
                        string s(1, tempseat);
                        string k(1, 'A');
                        temp += (to_string(input_row) + s + k);
                        tempseat++;
                        tempA--;
                    }
                    else if (tempC > 0)
                    {
                        string s(1, tempseat);
                        string k(1, 'C');
                        temp += (to_string(input_row) + s + k);
                        tempseat++;
                        tempC--;
                    }
                    else if (tempS > 0)
                    {
                        string s(1, tempseat);
                        string k(1, 'S');
                        temp += (to_string(input_row) + s + k);
                        tempseat++;
                        tempS--;
                    }
                    incre++;
                }
                test.setOrders(user, audi, temp); //creates new order
            }
        }
        file.close();
    }
    else
        cout << audi << " file does not exist" << endl;
}
