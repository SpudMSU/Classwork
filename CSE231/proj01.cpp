
#include <iostream>
#include <cmath>
#include<iomanip>
using namespace std;
int main() {
	double cp=0, str=0, dp=0, taf=0, yir=0, nom=0, fp=0, mp=0, c=0, a;
	cin >> cp >> str >> dp >> taf >> yir >> nom;
	fp= (((cp*str)+cp+taf) -dp);
	a= 1+yir/12;
	c= pow(a, nom);
	mp = fp*(yir/12*c)/(c-1);
	cout << fixed << setprecision(2) << mp; 
}
