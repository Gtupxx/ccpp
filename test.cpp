/*
 * @Author: 睿超 刘 1152349903@qq.com
 * @Date: 2022-12-30 18:55:00
 * @LastEditors: 睿超 刘 1152349903@qq.com
 * @LastEditTime: 2023-06-23 16:28:08
 * @FilePath: \ccpp\test.cpp
 * @Description:  
 * 
 */
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <stdexcept>

#include <cmath>
#include <limits>
#include <stdexcept>

namespace LambertW {

  const double inf = std::numeric_limits<double>::infinity();

  #define E 2.718281828459045235360287471352662497757247093699959574966967627724076630353547594571382178525166427427466391932003e0
  #define MIN_Z -0.367879441171442321595523770161460867445811131031767834507836801697461495744899803357147274345919643746627325277475e0
  #define MIN_P -0.033765242898423986093849222753002695152595309462001296970338474035219572986497253860698048686258522994908776059683e0

  inline double log1p(const double x) {
    if (x <= -1.)
      return -inf;
    if (fabs(x) > 1.e-4)
      return log(1. + x);
    return (-0.5*x + 1.)*x;
  }

  inline double expm1(const double x) {
    if (fabs(x) > 1.e-5)
      return exp(x) - 1.;
    return (0.5*x + 1.)*x;
  }

  inline double lambert_w0(const double z) {
    if (z < MIN_Z)
      throw std::domain_error("LambertW::lambert_w0");
    if (z == 0.)
      return 0.;
    if (z == MIN_Z)
      return -1.;
    if (z < MIN_P) {
      const double p = sqrt(2.*(E*z + 1.));
      double w = -1. + p*(1. + p*(-0.333333333333333333333 + p*0.152777777777777777778));
      for (int i=0; i<10; ++i) {
        const double e = exp(w);
        const double t = w*e - z;
        const double p = w + 1.;
        w -= t/(e*p - 0.5*(p + 1.)*t/p);
      }
      return w;
    }
    if (z < 1.) {
      const double p = sqrt(2.*(E*z + 1.));
      double w = -1. + p*(1. + p*(-0.333333333333333333333 + p*0.152777777777777777778));
      for (int i=0; i<10; ++i) {
        const double e = exp(w);
        const double t = w*e - z;
        const double p = w + 1.;
        w -= t/(e*p - 0.5*(p + 1.)*t/p);
      }
      return w;
    }
    double w = log(z);
    if (z > 3.)
      w -= log(w);
    for (int i=0; i<10; ++i) {
      const double e = exp(w);
      const double t = w*e - z;
      const double p = w + 1.;
      w -= t/(e*p - 0.5*(p + 1.)*t/p);
    }
    return w;
  }

}


int main ()
{
   std::fstream fs("i.txt");
   std::vector<std::pair<double, double>> v;
   if(fs.is_open())
   {
        std::cout << "opened" << std::endl;
   }
   while(!fs.eof())
   {
      int x, y;
      fs >> x >> y;
      v.emplace_back(std::pair<double, double>(x, y));
   }
   fs.close();
   for(auto &p:v)
   {
      p.first = LambertW::lambert_w0(p.first);
      p.second = LambertW::lambert_w0(p.second);
   }
   fs.open("o.txt", std::ios::out);
   for(auto& p:v)
   {
      fs << p.first << '\t' << p.second << std::endl;
   }
   fs.close();
}