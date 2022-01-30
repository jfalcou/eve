//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of mantissa"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::mantissa(T())  , T);
  TTS_EXPR_IS( eve::mantissa(v_t()), v_t);
};

//==================================================================================================
// mantissa  tests
//==================================================================================================
EVE_TEST( "Check behavior of mantissa on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(eve::valmin, eve::valmax)
                              , eve::test::logicals(0,3))
        )
<typename T,  typename M>(T const& a0,  M const & t)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  auto m =  [](auto x) -> v_t {int n; return std::frexp(x, &n)*2; };
  TTS_EQUAL( eve::mantissa(a0), map(m, a0));
  TTS_EQUAL( eve::mantissa[t](a0), eve::if_else(t, eve::mantissa(a0), a0));
};

EVE_TEST_TYPES( "Check behavior of mantissa on wide"
        , eve::test::simd::ieee_reals
        )
<typename T>(eve::as<T>)
{
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_EQUAL(eve::mantissa(eve::inf(eve::as<T>()))      , eve::inf(eve::as<T>()) );
    TTS_EQUAL(eve::mantissa(eve::minf(eve::as<T>()))     , eve::minf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::mantissa(eve::nan(eve::as<T>())) , eve::nan(eve::as<T>()) );
  }
  TTS_EQUAL(eve::mantissa(T(-1  )), T(-1    ));
  TTS_EQUAL(eve::mantissa(T( 1  )), T( 1    ));
  TTS_EQUAL(eve::mantissa(T( 0  )), T( 0    ));
  TTS_EQUAL(eve::mantissa(T( 2  )), T( 1    ));
  TTS_EQUAL(eve::mantissa(T( 1.5)), T( 1.5  ));
  TTS_EQUAL(eve::mantissa(T( 2.5)), T( 1.25 ));
};
