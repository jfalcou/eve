//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <tuple>

//==================================================================================================
//== Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::rat(scalar)"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using v_t =  eve::element_type_t<T>;
  TTS_EXPR_IS( eve::rat(T())                    , (kumi::tuple<T, T>)  );
  TTS_EXPR_IS( eve::rat(T(), T())               , (kumi::tuple<T, T>) );
  TTS_EXPR_IS( eve::rat(T(), v_t())             , (kumi::tuple<T, T>) );
  TTS_EXPR_IS( eve::rat(v_t(), v_t())           , (kumi::tuple<v_t, v_t>)  );
};

//==================================================================================================
// Tests for eve::rat
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::rat(simd)"
        , eve::test::simd::ieee_reals
        , tts::generate ( tts::ramp(1.0))
        )
<typename T>(T const& a0)
{
//   using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto [n, d] = eve::rat(a0/37);
  TTS_EQUAL(n, map([](auto e) -> v_t { return  e; }, a0));
  TTS_EQUAL(d, T(37));
};
