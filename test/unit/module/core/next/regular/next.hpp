//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/next.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/nan.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>

TTS_CASE_TPL("Check next return type", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::detail::as_integer_t<  T, signed>;
  using u_t   = eve::detail::as_integer_t<  T, unsigned>;
  using si_t  = eve::detail::as_integer_t<v_t, signed>;
  using su_t  = eve::detail::as_integer_t<v_t, unsigned>;

  TTS_EXPR_IS(eve::next(T())        , T);
  TTS_EXPR_IS(eve::next(T(), i_t()) , T);
  TTS_EXPR_IS(eve::next(T(), u_t()) , T);
  TTS_EXPR_IS(eve::next(T(), si_t()), T);
  TTS_EXPR_IS(eve::next(T(), su_t()), T);
}

TTS_CASE_TPL("Check eve::next one parameter behavior", EVE_TYPE)
{
  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::next(T(0)), T(1));
    TTS_EQUAL(eve::next(T(1)), T(2));

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::next(T(-1)), T( 0));
      TTS_EQUAL(eve::next(T(-2)), T(-1));
    }
  }
  else
  {
    TTS_IEEE_EQUAL(eve::next(eve::inf(eve::as<T>()))     , eve::nan(eve::as<T>())         );
    TTS_EQUAL(eve::next(eve::valmax(eve::as<T>()))       , eve::inf(eve::as<T>())         );
    TTS_EQUAL(eve::next(eve::minf(eve::as<T>()))         , eve::valmin(eve::as<T>())      );
    TTS_EQUAL(eve::next(T(-1))                  , T(-1)+eve::eps(eve::as<T>())/2 );
    TTS_EQUAL(eve::next(T(1))                   , T( 1)+eve::eps(eve::as<T>())   );
    TTS_EQUAL(eve::next(-eve::mindenormal(eve::as<T>())) , T(-0.)                );
    TTS_EQUAL(eve::next(T( 0 ))                 , eve::mindenormal(eve::as<T>()) );
    TTS_EQUAL(eve::next(T(-0.))                 , eve::mindenormal(eve::as<T>()) );
  }
}

TTS_CASE_TPL("Check eve::next two parameters behavior", EVE_TYPE)
{
  using v_t   = eve::element_type_t<T>;
  using i_t   = eve::detail::as_integer_t<T, signed>;
  using si_t  = eve::detail::as_integer_t<v_t, signed>;

  if constexpr(eve::integral_value<T>)
  {
    TTS_EQUAL(eve::next(T(0),  i_t(0)), T(0));
    TTS_EQUAL(eve::next(T(0),  i_t(2)), T(2));
    TTS_EQUAL(eve::next(T(1),  i_t(2)), T(3));
    TTS_EQUAL(eve::next(T(0), si_t(0)), T(0));
    TTS_EQUAL(eve::next(T(0), si_t(2)), T(2));
    TTS_EQUAL(eve::next(T(1), si_t(2)), T(3));

    TTS_EQUAL(eve::next(v_t(0), i_t(0)), T(0));
    TTS_EQUAL(eve::next(v_t(0), i_t(2)), T(2));
    TTS_EQUAL(eve::next(v_t(1), i_t(2)), T(3));

    if constexpr(eve::signed_value<T>)
    {
      TTS_EQUAL(eve::next(T(-1)   ,  i_t(2)), T(1));
      TTS_EQUAL(eve::next(T(-2)   ,  i_t(2)), T(0));
      TTS_EQUAL(eve::next(T(-1)   , si_t(2)), T(1));
      TTS_EQUAL(eve::next(T(-2)   , si_t(2)), T(0));
      TTS_EQUAL(eve::next(v_t(-1) ,  i_t(2)), T(1));
      TTS_EQUAL(eve::next(v_t(-2) ,  i_t(2)), T(0));
    }
  }
  else
  {
    TTS_IEEE_EQUAL(eve::next(eve::inf(eve::as<T>())      ,  i_t(2) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::next(eve::valmax(eve::as<T>())   ,  i_t(2) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::next(eve::inf(eve::as<T>())      , si_t(2) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::next(eve::valmax(eve::as<T>())   , si_t(2) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::next(eve::inf(eve::as<v_t>())    ,  i_t(2) ) , eve::nan(eve::as<T>()) );
    TTS_IEEE_EQUAL(eve::next(eve::valmax(eve::as<v_t>()) ,  i_t(2) ) , eve::nan(eve::as<T>()) );

    TTS_EQUAL(eve::next(  T(-1),  i_t(2)) , T(-1)+eve::eps(eve::as<T>())   );
    TTS_EQUAL(eve::next(  T( 1),  i_t(2)) , T( 1)+eve::eps(eve::as<T>())*2 );
    TTS_EQUAL(eve::next(  T(-1), si_t(2)) , T(-1)+eve::eps(eve::as<T>())   );
    TTS_EQUAL(eve::next(  T( 1), si_t(2)) , T( 1)+eve::eps(eve::as<T>())*2 );
    TTS_EQUAL(eve::next(v_t(-1),  i_t(2)) , T(-1)+eve::eps(eve::as<T>())   );
    TTS_EQUAL(eve::next(v_t( 1),  i_t(2)) , T( 1)+eve::eps(eve::as<T>())*2 );
    TTS_EQUAL(eve::next(  T( 0), 1      ) , eve::mindenormal(eve::as<T>()) );
    TTS_EQUAL(eve::next(  T(-0), 1      ) , eve::mindenormal(eve::as<T>()) );
    TTS_EQUAL(eve::next(  T( 0), 0      ) , T( 0 )                );
    TTS_EQUAL(eve::next(  T(-0), 0      ) , T(-0.)                );

    TTS_EQUAL(eve::next(-eve::mindenormal(eve::as<T>()), 1), T( 0 )        );
  }
}
