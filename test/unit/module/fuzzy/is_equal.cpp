//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/function/is_equal.hpp>
#include <eve/function/numeric/is_equal.hpp>
#include <eve/function/fuzzy/is_equal.hpp>
#include <eve/constant/eps.hpp>
#include <eve/logical.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of almost(is_equal)"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using eve::logical;
  using v_t =  eve::element_type_t<T>;
  TTS_EXPR_IS( eve::almost(eve::is_equal)(T(), T())     , logical<T>   );
  TTS_EXPR_IS( eve::almost(eve::is_equal)(v_t(), v_t()) , logical<v_t> );
  TTS_EXPR_IS( eve::almost(eve::is_equal)(T(), v_t())   , logical<T> );
  TTS_EXPR_IS( eve::almost(eve::is_equal)(v_t(), T())   , logical<T> );
};


//==================================================================================================
//== Tests for almost(is_equal) corner cases for floating
//==================================================================================================
EVE_TEST( "Check behavior of eve::is_equal(simd)"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::limits())
        )
<typename aT>(aT const& )
{
  using T = typename aT::type;
  using eve::detail::map;
  using eve::as;
  using v_t = eve::element_type_t<T>;
  using ui_t = eve::as_integer_t<T, unsigned>;

  TTS_EQUAL(eve::almost(eve::is_equal)(T(1+eve::eps(as<T>()))  , T(1)                  , eve::eps(as<T>()))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(T(1+2*eve::eps(as<T>())), T(1)                  , eve::eps(as<T>()))   , eve::false_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(T(1+eve::eps(as<T>()))  , v_t(1)                , eve::eps(as<T>()))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(T(3)                    , T(1)                  , eve::eps(as<T>()))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_equal)(T(3)                    , v_t(1)                , eve::eps(as<T>()))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_equal)(T(1)                    , T(1)                  , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(T(1)                    , v_t(1)                , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(T(3)                    , T(1)                  , ui_t(3))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_equal)(T(3)                    , v_t(1)                , ui_t(3))   , eve::false_(eve::as<T>()));
  auto md = eve::mindenormal(eve::as<v_t>());
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(md)                 , T(0)                  , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(2*md)               , T(0)                  , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(3*md)               , T(0)                  , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(4*md)               , T(0)                  , ui_t(3))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(1)                  , v_t(1)                , ui_t(3))   , eve::true_(eve::as<T>()) );
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(3)                  , T(1)                  , ui_t(3))   , eve::false_(eve::as<T>()));
  TTS_EQUAL(eve::almost(eve::is_equal)(v_t(3)                  , v_t(1)                , ui_t(3))   , eve::false_(eve::as<T>()));
};
