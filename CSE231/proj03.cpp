#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<cmath>
#include<string>
using std::to_string; using std::string;

string abIndex_friend(long ab_numerator, long ab_denominator, long f_pair) {
	return to_string(ab_numerator) + "/" + to_string(ab_denominator) +
		":" + to_string(f_pair);
}
long divisor_sum(long num)
{
	int sum = 0;
	for (int i = 2; i <= sqrt(num); i++)
	{
		if (num%i == 0)
		{
			if (i == (num / i))
				sum += i;
			else
				sum += (i + num / i);
		}
	}
	return (sum + 1 + num);
}
long gcd(long num1, long num2) {
	long x = 0;
	while (num2 > 0) {
		x = num2;
		num2 = num1 % num2;
		num1 = x;
	}
	return num1;
}
double abIndexNume(double n) {
	return (divisor_sum(n) / gcd(divisor_sum(n), n));
}
double abIndexDenom(double n) {
	return (n / gcd(divisor_sum(n), n));
}
double abIndex(double n) {
	return ((divisor_sum(n) / gcd(divisor_sum(n), n))) / ((n / gcd(divisor_sum(n), n)));
}
bool is_solitary(long x) {
	if (gcd(divisor_sum(x), x) == 1)
		return true;
	return false;
}
string friendly_check(int num, int lim) {
	for (int i = 2; i < lim; i++) {
		if (i == num) {
			i++;
		}
		if (abIndex(i) == abIndex(num)) {
			return abIndex_friend(abIndexNume(num), abIndexDenom(num), i);
		}
	}
	return abIndex_friend(abIndexNume(num), abIndexDenom(num), -1);
}
int main() {
	cout << boolalpha;   // print true or false for bools
	int test;
	cin >> test;
	switch (test) {
	case 1: {   // divisor sum test
		long input;
		cin >> input;
		cout << divisor_sum(input) << endl;
		break;
	} // of case 1

	case 2: {    // gcd test
		long first, second;
		cin >> first >> second;
		cout << gcd(first, second) << endl;
		break;
	} // of case 2

	case 3: {    // is_solitary test
		long input;
		cin >> input;
		cout << is_solitary(input) << endl;
		break;
	} // of case 3

	case 4: {
		// friend check. Make sure the return value is the
		// result of calling abIndex_friend, a string!
		long input, limit;
		cin >> input >> limit;
		cout << friendly_check(input, limit) << endl;
		break;
	} // of case 4
	} // of switch
} // of m
