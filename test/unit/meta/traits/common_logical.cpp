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

TTS_CASE("eve::common_logical on boolean x boolean")
{
  TTS_TYPE_IS((eve::common_logical_t<bool, bool>), bool);
};

TTS_CASE_TPL("eve::common_logical on boolean x other"
            , eve::test::simd::all_types
            )
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
 
TTS_CASE_TPL("eve::common_logical on scalar x scalar"
            , cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types> 
            )
<typename T, typename U>( tts::type<kumi::tuple<T,U>> )
{
  TTS_TYPE_IS((eve::common_logical_t<T, U>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<T, eve::logical<U>>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, U>), eve::logical<T>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<U>>), eve::logical<T>);
};

TTS_CASE_TPL("eve::common_logical on wide x wide"
            , cartesian<eve::test::scalar::all_types, eve::test::scalar::all_types> 
            )
<typename T, typename U>( tts::type<kumi::tuple<T, U>> )
{
  using Wt = eve::wide<T>;
  using Wu = eve::wide<U>;

  using uWt = eve::as_wide_as_t<T, Wu>;

  TTS_TYPE_IS((eve::common_logical_t<Wt, Wu>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<Wt, eve::logical<Wu>>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<Wt>, Wu>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<Wt>, eve::logical<Wu>>), eve::logical<Wt>);

  TTS_TYPE_IS((eve::common_logical_t<T, Wu>), eve::logical<uWt>);
  TTS_TYPE_IS((eve::common_logical_t<T, eve::logical<Wu>>), eve::logical<uWt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, Wu>), eve::logical<uWt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<Wu>>), eve::logical<uWt>);

  TTS_TYPE_IS((eve::common_logical_t<Wt, U>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<Wt, eve::logical<U>>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<Wt>, U>), eve::logical<Wt>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<Wt>, eve::logical<U>>), eve::logical<Wt>);
};
