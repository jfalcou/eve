//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core/detail/generic/horn1.hpp>
#include <type_traits>

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

EVE_TEST_TYPES( "Check behavior of detail::horn", eve::test::simd::ieee_reals)
<typename T>(eve::as<T>)
{
  using v_t = eve::element_type_t<T>;
  using eve::detail::horn1;

  TTS_EQUAL((horn1<T, coeff0<v_t>()>(T(0)))                              , T( 0));
  TTS_EQUAL((horn1<T, coeff1<v_t>(), coeff0<v_t>(), coeff1<v_t>()>(T(1))), T( 3));
  TTS_EQUAL((horn1<T, coeff2<v_t>(), coeff1<v_t>(), coeff1<v_t>()>(T(2))), T(16));
};
