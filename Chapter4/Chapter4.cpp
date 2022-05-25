/*
The Object Life Cycle
The object life cycle is the series of stages a C++ object goes through during its lifetime. 

An Object's Storage Duration
An object is a region of storage that has a type and a value. When you declare a variable, you create an object.
A variable is simply an object that has a name.
*/

#include <iostream>
#include <thread>
#include <cstdlib>
using namespace std;

/*
Allocation, Deallocation, and Lifetime
Every object requires storage. You reserve storage for objects in a process called allocation. When you're done with an
object, you release the object's storage in a process called deallocation.

An object's storage duration begins when the object is allocated and ends when the object is deallocated. The lifetime of
an object is a runtime property that is bound by the object's storage duration. An object's lifetime begins once its constructor
completes, and it ends just before a destructor is invoked. 
In summary, each object passes through the following stages:
    1. The object's storage duration begins, and storage is allocated.
    2. The object's constructor is called.
    3. The object's lifetime begins.
    4. You can use the object in your program.
    5. The object's lifetime ends.
    6. The object's destructor is called.
    7. The object's storage duration ends, and the storage is deallocated.
*/

/*
MEMORY MANAGEMENT
At runtime, programs create objects. Periodically, the garbage collector determines which objects are no longer required by the program
and safely deallocates them. This approach frees the programmer from worrying about managing an object's life cycle, but it incurs several
costs, including runtime performance, and requires some powerful programming techniques like deterministic resource management.

C++ takes a more efficient approach. The trade-off is that C++ programmers must have intimate knowledge of storage durations. It's our job,
not the garbage collector's, to craft object lifetimes.
*/

/*
AUTOMATIC STORAGE DURATION
An automatic object is allocated at the beginning of an enclosing code block, and it's deallocated at the end. The enclosing block is the automatic
object's scope. Automatic objects are said to have automatic storage duration. Note that function parameters are automatic, even though notationally
they appear outside the function body.

The function power_up_rat_thing is the scope for the automatic variables nuclear_isotopes and waste_heat
*/

void power_up_rat_thing(int nuclear_isotopes) {
    int waste_heat = 0;
}

/*
Both variables are allocated each time power_up_rat_thing is invoked. Just before power_up_rat_thing returns, these variables are deallocated.
Because you cannot access these variables outside of power_up_rat_thing, automatic variables are also called local variables.
*/

/*
STATIC STORAGE DURATION
A static object is declared using the static or extern keyword. You declare static variables at the same level you declare functions - at global scope (or namespace scope).
Static objects with global scope have static storage duration and are allocated when the program starts and deallocated when the program stops.
*/

static int rat_things_power{ 200 };

/*
When you use the static keyword, you specify internal linkage. Internal linkage means that a variable is inaccessible to other translation units. You can alternately specify
external linkage, which makes a variable accessible to other translation units. For external linkage, you use the extern keyword instead of static.

With extern instead of static, you can access rat_things_power from other translation units.
*/

/*
Local Static Variables
A Local Static Variable is a special kind of static variable that is a local - rather than global - variable. Local static variables are declared at function scope, 
just like automatic variables. But their lifetimes begin upon the first invocation of the enclosing function and end when the program exits.

You cannot refer to rat_things_power from outside of the power_up_rat_thing function due to its local scope.
*/

/*
Encapsulation: a bundling of data with a function that operates on that data.
*/

/*
Static Members
Are members of a class that aren't associated with a particular instance of a class. Normal class members have lifetimes nested within the class's lifetime,
but static members have static storage duration.

These members are essentially similar to static variables and functions declared at global scope; however, you must refer to them by the containing class's name,
using the scope resolution operator ::. In fact, you must initialize static members at global scope. You cannot initialize a static member within a containing class definition.

NOTE: There is an exception to the static member initialization rule: you can declare and define integral types within a class definition as long as they're also const.
*/

/*
Thread-Local Storage Duration
Mutable global variables are the source of many thread safety issues. Sometimes, you can avoid these issues by giving each thread its own scope of a variable. You can do this by
specifying that an object has thread storage duration.

You can modify any variable with static storage duration to have thread local storage duration by adding the thread_local keyword to the static or extern keyword. If only
thread_local is specified, static is assumed. The variable's linkage is unchanged.
*/

/*
The following example is NOT thread safe. Depending on the order of reads and writes, rat_things_power could become corrupted. 
*/

void power_up_rat_things(int nuclear_isotopes) {
    static int rat_thing_power = 200;
    rat_thing_power = rat_thing_power + nuclear_isotopes;
    const auto waste_heat = rat_thing_power * 20;

    if (waste_heat > 10,000) {
        printf("Warning! Hot doggie!\n");
    }

    printf("Rat thing power: %d\n", rat_thing_power);
}

/*
If we changed rat_thing_power to:
    static thread_local int rat_thing_power = 200;
Then each thread would represent its own Rat thing; if one thread modifies its rat_thing_power, the modification will not affect the other threads.
*/

/*
Dynamic Storage Duration
Objects with Dynamic Storage Duration are allocated and deallocated on request. You have manual control over when a dynamic object's life begins and when it ends.
Dynamic objects are also called allocated objects for this reason.

The primary way to allocate a dynamic object with a new expression. A new expression begins with the new keyword followed by the desired type of the dynamic object.
New expressions create objects of a given type and then return a pointer to the newly minted object.
*/

/*Consider the following dynamic object */
int* my_int_ptr = new int;

/*
You declare a pointer to int and initialize it with the result of the new expression on the right side of the equal sign. 

You can also initialize a dynamic object within a new expression, as shown here:
*/

int* my_int_ptr2 = new int{ 42 }; // initializes dynamic object to 42

/*
After allocating storage for the int, the dynamic object will be initialized as usual. After initialization completes, the dynamic object's lifetime begins.
You deallocate dynamic objects using the delete expression, which is composed of the delete keyword followed by a pointer to the dynamic object. 
Delete expressions always return void.

*/

/*
The value contained in memory where the deleted object resided is undefined, meaning the compiler can produce code that leaves anything there. In practice,
major compilers will try to be as efficient as possible, so typically the object's memory will remain untouched until the program reuses it for some other purposes.
You would have to implement a custom destructor to, for example, zero out some sensitive contents.
*/


/*
NOTE: Because the compiler doesn't typically clean up memory after an object is deleted, a subtle and potentially serious type of bug called a "use after free" can occur.
If you delete an object and accidentally reuse it, your program might appear to function correctly because the deallocated memory might still contain reasonable values. In 
some situations, the problems don't manifest until the program has been in production for a long time - or until a security researcher finds a way to exploit the bug and
discloses it!
*/

/*
MEMORY LEAKS
You must make sure that dynamic objects you allocate are also deallocated. Failure to do so causes memory leaks in which memory that is no longer needed by your program
isn't released. When you leak memory, you use up a resource in your environment that you'll never reclaim. This can cause performance problems or worse.
*/

/*
NOTE: In practice, your program's operating environment might clean up leaked resources for you. For example, if you've written user-mode code, modern operating systems will
clean up the resources when the program exits. However, if you've written kernel code, those operating systems won't clean up the resources. You'll only reclaim them when
the computer reboots.
*/

/*Object lifecycle tracer class */
struct Tracer {
    Tracer(const char* name, int s) : name{ name }, t{s} {
        printf("%s constructed.\n", name);
    }
    ~Tracer() {
        printf("%s destructed.\n", name);
    }
private:
    const char* name;
    const int t;
};

/*
Regarding the lifecycle of these variables:
They will be initialized before the main function is called
*/
static Tracer t1{ "Static variable" };
thread_local Tracer t2{ "Thread-local variable" };

void run_tracer() {
    const auto t2_ptr = &t2;
    printf("A\n");
    Tracer t3{ "Automatic variable" };
    printf("B\n");
    const auto* t4 = new Tracer{ "Dynamic variable" };
    printf("C\n");

    /*Automatic variable will be destructed when this method is out of scope.*/
    /*Static and thread local variables will be destructed when the application exits*/
    /*Notice that there is no corresponding message generated by the dynamic destructor of Tracer. The reason is that we've (intentionally) leaked the object pointed to by t4*/
}

int main()
{
    int test = 1;
    int test2 = 1;
    int test3 = 1;
    int test4 = 1;

    power_up_rat_thing(test);

    /*To deallocate the object pointed to by my_int_ptr, you would use the following delete expression:*/
    delete my_int_ptr;
    delete my_int_ptr2;

    /*
    Dynamic Arrays: Arrays with dynamic storage duration. You create dynamic arrays with array new expressions.
    */
    int* my_dynamic_int_array = new int[rat_things_power] {};

    /*
    Array new expressions return a pointer to the first element of the newly allocated array. The number of elements doesn't need to be a constant: the size of the array can
    be determined at runtime.

    To deallocated a dynamic array, use the array delete expression. Unlike the array new expression, the array delete expression doesn't require a length:
    */

    delete[] my_dynamic_int_array;

    run_tracer();

    int i;
    cin >> i;

    return 0;
}