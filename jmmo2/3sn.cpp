#include <bits/stdc++.h>
#define PI 3.14159265358979
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

double cgap(double sum, double alpha, double theta, double pl, double rp)
{
    double up = rp - pl - (110.0f + (-1852.0f + sum) * tan(alpha * PI / 180.0f)) / cos((-theta / 2.0f + alpha) * PI / 180.0f);
    double down = tan(alpha * PI / 180.0f) / cos((-theta / 2.0f + alpha) * PI / 180.0f) - 1.0f / cos(alpha * PI / 180.0f);
    return up / down;
}
int main()
{
    double theta = 120.0f;
    double alpha = 1.5f;
    double l = 0.0f, r = 0.0f;
    vector<double> gaps = {};
    double mindep = deep(-1.0f, alpha);
    // cout << mindep;
    gaps.emplace_back(mindep * sqrt(3.0f));
    l = l_width(deep(-1852.0f + gaps[0], alpha), theta, alpha);
    r = r_width(deep(-1852.0f + gaps[0], alpha), theta, alpha);
    double sum = gaps[0];
    int cnt = 1;
    while (sum + l * cos(alpha) < 2.0f * 1852.0f)
    {
        double rep = 0.1f * (l + r);
        double gap = cgap(sum, alpha, theta, l, rep);
        gaps.emplace_back(gap);
        double dep = deep(-1852.0f + gaps[cnt] + sum, alpha);
        r = r_width(dep, theta, alpha);
        l = l_width(dep, theta, alpha);
        sum += gap;
        cnt++;
    }
    for (auto g : gaps)
    {
        cout << g << endl;
    }
    cout << "the number of the lines:" << gaps.size() << endl;
    cout << "total length:" << (2.0f * gaps.size()) << endl;
}