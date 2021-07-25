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
#include <eve/function/bound.hpp>
#include <eve/function/pedantic/bound.hpp>
#include <eve/function/numeric/bound.hpp>
#include <eve/function/saturated/bound.hpp>
#include <eve/function/diff/bound.hpp>
#include <eve/function/sign.hpp>
#include <eve/function/is_positive.hpp>
#include <algorithm>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of bound"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::bound(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::bound(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::bound(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::bound(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::bound(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::bound(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::bound(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::bound(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::bound(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::bound(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::bound(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::bound(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::bound(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::bound(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::bound(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// bound tests
//==================================================================================================

EVE_TEST( "Check behavior of bound on all types full range"
        , eve::test::simd::all_types
        , eve::test::generate (  eve::test::randoms(eve::valmin, eve::valmax)
                              ,  eve::test::randoms(eve::valmin, eve::valmax)
                              )
        )
<typename T, typename M>(  T const& a0, T const& a1)
{
  using eve::bound;
  using eve::detail::map;
  using eve::ctrl_range;
  TTS_IEEE_EQUAL(bound(a0, a1, ctrl_range::max, ctrl_range::sign_from_cmp), eve::max(a0, a1));
};
