//Gerald Torrijos
//gxt170002

#include "../include/hashMap.h"
#include <cmath>
#include <string>
#include <iostream>

using namespace std;
//handles hashmap

hashMap::hashMap() //creates an empty hashtable
{
    current_filled = 0;
    table_size = default_size;
    table = new HashNode *[table_size]; //takes default size and creates an array
    for (int i = 0; i < table_size; i++)
        table[i] = nullptr;
}

hashMap::~hashMap()
{
    for (int i = 0; i < table_size; i++)
        if (table[i] != nullptr) //goes to each position of array
        {
            HashNode *temp = nullptr;
            HashNode *current = table[i]; //then moves down the chain
            while (current)
            {
                HashNode *temp = current;
                if (temp->get_root()) //and down the linked list of orders
                {
                    order_node *temp_order = nullptr;
                    order_node *current_order = temp->get_root();
                    while (current_order)
                    {
                        temp_order = current_order;
                        current_order = current_order->next_order;
                        delete temp_order; //deletes the orders
                    }
                }
                current = current->getNext();
                temp->setNext(nullptr);
                delete temp; //deletes the user
            }
        }
    delete[] table; //deletes the table
}

int hashMap::position(string user) //gets index from user
{
    int i = 0;
    int sum = 0;
    while (i < user.length()) //adds up sum of char
    {
        sum += (int)user[i];
        i++;
    }
    return sum % table_size; //then gets remainder of dividing by table size
}

void hashMap::set_index(string user, string pass) //fills hashtable
{

    int pos = position(user);
    HashNode *node = new HashNode(pos, user, pass);
    if (table[pos] == nullptr) //gets index and fills it if empty
    {
        table[pos] = node;
        current_filled++;
    }
    else //otherwise it calls collision to do chaining
    {
        HashNode *current = table[pos];
        while (current->getNext() != nullptr)
        {
            current = current->getNext();
        }
        current->setNext(node);
    }
    if ((((double)current_filled) / ((double)table_size)) >= load_factor) //calls resize if the table size goes over load factor
        resize_hash();
}

void hashMap::resize_hash() //resizes table by creating new array with the size doubles
{
    table_size = table_size * 2;
    HashNode **new_table = new HashNode *[table_size];
    for (int i = 0; i < table_size; i++)
        new_table[i] = nullptr;
    for (int i = 0; i < (table_size / 2); i++)
    {
        if (table[i] != nullptr)
        {
            HashNode *current = table[i];

            while (current)
            {
                HashNode *next = current->getNext();

                int pos = position(current->getUser()); //resets index
                HashNode *node = new HashNode(pos, current->getUser(), current->getPass());
                if (new_table[pos] == nullptr) //adds the node to table with new index
                {
                    new_table[pos] = node;
                }
                else
                {
                    HashNode *new_table_current = new_table[pos];
                    while (new_table_current->getNext() != nullptr)
                    {
                        new_table_current = new_table_current->getNext();
                    }
                    new_table_current->setNext(node);
                }

                current = next;
            }
        }

        delete table[i];
    }
    delete[] table;
    table = new_table;
}

void hashMap::printMap()
{
    for (int i = 0; i < table_size; i++)
    {
        HashNode *current = table[i];
        if (current == nullptr)
            continue;
        while (current != nullptr)
        {
            cout << current->getUser() << " " << current->getIndex() << "  ";
            current = current->getNext();
        }
        cout << endl;
    }
}

//handles user login

bool hashMap::pass_correct(string user, string pass) //looks for username in hashmap and compares the password
{
    int pos = position(user);
    if (table[pos])
    {
        if (table[pos]->getUser() == user && table[pos]->getPass() == pass) //compares use and password
            return true;
        else
        {
            HashNode *current = table[pos];
            while (current->getNext())
            {
                current = current->getNext();
                if (current->getUser() == user && current->getPass() == pass) //compares use and password
                    return true;
            }
            return false; //reaches nullptr so it doesn't exist
        }
    }
    else
        return false; //reaches nullptr so it doesn't exist
}

HashNode *hashMap::user_pos(string user) //finds the hashnode from user name
{
    HashNode *current = table[position(user)];
    while (current->getUser() != user)
        current = current->getNext();
    return current;
}


//handles orders

void hashMap::setOrders(string user,string room,string orders) //adds order to list
{
    user_pos(user)->add_orders(orders,room);
}

string hashMap::getOrder(string user,int order) // returns order string
{
    order_node* current = user_pos(user)->get_root();
    int  i = 1;
    if(current==nullptr) //checks first if there are orders
        return "no orders yet";
    
    while(i<order) //then moves pointer to ccorrect order
    {
        current=current->next_order;
        if(!current)
            return "no orders yet";
        i++;
    }
    if(current->a_one!="") //returns the order that has something in the string
        return "1"+current->a_one;
    else if(current->a_two!="")
        return "2"+current->a_two;
    else if(current->a_three!="")
        return "3"+current->a_three;
    return "";
}

void hashMap::get_all_orders(string user, string from) //gets all the orders
{
    order_node* curr = user_pos(user)->get_root();
    int order_num = 1; //order num
    int total_a = 0;
    int total_c = 0;
    int total_s = 0;

    if(!curr)
    {
        cout<<"No orders have been placed"<<endl;
        cout<<endl;
        return;
    }

    while(curr) //moves curr down order list
    {
        int adults = 0;
        int childs = 0;
        int seniors = 0;
        string raw = "";
        cout<<"Currently in order "<<order_num<<": "<<endl; //prints out order num
        if(curr->a_one!="") //prints out the auditorium its from
        {
            cout<<"\tAuditorium: 1"<<endl;
            raw = curr->a_one;
        }
        else if(curr->a_two!="")
        {
            cout<<"\tAuditorium: 2"<<endl;
            raw = curr->a_two;
        }
        else if(curr->a_three!="")
        {
            cout<<"\tAuditorium: 3"<<endl;
            raw = curr->a_three;
        }
        cout<<"\t";
        for(int i = 0;i<(int)raw.length();i+=3) //prints out the tickets and adds up the types
        {
            cout<<raw.substr(i,2)<<" ";
            if(raw.substr(i+2,1)=="A")
                adults++;
            else if(raw.substr(i+2,1)=="C")
                childs++;
            else if(raw.substr(i+2,1)=="S")
                seniors++;
        }
        curr=curr->next_order;
        total_a+=adults;
        total_c+=childs;
        total_s+=seniors;
        cout<<"\n\tAdult tickets: "<<adults<<"\n\tChild tickets: "<<childs<<"\n\tSenior tickets: "<<seniors<<endl; //display all the ticket types
        double total = ((double)adults*10.0)+((double)childs*5)+((double)seniors*7.5);
        if(from=="Receipt") //if needed for a receipt display the price
            cout<<"\tTotal in order " <<order_num<< " is: $"<<total<<endl;
        order_num++;
    }
    double total = ((double)total_a*10.0)+((double)total_c*5)+((double)total_s*7.5);
    if(from=="Receipt") //if needed for a receipt display the price
        cout<<"\nTotal is $"<<total<<endl;
}

void hashMap::change_order(string user, string order, int order_num) //looks for order and changes it with a new order
{
    order_node* current = user_pos(user)->get_root();
    int  i = 1;
    while(i<order_num) // moves order pointer to order num
    {
        current=current->next_order;
        i++;
    }
    if(current->a_one!="")
        current->a_one=order;
    else if(current->a_two!="")
        current->a_two=order;
    else if(current->a_three!="")
        current->a_three=order;
    if(current->a_one==""&&current->a_two==""&&current->a_three=="") //if all order strings are empty there are no orders
        delete_order(current,user_pos(user));                       // so it must be deleted
}

void hashMap::delete_order(order_node* current,HashNode* pos) //removes an order from list
{
    if(current==pos->get_root()) // if its the root order,
    {
        if(current->next_order) // it sets the new root to the next
        {
            pos->change_root(current->next_order);
            current->next_order=nullptr;
            delete current;
        }
        else
            pos->change_root(nullptr);
    }
    else //otherwise it just removes the node and resets the pointer b4
    {
        order_node* temp = pos->get_root();
        while(temp->next_order!=current)
            temp=temp->next_order;
        if(!current->next_order)
        {
            temp->next_order=nullptr;
            delete current;
        }
        else
        {
            temp->next_order=current->next_order;
            current->next_order=nullptr;
            delete current;
        }
    }
}
