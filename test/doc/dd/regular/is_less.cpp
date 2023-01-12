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
    << "<- z1       = " << z1 << std::endl
    << "<- z2       = " << z2 << std::endl
//     << "-> is_less(z1, z2) = " << (z1 < z2) << std::endl
//     << "-> is_less(z1, z2) = " << eve::is_less(z1, z2) << std::endl
//     << "-> is_equalz1, z2) = " << eve::is_equal(z1, z2) << std::endl
//     << std::setprecision(16) << z1 -z2 << std::endl
   ;

  std::cout << eve::low(z1) << " == " << eve::low(z2) << std::endl;
  std::cout << eve::high(z1) << " == " << eve::high(z2) << std::endl;
  std::cout << (z1 == z2) << std::endl;
  std::cout
    << "---- simd" << std::setprecision(8) << std::endl
    << "<- z1       = " << z1 << std::endl
    << "<- z2       = " << z2 << std::endl
   ;

  using dd_t = eve::dd<float>;
  dd_t z3(1, 2);
  dd_t z4(2, 1);
  std:: cout << "z3 "<< z3 << std::endl;
  std:: cout << "z4 "<< z4 << std::endl;
  std::cout << eve::low(z3) << " == " << eve::low(z4) << std::endl;
  std::cout << eve::high(z3) << " == " << eve::high(z4) << std::endl;
  std::cout << (z3 == z4) << std::endl;
  return 0;
}
