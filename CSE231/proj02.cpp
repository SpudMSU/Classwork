#include <iostream>
#include <cmath>
#include <sstream>
using namespace std;
int main() {
	int uprBnd, lwrBnd, showTxt, lngst, seq = 0, count, seq2 = 0;
	double bggstOp; //Originally I was using this to store the biggest num in and it was a long long. However for some reason if I used it in a conditional statement it would no longer function so I made a seperate variable for it
	long long number, bggstStore;
	cin >> lwrBnd >> uprBnd >> showTxt;
	if (lwrBnd < 2 || uprBnd < 2 || lwrBnd > uprBnd) {
		cout << "Error";
		return 0;
	}
	for (int i = lwrBnd; i <= uprBnd; i++) {
		number = i;
		count = 0;
		if (showTxt == 1)
			cout << i << ": ";
		while (number != 1) {
			if (number > bggstOp) {
				bggstOp = number;
				bggstStore = number;
				seq2 = i;
			}
			if (number % 2 == 0)
				number = floor(sqrt(number));
			else
				number = floor(sqrt(number)*sqrt(number)*sqrt(number));
			if (showTxt == 1) {
				cout << number;
				if (number != 1)
					cout << ",";
			}
			count++;
		}
		if (showTxt == 1)
			cout << endl;
		if (count > seq) {
			seq = count;
			lngst = i;
		}
	}
	cout << lngst << ", " << seq << endl << seq2 << ", " << bggstStore;
}
