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
EVE_TEST_TYPES( "Check return types of maxabs"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::maxabs(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::maxabs(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::maxabs(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::maxabs(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::maxabs(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::maxabs(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::maxabs(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::maxabs(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxabs(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxabs(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxabs(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::maxabs(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::maxabs(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::maxabs(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// maxabs tests
//==================================================================================================

EVE_TEST( "Check behavior of maxabs on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::maxabs;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return eve::max(eve::abs(a), eve::abs(b), eve::abs(c)); };
  auto dm1 = [](auto a, auto b, auto c)-> v_t {return eve::maxabs(a, b, c) == eve::abs(a)? eve::sign(a) : 0;  };
  auto dm2 = [](auto a, auto b, auto c)-> v_t {return eve::maxabs(a, b, c) == eve::abs(b)? eve::sign(b) : 0;  };
  auto dm3 = [](auto a, auto b, auto c)-> v_t {return eve::maxabs(a, b, c) == eve::abs(c)? eve::sign(c) : 0;  };
  TTS_ULP_EQUAL(maxabs((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(maxabs)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_1st(maxabs)((a0), (a1), (a2)), map(dm1, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_2nd(maxabs)((a0), (a1), (a2)), map(dm2, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::diff_3rd(maxabs)((a0), (a1), (a2)), map(dm3, a0, a1, a2), 2);
  TTS_IEEE_EQUAL(maxabs[t](a0, a1), eve::if_else(t, maxabs(a0, a1), a0));
};

EVE_TEST_TYPES( "Check values of maxabs"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::maxabs)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxabs)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::maxabs)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::maxabs)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxabs)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::maxabs)(T( 0 ), T(-0.)))));
};
