//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include <eve/module/core.hpp>
#include "test.hpp"

template<typename L1> struct rewrap;
template<typename... Ts>
struct rewrap<kumi::tuple<Ts...>> { using type = tts::types<Ts...>; };

template<typename L1, typename L2> struct cartesian;

template <typename A, typename B>
static constexpr auto find_priority_type()
{
  using ea_t = eve::as_arithmetic_t<eve::element_type_t<A>>;
  using eb_t = eve::as_arithmetic_t<eve::element_type_t<B>>;

  if constexpr (std::same_as<ea_t, eb_t>)      return A{};
  // smallest type
  else if constexpr (sizeof(ea_t) != sizeof(eb_t))
  {
    if constexpr (sizeof(ea_t) < sizeof(eb_t)) return A{};
    else                                       return B{};
  }
  // unsigned first
  else if constexpr (eve::signed_value<ea_t> != eve::signed_value<eb_t>)
  {
    if constexpr (eve::signed_value<ea_t>)     return A{};
    else                                       return B{};
  }
  // integral first
  else if constexpr (eve::integral_value<ea_t> != eve::integral_value<eb_t>)
  {
    if constexpr (eve::integral_value<ea_t>)   return A{};
    else                                       return B{};
  }
}

template<typename T, typename U>
using priority_t = eve::as_logical_t<decltype(find_priority_type<T, U>())>;

template<typename... T1s, typename... T2s>
struct cartesian<tts::types<T1s...>, tts::types<T2s...>>
{
  using base       = kumi::result::cartesian_product_t<kumi::tuple<T1s...>,kumi::tuple<T2s...>>;
  using types_list = typename rewrap<base>::type;
};

TTS_CASE("eve::common_logical on boolean x boolean")
{
  TTS_TYPE_IS((eve::common_logical_t<bool, bool>), bool);
};

TTS_CASE_TPL("eve::common_logical on boolean x other", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using S = eve::element_type_t<T>;

  TTS_TYPE_IS((eve::common_logical_t<bool, T>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<T, bool>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<bool, eve::logical<T>>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, bool>), eve::logical<T>);

  TTS_TYPE_IS((eve::common_logical_t<bool, S>), eve::logical<S>);
  TTS_TYPE_IS((eve::common_logical_t<S, bool>), eve::logical<S>);
  TTS_TYPE_IS((eve::common_logical_t<bool, eve::logical<S>>), eve::logical<S>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<S>, bool>), eve::logical<S>);
};

TTS_CASE_TPL("eve::common_logical on scalar x scalar", cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types>)
<typename T, typename U>( tts::type<kumi::tuple<T,U>> )
{
  using expected_t = priority_t<T, U>;

  TTS_TYPE_IS((eve::common_logical_t<T, U>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<T, eve::logical<U>>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, U>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<U>>), expected_t);
};

TTS_CASE_TPL("eve::common_logical on wide x wide", cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types>)
<typename T, typename U>( tts::type<kumi::tuple<T, U>> )
{
  using Wt = eve::wide<T, eve::fixed<4>>;
  using Wu = eve::wide<U, eve::fixed<4>>;
  using LWt = eve::logical<Wt>;
  using LWu = eve::logical<Wu>;

  using expected_t = priority_t<LWt, LWu>;

  TTS_TYPE_IS((eve::common_logical_t<Wt, Wu>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<Wt, LWu>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<LWt, Wu>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<LWt, LWu>), expected_t);

  TTS_TYPE_IS((eve::common_logical_t<T, Wu>), LWu);
  TTS_TYPE_IS((eve::common_logical_t<T, LWu>), LWu);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, Wu>), LWu);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, LWu>), LWu);

  TTS_TYPE_IS((eve::common_logical_t<Wt, U>), LWt);
  TTS_TYPE_IS((eve::common_logical_t<Wt, eve::logical<U>>), LWt);
  TTS_TYPE_IS((eve::common_logical_t<LWt, U>), LWt);
  TTS_TYPE_IS((eve::common_logical_t<LWt, eve::logical<U>>), LWt);
};
