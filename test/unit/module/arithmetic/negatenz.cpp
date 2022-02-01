//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/minf.hpp>
#include <eve/module/core/constant/nan.hpp>
#include <eve/module/core/constant/inf.hpp>
#include <eve/function/negatenz.hpp>
#include <eve/function/signnz.hpp>
#include <eve/function/diff/negatenz.hpp>

//==================================================================================================
//== Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of negatenz"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  //regular
  TTS_EXPR_IS( eve::negatenz(T(), T()  ) , T);
  TTS_EXPR_IS( eve::negatenz(T(), v_t()) , T);
  TTS_EXPR_IS( eve::negatenz(v_t(), T()) , T);
  if constexpr(eve::floating_value<T>)
  {
    TTS_EXPR_IS( eve::negatenz(T(),int()) , T);
    TTS_EXPR_IS( eve::negatenz(int(), T()) , T);
  }
  TTS_EXPR_IS( eve::negatenz(v_t(), v_t()) , v_t);
};

//==================================================================================================
//== negatenz tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of negatenz"
        , eve::test::simd::all_types
        )
<typename T>(eve::as<T>)
{
 if constexpr(eve::floating_value<T>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(eve::negatenz(eve::inf(eve::as<T>()) , eve::inf(eve::as<T>()) ), eve::inf(eve::as<T>()));
      TTS_EQUAL(eve::negatenz(eve::minf(eve::as<T>()), eve::minf(eve::as<T>())), eve::inf(eve::as<T>()));

      TTS_IEEE_EQUAL(eve::negatenz(eve::nan(eve::as<T>()), eve::nan(eve::as<T>()) ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negatenz(eve::nan(eve::as<T>()), T(0)          ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negatenz(eve::nan(eve::as<T>()), T(0)          ), eve::nan(eve::as<T>()));
      TTS_IEEE_EQUAL(eve::negatenz(eve::nan(eve::as<T>()), T(1)          ), eve::nan(eve::as<T>()));
    }

    TTS_EQUAL(eve::negatenz(T(-1), T(-1)), T( 1));
    TTS_EQUAL(eve::negatenz(T( 1), T( 1)), T( 1));
    TTS_EQUAL(eve::negatenz(T( 0), T( 0)), T( 0));
    TTS_EQUAL(eve::negatenz(T( 1), T( 0)), T( 1));
    TTS_EQUAL(eve::negatenz(T( 2), T(-3)), T(-2));
    TTS_EQUAL(eve::negatenz(T( 2), T( 3)), T( 2));
  }
  else if constexpr(eve::signed_value<T>)
  {
    TTS_EQUAL(eve::negatenz(T(-1), T(-1)), T( 1));
    TTS_EQUAL(eve::negatenz(T(-1), T( 1)), T(-1));
  }

  TTS_EQUAL(eve::negatenz(T(1), T(1)), T(1));
  TTS_EQUAL(eve::negatenz(T(0), T(0)), T(0));
  TTS_EQUAL(eve::negatenz(T(1), T(0)), T(1));
};


EVE_TEST( "Check behavior of negatenz(wide)"
            , eve::test::simd::all_types
            , eve::test::generate ( eve::test::randoms(eve::valmin, eve::valmax)
                                  , eve::test::randoms(eve::valmin, eve::valmax)
                                  )
            )
<typename T>(T const& a0, T const& a1 )
{
  using eve::negatenz;
  using eve::detail::map;
  using v_t = eve::element_type_t<T>;
  TTS_ULP_EQUAL( negatenz(a0, a1), map([](auto e, auto f) -> v_t { return e*eve::signnz(f); }, a0, a1), 2);
  if constexpr(eve::floating_value<T>)
  {
    TTS_ULP_EQUAL( eve::diff_1st(negatenz)(a0, a1), eve::signnz(a1), 2);
    TTS_ULP_EQUAL( eve::diff_2nd(negatenz)(a0, a1), eve::zero(eve::as(a0)), 2);
  }
};
