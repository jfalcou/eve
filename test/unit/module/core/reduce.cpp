//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
TTS_CASE_TPL( "Check return types of eve::reduce(wide)", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( (eve::reduce(T{})                       ) , v_t  );
  TTS_EXPR_IS( (eve::reduce(T{}, eve::plus)            ) , v_t  );
  TTS_EXPR_IS( (eve::splat(eve::reduce)(T{})           ) , T    );
  TTS_EXPR_IS( (eve::splat(eve::reduce)(T{}, eve::plus)) , T    );
};

//==================================================================================================
// Arithmetic tests
//==================================================================================================
TTS_CASE_TPL( "Check behavior of eve::reduce(eve::wide)"
              , eve::test::simd::all_types
              )
<typename T>(tts::type<T>)
{
  T data = [](auto i, auto c) { return i<c/2 ? 10*(i+1) : -(10*(i+1)+1); };
  data += 1;

  typename T::value_type ref = 0;
  for(std::ptrdiff_t i=0;i<T::size();++i) ref += data.get(i);

  TTS_EQUAL(eve::reduce(data, [](auto a, auto b) { return a+b; }) , ref);
  TTS_EQUAL(eve::reduce(data, eve::plus)                          , ref);
  TTS_EQUAL(eve::reduce(data, eve::add)                           , ref);
  TTS_EQUAL(eve::reduce(data)                                     , ref);

  TTS_EQUAL(eve::splat(eve::reduce)(data, [](auto a, auto b) { return a+b; }) , T(ref));
  TTS_EQUAL(eve::splat(eve::reduce)(data, eve::plus)                          , T(ref));
  TTS_EQUAL(eve::splat(eve::reduce)(data, eve::add)                           , T(ref));
  TTS_EQUAL(eve::splat(eve::reduce)(data)                                     , T(ref));
};

//==================================================================================================
// Logical tests
//==================================================================================================
TTS_CASE_WITH( "Check behavior of eve::reduce(eve::wide)"
        , eve::test::simd::all_types
        , tts::generate ( tts::logicals(0,3) )
        )
<typename T>(T const& a0)
{
  TTS_EQUAL(eve::reduce(a0, eve::logical_and), eve::all(a0) );
  TTS_EQUAL(eve::reduce(a0, eve::logical_or ), eve::any(a0) );
};
