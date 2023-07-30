#include <eve/module/quaternion.hpp>
#include <eve/wide.hpp>
#include <iostream>

using wide_ft = eve::wide <float, eve::fixed<4>>;

namespace eve::detail
{
  template<value T0, value... Cs>
  EVE_FORCEINLINE constexpr auto
  horner_right(T0 const& xx, Cs... cs) noexcept
  -> common_value_t<T0, Cs...>
  {
    using r_t          = common_value_t<T0, Cs...>;
    constexpr size_t N = sizeof...(Cs);
    if constexpr( N == 0 ) return r_t(0);
    else if constexpr( N == 1 ) return (r_t(cs), ...);
    else if constexpr( N == 2 ) return (fma)(r_t(xx), r_t(cs)...);
    else
    {
      auto x    = r_t(xx);
      auto dfma = (fma);
      r_t  that(zero(as<r_t>()));
      auto next = [&](auto that, auto arg) { return dfma(x, that, arg); };
      ((that = next(that, cs)), ...);
      return that;
    }
  }
}

int main()
{
  wide_ft r0 = { 30.0f, 6.0f, -1.0f, 0.4f};
  wide_ft i0 = { 2.0f , -2.0,  -4.0, 0.0};
  wide_ft j0 = { 1.0f, -1.0f,  -3.0f, 1.4f};
  wide_ft k0 = { -2.0, 1.4f, 2.1f, 6.7f};
  auto q0 = eve::as_quaternion_t<wide_ft>(r0, i0, j0, k0);
  wide_ft r1 = { 4.0f, 1.0f, -1.0f, 0.5f};
  wide_ft i1 = { 2.0f , -1.0,  -5.0, 0.0};
  wide_ft j1 = { 5.0f, -3.0f,  -4.0f, 1.5f};
  wide_ft k1 = { -2.0, 1.5f, 2.3f, 6.7f};
  auto q1 = eve::as_quaternion_t<wide_ft>(r1, i1, j1, k1);
  wide_ft r2 = { 4.0f, 0.0f, -1.0f, -0.5f};
  wide_ft i2 = { -2.0f , 1.0,  3.0, 10.0};
  wide_ft j2 = { 0.0f, 1.0f, -1.0f, 0.5f};
  wide_ft k2 = { 2.0f, -1.0f,  -5.0f, 0.0f};
  auto q2 = eve::as_quaternion_t<wide_ft>(r2, i2, j2, k2);
  wide_ft r3 = { 4.0f, 0.0f, -3.0f, -0.5f};
  wide_ft i3 = { -3.0f , 3.0,  3.0, 30.0};
  wide_ft j3 = { 0.0f, 3.0f, -3.0f, 0.5f};
  wide_ft k3 = { 3.0f, -3.0f,  -5.0f, 0.0f};
  auto q3 = eve::as_quaternion_t<wide_ft>(r3, i3, j3, k3);


  std::cout
    << "---- simd" << std::endl
    << "<- q0                 = " << q0 << std::endl
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
    << "-> fma(q1, q2, q3)    = " << eve::fma(q1, q2, q3) << std::endl
    << "-> fma(q2, q1, q3)    = " << eve::fma(q2, q1, q3) << std::endl
    << "-> horner(1.0f, q1, q2, q3)  = " << eve::horner(1.0f, q1, q2, q3) << std::endl
    << "-> q1+ q2+ q3)               = " << q1+q2+q3 << std::endl
    << "-> horner_right(q0, q1, q2, q3)    = " << eve::detail::horner_right(q0, q1, q2, q3) << std::endl
    << "-> sqr(q0)*q1+ q0*q2+ q3     = " << eve::sqr(q0)*q1+ q0*q2+ q3 << std::endl
    << "-> horner_right(q0, q1, q2)    = " << eve::detail::horner_right(q0, q1, q2) << std::endl
    << "-> q0*q1+ q2                   = " << q0*q1+ q2 << std::endl
    << "-> fma(q0, q1, q2)             = " <<  eve::fma(q0, q1, q2) << std::endl
    << " ============= "<< std::endl
    << "-> horner(q0, q1, q2, q3)    = " << eve::horner(q0, q1, q2, q3) << std::endl
    << "-> q1*sqr(q0)+q2*q0+q3       = " <<  q1*eve::sqr(q0)+q2*q0+q3 << std::endl
    << "-> horner(q0, q1, q2)          = " << eve::horner(q0, q1, q2) << std::endl
    << "-> q1*q0 + q2                  = " << q1*q0+ q2 << std::endl
    << "-> fma(q1, q0, q2)             = " <<  eve::fma(q1, q0, q2) << std::endl
    ;

  return 0;
}
