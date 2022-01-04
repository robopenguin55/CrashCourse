// CrashCourse.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdio>

/*
Pointers are the fundamental mechanism used to refer to memory addresses. Pointers encode
both pieces of information required to interact with another object - that is, the objects
address and the objects type.
*/

struct Hal {
    Hal() : version{ 9000 } { // Constructor
        printf("I'm completely operational. \n");
    }
    ~Hal() { // Destructor
        printf("Stop, Dave.\n");
    }
    const int version;
};

template <typename T>
T add(T x, T y, T z) {
    return x + y + z;
}

/*The simplest of the user-defined types. The values that an enumeration can take
are restricted to a set of possible values. Enumerations are excellent for modeling categories
Under the hood, these values are simply integers.*/
enum class Race {
	Dinan,
	Teklan,
	Ivyn,
	Moiran,
	Camite,
	Julian,
	Aidan
};

/*Plain-old-data (POD) classes are simple containers. 
PODs have useful low-level features: they're C compatible, you can employ machine instructions
that are highly efficient to copy or move them, and they can be efficiently represented in memory.
As a general rule, you should order members from largest to smallest within POD definitions*/
struct Book {
	char name[256];
	int year;
	int pages;
	bool hardcover;
};

/*You can think of unions as different views or interpretations of a block of memory. They can be
useful in some low-level situations, such as when marshalling structures that must be consistent across 
architectures, dealing with type-checking issues related to C/C++ interoperation, and even when packing
bitfields. 

The union Variant can be interpreted as a char[10], an int, or a double. It takes up only as much memory
as its largest member. BECAUSE ALL MEMBERS OF A UNION ARE IN THE SAME PLACE, YOU CAN CAUSE DATA CORRUPTION
VERY EASILY*/
union Variant {
	char string[10];
	int integer;
	double floating_point;
};

int main()
{
	Race race = Race::Dinan;
	
	switch(race) {
		case Race::Dinan:{
			break;
		}
		case Race::Teklan:{
			break;
		}
		case Race::Ivyn:{
			break;
		}
		default:{
			break;
		}
	}
	
	Book neuromancer; 
	neuromancer.pages = 271;
	
	printf("Neuromancer has %d pages.",neuromancer.pages);
	
    auto a = add(1, 2, 3);
    auto b = add(1L, 2L, 3L);
    auto c = add(1.F, 2.F, 3.F);

    auto hal = new Hal{}; // Memory is allocated, then constructor is called
    delete hal; // Destructor is called, then memory is deallocated
    
    
    Variant v;
    v.integer = 42;
    printf("The ultimate answer: %d\n",v.integer);
    v.floating_point = 2.7182818284;
    printf("Eulers number e: %f\n", v.floating_point);
    printf("A dumpster fire: %d\n", v.integer);


	// There are many ways to initialize an array
	int array_1[]{ 1,2,3 };
	int array_2[5]{};
	int array_3[5]{ 1,2,3 }; // the remaining two elements initialize to 0
	int array_4[5];

    
    int i;
    std::cin >> i;
}
