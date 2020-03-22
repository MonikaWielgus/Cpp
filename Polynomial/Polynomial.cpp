//Monika Wielgus
#include "Polynomial.h"

std::string intToStr(int n){

    std::string temp;
    std::string result;
    if(n<0){
		result = "-";
		n=-n;
    }
    do{
        temp += n%10+48;
        n -= n%10;
    }while(n/=10);

	for(int i=temp.size()-1; i >= 0; i--){
		result += temp[i];
	}
    return result;
}
Polynomial::Polynomial(){

    degree=0;
    coef=new Z2[1];
    coef[0]=0;
}
Polynomial::Polynomial(unsigned int a, Z2 *array){

    int z;
    for(z=a; z>=0; z--){ //zeros at the end of the array
        if(array[z]==1) break;
    }
    if(z==-1){ //only zeros
        this->degree=0;
        this->coef=new Z2[1]();
    }
    else{
        this->degree=z;
        this->coef=new Z2[z+1];
        for(int i=0; i<=z; i++){
            this->coef[i]=array[i];
        }
    }
}


short int Polynomial::operator[](unsigned int index) const{

    if(index>degree){
        std::cout << "Wrong index \n";
        return *coef;
    }
    else{
        return *(coef+index);
    }
}

std::string Polynomial::toString(std::string xVar){

	std::string result;
	if(degree==0&&coef[0]==0)
        result="0";
	else if(degree==0&&coef[0]==1)
        result="1";
	else{
		if(degree>0&&coef[0]==1)
            result+="1+";
		for(unsigned int i=1; i<degree; i++){
			if(coef[i]!=0){
				result+=xVar;
				result+="^";
				result+=intToStr(i);
				result+="+";
			}
		}
		result+=xVar;
		result+="^";
		result+=intToStr(degree);
	}
	return result;
}

unsigned int Polynomial::deg() const{
	return degree;
}

Polynomial operator+(const Polynomial &a, const Polynomial &b)
{
    if(a.degree>b.degree){
		Z2 *array=new Z2[a.degree+1];
        for(unsigned int i=0; i<=b.degree; i++){
            array[i]=a.coef[i]+b.coef[i];
        }
        for(unsigned int i=b.degree+1; i<=a.degree; i++){
            array[i]=a.coef[i];
        }
		Polynomial result(a.degree, array);
		delete []array;
		return result;
    }
    else{
		Z2 *array= new Z2[b.degree+1];
        for(unsigned int i=0; i<=a.degree; i++){
            array[i]=a.coef[i]+b.coef[i];
        }
        for(unsigned int i=a.degree+1; i<=b.degree; i++){
            array[i]=b.coef[i];
        }

		Polynomial result(b.degree, array);
		delete []array;
		return result;
	}
}

Polynomial operator*(const Polynomial &a, const Polynomial &b){

    int temp_degree=a.degree+b.degree;
	Z2 *temp_coef=new Z2[temp_degree+1];
    for(unsigned int i=0; i<=a.degree+b.degree; i++){
        temp_coef[i] = 0;
    }
    for(unsigned int i=0; i<=a.degree; i++){
        for(unsigned int j=0; j<=b.degree; j++){
            temp_coef[i+j]+=a.coef[i]*b.coef[j];
        }
    }
    Polynomial result(temp_degree, temp_coef);
	delete []temp_coef;
    return result;
}

std::ostream& operator<<(std::ostream& out, const Polynomial& x){

    out << "{";
    for(unsigned int i=0; i<x.degree; i++){
        out << x.coef[i] << ",";
    }
    out << x.coef[x.degree] << "}";
    return out;
}

std::istream& operator>>(std::istream& in, Polynomial& x){

	char temp[256];
	int s=0;
	in.getline(temp,256);
	int j=0;
	for(int i=0; i<256; i++){
		if(s==0){
			if(temp[i]=='{') s=1; //we've found '('
		}
		if(s==1){ //we look for numbers
			if(temp[i]=='0'||temp[i]=='1'){
				x.coef[j]=temp[i];
				j++;
			}
			if(temp[i]=='}') break;
		}
	}
	if(j>0){
		x.degree=j-1;
	}
	else{
		x.degree=j;
		x.coef[0]=0;
	}
	Polynomial p(x.degree, x.coef);
	x.degree=p.degree;
	for(unsigned int i=0; i<=p.degree; i++){
		x.coef[i]=p.coef[i];
	}
	delete [] p.coef;
	return in;
}
