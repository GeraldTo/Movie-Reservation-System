//Gerald Torrijos
//gxt170002

#ifndef HASHMAP_H
#define HASHMAP_H
#include "hashNode.h"

class hashMap
{
    private:
        HashNode **table;
        int table_size;
        int current_filled;
        const double load_factor = .5;
        const int default_size = 10;
    public:
        hashMap();
        virtual ~hashMap();
        int get_size(){return table_size;}
        int position(std::string);
        HashNode* user_pos(std::string);
        void resize_hash();
        void set_index(std::string,std::string);
        bool pass_correct(std::string,std::string);
        void printMap();
        
        std::string getOrder(std::string,int);
        void change_order(std::string,std::string,int);
        void delete_order(order_node*,HashNode*);
        void get_all_orders(std::string,std::string);
        void setOrders(std::string,std::string,std::string);
        
        

};

#endif // HASHMAP_H
