#include<iostream>
using std::cout; using std::cin; using std::endl; using std::boolalpha;
#include<string>
using std::string; using std::to_string;
#include<cmath>
#include <sstream>

const string the_chars = "0123456789abcdef";


string reverse_str(string str) {
	string strBack = ""; //where the backwards string will be stored
	for (int i = str.length() - 1; i >= 0; i--) //sets i to the highest point in the string array and counts down. Will not stop untill after it reaches 0
		strBack += str[i]; //adds the character at position i in string
	return strBack;
}
bool is_palindrome(string str) {
	if (str == reverse_str(str)) //checks to see if the string backwards is the same
		return true;
	return false; //returns false if the if statement conditions were not met
}
string long_to_base(long n, long base) {
	string num;
	int remainder = 0; 
	while (n != 0) { // runs as long as the number doesnt equal 0. n will be the counter in this loop
		remainder = n % base; //following is psuedocode following the instructions of the pdf
		if (base == 16)
			num += the_chars[remainder];
		else if (base == 2)
			num += to_string(remainder);
		n /= base;
	}
	return reverse_str(num); //because the string is calculated backwards
}
bool is_prime(long num) {
	for (int i = 2; i<num; i++)
		if (num % i == 0) //checks if its evenly dvisible. if yes then its not
			return false;
	return true; // was not true for above conditions so is therefore true
}
string is_pal_prime(long num) {
	if (!is_prime(num)) //checks if it isnt prime. if not it returns automatically
		return "not-pal-prime";
	else if (is_palindrome(long_to_base(num, 2))) //order was specified by pdf file
		return "binary-pal-prime";
	else if (is_palindrome(long_to_base(num, 16)))
		return "hex-pal-prime";
	else if (is_palindrome("" + num))
		return "decimal-pal-prime";
	return "not-pal-prime"; // not true for any other conditions so is therefore true for this one
}
int main() {
	long test_num;
	cin >> test_num;
	cout << boolalpha;

	switch (test_num) {

	case 1: {
		string input;
		cin >> input;
		cout << reverse_str(input);
		break;
	}

	case 2: {
		string input;
		cin >> input;
		cout << is_palindrome(input);
		break;
	}

	case 3: {
		long n, base;
		cin >> n >> base;
		cout << long_to_base(n, base);
		break;
	}

	case 4: {
		long n;
		cin >> n;
		cout << is_prime(n);
		break;
	}

	case 5: {
		long n;
		cin >> n;
		cout << is_pal_prime(n);
		break;
	}

	} // of switch
}  // of 
