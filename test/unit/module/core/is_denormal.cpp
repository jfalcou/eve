//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::is_denormal(simd)"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using eve::logical;
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::is_denormal(T())    , logical<T>   );
  TTS_EXPR_IS( eve::is_denormal(v_t())  , logical<v_t> );
};

//==================================================================================================
// Test for corner-cases values
//==================================================================================================
TTS_CASE_TPL( "Check corner-cases behavior of is_denormal on wide", eve::test::simd::ieee_reals)
<typename T>(tts::type<T> const& tgt)
{
  using eve::is_denormal;
  using eve::as;

  auto cases = tts::limits(tgt);

  if constexpr(eve::platform::supports_denormals)
  {
    TTS_EQUAL     (is_denormal(cases.smallestposval/2), eve::true_(as<T>()));
    TTS_EQUAL     (is_denormal(cases.mindenormal ) , eve::true_(as<T>()));
  }
  TTS_IEEE_EQUAL(is_denormal(cases.inf         ) , eve::false_(as<T>()));
  TTS_IEEE_EQUAL(is_denormal(cases.minf        ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.mzero       ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.zero        ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.smallestposval ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.valmin      ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.one         ) , eve::false_(as<T>()));
  TTS_EQUAL     (is_denormal(cases.mone        ) , eve::false_(as<T>()));
};
