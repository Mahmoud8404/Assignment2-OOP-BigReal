#include <utility>

#include "RealNumberClass.h"

//BigDecimal Int Functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////
// regex function that checks the validation of the input.
bool BigDecimalInt :: checkValidInput(string input)
{
    regex validInput("[-+]?[0-9]+");
    return regex_match(input, validInput);
}

// constructor that takes a string as an input.
void BigDecimalInt :: setNumber(string num)
{
    bool validNumber = checkValidInput(num);
    if(validNumber)
    {
        number = num;
        if(number[0] == '+')
        {
            number.erase(0,1);
            signNumber = '+';
        }
        else if (number[0] == '-')
        {
            number.erase(0,1);
            signNumber = '-';
        }
        else
        {
            signNumber = '+';
        }
    }
    else
    {
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// operator < overloading function.
bool BigDecimalInt :: operator < (const BigDecimalInt& anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 < comp2;
    }
    else
    {
        return comp1 > comp2;
    }
}

// operator > overloading function.
bool BigDecimalInt :: operator > (const BigDecimalInt &anotherDec)
{
    string comp1 = "", comp2 = "";
    long long len1 = number.length(), len2 = anotherDec.number.length();

    while (len1 < len2){
        comp1 += '0';
        len1++;
    }
    while (len2 < len1){
        comp2 += '0';
        len2++;
    }
    comp1 += number;
    comp2 += anotherDec.number;

    if(signNumber == '-' && anotherDec.signNumber == '+')
    {
        return false;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '-')
    {
        return true;
    }
    else if(signNumber == '+' && anotherDec.signNumber == '+')
    {
        return comp1 > comp2;
    }
    else
    {
        return comp1 < comp2;
    }
}

// operator == overloading function.
bool BigDecimalInt :: operator == (const BigDecimalInt anotherDec)
{
    if (signNumber == anotherDec.signNumber && number == anotherDec.number)
    {
        return true;

    }
    else
    {
        return false;
    }
}

// operator = overloading function.
BigDecimalInt& BigDecimalInt :: operator = (BigDecimalInt anotherDec)
{
    signNumber = anotherDec.signNumber;
    number = anotherDec.number;
    return *this;
}

//addition implementation.
string addition(string num1,string num2)
{
    auto it1 = num1.rbegin();
    auto it2 = num2.rbegin();
    string res = "";
    int carry = 0;
    while (it1 != num1.rend())
    {
        int twoDigitsSum;
        carry = 0;
        twoDigitsSum = ((*it1 - '0') + (*it2 - '0'));
        if (twoDigitsSum >= 10)
        {
            carry = 1;
        }
        res = char((twoDigitsSum % 10) + '0') + res;
        *(it1 + 1) = char(((*(it1 + 1) - '0') + carry) + '0');
        it1++;
        it2++;
    }
    if (carry)
    {
        res += char((carry) + '0');
    }
    return res;
}

//subtraction implementation
string subtraction(string num1,string num2){
    deque<long long>d;
    string res;

    for (long long i = num1.length() - 1; i >= 0; i--)
    {
        if (num1[i] < num2[i])
        {
            num1[i] = char (((num1[i] - '0') + 10) + '0');
            num1[i - 1] = char (((num1[i - 1] - '0') - 1) + '0');
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
        else
        {
            d.push_front((num1[i] - '0') - (num2[i] - '0'));
        }
    }

    for (auto i : d)
    {
        res += to_string(i);
    }
    return res;
}

// // operator + overloading function.
BigDecimalInt BigDecimalInt :: operator + (BigDecimalInt number2)
{
    BigDecimalInt result;
    char signNumber1 = signNumber, signNumber2 = number2.signNumber;
    string num1 = number, num2 = number2.number;
    BigDecimalInt number1 = *this;

    while (num1.length() < num2.length()){
        num1 = '0' + num1;
    }
    while (num2.length() < num1.length()){
        num2 = '0' + num2;
    }

    if (signNumber1 == signNumber2){
        result.signNumber = signNumber1;
        result.number = addition(num1,num2);

    }else{

        if(number1.signNumber == '-')
        {
            number1.signNumber = '+';
            result = (number2 - number1);
        }
        else{
            number2.signNumber = '+';
            result = (number1 - number2);
        }
    }
    return result;
}

// operator - overloading function.
BigDecimalInt BigDecimalInt :: operator - (BigDecimalInt anotherDec)
{
    BigDecimalInt obj;
    deque<long long> d;
    string strmin = "", res = "";
    string num1 = number, num2 = anotherDec.number;
    char sign1 = signNumber, sign2 = anotherDec.signNumber;

    if (number.length() > anotherDec.number.length())
    {
        for (long long i = 0; i < number.length() - anotherDec.number.length(); i++)
        {
            strmin += '0';
        }
        strmin += anotherDec.number;
        num2 = strmin;
    }
    else if (number.length() < anotherDec.number.length())
    {
        for (long long i = 0; i < anotherDec.number.length() - number.length(); i++)
        {
            strmin += '0';
        }
        strmin += number;
        num1 = strmin;
    }

    bool ok = false, is_determined = false;
    if (num1 < num2)
    {
        swap(num1, num2);
        swap(sign1, sign2);
        ok = true;
    }

    if (sign1 == sign2 )
    {
        res = subtraction(num1,num2);

        if(sign1=='-') ok = !ok;
    }
    else
    {
        res = addition(num1,num2);
        if(signNumber == '-')
        {
            obj.signNumber = '-';
            is_determined = true;
        }
        else
        {
            obj.signNumber = '+';
            is_determined = true;
        }

    }

    bool right = false;
    for (long long i = 0; i < res.length(); i++)
    {
        if (res[i] != '-' && res[i] != '0')
        {
            right = true;
        }
        if (!right && res[i] == '0')
        {
            res.erase(i, 1);
            i--;
        }
    }

    if(res.empty()) res = "0";
    if (!is_determined && (ok))
    {
        obj.signNumber = '-';
    }
    else if(!is_determined)
    {
        obj.signNumber = '+';
    }

    obj.number = res;
    return obj;
}

// function to return the size of number.
int BigDecimalInt :: size()
{
    return number.size();
}

// function returns the sign.
int BigDecimalInt :: sign()
{
    if (signNumber == '+')
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// operator << overloading function.
ostream &operator << (ostream &out, BigDecimalInt num)
{
    if(num.signNumber == '+')
    {
        out << num.number ;
    }
    else
    {
        if(num.number == "0")
        {
            out << num.number ;
        }
        else
        {
            out << num.signNumber << num.number ;
        }
    }
    return out;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//----------------------------------------BigReal Functions--------------------------------------------------
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////


// Function sets arguments from string
void BigReal :: setRealNumber(string input) {

    // Erases sign and
    fullNumber = std::move(input);
    if (fullNumber[0] == '+') {
        fullNumber.erase(0, 1);
        signNumber = '+';
    } else if (fullNumber[0] == '-') {
        fullNumber.erase(0, 1);
        signNumber = '-';
    } else if (fullNumber[0] == '.') {
        fullNumber.insert(0, "0");
        signNumber = '+';
    }else {
        signNumber = '+';
    }

    //
    string intNumber, floatNumber;
    int index = 0;
    while (fullNumber[index] != '.' && index < fullNumber.size()){
        intNumber += fullNumber[index];
        index++;
    }

    if (fullNumber[index] == '.'){
        index++;
        while(index < fullNumber.size()) {
            floatNumber += fullNumber[index];
            index++;
        }
    }else if (floatNumber.empty()){
        floatNumber += "0";
        goto exit;
    }

    exit:
    realNumber = intNumber;
    floatPointNumber = floatNumber;
}

// regex function that checks the validation of the input.
bool BigReal :: checkNumberValid(const string& input) {
    regex validInput("[-+]?([.]?[0-9]+||[0-9]+[.]{1}[0-9]+)");
    return regex_match(input, validInput);
}

// Constructor sets real number from string
BigReal :: BigReal(const string &input) {
    if(checkNumberValid(input)){
        setRealNumber(input);
    }
    else{
        cout << "Invalid" << "\n";
        exit(1);
    }
}

// Constructor sets real number from different class object
BigReal :: BigReal(BigDecimalInt bigInteger) {
    fullNumber = getNumber();
    signNumber = bigInteger.sign() ? '+' : '-';
}

// Constructor makes a copy of other objects of the same class
BigReal :: BigReal(const BigReal &other) {

    // Copying
    fullNumber = other.fullNumber;
    realNumber = other.realNumber;
    signNumber = other.signNumber;
    floatPointNumber = other.floatPointNumber;

}

// Constructor moves rvalues from other objects of the same class
BigReal :: BigReal(BigReal &&other) noexcept {

    // Moving rvalues to *this object from other object
    this->fullNumber = other.fullNumber;
    this->floatPointNumber = other.floatPointNumber;
    this->realNumber = other.realNumber;
    this->signNumber = other.signNumber;

    // Clearing rvalues from original object
    other.fullNumber.clear();
    other.floatPointNumber.clear();
    other.realNumber.clear();
    other.signNumber = '\0';

}

// Assignment = Operator Overloading
BigReal& BigReal :: operator= (const BigReal& other) {

    // Assigning
    fullNumber = other.fullNumber;
    realNumber = other.realNumber;
    signNumber = other.signNumber;
    floatPointNumber = other.floatPointNumber;
    return *this;
}

// Move = Operator Overloading
BigReal& BigReal :: operator=(BigReal &&other) noexcept {

    // Moving rvalues to *this object from original object
    this->fullNumber = other.fullNumber;
    this->realNumber = other.realNumber;
    this->signNumber = other.signNumber;
    this->floatPointNumber = other.floatPointNumber;

    // Clearing rvalues from original object
    other.fullNumber.clear();
    other.realNumber.clear();
    other.floatPointNumber.clear();
    other.signNumber = '\0';
    return *this;
}

// Function returns size of number
int BigReal :: size() {
    return fullNumber.length();
}

// Function returns sign of number
int BigReal :: sign() {
    return signNumber == '+';
}

// Operator < Overloading
bool BigReal :: operator< (BigReal anotherReal) {
    unsigned long long len1 = fullNumber.length(), len2 = anotherReal.fullNumber.length();

    if (signNumber == '-' && anotherReal.signNumber == '+') {
        return true;
    }
    else if (signNumber == '+' && anotherReal.signNumber == '-') {
        return false;
    }
    else if (signNumber == '+' && anotherReal.signNumber == '+') {
        if (len1 < len2) {
            return true;
        }
        else if (len1 == len2) {
            int index = 0;
            while (index < len1) {
                if ((fullNumber[index] - '0') == (anotherReal.fullNumber[index] - '0')) {
                    index++;
                }
                else if ((fullNumber[index] - '0') < (anotherReal.fullNumber[index] - '0')) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    } else {
        if (len1 > len2) {
            return true;
        }
        else if (len1 == len2) {
            int index = 0;
            while (index < len1) {
                if ((fullNumber[index] - '0') == (anotherReal.fullNumber[index] - '0')) {
                    index++;
                }
                else if ((fullNumber[index] - '0') < (anotherReal.fullNumber[index] - '0')) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
        else {
        return false;
        }
    }
    exit(1);
}

// Operator == Overloading
bool BigReal::operator== (const BigReal &anotherReal) {
    return (signNumber == anotherReal.signNumber && fullNumber == anotherReal.fullNumber);
}

// Operator > Overloading
bool BigReal :: operator> (BigReal anotherReal) {
    unsigned long long len1 = fullNumber.length(), len2 = anotherReal.fullNumber.length();

    if (signNumber == '-' && anotherReal.signNumber == '+') {
        return false;
    }
    else if (signNumber == '+' && anotherReal.signNumber == '-') {
        return true;
    }
    else if (signNumber == '+' && anotherReal.signNumber == '+') {
        if (len1 > len2) {
            return true;
        }
        else if (len1 == len2) {
            int index = 0;
            while (index <= len1) {
                if ((fullNumber[index] - '0') == (anotherReal.fullNumber[index] - '0')) {
                    index++;
                }
                else if ((fullNumber[index] - '0') > (anotherReal.fullNumber[index] - '0')) {
                    return true;
                }
                else {
                    return false;
                }
            }
        }
        else {
            return false;
        }
    }
    else {
        if (len1 < len2) {
            return true;
        }
        else if (len1 == len2) {
            int index = 0;
            while (index <= len1) {
                if ((fullNumber[index] - '0') == (anotherReal.fullNumber[index] - '0')) {
                    index++;
                }
                else if ((fullNumber[index] - '0') > (anotherReal.fullNumber[index] - '0')) {
                    return false;
                }
                else {
                    return true;
                }
            }
        }
        else {
            return false;
        }
    }
    exit(1);
}

// Operator << Overloading
ostream& operator<<(ostream& out, const BigReal& num) {
    if(num.signNumber == '+' || num.fullNumber == "0"){
        out << num.fullNumber ;
    }
    else{
        out << num.signNumber << num.fullNumber ;
    }
    return out;
}

// Operator >> Overloading
istream& operator>>(istream& out, BigReal& num) {
    string input;
    out >> input;
    if(num.checkNumberValid(input)){
        num.setRealNumber(input);
    }
    else{
        cout << "Invalid" << "\n";
        exit(1);
    }
}

//
void realAddition(string &real, string &fraction, string otherReal, string otherFraction){
    int sum;
    int carry;

    ////
    auto fractionIndex = fraction.rbegin();
    auto otherFractionIndex = otherFraction.rbegin();

    while (fractionIndex != fraction.rend()){
        sum = ((*fractionIndex - '0') + (*otherFractionIndex - '0'));

        if (sum >= 10){
            carry = 1;
        }
        else{
            carry = 0;
        }

        *fractionIndex = char((sum % 10) + '0');
        *(fractionIndex + 1) = char(((*(fractionIndex + 1) - '0') + carry ) + '0');

        fractionIndex++;
        otherFractionIndex++;
    }

    //
    if (carry){
        real.back() = char(((real.back() - '0') + carry) + '0');
    }

    //
     while (fraction.back() == 0){
         fraction.pop_back();
     }

     ////
    auto realIndex = real.rbegin();
    auto otherRealIndex = otherReal.rbegin();

    while (realIndex != real.rend()){
        sum = ((*realIndex - '0') + (*otherRealIndex - '0'));

        if (sum >= 10){
            carry = 1;
            sum %= 10;
        }
        else{
            carry = 0;
        }

        *realIndex = char(sum + '0');
        *(realIndex + 1) = char(((*(realIndex + 1) - '0') + carry ) + '0');

        realIndex++;
        otherRealIndex++;
    }

    //
    if(carry){
        real.insert(0, "1");
    }
}

//
void realSubtraction(string& real, string& fraction, string otherReal, string otherFraction) {
    int sub;
    int debt;

    auto fractionIndex = fraction.rbegin();
    auto otherFractionIndex = otherFraction.rbegin();

    while (fractionIndex != fraction.rend()){
        sub = ((*fractionIndex - '0') - (*otherFractionIndex - '0'));

        if (sub < 0){
            debt = 1;
            sub += 10;
        }
        else{
            debt = 0;
        }


        *fractionIndex = char(sub + '0');
        if ((fractionIndex+1) != fraction.rend()) {
            *(fractionIndex + 1) = char(((*(fractionIndex + 1) - '0') - debt) + '0');
        }else{
            if (debt){
                real.back() = char(((real.back() - '0') - debt) + '0');
            }
        }

        fractionIndex++;
        otherFractionIndex++;
    }

    //
    while (fraction.back() == '0' && fraction.length() != 1){
        fraction.pop_back();
    }

    ////
    auto realIndex = real.rbegin();
    auto otherRealIndex = otherReal.rbegin();

    while (realIndex != real.rend()){
        sub = ((*realIndex - '0') - (*otherRealIndex - '0'));

        if (sub < 0){
            debt = 1;
            sub += 10;
        }
        else{
            debt = 0;
        }

        *realIndex = char(sub + '0');
        *(realIndex + 1) = char(((*(realIndex + 1) - '0') - debt) + '0');

        realIndex++;
        otherRealIndex++;
    }


    //
    while (real.front() == '0' && real.length() != 1){
        real.erase(0,1);
    }

    //
    if (debt){
        real.front() = char(((real.front() - '0') - debt) + '0');
    }

    //
    if((real.front() - '0') < 0){
        real.front() = char(((real.front() - '0') + 10) + '0');
    }

}


// Operator + Overloading
BigReal BigReal::operator+(BigReal const &other) {

    BigReal temp = other;
    // Matching the lengths of numbers
    if (realNumber.size() > temp.realNumber.size()){
        while (realNumber.size() != temp.realNumber.size()){
            temp.realNumber.insert(0, "0");
        }
    }
    else if (realNumber.size() < temp.realNumber.size()){
        while (realNumber.size() != temp.realNumber.size()){
            realNumber.insert(0, "0");
        }
    }

    if (floatPointNumber.length() > temp.floatPointNumber.length()){
        while (floatPointNumber.length() != temp.floatPointNumber.length()){
            temp.floatPointNumber.push_back('0');
        }
    }
    else if (floatPointNumber.length() < temp.floatPointNumber.length()){
        while (floatPointNumber.length() != temp.floatPointNumber.length()){
            floatPointNumber.push_back('0');
        }
    }

    //
    if (signNumber == temp.signNumber) {
        realAddition(realNumber, floatPointNumber, temp.realNumber, temp.floatPointNumber);
    }
    else if (realNumber > temp.realNumber) {
        realSubtraction(realNumber, floatPointNumber, temp.realNumber, temp.floatPointNumber);
    }
    else{
        realSubtraction(temp.realNumber, temp.floatPointNumber, realNumber, floatPointNumber);
        swap(temp.realNumber, realNumber);
        swap(temp.floatPointNumber, floatPointNumber);
        if (signNumber == '+'){
            signNumber = '-';
        }else {
            signNumber = '+';
        }
    }
    fullNumber = realNumber + '.' +floatPointNumber;
    temp = *this;
    return temp;
}

BigReal BigReal::operator-(BigReal const &other) {

    BigReal temp = other;

    // Matching the lengths of numbers
    if (realNumber.length() > temp.realNumber.length()){
        while (realNumber.length() != temp.realNumber.length()){
            temp.realNumber.insert(0, "0");
        }
    }
    else if (realNumber.length() < temp.realNumber.length()){
        while (realNumber.length() != temp.realNumber.length()){
            realNumber.insert(0, "0");
        }
    }

    if (floatPointNumber.length() > temp.floatPointNumber.length()){
        while (floatPointNumber.length() != temp.floatPointNumber.length()){
            temp.floatPointNumber.push_back('0');
        }
    }
    else if (floatPointNumber.length() < temp.floatPointNumber.length()){
        while (floatPointNumber.length() != temp.floatPointNumber.length()){
            floatPointNumber.push_back('0');
        }
    }


    //
    if (signNumber != temp.signNumber) {
        realAddition(realNumber, floatPointNumber, temp.realNumber, temp.floatPointNumber);
    }
    else if (realNumber > temp.realNumber) {
        realSubtraction(realNumber, floatPointNumber, temp.realNumber, temp.floatPointNumber);
    }
    else{
        realSubtraction(temp.realNumber, temp.floatPointNumber, realNumber, floatPointNumber);
        swap(realNumber, temp.realNumber);
        swap(floatPointNumber, temp.floatPointNumber);
        if (signNumber == '+'){
            signNumber = '-';
        }else {
            signNumber = '+';
        }
    }

    fullNumber = realNumber + '.' + floatPointNumber;
    temp = *this;
    return temp;
}
