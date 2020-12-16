//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/bit_mantissa.hpp>
#include <eve/constant/valmin.hpp>
#include <eve/constant/valmax.hpp>
#include <eve/constant/one.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_eqz.hpp>
#include <eve/function/mantissa.hpp>
#include <tts/tests/range.hpp>
#include "measures.hpp"
#include "producers.hpp"
#include <cmath>

TTS_CASE_TPL("wide random check on bit_mantissa", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  auto std_bit_mantissa = [ ](auto e) { return eve::if_else(eve::is_eqz(e), eve::one, eve::abs(eve::mantissa(e))); };
  auto  my_bit_mantissa = [ ](auto e) { return eve::bit_or(one(eve::as(e)), eve::bit_mantissa(e)); };



  eve::exhaustive_producer<T> p(eve::valmin(eve::as<v_t>()), eve::valmax(eve::as<v_t>()));
  TTS_RANGE_CHECK(p, std_bit_mantissa, my_bit_mantissa);
}
