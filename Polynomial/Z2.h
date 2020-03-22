//Monika Wielgus
#include <iostream>
#include <sstream>
#ifndef Z2_h
#define Z2_h

class Z2{
    public:
    short int number;

    Z2();
    Z2(short int a);
    ~Z2(){}
    operator short int() const;
    Z2& operator +=(const Z2& b);
    Z2& operator *=(const Z2& b);
    Z2& operator/=(const Z2& b);

};

Z2 operator+(const Z2& a, const Z2& b);

Z2 operator*(const Z2& a, const Z2& b);

Z2 operator/(const Z2& a, const Z2& b);

std::ostream& operator<<(std::ostream& out, const Z2& a);
#endif
