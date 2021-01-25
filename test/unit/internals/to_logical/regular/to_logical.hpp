//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"
#include <eve/detail/function/to_logical.hpp>
#include <eve/logical.hpp>
#include <eve/wide.hpp>

TTS_CASE_TPL("Check detail::to_logical over wide", EVE_TYPE)
{
  T all_non_zero(42);
  T all_zero(0);
  T mixed_values([](auto i, auto) { return i%2 == 0 ? 69 : 0; } );

  eve::as_logical_t<T> all_true(true);
  eve::as_logical_t<T> all_false(false);
  eve::as_logical_t<T> mixed_bool([](auto i, auto) { return i%2 == 0; });

  TTS_EQUAL( eve::detail::to_logical(all_non_zero), all_true  );
  TTS_EQUAL( eve::detail::to_logical(all_zero)    , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_values), mixed_bool);
}

TTS_CASE_TPL("Check detail::to_logical over logical", EVE_TYPE)
{
  eve::as_logical_t<T> all_true(true);
  eve::as_logical_t<T> all_false(false);
  eve::as_logical_t<T> mixed_bool([](auto i, auto) { return i%2 == 0; });

  TTS_EQUAL( eve::detail::to_logical(all_true)   , all_true  );
  TTS_EQUAL( eve::detail::to_logical(all_false)  , all_false );
  TTS_EQUAL( eve::detail::to_logical(mixed_bool) , mixed_bool);
}
