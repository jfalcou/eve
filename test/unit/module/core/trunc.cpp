//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <type_traits>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of trunc", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS(eve::trunc(T()), T);
  TTS_EXPR_IS(eve::trunc(v_t()), v_t);
  TTS_EXPR_IS(eve::trunc(T(), eve::as<signed>()), (eve::as_integer_t<T, signed>));
  TTS_EXPR_IS(eve::trunc(v_t(), eve::as<signed>()), (eve::as_integer_t<v_t, signed>));
  TTS_EXPR_IS(eve::trunc(T(), eve::as<unsigned>()), (eve::as_integer_t<T, unsigned>));
  TTS_EXPR_IS(eve::trunc(v_t(), eve::as<unsigned>()), (eve::as_integer_t<v_t, unsigned>));

  if constexpr( eve::floating_value<T> )
  {
    TTS_EXPR_IS(eve::trunc[eve::almost](T()), T);
    TTS_EXPR_IS(eve::trunc[eve::almost](v_t()), v_t);
  }
};

//==================================================================================================
// almost tests
//==================================================================================================
TTS_CASE_TPL("Check  fuzzy", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  TTS_EQUAL(eve::trunc[eve::almost](eve::inc(-eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::inc(-2 * eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::inc(-3 * eve::eps(eve::as<T>()))), T(1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::inc(-4 * eve::eps(eve::as<T>()))), T(0));
  TTS_EQUAL(eve::trunc[eve::almost](eve::dec(eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::dec(2 * eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::dec(3 * eve::eps(eve::as<T>()))), T(-1));
  TTS_EQUAL(eve::trunc[eve::almost](eve::dec(4 * eve::eps(eve::as<T>()))), T(0));
};

//==================================================================================================
// trunc signed tests
//==================================================================================================
auto mini = []<typename T>(eve::as<T> const&) { return eve::signed_value<T> ? -50 : 0; };

TTS_CASE_WITH("Check behavior of trunc on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(tts::constant(mini), +50)))
<typename T>(T const& a0)
{
   using wi_t  = eve::as_integer_t<T, signed>;
 using uwi_t = eve::as_integer_t<T, unsigned>;
   using v_t   = eve::element_type_t<T>;
   using i_t   = eve::as_integer_t<v_t, signed>;
  using ui_t  = eve::as_integer_t<v_t, unsigned>;
  if constexpr( eve::floating_value<T> )
  {
    TTS_EQUAL(eve::trunc(a0), T([&](auto i, auto) { return v_t(std::trunc(a0.get(i))); }));
    TTS_EQUAL(eve::trunc(a0, eve::as<signed>()), wi_t([&](auto i, auto) { return i_t(a0.get(i)); }));
    TTS_EQUAL(eve::trunc(eve::abs(a0), eve::as<unsigned>()), uwi_t([&](auto i, auto) { return ui_t(std::abs(a0.get(i))); }));
  }
  else { TTS_EQUAL(eve::trunc(a0), a0); }

};

TTS_CASE_TPL(" fuzzy Check ", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using elt_t = eve::element_type_t<T>;
  T a = [](auto i, auto){ return eve::next(elt_t(-1), i); };
  T b = [](auto i, auto){ return eve::prev(elt_t(1), i); };
  T ra = [](auto i, auto){ return i <=  2 ? elt_t(-1) : elt_t(0);  };
  T rb = [](auto i, auto){ return i <=  2 ? elt_t(1): elt_t(0);  };
  TTS_EQUAL( eve::trunc[eve::almost = 2](a), ra);
  TTS_EQUAL( eve::trunc[eve::almost = 2](b), rb);
  elt_t epsi = eve::eps(eve::as<elt_t>());
  T ea = [epsi](auto i, auto){ return elt_t(-1)+i*epsi; };
  T eb = [epsi](auto i, auto){ return elt_t(1 )-i*epsi; };
  T era = [](auto i, auto){ return i <=  2 ? elt_t(-1) : elt_t(0);  };
  T erb = [](auto i, auto){ return i <=  2 ? elt_t(1): elt_t(0);  };
  TTS_EQUAL( eve::trunc[eve::almost = 2*epsi](ea), era);
  TTS_EQUAL( eve::trunc[eve::almost = 2*epsi](eb), erb);

};

TTS_CASE_TPL("Check corner-cases behavior of eve::trunc",
             eve::test::simd::ieee_reals)
  <typename T>(tts::type<T> const& tgt)
{
  auto cases = tts::limits(tgt);
  TTS_IEEE_EQUAL(eve::trunc(cases.nan), cases.nan);
  TTS_IEEE_EQUAL(eve::trunc(cases.inf), cases.inf);
  TTS_IEEE_EQUAL(eve::trunc(cases.minf), cases.minf);

};

//==================================================================================================
// Tests for masked trunc
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::trunc)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(-10000.0, 10000.0),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::trunc[mask](a0),
            eve::if_else(mask, eve::trunc(a0), a0));
};
