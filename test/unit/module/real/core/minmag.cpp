/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/mone.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/minmag.hpp>
#include <eve/function/pedantic/minmag.hpp>
#include <eve/function/numeric/minmag.hpp>
#include <eve/function/saturated/minmag.hpp>
#include <eve/function/diff/minmag.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/is_negative.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of minmag"
              , eve::test::simd::all_types
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::minmag(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::minmag(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::minmag(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::minmag(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::minmag(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::minmag(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::minmag(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::minmag(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::minmag(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// minmag tests
//==================================================================================================

EVE_TEST( "Check behavior of minmag on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmin)
                              ,  eve::test::randoms(eve::valmin, eve::valmin)
                              ,  eve::test::randoms(eve::valmin, eve::valmin)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::minmag;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return minmag(minmag(a, b), c); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::minmag(a, b, c) == a? 1 : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::minmag(a, b, c) == b? 1 : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::minmag(a, b, c) == c? 1 : 0;  };
  TTS_ULP_EQUAL(minmag((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(minmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(minmag)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(minmag)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(minmag)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
};

EVE_TEST_TYPES( "Check values of minmag"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as_<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::minmag)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::minmag)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::minmag)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::minmag)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::minmag)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::minmag)(T( 0 ), T(-0.)))));
};
