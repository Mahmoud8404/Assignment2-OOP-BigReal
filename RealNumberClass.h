#ifndef UNTITLED16_REALNUMBERCLASS_H
#define UNTITLED16_REALNUMBERCLASS_H

#include <iostream>
#include <deque>
#include <regex>

using namespace std;
#include <iostream>
#include <deque>
#include <regex>

using namespace std;

class BigDecimalInt{
private:
    string number;
    char signNumber;
    bool checkValidInput(string input);

public:
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (const BigDecimalInt anotherDec);
    BigDecimalInt& operator = (BigDecimalInt anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);
    BigDecimalInt operator - (BigDecimalInt anotherDec);
    friend ostream &operator << (ostream &out, BigDecimalInt num);
    int size();
    int sign();
    void setNumber(string num);
    string getNumber(){
        return number;
    }

    BigDecimalInt(){}
    BigDecimalInt(string num)
    {
        setNumber(num);
    }

};

/*class BigReal : public BigDecimalInt{
    private:
    void setRealNumber(string strReal);
    bool checkValidRealNumber(string input);

    public:
        BigReal (double realNumber = 0.0); // Default constructor
        BigReal (string realNumber);
        BigReal (BigDecimalInt bigInteger);
        BigReal (const BigReal& other); // Copy constructor
        BigReal (BigReal&& other); // Move constructor
        BigReal& operator= (BigReal& other); // Assignment operator
        BigReal& operator= (BigReal&& other); // Move assignment
        BigReal operator+ (BigReal& other);
        BigReal operator- (BigReal& other);
        bool operator< (BigReal anotherReal);
        bool operator> (BigReal anotherReal);
        bool operator== (BigReal anotherReal);
        int size();
        int sign();
        friend ostream& operator << (ostream& out, BigReal num);
        friend istream& operator >> (istream& out, BigReal num);

        BigReal(){}
};*/
#endif
