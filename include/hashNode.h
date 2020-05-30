//Gerald Torrijos
//gxt170002

#ifndef HASHNODE_H_INCLUDED
#define HASHNODE_H_INCLUDED
#include <string>
#include <iostream>

struct order_node
{
    order_node *next_order;
    std::string a_one;
    std::string a_two;
    std::string a_three;
};
class HashNode
{
private:
    order_node *root;
    std::string user;
    int index;
    std::string pass;
    HashNode *next;

public:
    HashNode(int ind, std::string val, std::string p) //creates the hashnode
    {
        user = val;
        index = ind;
        pass = p;
        next = nullptr;
        root = nullptr;
    }

    HashNode *getNext()
    {
        return next;
    }
    int getIndex()
    {
        return index;
    }
    void setNext(HashNode *a)
    {
        next = a;
    }
    std::string getUser()
    {
        return user;
    }
    std::string getPass()
    {
        return pass;
    }

    
    order_node *get_root()
    {
        return root;
    }
    void change_root(order_node *current)
    {
        root = current;
    }
    void add_orders(std::string order, std::string audi) //generates a linked list of orders to represent multiple orders
    {
        if (!root) //if there is no head node it creates one
        {
            root = new order_node;
            root->next_order = nullptr;
            if (audi == "A1.txt")
                (root->a_one) = order;
            else if (audi == "A2.txt")
                root->a_two = order;
            else if (audi == "A3.txt")
                root->a_three = order;
        }
        else //otherwise adds it to end of node
        {
            order_node *current = root;
            order_node *new_node = new order_node;
            if (audi == "A1.txt")
                (new_node->a_one) = order;
            else if (audi == "A2.txt")
                new_node->a_two = order;
            else if (audi == "A3.txt")
                new_node->a_three = order;
            new_node->next_order = nullptr;

            while (current->next_order)
                current = current->next_order;
            current->next_order = new_node;
        }
    }


    
};

#endif // HASHNODE_H_INCLUDED
