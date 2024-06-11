#include <bits/stdc++.h>
#define PI 3.14159265359879
using namespace std;

    double deep(double x, double alpha)
    {
        double ans = 110.0f;
        ans += x * tan(alpha * PI / 180.0f);
        return ans;
    }

    double l_width(double d, double theta, double alpha)
    {
        return d * sin((theta / 2.0) * PI / 180.0f) / sin((90.0f - (theta / 2.0) - alpha) * PI / 180.0f);
    }

    double r_width(double d, double theta, double alpha)
    {
        return d * sin(theta / 2.0 * PI / 180.0f) / sin((90.0f - (theta / 2.0) + alpha) * PI / 180.0f);
    }

    double rep_width(double d, double theta, double alpha, double prer, double l)
    {
        double sum = prer + l;
        double len = d / cos(alpha * PI / 180.0f);
        return sum - len;
    }

int main()
{
    double theta = 120.0f;
    double alpha = 1.5f;
    double l = 0.0f, r = 0.0f;
    double dep = deep(-2.0f * 1852.0f, alpha);
    r = l = l_width(dep, theta, 0);
    cout << "gap between the bank:" << r << endl;
    double gap = 0.9f * (r + l);
    double mingap = gap;
    cout << "gap:" << gap << endl;
    double dep2 = deep(2.0f * 1852.0f, alpha);
    r = l = l_width(dep2, theta, 0);
    double rate = 100.0f * (1.0f - gap / (l + r));
    cout << "deep rate:" << rate << endl;
    int n = int(2.0f * 1852.0f / mingap);
    cout <<"the number of the lines:"<< n << endl;
    cout << "total length:" << (4.0f * n);
}