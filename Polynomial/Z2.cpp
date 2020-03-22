//Monika Wielgus
#include <iostream>
#include "Z2.h"

Z2::Z2(){
    number=0;
}

Z2::Z2(short int a){
    if(a>=0)
        number=a%2;
    else{
        a=-a;
        number=a%2;
    }
}

Z2& Z2::operator +=(const Z2& b){
    this->number=(number+b.number)%2;
    return *this;
}

Z2::operator short int() const{
    return number;
}

Z2& Z2::operator *=(const Z2& b){
    this->number=((this->number)*(b.number));
    return *this;
}

Z2& Z2::operator/=(const Z2& b){
    if (b.number==0){
        std::cout << "Dzielenie przez zero\n";
        return *this;
    }
    else{
        this->number=((this->number)/(b.number));
        return *this;
    }
}

Z2 operator+(const Z2& a, const Z2& b){
    Z2 x = Z2();
    x=(((a.number)+(b.number))%2);
    return x;
}

Z2 operator*(const Z2& a, const Z2& b){
    Z2 x = Z2();
    x=(((a.number)*(b.number))%2);
    return x;
}

Z2 operator/(const Z2& a, const Z2& b){
    if(b.number==0){
        std::cout << "Division by zero\n";
        return a;
    }
    else{
        Z2 x = Z2();
        x.number=a.number/b.number;
        return x;
    }
}

std::ostream& operator<<(std::ostream& out, const Z2& a){
    out << a.number;
    return out;
}
