//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of remdiv", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t   = eve::element_type_t<T>;
  using tup_t = kumi::tuple<T, T>;
  // regular
  TTS_EXPR_IS(eve::remdiv(T(), T()), tup_t);
  TTS_EXPR_IS(eve::remdiv(T(), v_t()), tup_t);
  TTS_EXPR_IS(eve::remdiv(v_t(), T()), tup_t);
  TTS_EXPR_IS(eve::remdiv(v_t(), v_t()), (kumi::tuple<v_t, v_t>));
};

//==================================================================================================
//==  remdiv simd tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&)
{ return std::is_signed_v<eve::element_type_t<T>> ? -100 : 1; };

TTS_CASE_WITH("Check behavior of remdiv on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(tts::constant(mini), 100),
                            tts::randoms(tts::constant(mini), 100)))
<typename T>(T a0, T a1)
{
  using eve::remdiv;
  using eve::toward_zero;
  using eve::detail::map;
  a1          = eve::if_else(eve::is_eqz(a1), eve::one, a1);
  auto [r, d] = eve::remdiv(a0, a1);

  if constexpr( eve::integral_simd_value<T> )
  {
    TTS_EQUAL(r, map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1));
    TTS_EQUAL(d, map([](auto e, auto f) { return toward_zero(eve::div)(e, f); }, a0, a1));
  }
  else
  {
    auto thrs = std::same_as<eve::element_type_t<T>, float> ? 5e-4 : 5e-12;
    TTS_RELATIVE_EQUAL(r, map([](auto e, auto f) { return eve::rem(e, f); }, a0, a1), thrs)
        << "a0 " << a0 << '\n'; // fma not avail scalar double it seems
    std::cout << "a0 " << a0 << std::endl;
    TTS_RELATIVE_EQUAL(d,
                       map([](auto e, auto f) { return toward_zero(eve::div)(e, f); }, a0, a1),
                       thrs); // fma not avail scalar double it seems
  }
};

//==================================================================================================
//== Test for fixed values
//==================================================================================================
TTS_CASE_TPL("Check fixed-cases behavior of eve::remdiv", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::toward_zero;

  if constexpr( eve::signed_value<T> )
  {
    {
      auto [r, d] = eve::remdiv(T(-1), T(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(v_t(-1), T(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(T(-1), v_t(2));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(0));
    }
    {
      auto [r, d] = eve::remdiv(T(-4), T(3));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(-4), v_t(3));
      TTS_EQUAL(r, T(-1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(4), T(-3));
      TTS_EQUAL(r, T(1));
      TTS_EQUAL(d, T(-1));
    }
    {
      auto [r, d] = eve::remdiv(T(4), v_t(-3));
      TTS_EQUAL(r, T(1));
      TTS_EQUAL(d, T(-1));
    }
  }
  {
    auto [r, d] = eve::remdiv(T(12), T(4));
    TTS_EQUAL(r, T(0));
    TTS_EQUAL(d, T(3));
  }
  {
    auto [r, d] = eve::remdiv(T(1), T(2));
    TTS_EQUAL(r, T(1));
    TTS_EQUAL(d, T(0));
  }
  {
    auto [r, d] = eve::remdiv(T(4), T(3));
    TTS_EQUAL(r, T(1));
    TTS_EQUAL(d, T(1));
  }
  {
    auto [r, d] = eve::remdiv(T(3), T(4));
    TTS_EQUAL(r, T(3));
    TTS_EQUAL(d, T(0));
  }
};
