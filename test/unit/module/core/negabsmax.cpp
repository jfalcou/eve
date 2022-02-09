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
EVE_TEST_TYPES( "Check return types of negabsmax"
              , eve::test::simd::signed_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( eve::negabsmax(T(), T()  )  , T);
  TTS_EXPR_IS( eve::negabsmax(T(), v_t())  , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), T())  , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), v_t()) ,v_t );

  TTS_EXPR_IS( eve::negabsmax(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::negabsmax(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::negabsmax(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::negabsmax(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::negabsmax(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmax(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmax(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmax(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmax(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmax(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negabsmax(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negabsmax tests
//==================================================================================================

EVE_TEST( "Check behavior of negabsmax on all types full range"
        , eve::test::simd::signed_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::negabsmax;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;

  auto m = [](auto a, auto b, auto c)-> v_t {return -eve::abs(eve::max(a, b, c)); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == a? -eve::sign(a) : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == b? -eve::sign(b) : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::max(a, b, c) == c? -eve::sign(c) : 0;  };
  TTS_ULP_EQUAL(negabsmax((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(negabsmax)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(negabsmax)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(negabsmax)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(negabsmax)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
  TTS_IEEE_EQUAL(negabsmax[t](a0, a1), eve::if_else(t, negabsmax(a0, a1), a0));
 };

EVE_TEST_TYPES( "Check values of negabsmax"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(T(1)  , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(v_t(1), eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negabsmax)(T(1)  , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmax)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negabsmax)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<T>()) ) , T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<v_t>())), T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(-1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(T(1)   , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(v_t(1) , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negabsmax)(T(1)   , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmax)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negabsmax)(T( 0 ), T(-0.)))));
};
