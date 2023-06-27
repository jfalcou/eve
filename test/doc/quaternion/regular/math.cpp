#include <eve/module/quaternion.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft r1 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft i1 = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft j1 = { 1.0f, -3.0f,  -4.0f, 1.5f};
  wide_ft k1 = { -2.0, 1.5f, 2.3f, 6.7f};
  auto q1 = eve::as_quaternion_t<wide_ft>(r1, i1, j1, k1);
  wide_ft r2 = { 4.0f, 0.0f, -1.0f, -0.5f};
  wide_ft i2 = { -2.0f , 1.0,  3.0, 10.0};
  wide_ft j2 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft k2 = { 2.0f, -1.0f,  -5.0f, 0.0f};
  auto q2 = eve::as_quaternion_t<wide_ft>(r2, i2, j2, k2);


  std::cout
    << "---- simd" << std::endl
    << "<- q1                 = " << q1 << std::endl
    << "<- q2                 = " << q2 << std::endl
    << "-> cos(q1)            = " << eve::cos(q1) << std::endl
    << "-> cosh(q1)           = " << eve::cosh(q1) << std::endl
    << "-> cot (q1)           = " << eve::cot(q1) << std::endl
    << "-> exp (q1)           = " << eve::exp(q1) << std::endl
    << "-> expm&(q1)          = " << eve::expm1(q1) << std::endl
    << "-> hypot(q1, q2)      = " << eve::hypot(q1, q2) << std::endl
    << "-> lpnorm(3, q1, q2)  = " << eve::lpnorm(3, q1, q2) << std::endl
    << "-> manhattan(q1, q2)  = " << eve::manhattan(q1, q2) << std::endl
    << "-> pow(q1, 4)         = " << eve::pow(q1, 4) << std::endl
    << "-> powm1q1, 4)        = " << eve::powm1(q1, 4) << std::endl
    << "-> sin(q1)            = " << eve::sin(q1) << std::endl
    << "-> sinh(q1)           = " << eve::sinh(q1) << std::endl
    << "-> sqrt(q1)           = " << eve::sqrt(q1) << std::endl
    << "-> tan(q1)            = " << eve::tan(q1) << std::endl
    << "-> tanh(q1)           = " << eve::tanh(q1) << std::endl
    ;

  return 0;
}
