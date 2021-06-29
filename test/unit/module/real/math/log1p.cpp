//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/concept/value.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/diff/log1p.hpp>
#include <eve/function/inc.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of log1p"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::log1p(T())  , T);
  TTS_EXPR_IS( eve::log1p(v_t()), v_t);
};

//==================================================================================================
// log1p  tests
//==================================================================================================
EVE_TEST( "Check behavior of log1p on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0.0, eve::valmax)
                             , eve::test::randoms(0.5, 2.0))
        )
<typename T>(T const& a0, T const& a1)
{
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;

  TTS_ULP_EQUAL(eve::log1p(a0)      , map([](auto e) -> v_t { return std::log1p(e); }, a0), 2);
  TTS_ULP_EQUAL(eve::log1p(a1)      , map([](auto e) -> v_t { return std::log1p(e); }, a1), 2);
  TTS_ULP_EQUAL(eve::diff(eve::log1p)(a0), eve::rec(eve::inc(a0)), 2);
  TTS_ULP_EQUAL(eve::diff(eve::log1p)(a1), eve::rec(eve::inc(a1)), 2);
};

EVE_TEST_TYPES( "Check return types of log1p"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  if constexpr(eve::platform::supports_invalids)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::inf(eve::as<T>()))  , eve::inf(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::nan(eve::as<T>()))  , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::log1p(eve::mone(eve::as<T>())) , eve::minf(eve::as<T>()));
    TTS_IEEE_EQUAL(eve::log1p(T( 0 ))         , T( 0 )        );
  }
  if constexpr(eve::platform::supports_denormals)
  {
    TTS_IEEE_EQUAL(eve::log1p(eve::mindenormal(eve::as<T>())), T(std::log1p(eve::mindenormal(eve::as<v_t>()))));
  }

  auto epsi = eve::eps(eve::as<T>());

  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(1))                    , eve::log_2(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::log1p(T(0))                    , T(0)                    , 0.5 );
  TTS_ULP_EQUAL(eve::log1p(eve::smallestposval(eve::as<T>())), eve::smallestposval(eve::as<T>()), 0.5 );
  TTS_ULP_EQUAL(eve::log1p(epsi)                    , epsi                    , 0.5 );
};
