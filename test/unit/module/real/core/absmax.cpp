/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/max.hpp>
#include <eve/function/absmax.hpp>
#include <eve/function/pedantic/absmax.hpp>
#include <eve/function/numeric/absmax.hpp>
#include <eve/function/saturated/absmax.hpp>
#include <eve/function/diff/absmax.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/is_positive.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of absmax"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::absmax(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::absmax(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::absmax(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::absmax(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::absmax(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::absmax(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::absmax(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::absmax(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::absmax(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::absmax(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::absmax(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::absmax(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::absmax(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::absmax(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// absmax tests
//==================================================================================================

EVE_TEST( "Check behavior of absmax on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::absmax;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return eve::abs(eve::max(a, b, c)); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == a? eve::sign(a) : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == b? eve::sign(b) : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == c? eve::sign(c) : 0;  };
  TTS_ULP_EQUAL(absmax((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(absmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (absmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(absmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(absmax)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(absmax)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(absmax)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
  TTS_IEEE_EQUAL(absmax[t](a0, a1), eve::if_else(t, absmax(a0, a1), a0));
};

EVE_TEST_TYPES( "Check values of absmax"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmax)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::absmax)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::absmax)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmax)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::absmax)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::absmax)(T( 0 ), T(-0.)))));
};
