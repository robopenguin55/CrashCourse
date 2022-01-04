// Chapter3.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

/*
dereference operator (*)
The Dereference operator can cause a lot of confusion for beginners because the dereference operator,
the pointer declaration, and multiplication all use asterisks. 

int * gettysburg_address : pointer

*gettysburg_address : dereference

if a dereferenced pointer appears anywhere except the left side of an equal sign, you're reading from the address.
To retrieve the int pointed to by gettysburg_address, you just tack on the dereference operator.
*/

/*
member of pointer operator or arrow operator (->)
- dereferences a pointer
- accesses a member of the pointed-to object

(*clock_ptr).get_year()

and 

clock_ptr->get_year() 

are equivalent

*/

/*
Pointers share several characteristics with arrays. Pointers encode object location.
Arrays encode the location and length of contiguous objects.

At the slightest provocation, an array will decay into a pointer. A decayed array loses length information
and converts to a pointer to the array's first element.

*/

int main()
{
    int gettysburg{};
    int* gettysburg_address = &gettysburg; // initialize the pointer to the address of gettysburg

    printf("Value at gettysburg_address: %d\n", *gettysburg_address); // print the int pointed to by gettysburg_address (Should be 0)
    printf("Gettysburg Address: %p\n", gettysburg); // print the value of gettysburg_address itself (Should be some address)
    *gettysburg_address = 17325;


    printf("Value at gettysburg_address: %d\n", *gettysburg_address); // print the int pointed to by gettysburg_address (Should be 17325)
    printf("Gettysburg Address: %p\n", gettysburg); // print the value of gettysburg_address itself (Same address as before)


    printf("gettysburg : %d\n", gettysburg);

    // first, initialize an int array key_to_the_universe
    // next, initialize the int pointer key_ptr to key_to_the_universe, which decays into a pointer
    // after initialization, key_ptr points to the first element of key_to_the_universe

    int key_to_the_universe[]{ 3,6,9 }; 
    int* key_ptr = key_to_the_universe; // points to 3

    // Pointer arithmetic
    /*
    To obtain the address of the nth element of an array, you have two options.
    First, you can take the direct approach of obtaining the nth element with square brackets ([])
    and then use the address-of (&) operator:
    */

    int* second_option_ptr = &key_ptr[1];

    /*
    Pointer arithmetic, the set of rules for addition and subtraction on pointers, provides and alternate approach. 
    When you add or subtract integers to pointers, the compiler figures out the correct byte offset using the size of the pointed-to type.
    For example, adding 4 to a uint64_t pointer adds 32 bytes:

    a uint64_t takes up 8 bytes, so 4 of them take up 32 bytes. The following is equivalent to the previous option of obtaining the address of the nth
    element of an array:
    */

    int* second_option_ptr2 = key_ptr + 1;

    /*
    POINTERS ARE DANGEROUS!
    Buffer overflows : For arrays and pointers, you can access arbitrary array elements with the bracket operator ([]) or with pointer arithmetic. These are
    very powerful tools for low-level programming because you can interact with memory more or less without abstraction. This gives you exquisite control over
    the system, which you need in some environments (for example, in system programming contexts like implementing network protocols or with embedded controllers).
    With great power comes great responsibility, however, and you must be very careful. Simple mistakes with pointers can have catastrophic and mysterious consequences.
    */

    char lower[] = "abc?e";
    char upper[] = "ABC?E";

    char* upper_ptr = upper;       // equivalent: &upper[0]

    lower[3] = 'd';                // lower now contains: a b c d e \0
    upper_ptr[3] = 'D';            // upper now contains: A B C D E \0

    char letter_d = lower[3];      // letter_d = 'd'
    char letter_D = upper_ptr[3];  // letter_D = 'D'

    printf("lower: %s upper: %s", lower, upper);

    //lower[7] = 'g'; // Super bad. NEVER DO THIS!

    /*
    Line 107 demonstrates writing out-of-bounds memory. By accessing the element at index 7,
    you've gone past the storage allotted to lower. No bounds checking occurs (FALSE: VS does this); this code compiles without warning.
    At runtime (if VS didn't check bounds for us), you get undefined behavior. This means that C++ language specification doesn't prescribe
    what happens, so your program might crash, open a security vulnerability, or spawn an artificial general intelligence.
    */

    int i = 0;
    std::cin >> i;
}
