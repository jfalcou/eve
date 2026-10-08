//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL("Check return types of maxrepint", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::as;

  TTS_EXPR_IS(eve::maxrepint(as<T>()), T);
  TTS_EXPR_IS(eve::maxrepint(as<v_t>()), v_t);
};

//==================================================================================================
// maxrepint is defined by its relation to the constants it derives from
//==================================================================================================
TTS_CASE_TPL("Check behavior of maxrepint", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using eve::as;
  if constexpr( eve::integral_value<T> ) TTS_EQUAL(eve::maxrepint(as<T>()), eve::valmax(as<T>()));
  else                                   TTS_EQUAL(eve::maxrepint(as<T>()), eve::maxflint(as<T>()));
};

//==================================================================================================
// masked maxrepint
//==================================================================================================
TTS_CASE_WITH("Check behavior of maxrepint[mask] on wide",
              eve::test::simd::all_types,
              tts::generate(tts::randoms(eve::valmin, eve::valmax),
              tts::logicals(0, 3)))
<typename T, typename M>(T const& a0, M const& mask)
{
  TTS_IEEE_EQUAL(eve::maxrepint[mask](eve::as(a0)), eve::if_else(mask, eve::maxrepint(eve::as(a0)), eve::zero));
};
