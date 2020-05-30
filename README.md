# Movie-Reservation-System
Written in C++. Reserves seats in a movie theater and has a login system

This project uses hashmaps, file reading/writing, and a 2d array.

I essentially created a movie reservation system that uses a basic login system to keep track of orders, ticket types, and cost.
I created a hashmap that contains usernames and passwords using a .dat file. 
The hashmap has a load factor of .5 and handles collisions by adding the user info in a linked list.
The program implements a 2d array to represent the movie theater.
The theater is read from a file with A = Adults, C = Children, S = Seniors, and . = empty.
The program infinitely loops a login menu until the admin exits 
There are only normal users and an admin user and they can all log out
The admin can view a report of the theaters
The user can reserve, adjust orders (add, delete, modify), view orders, and view reciept
In reserving user is prompted is prompted to choose a theater
The user can then view it and is prompted to enter a valid location to reserve then asked for quatity of each ticket type.
If seats are not available then they are asked if they want the closest seats to the middle
