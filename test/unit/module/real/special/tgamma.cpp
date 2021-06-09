//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/tgamma.hpp>
#include <type_traits>
#include <cmath>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/platform.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of tgamma"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::tgamma(T())  , T);
  TTS_EXPR_IS( eve::tgamma(v_t()), v_t);
};

//==================================================================================================
// tgamma  tests
//==================================================================================================
EVE_TEST( "Check behavior of tgamma on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(-10.0, 10.0))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  using eve::tgamma;
#if defined(__cpp_lib_math_special_functions)
  TTS_ULP_EQUAL( tgamma(a0),  map([&](auto e) -> v_t{ return std::tgamma(e); }, a0), 2);
#endif  // __cpp_lib_math_special_functions

  if constexpr( eve::platform::supports_invalids )
  {
    TTS_IEEE_EQUAL(tgamma(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(tgamma(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(tgamma(eve::minf(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }
  TTS_IEEE_EQUAL(tgamma(T( 0 )), eve::inf(eve::as<T>())  );
  TTS_IEEE_EQUAL(tgamma(T(-0.)), eve::minf(eve::as<T>()) );
  TTS_IEEE_EQUAL(tgamma(T( 1 )), T(1)           );
  TTS_IEEE_EQUAL(tgamma(T( 2 )), T(1)           );
  TTS_IEEE_EQUAL(tgamma(T( 3 )), T(2)           );
  TTS_IEEE_EQUAL(tgamma(T( 5 )), T(24.0)        );
  TTS_ULP_EQUAL(tgamma(T(0.5)), T(1.772453850905516), 0.5);
};
