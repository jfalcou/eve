//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core.hpp>

template<typename T, typename U, typename Expected>
void test_with_types()
{
  TTS_TYPE_IS((eve::common_logical_t<T, U>), Expected);
  TTS_TYPE_IS((eve::common_logical_t<U, T>), Expected);
}

TTS_CASE_TPL("eve::common_logical on boolean x other", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using S = eve::element_type_t<T>;

  test_with_types<bool, T, eve::logical<T>>();
  test_with_types<bool, eve::logical<T>, eve::logical<T>>();
  test_with_types<bool, S, eve::logical<S>>();
  test_with_types<bool, eve::logical<S>, eve::logical<S>>();
};

TTS_CASE_TPL("eve::common_logical on scalar x scalar", eve::test::scalar::all_types)
<typename T>(tts::type<T>)
{
  // same type
  TTS_TYPE_IS((eve::common_logical_t<T, T>), eve::logical<T>);

  // different floatiness
  if constexpr (std::floating_point<T>)
  {
    using U = eve::as_integer_t<T>;
    test_with_types<T, U, eve::logical<U>>();
  }

  // different signedness
  if constexpr (std::signed_integral<T>)
  {
    using U = std::make_unsigned_t<T>;
    test_with_types<T, U, eve::logical<U>>();
  }

  // different sizes
  using D = eve::downgrade_t<T>;
  using U = eve::upgrade_t<T>;

  test_with_types<T, D, eve::logical<D>>();
  test_with_types<T, U, eve::logical<T>>();
};

TTS_CASE("eve::common_logical on special cases")
{
  TTS_TYPE_IS((eve::common_logical_t<bool, bool>), bool);

  if constexpr (sizeof(long) == sizeof(long long))
  {
    test_with_types<long, long long, eve::logical<long long>>();
  }
};

template<typename T, typename U, typename ES, typename EW = ES>
void test_with_types_simd()
{
  using es_t = eve::logical<eve::wide<ES, eve::fixed<2>>>;
  using ew_t = eve::logical<eve::wide<EW, eve::fixed<2>>>;

  using Lt  = eve::logical<T>;
  using Wt  = eve::wide<T, eve::fixed<2>>;
  using LWt = eve::logical<Wt>;

  using Wu  = eve::wide<U, eve::fixed<2>>;
  using LWu = eve::logical<Wu>;

  test_with_types<T, Wu, es_t>();
  test_with_types<Lt, Wu, es_t>();
  test_with_types<T, LWu, es_t>();
  test_with_types<Lt, LWu, es_t>();
  
  test_with_types<Wt, Wu, ew_t>();
  test_with_types<LWt, Wu, ew_t>();
  test_with_types<Wt, LWu, ew_t>();
  test_with_types<LWt, LWu, ew_t>();
}

TTS_CASE_TPL("eve::common_logical on wides", eve::test::scalar::all_types)
<typename T>( tts::type<T> )
{
  // same type
  TTS_TYPE_IS((eve::common_logical_t<eve::wide<T>, eve::wide<T>>), eve::logical<eve::wide<T>>);
  TTS_TYPE_IS((eve::common_logical_t<eve::logical<eve::wide<T>>, eve::logical<eve::wide<T>>>), eve::logical<eve::wide<T>>);

  // different floatiness
  if constexpr (std::floating_point<T>)
  {
    using U   = eve::as_integer_t<T>;
    test_with_types_simd<T, U, U>();
  }

  // different signedness
  if constexpr (std::signed_integral<T>)
  {
    using U   = std::make_unsigned_t<T>;
    test_with_types_simd<T, U, U>();
  }

  // different sizes
  using D = eve::downgrade_t<T>;
  using U = eve::upgrade_t<T>;

  test_with_types_simd<T, D, D, D>();
  test_with_types_simd<T, U, U, T>();
};

TTS_CASE("eve::common_logical on tuples")
{
  using t1 = kumi::tuple<float, unsigned char>;
  using t2 = kumi::tuple<long long, double>;

  TTS_TYPE_IS((eve::common_logical_t<t1, t2>), eve::logical<float>);
  TTS_TYPE_IS((eve::common_logical_t<eve::wide<t1>, eve::wide<t2>>), eve::logical<eve::wide<float>>);
};
