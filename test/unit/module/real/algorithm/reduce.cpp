//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/function/reduce.hpp>
#include <eve/function/plus.hpp>

//==================================================================================================
// Types tests
//==================================================================================================
EVE_TEST_TYPES( "Check return types of eve::reduce(wide)", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  TTS_EXPR_IS( (eve::reduce(T{}, eve::plus)            ) , v_t  );
  TTS_EXPR_IS( (eve::splat(eve::reduce)(T{}, eve::plus)) , T    );
};

//==================================================================================================
// Arithmetic tests
//==================================================================================================
EVE_TEST( "Check behavior of eve::reduce(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::ramp(1) )
        )
<typename T>(T const& a0)
{
  using v_t = eve::element_type_t<T>;
  auto ref = (a0.size()*(a0.size()+1))/2;

  TTS_EQUAL(eve::reduce(a0, [](auto a, auto b) { return a+b; })            , v_t(ref) );
  TTS_EQUAL(eve::splat(eve::reduce)(a0, [](auto a, auto b) { return a+b; }), T(ref)   );
};

//==================================================================================================
// Logical tests
//==================================================================================================
EVE_TEST( "Check behavior of eve::reduce(eve::wide)"
        , eve::test::simd::all_types
        , eve::test::generate ( eve::test::logicals(0,3) )
        )
<typename T>(T const& a0)
{
  TTS_EQUAL(eve::reduce(a0, eve::logical_and), eve::all(a0) );
  TTS_EQUAL(eve::reduce(a0, eve::logical_or ), eve::any(a0) );
};
