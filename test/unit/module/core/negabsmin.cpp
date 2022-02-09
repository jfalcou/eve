/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <algorithm>
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of negabsmin"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::negabsmin(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::negabsmin(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::negabsmin(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::negabsmin(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::negabsmin(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::negabsmin(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::negabsmin(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::negabsmin(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmin(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmin(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmin(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmin(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmin(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmin(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negabsmin tests
//==================================================================================================

EVE_TEST( "Check behavior of negabsmin on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::negabsmin;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;

  auto m = [](auto a, auto b, auto c)-> v_t {return -eve::abs(eve::min(a, b, c)); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == a? -eve::sign(a) : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == b? -eve::sign(b) : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::min(a, b, c) == c? -eve::sign(c) : 0;  };
  TTS_ULP_EQUAL(negabsmin((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(negabsmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (negabsmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(negabsmin)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(negabsmin)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(negabsmin)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(negabsmin)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
  TTS_IEEE_EQUAL(negabsmin[t](a0, a1), eve::if_else(t, negabsmin(a0, a1), a0));
 };

EVE_TEST_TYPES( "Check values of negabsmin"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(T(1)  , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(v_t(1), eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmin)(T(1)  , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmin)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmin)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)((eve::nan(eve::as<T>()) ) , T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)((eve::nan(eve::as<v_t>())), T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(-1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)(T(1)   , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)(v_t(1) , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmin)(T(1)   , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmin)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmin)(T( 0 ), T(-0.)))));
};
