//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"
#include "unit/module/core/logical_ops.hpp"

#include <eve/module/core.hpp>

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

TTS_CASE_TPL("eve::common_logical on scalar x scalar", tts::cartesian_square<eve::test::scalar::all_types>)
<typename T, typename U>( tts::type<kumi::tuple<T,U>> )
{
  using expected_t = priority_t<T, U>;

  TTS_TYPE_IS((eve::common_logical_t<T, U>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<T, eve::logical<U>>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, U>), expected_t);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<T>, eve::logical<U>>), expected_t);
};

TTS_CASE_TPL("eve::common_logical on wide x wide", tts::cartesian_square<eve::test::scalar::all_types>)
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

TTS_CASE("eve::common_logical on tuples")
{
  using t1 = kumi::tuple<float, unsigned char>;
  using t2 = kumi::tuple<long long, double>;

  TTS_TYPE_IS((eve::common_logical_t<t1, t2>), eve::logical<float>);
  TTS_TYPE_IS((eve::common_logical_t<eve::wide<t1>, eve::wide<t2>>), eve::logical<eve::wide<float>>);
};
