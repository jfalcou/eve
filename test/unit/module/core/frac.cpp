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

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::frac(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS(eve::frac(T()), T);

  TTS_EXPR_IS(eve::frac(v_t()), v_t);
};

//==================================================================================================
// Tests for eve::frac
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::frac(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0)))
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;

  TTS_EQUAL(eve::frac(a0), tts::map([](auto e) -> v_t { return e - std::trunc(e); }, a0));
  TTS_EXPECT(eve::all(eve::is_negative(eve::frac(eve::mzero(eve::as(a0))))));
};


TTS_CASE_TPL(" fuzzy Check ", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using elt_t = eve::element_type_t<T>;
  T a = [](auto i, auto){ return eve::next(elt_t(-1), i); };
  T b = [](auto i, auto){ return eve::prev(elt_t(1), i); };
  T ra = [](auto i, auto){ return i <=  2 ? elt_t(-1) : elt_t(0);  };
  T rb = [](auto i, auto){ return i <=  2 ? elt_t(1): elt_t(0);  };
  TTS_EQUAL( eve::frac[eve::almost = 2](a), a-ra);
  TTS_EQUAL( eve::frac[eve::almost = 2](b), b-rb);
  elt_t epsi = eve::eps(eve::as<elt_t>());
  T ea = [epsi](auto i, auto){ return elt_t(-1)+i*epsi; };
  T eb = [epsi](auto i, auto){ return elt_t(1 )-i*epsi; };
  T era = [](auto i, auto){ return i <=  2 ? elt_t(-1) : elt_t(0);  };
  T erb = [](auto i, auto){ return i <=  2 ? elt_t(1): elt_t(0);  };
  TTS_EQUAL( eve::frac[eve::almost = 2*epsi](ea), ea-era);
  TTS_EQUAL( eve::frac[eve::almost = 2*epsi](eb), eb-erb);

};

//==================================================================================================
// Tests for masked frac
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::masked(eve::frac)(eve::wide)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0,
                         M const& mask)
{
  TTS_IEEE_EQUAL(eve::frac[mask](a0),
            eve::if_else(mask, eve::frac(a0), a0));
};
