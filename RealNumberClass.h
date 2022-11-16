#ifndef UNTITLED16_REALNUMBERCLASS_H
#define UNTITLED16_REALNUMBERCLASS_H

#include <iostream>
#include <deque>
#include <regex>
using namespace std;

class BigDecimalInt{
private:
    string number;
    char signNumber{};
    bool checkValidInput(string input);

public:
    bool operator < (const BigDecimalInt& anotherDec);
    bool operator > (const BigDecimalInt& anotherDec);
    bool operator == (BigDecimalInt anotherDec);
    BigDecimalInt& operator = (BigDecimalInt anotherDec);
    BigDecimalInt operator + (BigDecimalInt number2);
    BigDecimalInt operator - (BigDecimalInt anotherDec);
    friend ostream &operator << (ostream &out, BigDecimalInt num);
    virtual int size();
    virtual int sign();

    void setNumber(string num);
    string getNumber(){
        return number;
    }

    BigDecimalInt()= default;
    explicit BigDecimalInt(string num)
    {
        setNumber(num);
    }

};

class BigReal : public BigDecimalInt{
    private:

    string fullNumber;
    string realNumber;
    string floatPointNumber;
    char signNumber {};

    public:
        BigReal () = default;
        explicit BigReal (const string &realNumber);
        BigReal (BigDecimalInt bigInteger);
        BigReal (const BigReal &other);
        BigReal (BigReal &&other) noexcept ;
        BigReal& operator= (const BigReal &other);
        BigReal& operator= (BigReal &&other) noexcept ;
        BigReal operator+ (BigReal const &other);
        BigReal operator- (BigReal const &other);
        bool operator< (BigReal anotherReal);
        bool operator> (BigReal anotherReal);
        bool operator== (const BigReal &anotherReal);
        int size() override;
        int sign() override;
        friend ostream& operator << (ostream& out, const BigReal& num);
        friend istream& operator >> (istream& out, BigReal& num);

        friend void realAddition(string &real, string &fraction, string otherReal, string otherFraction);
        friend void realSubtraction(string &real, string &fraction, string otherReal, string otherFraction);
        static bool checkNumberValid(const string &input);
        void setRealNumber(string input);
        string getRealNumber(){
            return fullNumber;
        }
};
#endif
