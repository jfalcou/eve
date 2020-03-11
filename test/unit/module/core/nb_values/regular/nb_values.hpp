//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/constant/mzero.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <tts/tests/relation.hpp>
#include <tts/tests/types.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/minf.hpp>  
#include <eve/constant/eps.hpp>
#include <eve/constant/nan.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mzero.hpp> 
#include <eve/function/inc.hpp>
#include <eve/function/dec.hpp>
#include <eve/function/is_odd.hpp>
#include <eve/function/is_even.hpp>
#include <eve/function/all.hpp>
#include <eve/function/nb_values.hpp>
#include <eve/function/unary_minus.hpp>
#include <type_traits>

TTS_CASE("Check eve::nb_values return type")
{
  using r_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>; 
  TTS_EXPR_IS((eve::nb_values(EVE_TYPE(0), EVE_TYPE(0))), (r_t));
}

TTS_CASE("Check eve::nb_values  behavior")
{
  using eve::nb_values; 
  TTS_EXPR_IS( nb_values(EVE_TYPE(), EVE_TYPE()), (eve::detail::as_integer_t<EVE_TYPE, unsigned>));
  using r_t = eve::detail::as_integer_t<EVE_TYPE, unsigned>; 
  if constexpr(std::is_floating_point_v<EVE_VALUE>)
  {
    if constexpr(eve::platform::supports_invalids)
    {
      TTS_EQUAL(nb_values(eve::Inf<EVE_TYPE>(), eve::Inf<EVE_TYPE>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Minf<EVE_TYPE>(), eve::Minf<EVE_TYPE>()), eve::Zero<r_t>());
      TTS_EQUAL(nb_values(eve::Nan<EVE_TYPE>(), eve::Nan<EVE_TYPE>()), eve::Valmax<r_t>());
    }
    
    TTS_EQUAL( nb_values(eve::One<EVE_TYPE>(), eve::inc(eve::Eps<EVE_TYPE>()))
             , r_t(1)
             );
    
    TTS_EQUAL( nb_values(eve::One<EVE_TYPE>(), EVE_TYPE(-eve::dec(eve::Eps<EVE_TYPE>())))
             , r_t(2)
             );
    
    TTS_EQUAL( nb_values(eve::One<EVE_TYPE>(), EVE_TYPE(-eve::dec(eve::Eps<EVE_TYPE>()/2)))
             , r_t(1)
             );
    TTS_EQUAL( nb_values(eve::Mzero<EVE_TYPE>(), EVE_TYPE(eve::Zero<EVE_TYPE>()))
             , r_t(1)
             );
    TTS_EXPECT(eve::all(eve::is_odd(nb_values(EVE_TYPE(-10), EVE_TYPE(10))))); 
  }
  else if constexpr(std::is_signed_v<EVE_VALUE>)
  {
    TTS_EXPECT(eve::all(eve::is_even(nb_values(EVE_TYPE(-10), EVE_TYPE(10)))));
  }
  else
  {
    TTS_EQUAL((nb_values(eve::One<EVE_TYPE>(), EVE_TYPE(10))), (r_t(9)));
    TTS_EQUAL(nb_values(eve::Zero<EVE_TYPE>(), eve::Zero<EVE_TYPE>()), eve::Zero<r_t>()); 
  }    
}
