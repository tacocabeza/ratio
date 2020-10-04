#include "Ratio.h"
#include <cassert>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <fstream>
using std::cout;
using std::cerr;
using std::istringstream;
using std::runtime_error;
using std::ifstream;
int main() {
    Ratio half(-100,-200), third(half);
    const Ratio five(10/2);
    third.numerator(24);            // now 24/2 ⇒ 12/1
    third.denominator(72);          // now 12/72 ⇒ 1/6
    third *= 2;                     // now 2/6 ⇒ 1/3
    assert(0.3333333333 < third && third < 0.3333333334);
    assert(0.3333333333 < third.ratio() && third.ratio() < 0.3333333334);
    assert(half == half);
    assert(0.5 == half);
    assert(five == 5);
    assert(6 != five);
    assert(half > third);
    assert(half >= third);
    assert(third < half);
    assert(third <= half);
    assert(third != half);
    assert(third + half == Ratio(50,60));
    assert(1/(third * half) == 6.0);
    Ratio a(1), b(2), c(3), d(4);
    a = b = c = d = half;
    assert(a == 0.5);
    assert(0+1/b+0 == 2);
    b /= d;
    assert(b == 1);
    assert(d == half);

    istringstream in(" 1/7\n \n123 / 456 4q5");    // 123/456 ⇒ 41/152
    if (!(in >> a >> b)){
        cerr << "read failure\n";
	}	
    assert(a.numerator() == 1);
    assert(a.denominator() == 7);
    assert(b.denominator() == 152);
    assert(b.numerator() == 41);
	
    if (in >> c){
        cerr << "unexpected success\n";
	}
	

    assert(1 == 2*c);           // must contain old value

    bool caught = false;
    try {
        Ratio bad(1, 0);
    }
    catch (const runtime_error &err) {
        caught = true;
    }
    assert(caught);

    cout << "Hooray!\n";


	// my testing begins
	

	const Ratio oof(500,20);

	Ratio sloth = oof;
	
	cout << oof << " " << sloth << "\n";

	sloth += 2.3;

	assert(sloth >= oof);
	assert(sloth != 10.0230302);
	cout << oof << " " << sloth << "\n";

	Ratio fail(1/2);
	Ratio fail1 = fail - .5;

	ifstream in2("data");

	if(!in2){
		cerr << "Can't open data\n";
		return 1;
	}
	
	while( in2 >> sloth)
		cout << "»»» " << sloth << '\n';
	
	try {
		sloth.denominator(0);
		cout << "should not get here.\n";
	}
	catch (const runtime_error &err)
	{	
		cout << "error detected: " << err.what() << "\n";
	}

	
	short twelve = 12;
	int four = 4;
	long bignum = 1000;
	
	float pi = 3.14;
	long double answer = sloth.ratio();

	assert(answer == sloth);
	assert(sloth  != four);
	assert(sloth*twelve == answer * 12);
	assert(answer * twelve == sloth * twelve);
	assert(answer/four == sloth/four);
	assert(sloth /four == answer/four);
	assert(answer - bignum == sloth - bignum);
	assert(bignum - answer == bignum-sloth);
		
	assert(answer + bignum == sloth + bignum);
	assert(bignum + answer == bignum+sloth);

	assert(half - Ratio(1,2) == 0);
	
	assert(half < 1.55555555555555555);
	assert(1.5555555555 > half);
	assert(half != 1.55555555555555);

	assert(.5 <= half);
	assert(half >= .01);

	assert(pi > half);
	assert(half > .23);
    return 0;
}
