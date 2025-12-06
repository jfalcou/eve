//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::frexp(simd)", eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::frexp(T()), (eve::wide<kumi::tuple<v_t,v_t>, typename T::cardinal_type>));
  TTS_EXPR_IS(eve::frexp(v_t()), (kumi::tuple<v_t, v_t>));
  TTS_EXPR_IS(eve::frexp[eve::pedantic](T()), (eve::wide<kumi::tuple<v_t,v_t>, typename T::cardinal_type>));
  TTS_EXPR_IS(eve::frexp[eve::pedantic](v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
// Tests for eve::frexp
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::frexp(simd)",
              eve::test::simd::ieee_reals_wf16,
              tts::generate(tts::randoms(eve::valmin, eve::valmax)))
<typename T>(T const& a0)
{
  auto [x, n] = eve::frexp(a0);
  auto [xx, nn] =  eve::ifrexp(a0);
  TTS_EQUAL(x, xx);
  TTS_EQUAL(nn, eve::convert(n, eve::as_element(decltype(nn)())));
};

//==================================================================================================
// Test for corner-cases values pedantic !
//==================================================================================================
TTS_CASE_TPL("Check corner-cases behavior of eve::frexp[eve::pedantic] variants on wide",
             eve::test::simd::ieee_reals_wf16)
<typename T>(tts::type<T> tgt)
{
  auto cases = tts::limits(tgt);

  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.nan);
    TTS_IEEE_EQUAL(x, cases.nan);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.inf);
    TTS_EQUAL(x, cases.inf);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp(cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.zero);
    TTS_EQUAL(x, cases.zero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.mzero);
    TTS_EQUAL(x, cases.mzero);
    TTS_EQUAL(n, cases.zero);
  }
  {
    auto [x, n] = eve::frexp[eve::pedantic](cases.minf);
    TTS_EQUAL(x, cases.minf);
    TTS_EQUAL(n, cases.zero);
  }

  if constexpr( eve::platform::supports_denormals )
  {
    using v_t = eve::element_type_t<T>;
    auto [x, n] = eve::frexp[eve::pedantic](cases.mindenormal);
    TTS_EQUAL(x, eve::half(eve::as<T>()));

    if constexpr( std::is_same_v<v_t, float> ) TTS_EQUAL(n, T(-150) + 2);
    else if constexpr( std::is_same_v<v_t, double> ) TTS_EQUAL(n, T(-1075) + 2);
  }
  {
    auto a = eve::mindenormal(eve::as<T>());
    while(eve::all(eve::is_denormal(a)))
    {
      using i_t = eve::as_integer_t<T, signed>;
      auto [p0, p1f] = eve::frexp[eve::pedantic](a);
      auto p1 = eve::convert(p1f, eve::as_element<i_t>());
      auto denormality = p1+eve::maxexponentp1(eve::as<T>())-1;
      auto p1c = eve::add[eve::is_denormal(a)](p1, -denormality);
      auto p0c = p0*exp2<T>(denormality);
      auto p0c2 = eve::ldexp(p0, denormality);
      TTS_EQUAL(a, p0c*exp2<T>(p1c));
      TTS_EQUAL(a, p0c2*exp2<T>(p1c));
      a *= T(5.0);
    }
  }
};
