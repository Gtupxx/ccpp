#include <bits/stdc++.h>
#define PI 3.14159265359879
using namespace std;

    double deep(double x, double alpha)
    {
        double ans = 70.0f;
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
    freopen("T1data.txt", "w", stdout);
    vector<double> xs = {-800.0f, -600.0f, -400.0f, -200.0f, 0.0f, 200.0f, 400.0f, 600.0f, 800.0f};
    vector<double> deeps, lws, rws, rprs;
    /**
     * deeps: a vector contains the deep of each x
     * lws: a vector contains the width of the left part
     * rws: a vector contains the width of the right part
     * rprs: a vector contains the repeat rate of each part
    */
    double l = 0.0f, r = 0.0f;

    for (auto x : xs)
    {
        // compute the deep
        double de = deep(x, alpha);
        deeps.emplace_back(de);

        double prer = r;
        // compute the width of each part
        l = l_width(de, theta, alpha);
        lws.emplace_back(l);
        r = r_width(de, theta, alpha);
        rws.emplace_back(r);

        // compute the rate of the repeat part
        double d = 200.f;
        double rep = rep_width(d, theta, alpha, prer, l);
        double eta;
        if (x > -800.0f)
        {
            eta = rep / (l + r) * 100;
        }
        else
            eta = 0.0f;
        rprs.emplace_back(eta);
    }

    for (int i = 0; i < deeps.size(); i++)
    {
        printf("%.2f\t", xs[i]);
    }
    printf("\n");

    for (int i = 0; i < deeps.size(); i++)
    {
        printf("%.2f\t", deeps[i]);
    }
    printf("\n");

    for (int i = 0; i < deeps.size(); i++)
    {
        printf("%.2f\t", lws[i] + rws[i]);
    }
    printf("\n");

    for (int i = 0; i < deeps.size(); i++)
    {
        printf("%.2f\t", rprs[i]);
    }
    printf("\n");
}