//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <tts/tests/basic.hpp>
#include <tts/tests/relation.hpp>
#include <eve/constant/false.hpp>
#include <eve/constant/true.hpp>
#include <eve/function/if_else.hpp>
#include <eve/wide.hpp>

TTS_CASE("ignore_all behavior")
{
  using eve::wide;
  using eve::conditional_expr;
  using eve::ignore_all;
  using eve::if_else;
  using eve::as_;

  using type = wide<float>;

  TTS_EXPECT( conditional_expr<eve::ignore_all_>  );
  TTS_EQUAL( (ignore_all.mask( as_<type>() )), eve::False( as_<type>() ) );

  TTS_EQUAL( (if_else(ignore_all,type(42), type(69))), type(69));
}

TTS_CASE("ignore_none behavior")
{
  using eve::wide;
  using eve::conditional_expr;
  using eve::ignore_none;
  using eve::if_else;
  using eve::as_;

  using type = wide<float>;

  TTS_EXPECT( conditional_expr<eve::ignore_none_>  );
  TTS_EQUAL( (ignore_none.mask( as_<type>() )), eve::True( as_<type>() ) );

  TTS_EQUAL( (if_else(ignore_none,type(42), type(69))), type(42));
}
