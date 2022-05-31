#include <iostream> 
using namespace std;
//a
void main() {
	double a = 5.44;
	double k = 0, i = 1;
	while (a > k) {
		k = k + 1.0 / i;
		i++;
	}
	printf("%lf", k);
}
//b
int main()
{
	float summa;
	int n;
	cout << "n: "; cin >> n;
	summa = 0;
	for (int i = 1; i <= n; i++) {
		summa = summa + (double)1 / i;
	}
	cout << "summa = : " << summa << endl;
	system("PAUSE"); 
	return 0;
}