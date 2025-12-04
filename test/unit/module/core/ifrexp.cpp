//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <cmath>


template<eve::floating_value T,  eve::integral_value U>
auto exp2(U a1) noexcept
{
  using r_t =   eve::as_wide_as_t<T, U >;
  if constexpr( eve::unsigned_value<U> )
  {
    r_t base(2);
      U expo = a1;

      r_t result = eve::one(eve::as<r_t>());
      while( eve::any(eve::detail::to_logical(expo)) )
      {
        result *= eve::if_else(eve::is_odd(expo), base, eve::one);
        expo = (expo >> 1);
        base = eve::sqr(base);
      }
      return result;
  }
  else
  {
    using u_t = eve::as_integer_t<U, unsigned>;
    r_t tmp     = exp2<T>(eve::bit_cast(eve::abs(a1), eve::as<u_t>()));
    return eve::if_else(eve::is_ltz(a1), eve::rec[eve::pedantic](tmp), tmp);
  }
}

TTS_CASE_TPL("Check (eve::ifrexp behavior", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using i_t = eve::as_integer_t<T, signed>;
  {
    auto [p0, p1] = eve::ifrexp(T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp(T(0));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, i_t(0));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::pedantic](T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::pedantic](T(0));
    TTS_EQUAL(p0, T(0));
    TTS_EQUAL(p1, i_t(0));
  }
  if constexpr( eve::platform::supports_nans )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::nan(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::nan(eve::as<T>())));
    TTS_EQUAL(r1, (i_t(0)));
  }
  if constexpr( eve::platform::supports_infinites )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::inf(eve::as<T>()));
    auto [q0, q1] = eve::ifrexp[eve::pedantic](eve::minf(eve::as<T>()));

    TTS_IEEE_EQUAL(r0, (eve::inf(eve::as<T>())));
    TTS_EQUAL(r1, i_t(0));

    TTS_IEEE_EQUAL(q0, (eve::minf(eve::as<T>())));
    TTS_EQUAL(q1, i_t(0));
  }
  if constexpr( eve::platform::supports_denormals )
  {
    auto [r0, r1] = eve::ifrexp[eve::pedantic](eve::mindenormal(eve::as<T>()));

    TTS_ULP_EQUAL(r0, T(0.5), 1);
    TTS_EQUAL(r1, i_t(eve::minexponent(eve::as<T>()) - eve::nbmantissabits(eve::as<T>()) + 1));
  }
  {
    auto [p0, p1] = eve::ifrexp[eve::raw](T(1));
    TTS_EQUAL(p0, T(0.5));
    TTS_EQUAL(p1, i_t(1));
  }
  if constexpr(eve::cardinal_v<T> == 1)
  {
    auto a = eve::mindenormal(eve::as<T>()); //*T(1.2345);
    auto [p0, p1] = eve::ifrexp[eve::pedantic](a);
//    auto ex = eve::exp2(eve::convert(p1, eve::as_element<T>()));
//    TTS_EQUAL(a, p0*ex) << "p0 " << p0 << " p1 " << p1 << " ex " << ex << '\n';
//    TTS_EQUAL(a, eve::ldexp(p0, p1)) << "p0 " << p0 << " p1 " << p1 << " a " << std::hexfloat << a << '\n';
    auto denormality = p1+eve::maxexponentp1(eve::as<T>());
    std::cout << "eve::maxexponentp1(eve::as<T>()) " << eve::maxexponentp1(eve::as<T>()) << std::endl;
    std::cout << "p0                               " << p0 << std::endl;
    std::cout << "p1                               " << p1 << std::endl;
    std::cout << "denormality " << denormality << std::endl;
    auto p1c = eve::add[eve::is_denormal(a)](p1, -denormality+1);
    auto p0c = p0*exp2<T>(denormality-1);
//    TTS_EQUAL(a, eve::ldexp(p0c, p1c)) << "p0c " << p0c << " p1c " << p1c << " a " << std::hexfloat << a << '\n';
    std::cout << std::hexfloat << "p0c " << p0c <<  "p1c " << p1c << " exp2(p1c) " << exp2<T>(p1c) << std::endl;
    TTS_EQUAL(a, p0c*exp2<T>(p1c));

  }
    std::cout <<  "std::ldexp(1.0, -1074) " << std::ldexp(1.0, -1074)  << std::endl;

//   {
//     auto a = eve::mindenormal(eve::as<T>())*T(-1.2345);
//     auto [p0, p1] = eve::ifrexp[eve::pedantic](a);
//     TTS_EQUAL(a, p0*exp2(T(p1)));

//   }
};
