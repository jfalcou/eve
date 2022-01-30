/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>
#include <eve/module/arithmetic.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of absmin"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::absmin(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::absmin(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::absmin(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::absmin(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::absmin(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::absmin(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::absmin(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::absmin(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::absmin(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::absmin(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::absmin(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::absmin(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::absmin(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::absmin(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::absmin(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// absmin tests
//==================================================================================================

EVE_TEST( "Check behavior of absmin on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::absmin;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;

  auto m = [](auto a, auto b, auto c)-> v_t {return eve::abs(eve::min(a, b, c)); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == a? eve::sign(a) : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == b? eve::sign(b) : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == c? eve::sign(c) : 0;  };
  TTS_ULP_EQUAL(absmin((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(absmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (absmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(absmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(absmin)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(absmin)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(absmin)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
  TTS_IEEE_EQUAL(absmin[t](a0, a1), eve::if_else(t, absmin(a0, a1), a0));
 };

EVE_TEST_TYPES( "Check values of absmin"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::absmin)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::absmin)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::absmin)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::absmin)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::absmin)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::absmin)(T( 0 ), T(-0.)))));
};
