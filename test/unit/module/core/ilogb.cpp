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
TTS_CASE_TPL("Check return types of eve::ilogb(simd)", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using i_t  = eve::as_integer_t<T>;
  using v_t  = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;
  TTS_EXPR_IS(eve::ilogb(T()), i_t);
  TTS_EXPR_IS(eve::ilogb(v_t()), vi_t);
};

//==================================================================================================
// Tests for eve::ilogb
//==================================================================================================
TTS_CASE_WITH("Check behavior of eve::ilogb(simd)",
              eve::test::simd::ieee_reals,
              tts::generate(tts::between(-1.0, 1.0), tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& t)
{
  using i_t  = eve::as_integer_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::ilogb(a0),
            tts::map(
              [](auto e) -> vi_t
              {
                int ee;
                std::frexp(e, &ee);
                return ee - 1;
              },
              a0));
  TTS_EQUAL(eve::ilogb[t](a0),
            eve::if_else(t, eve::ilogb(a0), eve::convert(a0, eve::as<vi_t>())));
  TTS_EQUAL(eve::ilogb(2.5), std::int64_t(std::ilogb(2.5)));
};

//==================================================================================================
// special tests
//==================================================================================================
TTS_CASE_TPL("Check return types of eve::ilogb(simd)", eve::test::simd::ieee_reals)
  <typename T>(tts::type<T>)
{
  using        eve::as;
  using i_t  = eve::as_integer_t<T>;
  using v_t  = eve::element_type_t<T>;
  using vi_t = eve::element_type_t<i_t>;

  TTS_EQUAL(eve::ilogb(T(0)), eve::valmin(as<i_t>()));
  TTS_EQUAL(eve::ilogb(v_t(0)), eve::valmin(as<vi_t>()));
  TTS_EQUAL(eve::ilogb(T(1)), i_t(0));
  TTS_EQUAL(eve::ilogb(v_t(1)), vi_t(0));
  TTS_EQUAL(eve::ilogb(eve::inf(eve::as<T>())), eve::valmin(eve::as<i_t>()));
  TTS_EQUAL(eve::ilogb(eve::inf(eve::as<v_t>())), eve::valmin(eve::as<vi_t>()));
  TTS_EQUAL(eve::ilogb(eve::minf(eve::as<T>())), eve::valmin(eve::as<i_t>()));
  TTS_EQUAL(eve::ilogb(eve::minf(eve::as<v_t>())), eve::valmin(eve::as<vi_t>()));
  TTS_EQUAL(eve::ilogb(eve::nan(eve::as<T>())), eve::valmin(eve::as<i_t>()));
  TTS_EQUAL(eve::ilogb(eve::nan(eve::as<v_t>())), eve::valmin(eve::as<vi_t>()));

};
