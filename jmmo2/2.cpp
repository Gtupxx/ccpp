#include<bits/stdc++.h>
#define PI 3.14159265358979
using namespace std;

double l_width(double d, double theta, double alpha)
{
    return d * sin((theta / 2.0) * PI / 180.0f) / sin((90.0f - (theta / 2.0) - alpha) * PI / 180.0f);
}

double r_width(double d, double theta, double alpha)
{
    return d * sin(theta / 2.0 * PI / 180.0f) / sin((90.0f - (theta / 2.0) + alpha) * PI / 180.0f);
}

double subalpha(double beta, double alpha)
{
    double rad = atan(tan(alpha * PI / 180.0f) * sin(beta * PI / 180.0f));
    return rad / PI * 180.0f;
}

double deep(double x, double alpha)
    {
        double base_deep = 120.0f;
        double ans = base_deep + x * tan(alpha * PI / 180.0f);
        return ans;
    }
int main()
{
    double theta = 120.0f;
    double alpha = 1.5f;
    freopen("T2data.txt", "w", stdout);
    vector<double> xs = {0.0f, 0.3f, 0.6f, 0.9f, 1.2f, 1.5f, 1.8f, 2.1f};
    vector<double> betas = {0.0f, 45.0f, 90.0f, 135.0f, 180.0f, 225.0f, 270.0f, 315.0f};
    vector<vector<double>> ans;
    double l = 0.0f, r = 0.0f;

    for (auto beta : betas)
    {
        vector<double> row;
        for(auto x : xs)
        {
            double salp = subalpha(beta, alpha);
            double dep = deep(x*1852.0f,salp);
            l = l_width(dep, theta, salp);
            r = r_width(dep, theta, salp);
            row.emplace_back(l + r);
        }
        ans.emplace_back(row);
    }
    for (auto row : ans)
    {
        for(auto d : row)
        {
            printf("%.2f\t", d);
        }
        cout << endl;
    }
}