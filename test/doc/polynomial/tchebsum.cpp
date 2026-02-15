// revision 1
#include <eve/module/math.hpp>
#include <eve/module/polynomial.hpp>
#include <iostream>
#include <array>

double tch1(auto t, auto c)
{
  double u0 = 0;
  double u1 = 0;
  double u2 = 0;
  auto tt = t+t;

  for(int i=c.size()-1; i >= 0 ; --i)
  {
    u2=u1;
    u1=u0;
    u0=tt*u1+c[i]-u2;
  }
  return (u0-u2)/2;
}

double tch2(auto t, auto ... c)
{
  double u0 = 0;
  double u1 = 0;
  double u2 = 0;
  auto tt = t+t;

  auto clemshaw_step = [&](auto ci){
    u2=u1;
    u1=u0;
    u0 = fma(tt, u1, ci-u2);
    return u0;
  };

  ((u0 = clemshaw_step(c)), ...);
  return (u0-u2)/2;
}

int main()
{
  std::array<double, 4> c{1, 2, 3, 4};
 std::array<double, 4> d{4.0, 3.0, 2.0, 1.0};
  std::cout <<  tch1(-2.0, c) << std::endl;
  std::cout <<  eve::tchebsum[eve::increasing](2.0, c)<< std::endl;
  std::cout <<  eve::tchebsum[eve::decreasing](2.0, d)<< std::endl;
  std::cout <<  tch2(2.0, 4.0, 3.0, 2.0, 1.0)<< std::endl;
  std::cout <<  eve::tchebsum[eve::decreasing](2.0, 4.0, 3.0, 2.0, 1.0)<< std::endl;
  std::cout <<  eve::tchebsum(2.0, 1.0, 2.0, 3.0, 4.0)<< std::endl;

  eve::wide<double, eve::fixed<4>> xx{-2.0, -0.44, 0.44, 2.0};
  std::cout <<  eve::tchebsum[eve::increasing](xx, c)<< std::endl;
  std::cout <<  eve::tchebsum[eve::decreasing](xx, d)<< std::endl;
  std::cout <<  eve::tchebsum(xx, 1.0, 2.0, 3.0, 4.0)<< std::endl;

}
