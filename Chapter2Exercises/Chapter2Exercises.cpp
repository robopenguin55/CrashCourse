// Chapter2Exercises.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

enum class Operation
{
    Add,
    Subtract,
    Multiply,
    Divide
};

struct Calculator
{
    Operation op;

    Calculator(Operation o) {
        op = o;
    }

    int calculate(int a, int b) {
        int c{};

        switch (op)
        {
        case Operation::Add: {
            c = a + b;
            break;
        }
        case Operation::Subtract: {
            c = a - b;
            break;
        }
        case Operation::Multiply: {
            c = a * b;
            break;
        }
        case Operation::Divide: {
            c = a / b;
            break;
        }
        default:
            break;
        }

        return c;
    }
};

int main()
{
    auto add = Calculator{ Operation::Add };
    auto sub = Calculator{ Operation::Subtract };
    auto mult = Calculator{ Operation::Multiply };
    auto div = Calculator{ Operation::Divide };

    int sum = add.calculate(5, 2);
    int result = sub.calculate(5, 2);
    int product = mult.calculate(5, 2);
    int quotient = div.calculate(5, 2);

    printf("5+2=%d \n", sum);
    printf("5-2=%d \n", result);
    printf("5*2=%d \n", product);
    printf("5/2=%d \n", quotient);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
