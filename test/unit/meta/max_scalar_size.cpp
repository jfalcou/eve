//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "eve/detail/kumi.hpp"
#include "test.hpp"
#include <eve/traits/max_scalar_size.hpp>

TTS_CASE( "Check max_scalar_size on proper types" )
{
  TTS_CONSTEXPR_EQUAL(sizeof(int),  eve::max_scalar_size_v<int>);
  TTS_CONSTEXPR_EQUAL(sizeof(std::int8_t), eve::max_scalar_size_v<std::int8_t>);
  TTS_CONSTEXPR_EQUAL(sizeof(std::int8_t), (eve::max_scalar_size_v<kumi::tuple<std::int8_t, std::int8_t>>));
  TTS_CONSTEXPR_EQUAL(sizeof(int),  (eve::max_scalar_size_v<kumi::tuple<
                                       int, kumi::tuple<std::int8_t, std::int8_t>>>));
};

struct not_literal : kumi::tuple<double,int>
{
  using is_product_type = void;
  not_literal(int n) : kumi::tuple<double,int>{6.98,n} {}
};

template<>
struct std::tuple_size<not_literal> : std::integral_constant<std::size_t, 2> {};

template <std::size_t I>
struct std::tuple_element<I, not_literal> : std::conditional<I==0,double,int>
{};


TTS_CASE( "Check max_scalar_size on non-literal, non-def. constructible types" )
{
  TTS_CONSTEXPR_EQUAL(sizeof(double),  eve::max_scalar_size_v<not_literal>);
};
