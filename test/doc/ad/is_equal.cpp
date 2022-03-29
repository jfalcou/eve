#include <eve/module/ad.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft   = eve::wide<float, eve::fixed<4>>;
using wide_vdt  = eve::wide<eve::valder<float>, eve::fixed<4>>;
using vd_t      = eve::valder<float>;

int main()
{
  auto inf = eve::inf(eve::as<float>());
  auto nan = eve::nan(eve::as<float>());
  wide_ft fr1 = {-1.0f, 2.0f, -3.0f,  0.0f};
  wide_ft fi1 = { 0.0f, 2.0f,  2.0f, -3.5f};
  wide_vdt f1{fr1, fi1};
  wide_ft fr2 = {-1.0f, 2.0f, inf,  0.0f};
  wide_ft fi2 = { 0.0f, 2.0f,  2.0f, nan};
  wide_vdt f2{fr2, fi2};

  std::cout << "---- simd" << '\n'
            << "<- f1                    = " << f1 << '\n'
            << "<- f2                    = " << f2 << '\n'
            << "-> is_equal(f1, f2)      = " << eve::is_equal(f1, f2) << '\n'
            << "-> is_equal(f1, fr2)     = " << eve::is_equal(f1, fr2) << '\n'
            << "-> is_equal(fr2, f1)     = " << eve::is_equal(fr1, f1) << '\n';

  float  sf1r = -1.0f;
  float  sf1i =  3.0f;
  vd_t   sf1{sf1r, sf1i};
  float  sf2r = -2.0f;
  float  sf2i =  4.0f;
  vd_t   sf2{sf2r, sf2i};

  std::cout << "---- scalar" << '\n'
            << "<- sf1                  = " << sf1 << '\n'
            << "<- sf2                  = " << sf2 << '\n'
            << "-> is_equal(sf1, sf2)   = " << eve::is_equal(sf1, sf2) << '\n';
  return 0;
}
