#include <eve/module/quaternion.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

int main()
{
  wide_ft r1 = { 0.0f, 1.0f, -1.0f, eve::mindenormal(eve::as<float>())};
  wide_ft i1 = { 2.0f , -1.0,  eve::inf(eve::as<float>()), 0.0};
  wide_ft j1 = { 1.0f, -3.0f,  -4.0f, 1.5f};
  wide_ft k1 = { eve::nan(eve::as<float>()), 1.5f, 2.3f, 6.7f};
  auto q1 = eve::as_quaternion_t<wide_ft>(r1, i1, j1, k1);
  wide_ft r2 = { 4.0f, 0.0f, -1.0f, -0.5f};
  wide_ft i2 = { -2.0f , 1.0,  3.0, 10.0};
  wide_ft j2 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft k2 = k1;
  auto q2 = eve::as_quaternion_t<wide_ft>(r2, i2, j2, k2);


  std::cout
    << "---- simd" << std::endl
    << "<- q1                 = " << q1 << std::endl
    << "<- q2                 = " << q2 << std::endl
    << "-> is_denormalq1)     = " << eve::is_denormal(q1) << std::endl
    << "-> is_equal(q1, q2)   = " << eve::is_equal(q1, q2) << std::endl
    << "-> is_eqz(q1)         = " << eve::is_eqz(q1) << std::endl
    << "-> is_finite(q1)      = " << eve::is_finite(q1) << std::endl
    << "-> is_infinite(q1)    = " << eve::is_infinite(q1) << std::endl
    << "-> is_nan(q1)         = " << eve::is_nan(q1) << std::endl
    << "-> is_nez(q1)         = " << eve::is_nez(q1) << std::endl
    << "-> is_not_denormalq1) = " << eve::is_not_denormal(q1) << std::endl
    << "-> is_not_equal(q1,q2)= " << eve::is_not_equal(q1, q2) << std::endl
    << "-> is_not_finite(q1)  = " << eve::is_not_finite(q1) << std::endl
    << "-> is_not_infinite(q1)= " << eve::is_not_infinite(q1) << std::endl
    << "-> is_not_nan(q1)     = " << eve::is_not_nan(q1) << std::endl
    << "-> is_not_pure(q1)    = " << eve::is_not_pure(q1) << std::endl
    << "-> is_pure(q1)        = " << eve::is_pure(q1) << std::endl
    << "-> is_real(q1)        = " << eve::is_real(q1) << std::endl
    ;

  return 0;
}
