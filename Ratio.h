#ifndef RATIO_H
#define RATIO_H

#include <iostream>
#include <algorithm> // std::gcd
#include <ctype.h>
class Ratio
{
	public:


		// constructors, just initialize everything to 1, user can 
		// change it
		explicit Ratio(long numerator, long denominator=1L);
		explicit Ratio(int numerator, int denominator=1);
 
		// Copy Constructor
		Ratio(const Ratio &rhs);
		
		//destructor
		~Ratio();
		Ratio() = delete;
		Ratio(double) = delete;
		Ratio(float) = delete;
		Ratio(long double) = delete;	
			// return numerator as a long
		long numerator() const;
		
		// return denominator as a long
		long denominator() const;
		
		// Assignment operator
		Ratio &operator=(const Ratio &rhs);
		
		// set numerator as a long
		void numerator(long numerator);
		// set the denominator. If the denominator is zero, throw a runtime_error with an appropriate string, and leave the object unchanged
		void denominator(long denominator);
		
		// Return a long double representing the fraction. For example, Ratio(3,4).ratio() would return a long double with the value 0.75. 
		long double ratio() const;
		// Add all the arguments to the current Ratio, resulting in yet another Ratio, returned by value. This method will not modify the current object, or any arguments. It is possible for this method to have one to eight Ratio arguments. 
		Ratio add(const Ratio &a,  const Ratio &b=Ratio(0), const Ratio &c=Ratio(0), const Ratio &d=Ratio(0), const Ratio &e=Ratio(0), const Ratio &f=Ratio(0), const Ratio &g=Ratio(0), const Ratio &h=Ratio(0))  const;
		//Subtract the argument from the current Ratio, resulting in a third Ratio, returned by value. This method will not modify the current object, or the argument.
		Ratio subtract(const Ratio &a) const;
		//Multiply the argument by the current Ratio, resulting in a third Ratio, returned by value. This method will not modify the current object, or the argument. 
		Ratio multiply(const Ratio &mult) const;
		//Divide the current Ratio by the argument, resulting in a third Ratio, returned by value. This method will not modify the current object, or the argument. If this results in a divisor of zero, throw a runtime_error with an appropriate string. 
		Ratio divide(const Ratio &div) const;
		
		//Compare the current object to another Ratio. If the current object is smaller, return an int less than zero. If the current object is larger, return an int greater than zero. If they’re equal, return zero. 
		int compare(const Ratio & cmp)const;
		//Compare the .ratio() of the current object to a long double. If the current object is smaller, return an int less than zero. If the current object is larger, return an int greater than zero. If they’re equal, return zero. 
		int compare(const long double & cmp)const;


		// return the greatest common divisor
		
		long gcd(long a, long b) const;		//courtesey of wikipedia : https://en.wikipedia.org/wiki/Euclidean_algorithm

		long gcd()const; //courtesey of wikipedia : https://en.wikipedia.org/wiki/Euclidean_algorithm

		void reduce();
		void negNormalize();

		Ratio operator+(const Ratio &rhs) const;
		Ratio operator-(const Ratio &rhs) const;
		Ratio operator*(const Ratio &rhs) const;
		Ratio operator/(const Ratio &rhs) const;

		// time to replace those weird clumsy methods! 🤗
		// these operator(+,-,*,/)=(const Ratio &rhs) will help support cases where rhs 
		// are not Ratios! 	
		Ratio &operator+=(const Ratio & rhs);
		Ratio &operator-=(const Ratio & rhs);
		Ratio &operator*=(const Ratio & rhs);
		Ratio &operator/=(const Ratio & rhs);

		// not const because where changing the object 
		Ratio &operator+=(const int rhs);
		Ratio &operator-=(const int rhs);
		Ratio &operator*=(const int rhs);
		Ratio &operator/=(const int rhs);

		bool operator==(const Ratio & rhs) const;
		bool operator!=(const Ratio & rhs) const;
		bool operator<(const Ratio & rhs) const;
		bool operator<=(const Ratio & rhs) const;
		bool operator>(const Ratio & rhs) const;
		bool operator>=(const Ratio & rhs) const;
			
		friend std :: istream &operator>>(std::istream &, Ratio &);
		// private data members
		private:
			
			long numerator_, denominator_;
			//int lnumerator_, ldenominator;
};


// functions
//Write the numerator, a slash, and the denominator to the ostream. Nothing else—no whitespace. 

Ratio operator+(const int lhs,const  Ratio &rhs);
Ratio operator+(const Ratio &lhs, const int rhs);

Ratio operator-(const int lhs,const  Ratio &rhs);
Ratio operator-(const Ratio &lhs, const int rhs);

Ratio operator*(const int lhs,const  Ratio &rhs);
Ratio operator*(const Ratio &lhs, const int rhs);

Ratio operator/(const int lhs,const  Ratio &rhs);
Ratio operator/(const Ratio &lhs, const int rhs);

//bool operator==(const int lhs, const Ratio &rhs); 
//bool operator==(const Ratio &lhs, const int rhs);
bool operator==(const double lhs, const Ratio &rhs); 
bool operator==(const Ratio &lhs, const double rhs);

//bool operator!=(const int lhs, const Ratio &rhs); 
//bool operator!=(const Ratio &lhs, const int rhs);
bool operator!=(const double lhs, const Ratio &rhs); 
bool operator!=(const Ratio &lhs, const double rhs);

//bool operator<(const int lhs, const Ratio &rhs);
//bool operator<(const Ratio &lhs, const int rhs);
bool operator<(const double lhs, const Ratio &rhs);
bool operator<(const Ratio &lhs, const double rhs);

//bool operator<=(const int lhs, const Ratio &rhs);
//bool operator<=(const Ratio &lhs, const int rhs);
bool operator<=(const double lhs, const Ratio &rhs);
bool operator<=(const Ratio &lhs, const double rhs);

//bool operator>(const int lhs, const Ratio &rhs);
//bool operator>(const Ratio &lhs, const int rhs);
bool operator>(const double lhs, const Ratio &rhs);
bool operator>(const Ratio &lhs, const double rhs);

//bool operator>=(const int lhs, const Ratio &rhs);
//bool operator>=(const Ratio &lhs, const int rhs);
bool operator>=(const double lhs, const Ratio &rhs);
bool operator>=(const Ratio &lhs, const double rhs);
std::ostream &operator<<(std::ostream &, const Ratio&);

#endif
