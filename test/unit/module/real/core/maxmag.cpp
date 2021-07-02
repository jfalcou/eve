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
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic/maxmag.hpp>
#include <eve/function/numeric/maxmag.hpp>
#include <eve/function/saturated/maxmag.hpp>
#include <eve/function/diff/maxmag.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/is_positive.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of maxmag"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::maxmag(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::maxmag(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::maxmag(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::maxmag(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::maxmag(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::maxmag(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::maxmag(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::maxmag(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxmag(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// maxmag tests
//==================================================================================================

EVE_TEST( "Check behavior of maxmag on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T>(  T const& a0, T const& a1, T const& a2)
{
  using eve::maxmag;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return maxmag(maxmag(a, b), c); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::maxmag(a, b, c) == a? 1 : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::maxmag(a, b, c) == b? 1 : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::maxmag(a, b, c) == c? 1 : 0;  };
  TTS_ULP_EQUAL(maxmag((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(maxmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (maxmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(maxmag)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(maxmag)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(maxmag)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(maxmag)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
};

EVE_TEST_TYPES( "Check values of maxmag"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxmag)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxmag)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxmag)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxmag)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxmag)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxmag)(T( 0 ), T(-0.)))));
};
