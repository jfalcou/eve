#include <eve/module/dd.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <iomanip>

using w_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  w_ft hi = { 0.0f, 1.0f, -1.0f, 0.5f};
  w_ft lo = { 2.0f , -1.0f,  -5.0f, 0.0f};
  using wd_t = eve::as_dd_t<w_ft>;
  wd_t z1(hi, lo);
  wd_t z2(lo, hi);

  std::cout
    << "---- simd" << std::setprecision(8) << std::endl
    << "<- z1            = " << z1 << std::endl
    << "<- z2            = " << z2 << std::endl
    << "<- eve::ddlo(z1) = " << eve::ddlo(z1) << std::endl
    << "<- eve::ddlo(z2) = " << eve::ddlo(z2) << std::endl;

  std::cout << "z1 ============= " << std::endl;
  std::cout << "z1" << z1 << std::endl;
  std::cout << "z1 ============= " << std::endl;

  using dd_t = eve::dd<float>;
  dd_t z3(1.f, 2.f);
  dd_t z4(2.f, 1.f);
  std::cout
    << "---- simd" << std::setprecision(8) << std::endl
    << "z3            = "<< z3 << std::endl
    << "z4            = "<< z4 << std::endl
    << "eve::ddlo(z3)  = "<< eve::ddlo(z3) << std::endl
    << "eve::ddhi(z4)  = "<< eve::ddhi(z4) << std::endl;
  return 0;
}
