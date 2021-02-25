//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/lookup.hpp>

TTS_CASE_TPL("Check eve::lookup return type", EVE_TYPE)
{
  using v_t = eve::element_type_t<T>;

  TTS_EXPR_IS((eve::lookup(T() , eve::as_integer_t<T >())), T );
  TTS_EXPR_IS((eve::lookup(v_t(), eve::as_integer_t<v_t>())), (v_t));
}

TTS_CASE_TPL("Check eve::lookup behavior", EVE_TYPE)
{
  using index_t = eve::as_integer_t<T>;

  #if defined(EVE_SIMD_TESTS)
  using v_t = eve::element_type_t<T>;

  T    value{[](auto i, auto)       { return static_cast<v_t>(1+i); } };
  T    reference{[](auto i, auto c) { return static_cast<v_t>(c-i); } };
  index_t indexes{[](auto i, auto c) { return c-i-1; } };

  TTS_EQUAL(eve::lookup(value, indexes) , reference );
  TTS_EQUAL(value[indexes]              , reference );
  #else

  TTS_EQUAL(eve::lookup((T(42)), index_t( 0) ), (T(42)) );
  TTS_EQUAL(eve::lookup((T(42)), index_t(-1) ), (T(0))  );

  #endif
}
