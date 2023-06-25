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
    << "-> abs(q1)            = " << eve::abs(q1) << std::endl
    << "-> add(q1, q2)        = " << eve::add(q1, q2) << std::endl
    << "-> average(q1,q2)     = " << eve::average(q1,q2) << std::endl
    << "-> ceil(q1)           = " << eve::ceil(q1) << std::endl
    << "-> conj(q1)           = " << eve::conj(q1) << std::endl
    << "-> dec(q1)            = " << eve::dec(q1) << std::endl
    << "-> dist(q1,q2)        = " << eve::dist(q1,q2) << std::endl
    << "-> div(q1,q2)         = " << eve::div(q1,q2) << std::endl
    << "-> floor(q1)          = " << eve::floor(q1) << std::endl
    << "-> frac(q1)           = " << eve::frac(q1) << std::endl
    << "-> inc(q1)            = " << eve::inc(q1) << std::endl
    << "-> ipart(q1)          = " << eve::ipart(q1) << std::endl
    << "-> jpart(q1)          = " << eve::jpart(q1) << std::endl
    << "-> kpart(q1)          = " << eve::kpart(q1) << std::endl
    << "-> lerp(q1,q2, 0.3f)  = " << eve::average(q1,q2) << std::endl
    << "-> maxabs(q1,q2)      = " << eve::maxabs(q1,q2) << std::endl
    << "-> minabs(q1,q2)      = " << eve::minabs(q1,q2) << std::endl
    << "-> minus(q1)          = " << eve::minus(q1) << std::endl
    << "-> mul(q1, q2)        = " << eve::mul(q1, q2) << std::endl
    << "-> nearest(q1)        = " << eve::nearest(q1) << std::endl
    << "-> negmaxabs(q1,q2)   = " << eve::negmaxabs(q1,q2) << std::endl
    << "-> negminabs(q1,q2)   = " << eve::negminabs(q1,q2) << std::endl
    << "-> oneminus(q1)       = " << eve::oneminus(q1) << std::endl
    << "-> plus(q1)           = " << eve::plus(q1) << std::endl
    << "-> pure(q1)           = " << eve::pure(q1) << std::endl
    << "-> real(q1)           = " << eve::real(q1) << std::endl
    << "-> rec(q1)            = " << eve::rec(q1) << std::endl
    << "-> reldist(q1,q2)     = " << eve::reldist(q1,q2) << std::endl
    << "-> sign(q1)           = " << eve::sign(q1) << std::endl
    << "-> sqr(q1)            = " << eve::sqr(q1) << std::endl
    << "-> sqr_abs(q1)        = " << eve::sqr_abs(q1) << std::endl
    << "-> sqrt(q1)           = " << eve::sqrt(q1) << std::endl
    << "-> trunc(q1)          = " << eve::trunc(q1) << std::endl
   ;

  return 0;
}
