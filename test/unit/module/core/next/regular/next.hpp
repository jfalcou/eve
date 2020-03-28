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
#include <tts/tests/relation.hpp>
#include <tts/tests/precision.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/eps.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mzero.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_negative.hpp>
#include <eve/function/is_positive.hpp>    
#include <type_traits>

TTS_CASE("Check next return type")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using u_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>;
  using si_t = eve::detail::as_integer_t<EVE_VALUE, signed>;
  using su_t = eve::detail::as_integer_t<EVE_VALUE, unsigned>;

  TTS_EXPR_IS(eve::next(EVE_TYPE()), (EVE_TYPE));
  TTS_EXPR_IS((eve::next(EVE_TYPE(), i_t())), (EVE_TYPE));
  TTS_EXPR_IS((eve::next(EVE_TYPE(), u_t())), (EVE_TYPE));  
  TTS_EXPR_IS((eve::next(EVE_TYPE(), si_t())), (EVE_TYPE));
  TTS_EXPR_IS((eve::next(EVE_TYPE(), su_t())), (EVE_TYPE));  
}

TTS_CASE("Check eve::next one parameter behavior")
{
  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::next(EVE_TYPE{0}), EVE_TYPE(1));
    TTS_EQUAL(eve::next(EVE_TYPE{1}), EVE_TYPE(2));
    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL(eve::next(EVE_TYPE(-1)), EVE_TYPE(0));
      TTS_EQUAL(eve::next(EVE_TYPE(-2)), EVE_TYPE(-1));
    }
  }
  else
  {
    TTS_IEEE_EQUAL(eve::next(eve::Inf<EVE_TYPE>()), (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Valmax<EVE_TYPE>())  , (eve::Inf<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Minf<EVE_TYPE>())    , (eve::Valmin<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mone<EVE_TYPE>())    , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()/2));
    TTS_EQUAL(eve::next(eve::One<EVE_TYPE>())     , (eve::One<EVE_TYPE>()+eve::Eps<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mzero<EVE_TYPE>())   , (eve::Zero<EVE_TYPE>()));
    TTS_EXPECT(eve::all(eve::is_positive(eve::next(eve::Mzero<EVE_TYPE>())))); 
    TTS_EQUAL(eve::next(-eve::Mindenormal<EVE_TYPE>())   , (eve::Mzero<EVE_TYPE>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::next(-eve::Mindenormal<EVE_TYPE>())))); 
    TTS_EQUAL(eve::next(eve::Zero<EVE_TYPE>())    , (eve::Mindenormal<EVE_TYPE>()));
  }
}

TTS_CASE("Check eve::next two parameters behavior")
{
  using i_t = eve::detail::as_integer_t<EVE_TYPE, signed>;
  using si_t = eve::detail::as_integer_t<EVE_VALUE, signed>;

  if constexpr(std::is_integral_v<EVE_VALUE>)
  {
    TTS_EQUAL(eve::next(EVE_TYPE{0}, i_t(0)), EVE_TYPE(0));          
    TTS_EQUAL(eve::next(EVE_TYPE{0}, i_t(2)), EVE_TYPE(2));
    TTS_EQUAL(eve::next(EVE_TYPE{1}, i_t(2)), EVE_TYPE(3));
    TTS_EQUAL(eve::next(EVE_TYPE{0}, si_t(0)),EVE_TYPE(0));          
    TTS_EQUAL(eve::next(EVE_TYPE{0}, si_t(2)),EVE_TYPE(2));
    TTS_EQUAL(eve::next(EVE_TYPE{1}, si_t(2)),EVE_TYPE(3));
    
    TTS_EQUAL(eve::next(EVE_VALUE{0}, i_t(0)), EVE_TYPE(0));
    TTS_EQUAL(eve::next(EVE_VALUE{0}, i_t(2)), EVE_TYPE(2));
    TTS_EQUAL(eve::next(EVE_VALUE{1}, i_t(2)), EVE_TYPE(3));

    if constexpr(std::is_signed_v<EVE_VALUE>)
    {
      TTS_EQUAL(eve::next(EVE_TYPE(-1), i_t(2)), EVE_TYPE(1));
      TTS_EQUAL(eve::next(EVE_TYPE(-2), i_t(2)), EVE_TYPE(0));
      TTS_EQUAL(eve::next(EVE_TYPE(-1), si_t(2)),EVE_TYPE(1));
      TTS_EQUAL(eve::next(EVE_TYPE(-2), si_t(2)),EVE_TYPE(0));

      TTS_EQUAL(eve::next(EVE_VALUE(-1), i_t(2)), EVE_TYPE(1));
      TTS_EQUAL(eve::next(EVE_VALUE(-2), i_t(2)), EVE_TYPE(0));
    }
  }
  else
  {
    TTS_IEEE_EQUAL(eve::next(eve::Inf<EVE_TYPE>(), i_t(2))   , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::next(eve::Valmax<EVE_TYPE>(), i_t(2)), (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mone<EVE_TYPE>(), i_t(2))       , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::One<EVE_TYPE>(), i_t(2))        , (eve::One<EVE_TYPE>()+eve::Eps<EVE_TYPE>()*2));
    
    TTS_IEEE_EQUAL(eve::next(eve::Inf<EVE_TYPE>(), si_t(2))   , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::next(eve::Valmax<EVE_TYPE>(), si_t(2)), (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mone<EVE_TYPE>(), si_t(2))       , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::One<EVE_TYPE>(), si_t(2))        , (eve::One<EVE_TYPE>()+eve::Eps<EVE_TYPE>()*2));
    
    TTS_IEEE_EQUAL(eve::next(eve::Inf<EVE_VALUE>(), i_t(2))   , (eve::Nan<EVE_TYPE>()));
    TTS_IEEE_EQUAL(eve::next(eve::Valmax<EVE_VALUE>(), i_t(2)), (eve::Nan<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mone<EVE_VALUE>(), i_t(2))       , (eve::Mone<EVE_TYPE>()+eve::Eps<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::One<EVE_VALUE>(), i_t(2))        , (eve::One<EVE_TYPE>()+eve::Eps<EVE_TYPE>()*2));

    TTS_EQUAL(eve::next(eve::Zero<EVE_TYPE>(), 1)             , (eve::Mindenormal<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mzero<EVE_TYPE>(), 1)            , (eve::Zero<EVE_TYPE>()));
    TTS_EXPECT(eve::all(eve::is_positive(eve::next(eve::Zero<EVE_TYPE>(), 1) ))); 
    TTS_EQUAL(eve::next(eve::Mzero<EVE_TYPE>(), 2)            , (eve::Mindenormal<EVE_TYPE>()));
    TTS_EQUAL(eve::next(-eve::Mindenormal<EVE_TYPE>(), 3)     , (eve::Mindenormal<EVE_TYPE>()));
    TTS_EQUAL(eve::next(-eve::Mindenormal<EVE_TYPE>(), 2)     , (eve::Zero<EVE_TYPE>()));
    TTS_EQUAL(eve::next(-eve::Mindenormal<EVE_TYPE>(), 1)     , (eve::Mzero<EVE_TYPE>()));
    TTS_EXPECT(eve::all(eve::is_negative(eve::next(-eve::Mindenormal<EVE_TYPE>(), 1) ))); 
    TTS_EXPECT(eve::all(eve::is_positive(eve::next(-eve::Mindenormal<EVE_TYPE>(), 2) )));

    TTS_EQUAL(eve::next(eve::Zero<EVE_TYPE>(), 0)             , (eve::Zero<EVE_TYPE>()));
    TTS_EQUAL(eve::next(eve::Mzero<EVE_TYPE>(), 0)            , (eve::Mzero<EVE_TYPE>()));
    TTS_EXPECT(eve::all(eve::is_positive(eve::next(eve::Zero<EVE_TYPE>(), 0) )));
    TTS_EXPECT(eve::all(eve::is_negative(eve::next(eve::Mzero<EVE_TYPE>(), 0) )));    
    
  }
}
