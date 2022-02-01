/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/constant/valmax.hpp>
#include <eve/module/core/constant/valmin.hpp>
#include <eve/module/core/constant/mone.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/min.hpp>
#include <eve/function/minabs.hpp>
#include <eve/function/pedantic/minabs.hpp>
#include <eve/function/numeric/minabs.hpp>
#include <eve/function/saturated/minabs.hpp>
#include <eve/function/diff/minabs.hpp>
#include <eve/function/negminabs.hpp>
#include <eve/function/pedantic/negminabs.hpp>
#include <eve/function/numeric/negminabs.hpp>
#include <eve/function/saturated/negminabs.hpp>
#include <eve/function/diff/negminabs.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/is_negative.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of negminabs"
              , eve::test::simd::signed_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::negminabs(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::negminabs(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::negminabs(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::negminabs(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::negminabs(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::negminabs(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::negminabs(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::negminabs(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negminabs(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negminabs(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negminabs(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::negminabs(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::negminabs(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::negminabs(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
//== negminabs tests
//==================================================================================================

EVE_TEST( "Check behavior of negminabs on all types full range"
        , eve::test::simd::signed_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::logicals(0, 3)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::negminabs;
  using eve::detail::map;
  using eve::abs;

  TTS_ULP_EQUAL(negminabs((a0), (a1), (a2)), -eve::minabs(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(negminabs)((a0), (a1), (a2)),  -eve::pedantic(eve::minabs)(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (negminabs)((a0), (a1), (a2)),  -eve::numeric(eve::minabs)(a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::saturated(negminabs)((a0), (a1), (a2)), -eve::saturated(eve::minabs)(a0, a1, a2) , 2);
  TTS_ULP_EQUAL(eve::diff_1st(negminabs)((a0), (a1), (a2)),  -eve::diff_1st(eve::minabs)(a0, a1, a2) , 2);
  TTS_ULP_EQUAL(eve::diff_2nd(negminabs)((a0), (a1), (a2)),  -eve::diff_2nd(eve::minabs)(a0, a1, a2) , 2);
  TTS_ULP_EQUAL(eve::diff_3rd(negminabs)((a0), (a1), (a2)),  -eve::diff_3rd(eve::minabs)(a0, a1, a2), 2);
  TTS_IEEE_EQUAL(negminabs[t](a0, a1), eve::if_else(t, negminabs(a0, a1), a0));
 };

EVE_TEST_TYPES( "Check values of negminabs"
              , eve::test::simd::ieee_reals
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(T(1)  , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(v_t(1), eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::pedantic(eve::negminabs)(T(1)  , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negminabs)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::pedantic(eve::negminabs)(T( 0 ), T(-0.)))));

  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)((eve::nan(eve::as<T>()) ) , T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)((eve::nan(eve::as<v_t>())), T(1))  , T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(-1) );

  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)(T(1)   , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)(v_t(1) , eve::nan(eve::as<T>())   ), T(-1) );
  TTS_IEEE_EQUAL(eve::numeric(eve::negminabs)(T(1)   , eve::nan(eve::as<v_t>()) ), T(-1) );

  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negminabs)(T(-0.), T( 0 )))));
  TTS_EXPECT(eve::all(eve::is_negative(eve::numeric(eve::negminabs)(T( 0 ), T(-0.)))));
};
