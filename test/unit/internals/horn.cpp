//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>

template<typename T> constexpr auto coeff0()
{
  if constexpr( std::same_as<T, float> )  return 0x00000000U;
  else                                    return 0x00000000ULL;
}

template<typename T> constexpr auto coeff1()
{
  if constexpr( std::same_as<T, float> )  return 0x3f800000U;
  else                                    return 0x3FF0000000000000ULL;
}

template<typename T> constexpr auto coeff2()
{
  if constexpr( std::same_as<T, float> )  return 0x40000000U;
  else                                    return 0x4000000000000000ULL;
}

TTS_CASE_TPL( "Check behavior of detail::horn", eve::test::simd::ieee_reals)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::horn;

  TTS_EQUAL((horn<T, coeff0<v_t>()>(T(0)))                              , T(0) );
  TTS_EQUAL((horn<T, coeff1<v_t>(), coeff0<v_t>(), coeff1<v_t>()>(T(1))), T(2) );
  TTS_EQUAL((horn<T, coeff2<v_t>(), coeff1<v_t>(), coeff1<v_t>()>(T(2))), T(8) );
};
