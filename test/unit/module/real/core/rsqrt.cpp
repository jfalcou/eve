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
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/function/rsqrt.hpp>
#include <eve/function/pedantic/rsqrt.hpp>
#include <eve/function/diff/rsqrt.hpp>
#include <cmath>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of rsqrt"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::rsqrt(T())  , T);
  TTS_EXPR_IS( eve::rsqrt(v_t()), v_t);
  TTS_EXPR_IS( eve::pedantic(eve::rsqrt)(T())  , T);
  TTS_EXPR_IS( eve::pedantic(eve::rsqrt)(v_t()), v_t);
  TTS_EXPR_IS( eve::diff(eve::rsqrt)(T())  , T);
  TTS_EXPR_IS( eve::diff(eve::rsqrt)(v_t()), v_t);
};

//==================================================================================================
//== rsqrt  tests
//==================================================================================================
EVE_TEST( "Check behavior of rsqrt on wide"
        , eve::test::simd::ieee_reals
        , eve::test::generate(eve::test::randoms(0, eve::valmax))
        )
<typename T>(T const& a0 )
{
  using v_t = eve::element_type_t<T>;
  auto st = [](auto e)-> v_t {return eve::rec(std::sqrt(e)); };
  auto dst= [](auto e)-> v_t {return v_t(-1.5)/(std::sqrt(e)*e); };
  TTS_ULP_EQUAL( eve::rsqrt(a0), map(st, a0), 2);
  TTS_ULP_EQUAL( eve::pedantic(eve::rsqrt)(a0), map(st, a0), 2);
  TTS_ULP_EQUAL( eve::diff(eve::rsqrt)(a0), map(dst, a0), 2);
};

EVE_TEST_TYPES( "Check return types of rsqrt"
            , eve::test::simd::ieee_reals
            )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  auto z = eve::mindenormal(eve::as<v_t>());

  TTS_IEEE_EQUAL((eve::pedantic(eve::rsqrt)(eve::nan(eve::as<T>()))) , (eve::nan(eve::as<T>())));
  TTS_EQUAL(eve::pedantic(eve::rsqrt)((T(0)))               , eve::inf(eve::as<T>()));
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(eve::mindenormal(eve::as<T>()))   , T(eve::rec(std::sqrt(z)))   , 2.0);
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)(2*eve::mindenormal(eve::as<T>())) , T(eve::rec(std::sqrt(2*z))) , 2.0);
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)((z))   , (eve::rec(std::sqrt(z)))   , 2.0);
  TTS_ULP_EQUAL(eve::pedantic(eve::rsqrt)((2*z)) , (eve::rec(std::sqrt(2*z))) , 2.0);
};
