// FCAI – Object-Oriented Programming 1 – 2022 - Assignment 2
// Program Name: RealNumber
// Last Modification Date: 12/11/2022
// Author - ID - Group: Mahmoud Saleh Mohammed Saleh - 20210788 - A
/*
description: In this program I developed a new C++ type (class) that inherits the class from last assignment.
that can hold unlimited real number values and performs arithmetic operations on them.
such as: +, -, <, and >.
 */

#include"RealNumberClass.h"
using namespace std;


int main() {

    string exampleTest, otherExampleTest;

    cout << "Please enter a real number: " << endl;
    cin>>exampleTest;

    cout << "Please enter a real number: " << endl;
    cin>>otherExampleTest;


    //////
    cout << "Testing Addition: " << endl;
    BigReal realObj(exampleTest), otherRealObj(otherExampleTest), defaultTestObj;

    defaultTestObj = realObj + otherRealObj;
    cout << exampleTest << " + " << otherExampleTest << " = " << defaultTestObj << endl;

    //////
    cout << "Testing Subtraction: " << endl;
    BigReal realObj1(exampleTest), otherRealObj1(otherExampleTest), defaultTestObj1;

    defaultTestObj1 = realObj1 - otherRealObj1;
    cout << exampleTest << " - " << otherExampleTest << " = " << defaultTestObj1 << endl;

    /////
    cout << "Testing Subtraction with opposite numbers positions: " << endl;
    BigReal realObj2(exampleTest), otherRealObj2(otherExampleTest), defaultTestObj2;

    defaultTestObj2 = otherRealObj2 - realObj2;
    cout << otherExampleTest << " - " << exampleTest << " = " << defaultTestObj2 << endl;

    ///////
    BigReal realObj3(exampleTest), otherRealObj3(otherExampleTest);
    cout << "Testing comparison operators: \n"
         << exampleTest << " > " << otherExampleTest << " = " << (realObj3 > otherRealObj3) << '\n'
         << exampleTest << " < " << otherExampleTest << " = " << (realObj3 < otherRealObj3) << endl;
    cout << "First Number: " << exampleTest << '\n'
         << "Sign: " << realObj3.sign() << endl;
    cout << "Second Number: " << otherExampleTest << '\n'
         << "Size: " << otherRealObj3.size() << endl;


    exit(0);
}




