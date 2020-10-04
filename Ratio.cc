#include "Ratio.h"
#include <typeinfo>
using namespace std;

// ctor

Ratio::Ratio(long numerator, long denominator) : numerator_(numerator), denominator_(denominator)
{
	if(denominator == 0L)
	{	
		throw std::runtime_error("Denominator Cannot be Zero, you madman!");
	}


	reduce();

	negNormalize();
	
}

Ratio :: Ratio(int numerator, int denominator) : /* Ratio(static_cast<long>(numerator), static_cast<long>(denominator))*/ numerator_(numerator), denominator_(denominator) {
	        if(denominator == 0)
        {
                throw std::runtime_error("Denominator Cannot be Zero, you madman!");
        }


        reduce();

        negNormalize();
}
void Ratio :: negNormalize()
{

	if(denominator_ < 0 && numerator_ > 0)
	{
		denominator_ = -denominator_;
		numerator_ = -numerator_;
	}

	else if(denominator_ < 0 && numerator_ < 0)
	{
		numerator_ = -numerator_;
		denominator_ = -denominator_;
	}

}
void Ratio :: reduce()
{
	long greatestDiv = gcd();
numerator_ /= greatestDiv; denominator_ /= greatestDiv;
}


// copy constructor 

Ratio::Ratio(const Ratio &rhs): numerator_(rhs.numerator_), denominator_(rhs.denominator_){


}
// Assignment operator
Ratio& Ratio :: operator=(const Ratio &rhs)
{
	numerator_ = rhs.numerator_;
	denominator_ = rhs.denominator_;
	return *this;
}
// dtor
Ratio :: ~Ratio(){}


// getters for numerator and denominator
long Ratio :: numerator() const 
{
	return numerator_;
}

void Ratio :: numerator(long numerator)
{
	numerator_ = numerator;

	*this = Ratio(numerator_,denominator_);	
}


void Ratio :: denominator(long denominator)
{
	if(denominator == 0)
	{
		throw std :: runtime_error("Denominator Cannot Be Zero, you madman!");
	}
	denominator_ = denominator;

	*this = Ratio(numerator_, denominator_);
}
long Ratio :: denominator() const
{ return denominator_;
}

long double Ratio :: ratio() const
{ 
 	
	return static_cast<double>(numerator_)/static_cast<double>(denominator_); // casting? 
}

ostream &operator<<(ostream &stream, const Ratio &ratio)
{
	return stream << ratio.numerator() << "/" << ratio.denominator();
}

istream& operator>>(istream &is, Ratio &ratio)
{
	long num = 0, den = 1;

	char slash = ' ';

	if(!(is >> std::skipws >>  num >> std::skipws >> slash >> std::skipws >> den))
	{
		is.setstate(std::ios_base::failbit);
	}

	if(slash != '/')
	{
				
		is.setstate(std::ios_base::failbit);
		return is;
	}
	
	ratio = Ratio(num,den);
	return is;
}
//courtesey of wikipedia : https://en.wikipedia.org/wiki/Euclidean_algorithm	
long Ratio :: gcd(long a, long b) const
{

	while( b != 0)
	{
		long temp = b;
		b = a % b;

		a = temp;
	}

	return a;

}
//courtesey of wikipedia : https://en.wikipedia.org/wiki/Euclidean_algorithm
long  Ratio :: gcd()const
{
	long num = numerator();

	long den = denominator();

	while(den != 0)
	{


		long temp = den;

		den = num % den;

		num = temp;


	}


	return num;

}

Ratio Ratio :: operator+(const Ratio &rhs) const
{
	//Ratio retval(0);

	// adding with like denoms

	if(this->denominator_ == rhs.denominator_)
	{

		//cout << this->numerator_ << "/" << this->denominator_ << " " << rhs.numerator_ << "/" << rhs.denominator_ << "\n";
	//	retval.numerator_ = numerator_ + rhs.numerator_;

	//	retval.denominator_ = rhs.denominator_;
		return Ratio((numerator_ + rhs.numerator()), rhs.denominator());
	}



	return Ratio((numerator_ * rhs.denominator()) + (rhs.numerator() * denominator_), rhs.denominator() * denominator_);

}

// 3/4 + 4/4
// 3/4 - 4/4 = -3/4 + 4/4

Ratio Ratio :: operator-(const Ratio &rhs) const
{
	if(this->denominator_ == rhs.denominator_)
	{

		//cout << this->numerator_ << "/" << this->denominator_ << " " << rhs.numerator_ << "/" << rhs.denominator_ << "\n";
	//	retval.numerator_ = numerator_ + rhs.numerator_;

	//	retval.denominator_ = rhs.denominator_;
		return Ratio((numerator_ - rhs.numerator()), rhs.denominator());
	}



	return Ratio((numerator_ * rhs.denominator()) - (rhs.numerator() * denominator_), rhs.denominator() * denominator_);
}

Ratio Ratio :: operator*(const Ratio &rhs) const
{
	return Ratio(numerator_ * rhs.numerator(), denominator_ * rhs.denominator());
}

Ratio Ratio :: operator/(const Ratio &rhs) const
{
	return Ratio(numerator_ * rhs.denominator(), denominator_ *rhs.numerator());
}

Ratio &Ratio :: operator+=(const Ratio &rhs)
{
	numerator_ *= rhs.denominator();
	numerator_ += denominator_ * rhs.numerator();
	denominator_ *= rhs.denominator();
	reduce();
	if(this->denominator_ == 0)
	{
		throw runtime_error("You madman, + resulted in a denominator of 0!");
	}
	negNormalize();	
	return *this;
}

Ratio &Ratio :: operator-=(const Ratio &rhs)
{
	numerator_ *= rhs.denominator();
	numerator_ -= denominator_ * rhs.numerator();
	denominator_ *= rhs.denominator();
	reduce();
	negNormalize();
	if(this->denominator_ == 0)
	{
		throw runtime_error("You madman, - resulted in a denominator of 0!");
	}
	return *this;
}	

Ratio &Ratio :: operator*=(const Ratio &rhs)
{
	numerator_ *= rhs.numerator();
	denominator_ *= rhs.denominator();	
	
	if(this->denominator_ == 0)
	{
		throw runtime_error("You madman, multiplication resulted in a denominator of 0!");
	}
	reduce();
	negNormalize();
	return *this;
}

Ratio &Ratio :: operator/=(const Ratio &rhs)
{
	numerator_ *= rhs.denominator();
	denominator_ *= rhs.numerator();
	
	if(this->denominator_ == 0)
	{
		throw runtime_error("You madman, division resulted in a denominator of 0!");
	}
	reduce();
	negNormalize();

	return *this;
} 
bool Ratio :: operator==(const Ratio &rhs) const
{
	return numerator_ == rhs.numerator() && denominator_ == rhs.denominator();
}

bool Ratio :: operator!=(const Ratio &rhs) const
{
	return !(*this == rhs);
}

bool Ratio :: operator<(const Ratio &rhs) const
{
	// could of just compared .ratio() values 😟 
	return this->ratio() < rhs.ratio();
}

bool Ratio :: operator<=(const Ratio &rhs) const
{
	return *this < rhs || *this == rhs;
}

bool Ratio :: operator>(const Ratio &rhs) const
{
	return !(*this < rhs);

}

bool Ratio :: operator>=(const Ratio &rhs) const
{
	return *this > rhs || *this == rhs;
}

Ratio Ratio :: multiply(const Ratio &a) const
{
	return *this * a;
}

Ratio Ratio :: add(const Ratio &a,  const Ratio &b, const Ratio &c, const Ratio &d, const Ratio &e, const Ratio &f, const Ratio &g, const Ratio &h) const
{
	return *this+a+b+c+e+d+f+g+h;
}

Ratio Ratio :: subtract(const Ratio &a) const
{
	return *this - a;
}

Ratio Ratio :: divide(const Ratio &div) const
{
	return *this / div;
}

int Ratio :: compare(const Ratio &rhs) const
{
	int retval = 0;
	if(*this < rhs)
	{
		retval = -1;
	}

	if(*this > rhs)
	{
		retval = 1;
	}

	if(*this == rhs)
	{
		retval = 0;
	}

	return retval;
}

int Ratio :: compare(const long double &comp) const
{
	int retval = 0;

	if(this->ratio() < comp)
	{
		retval = -1;

	}

	if(this->ratio() > comp) { retval = 1;

	}

	if(this->ratio() == comp)
	{
		retval = 0;
	}

	return retval;

}

Ratio operator+(const int lhs,const  Ratio &rhs)
{
	Ratio a(lhs);
	return a + rhs;
}

Ratio operator+(const Ratio &lhs, const int rhs)
{
	Ratio a(rhs);
	return lhs + a;
}


Ratio operator-(const int lhs, const Ratio &rhs)
{
	Ratio a(lhs);
	return a - rhs;
}

Ratio operator-(const Ratio &lhs, const int rhs)
{
	Ratio a(rhs);
	return lhs - a;
}

Ratio operator*(const int lhs, const Ratio &rhs)
{
	Ratio a(lhs);
	return a * rhs;
}

Ratio operator*(const Ratio &lhs, const int rhs)
{
	Ratio a(rhs);
	return lhs * a;
}

Ratio operator/(const int lhs, const Ratio &rhs)
{
	Ratio a(lhs);
	return a/rhs;
}

Ratio operator/(const Ratio &lhs, const int rhs)
{
	Ratio a(rhs);
	return lhs/a;
}

Ratio &Ratio :: operator+=(const int rhs)
{
	Ratio a(rhs);
	return *this += a;
}

Ratio &Ratio :: operator-=(const int rhs)
{
	Ratio a(rhs);
	return *this -= a;
}

Ratio &Ratio :: operator*=(const int rhs)
{
	Ratio a(rhs);
	return *this *= a;
}

Ratio &Ratio :: operator/=(const int rhs)
{
	Ratio a(rhs);
	return *this /= a;
}


bool operator==(const double lhs, const Ratio &rhs) 
{
	return lhs==rhs.ratio();
}

bool operator==(const Ratio &lhs, const double rhs) 
{
	return lhs.ratio()==rhs;
}
 

bool operator!=(const double lhs, const Ratio &rhs) 
{	
	return !(lhs==rhs);
}

bool operator!=(const Ratio &lhs, const double rhs) 
{
	return !(lhs == rhs);
}

bool operator<(const double lhs, const Ratio &rhs) {
	return lhs < rhs.ratio(); 
}
bool operator<(const Ratio &lhs, const double rhs)
{
	return lhs.ratio() < rhs;
}
bool operator>(const double lhs, const Ratio &rhs)
{
	return !(lhs < rhs);
}
bool operator>(const Ratio &lhs, const double rhs)
{
	return !(lhs < rhs);
}
bool operator <=(const double lhs, const Ratio &rhs)
{	
	return lhs < rhs.ratio() || lhs == rhs.ratio();
}

bool operator <=(const Ratio &lhs, const double rhs)
{	
	return lhs.ratio() < rhs || lhs.ratio() == rhs;
}

bool operator >=(const double lhs, const Ratio &rhs)
{	
	return lhs > rhs.ratio() || lhs == rhs.ratio();
}

bool operator >=(const Ratio &lhs, const double rhs)
{	
	return lhs.ratio() > rhs || lhs.ratio() == rhs;
}
