//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/reduce.hpp>
#include <eve/function/plus.hpp>
#include <type_traits>

TTS_CASE_TPL("Check eve::reduce return type", EVE_TYPE)
{
  TTS_EXPR_IS( (eve::reduce(T{}, eve::plus)            ) , EVE_VALUE );
  TTS_EXPR_IS( (eve::splat(eve::reduce)(T{}, eve::plus)) , T         );
}

TTS_CASE_TPL("Check eve::reduce behavior on wide", EVE_TYPE)
{
  T data = [](auto i, auto ) { return 1+i; };

  auto ref = (EVE_CARDINAL/2.)*(EVE_CARDINAL+1);

  TTS_EQUAL( (eve::reduce(data, [](auto a, auto b) { return a+b; } )), EVE_VALUE(ref) );
}

TTS_CASE_TPL("Check eve::reduce behavior on wide", EVE_TYPE)
{
  T data = [](auto i, auto ) { return 1+i; };

  T ref( (EVE_CARDINAL/2.)*(EVE_CARDINAL+1) );

  TTS_EQUAL( (eve::splat(eve::reduce)(data, [](auto a, auto b) { return a+b; } )), ref);
}
