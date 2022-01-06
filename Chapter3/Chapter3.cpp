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

struct ClockOfTheLongNow {
    ClockOfTheLongNow(long year) 
        : year{year}
    {}

    void add_year() {
        year++;
    }

    bool set_year(int new_year) {
        year = new_year;
        return true;
    }

    int get_year() const {
        return year;
    }
private:
    int year;
};

void add_year(ClockOfTheLongNow& clock) {
    clock.set_year(clock.get_year() + 1); // No dref operator needed
}


struct Avout {
    Avout(const char* name, long year_of_apert)
        : name{ name }, apert{ year_of_apert }{}
    void announce() const {
        printf("My name is %s and my next apert is %d. \n", name, apert.get_year());
    }

    const char* name;
    ClockOfTheLongNow apert;
};

void read_from(const char* l_or_u_string, int index) {
    auto size = sizeof(l_or_u_string) / sizeof(char);

    if (index > size) {
        printf("I don't think so. string size is %d and you're looking for index %d \n", size, index);
        return;
    }


}

void write_to(char l_or_u_string[], int size, const char new_char, int index) {
}

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

    read_from(upper, 3);

    //lower[7] = 'g'; // Super bad. NEVER DO THIS!

    /*
    Line 107 demonstrates writing out-of-bounds memory. By accessing the element at index 7,
    you've gone past the storage allotted to lower. No bounds checking occurs (FALSE: VS does this); this code compiles without warning.
    At runtime (if VS didn't check bounds for us), you get undefined behavior. This means that C++ language specification doesn't prescribe
    what happens, so your program might crash, open a security vulnerability, or spawn an artificial general intelligence.
    */


    /*
    void Pointers and std::byte pointers
    The void pointers have important restrictions, the principal of which is that you cannot dereference a void*. Because the pointed to type
    has been erased, dereferencing makes no sense (recall that the set of values for void objects is empty). 
    
    Other times you want to interact with raw memory at the byte level. Examples include low-level operations like copying raw data between files
    and memory, encryption, and compression. You cannot use a void pointer for such purposes because bit-wise and arithmetic operations are disabled.
    In such situations, you can use a std::byte pointer.
    */

    /*
    nullptr and Boolean Expressions
    Pointers can have a special literal value, nullptr. Generally, a pointer that equals nullptr doesn't point to anything. You could use nullptr to 
    indicate, for example, that there's no more memory left to allocate or that some error occurred.

    Pointers have an implicit conversion to bool. Any value that is not nullptr converts implicitly to true, whereas nullptr converts to false.
    This is useful when a function returning a pointer ran successfully. A common idiom is that such a function returns nullptr in the case of failure. The canonical example is memory allocation.
    */

    /*
    REFERENCES
    References are safer, more convenient versions of pointers. You declare references with the & declarator appended to the type name. References cannot be assigned to null (easily), and they cannot be
    reseated (or reassigned).

    The syntax for dealing in references is much cleaner than for pointers. Rather than using the member-of-pointer and dereference operators, you use references exactly as if they're of the pointed-to type.
    */

    ClockOfTheLongNow clock{2019};
    printf("The year is %d.\n", clock.get_year()); // 
    add_year(clock); // Clock is implicitly passed by reference!
    printf("The year is %d.\n", clock.get_year()); // 

    /*
    Usage of Pointers and References
    Pointers and References are largely interchangeable, but both have tradeoffs. If you must sometimes change your reference type's value - that is, if you must change what your reference type refers
    to - you must use a pointer. Many data structures (including forward-linked lists) require that you be able to change a pointer's value. Because references cannot be reseated and they shouldn't 
    generally be assigned to nullptr, they're sometimes not suitable.
    */


    /*
    Forward-linked lists: The canonical pointer-based data structure
    This data structure is made up of a series of elements. Each element holds a pointer to the next element.
    The last element in the linked list holds a nullptr. Inserting elements into a linked list is very efficient, and elements can be discontinuous in memory. 
    */

    /*
    Employing References
    Pointers provide a lot of flexibility, but this flexibility comes at a safety cost. If you don't need the flexibility of reseatability and nullptr, references
    are the go-to reference type.
    */

    /* Driving home the point that references cannot be reseated */
    int original = 100;
    int& original_ref = original;
    int* original_ptr = &original; // assign address of original to pointer

    printf("Original: %d\n", original);
    printf("Reference: %d\n", original_ref);
    printf("Original Pointer %d\n", *original_ptr); // dereference ptr to see value of original
    
    int new_value = 200;
    original_ref = new_value; // This assigns the value of new_value to the object it points to (doesn't reseat original_ref so it points to new_value)

    printf("Original: %d\n", original);
    printf("Original Pointer: %d\n", *original_ptr);
    printf("New Value: %d\n", new_value);
    printf("Reference: %d\n", original_ref);

    /*
    this pointers
    When you program a method, sometimes you need to access the current object, which is the object that is executing the method.

    Within method definitions, you can access the current object using the this pointer. Usually, this isn't needed, because this
    is implicit when accessing members. But sometimes you might need to disambiguate - for example, if you declare a method parameter
    whose name collides with a member variable. 
    */

    /*
    const Correctness
    The keyword const roughly means "I promise not to modify." If code attempts to modify a const variable, the compiler will emit
    an error. When used correctly, const is one of the most powerful language features in all modern programming languages because
    it helps you to eliminate many kinds of common prgramming mistakes at compile time.

    const arguments
    Marking an argument as const precludes its modification within a function's scope.

    const methods
    Marking a method const communicates that you promise not to modify the current object's state within the const method.

    const member variables
    You can mark member variables const by adding the keyword to the member's type. The const member variables cannot be modified
    after their initialization.

    struct Avout {
        const char* name = "Erasmus";
        ClockOfTheLongNow apart;
    };


    Sometimes you want the safety of marking a member variable const but would also like to initialize  the member with arguments passed into
    a constructor. For this you employ initializer lists.

    Member Initalizer Lists
    Member initializer lists are the primary mechanism for initializing class members. To declare a member initializer list, place a colon after the
    argument list in a constructor. Then insert one or more comma-separated member initializers. A member initializer is the name of the member followed
    by a braced intialization {}. Member initializers allow you to set the value of const fields at runtime.
    */
    
    Avout raz{ "Erasmus", 3010 };
    Avout jad{ "Jad", 4000 };

    raz.announce();
    jad.announce();

    /*
    All member initializations execute before the constructor's body. This has two advantages:
    1. It ensures validity of all members before the constructor executes, so you can focus on initialization logic rather than member error checking.
    2. The members initialize once. If you reassign members in the constructor, you potentially do extra work.

    NOTE: You should order the member initializers in the same order they appear in the class definition, because their constructors will be called in this order

    */

    /*
    auto Type Deduction
    The auto keyword tells the compiler to devine type information for you, relieving you from inputting redundant type information.

    Initialization with auto
    In almost all situations, the compiler can determine the correct type of an object using the initialization value. 
    */

    /*This assignment contains redundant information*/
    int answer = 42;

    /*The compiler knows answer is an int because 42 is an int. You can use auto instead*/
    auto the_answer{ 42 };           // int
    auto foot{ 12L };                // long
    auto rootbeer{ 5.0F };           // float
    auto cheeseburger{10.0};         // double
    auto politifact_claims{ false }; // bool
    auto cheese{ "string" };         // char[7]

    /*This also works when initializing with parentheses () and the lone = */

    auto th_answer = 42;
    auto foot_1(12L);

    /*
    auto and Reference Types
    It's common to add modifiers like &, *, and const to auto. Such modifications add the intended meanings(reference, pointer, and const respectively) */
    auto year{ 2021 };            // int
    auto& year_ref = year;        // int&
    const auto& year_cref = year; // const int&
    auto* year_ptr = &year;       // int*
    const auto* year_cptr = &year;// const int*

    /*As a general rule, use auto always*/

    /*
    NOTE: There are some corner cases to using braced initialization where you might get surprising results, but these are few, especially after C++ 17 fixed some pedantic
    nonsense behavior. Prior to C++ 17, using auto with braces{} specified a special object called a std::initializer_list, which you'll meet in Chapter 13.
    */


    int i = 0;
    std::cin >> i;
}
