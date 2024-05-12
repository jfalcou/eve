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
TTS_CASE_TPL( "Check return types of max"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS( eve::max(T(), T(), T()  )  , T);
  TTS_EXPR_IS( eve::max(T(), v_t(), T())  , T);
  TTS_EXPR_IS( eve::max(v_t(), T(), T())  , T);
  TTS_EXPR_IS( eve::max(T(), T(), v_t() ) , T);
  TTS_EXPR_IS( eve::max(v_t(), v_t(), T()) , T);
  TTS_EXPR_IS( eve::max(v_t(), T(), v_t()) , T);
  TTS_EXPR_IS( eve::max(v_t(), v_t(), v_t()) , v_t);
  TTS_EXPR_IS(eve::max(  T(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::max(  T(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::max(  T(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::max(  T(), v_t(), v_t()), T  );
  TTS_EXPR_IS(eve::max(v_t(),   T(),   T()), T  );
  TTS_EXPR_IS(eve::max(v_t(),   T(), v_t()), T  );
  TTS_EXPR_IS(eve::max(v_t(), v_t(),   T()), T  );
  TTS_EXPR_IS(eve::max(v_t(), v_t(), v_t()), v_t);
};

//==================================================================================================
// max tests
//==================================================================================================

TTS_CASE_WITH( "Check behavior of max on all types full range"
        , eve::test::simd::all_types
        , tts::generate (  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::randoms(eve::valmin, eve::valmax)
                              ,  tts::logicals(0, 3)
                             )
        )
<typename T, typename M>(  T const& a0, T const& a1, T const& a2, M const & t)
{
  using eve::max;
  using eve::detail::map;
  using eve::abs;
  using v_t = eve::element_type_t<T>;
  auto m = [](auto a, auto b, auto c)-> v_t {return std::max(std::max(a, b), c); };
  TTS_ULP_EQUAL(max((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::pedantic(max)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);
  TTS_ULP_EQUAL(eve::numeric (max)((a0), (a1), (a2)), map(m, a0, a1, a2), 2);



  TTS_IEEE_EQUAL(max[t](a0, a1), eve::if_else(t, max(a0, a1), a0));
};

TTS_CASE_TPL( "Check values of max"
              , eve::test::simd::ieee_reals
              )
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(eve::nan(eve::as<T>())   , T(1)  ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(eve::nan(eve::as<v_t>()) , T(1)  ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(eve::nan(eve::as<T>())   , v_t(1)) , eve::nan(eve::as<T>()) );

    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(T(1)  , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(v_t(1), eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::pedantic(eve::max)(T(1)  , eve::nan(eve::as<v_t>()) ), T(1) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::max)(T(-0.), T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::pedantic(eve::max)(T( 0 ), T(-0.)))));

    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<T>()) ) , T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<v_t>())), T(1))  , T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)((eve::nan(eve::as<T>()) ) , v_t(1)) , T(1) );

    TTS_IEEE_EQUAL(eve::numeric(eve::max)(T(1)   , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)(v_t(1) , eve::nan(eve::as<T>())   ), T(1) );
    TTS_IEEE_EQUAL(eve::numeric(eve::max)(T(1)   , eve::nan(eve::as<v_t>()) ), T(1) );

    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::max)(T(-0.), T( 0 )))));
    TTS_EXPECT(eve::all(eve::is_positive(eve::numeric(eve::max)(T( 0 ), T(-0.)))));
};
