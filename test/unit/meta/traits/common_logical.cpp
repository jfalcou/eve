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

template<typename... T1s, typename... T2s> 
struct cartesian<tts::types<T1s...>, tts::types<T2s...>>
{
  using base       = kumi::result::cartesian_product_t<kumi::tuple<T1s...>,kumi::tuple<T2s...>>; 
  using types_list = typename rewrap<base>::type;
};
 
TTS_CASE_TPL("eve::common_logical on scalars"
            , cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types> 
            )
<typename T, typename U>( tts::type<kumi::tuple<T,U>> )
{
  TTS_TYPE_IS((eve::common_logical_t<T, T>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<T, U>), eve::logical<T>);

  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<T>>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<U>>), eve::logical<T>);
};

TTS_CASE_TPL("eve::common_logical on wides"
            , cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types> 
            )
<typename T, typename U>( tts::type<kumi::tuple<T,U>> )
{
  eve::detail::for_<1, 1, 9>([](auto i) {
    constexpr auto card_v = 1 << i;

    if constexpr (card_v <= eve::expected_cardinal_v<T>) {
      using W = eve::wide<T, eve::fixed<card_v>>;

      TTS_TYPE_IS((eve::common_logical_t<W, W>), eve::logical<W>);
      TTS_TYPE_IS((eve::common_logical_t<W, U>), eve::logical<W>);
      TTS_TYPE_IS((eve::common_logical_t<U, W>), eve::logical<W>);
      TTS_TYPE_IS((eve::common_logical_t<bool, W>), eve::logical<W>);
      TTS_TYPE_IS((eve::common_logical_t<W, bool>), eve::logical<W>);
    }
  });
};
