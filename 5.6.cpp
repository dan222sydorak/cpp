//a
# include <iomanip>
# include <iostream>
# include <ctime>
using namespace std;


void i4cf_evaluate(int n, int a[], int b[], int p[], int q[])
{
    int i,j;
    cin >> n >> j;
    cout << n << "j=" << j;

    for (i = 0; i <= n; i++)
    {
        if (i == 0)
        {
            p[i] = a[i] * 1 + 0;
            q[i] = a[i] * 0 + 1;
        }
        else if (i == 1)
        {
            p[i] = a[i] * p[i - 1] + b[i] * 1;
            q[i] = a[i] * q[i - 1] + b[i] * 0;
        }
        else
        {
            p[i] = a[i] * p[i - 1] + b[i] * p[i - 2];
            q[i] = a[i] * q[i - 1] + b[i] * q[i - 2];
        }
    }

    return;
}

//c
