//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

TTS_CASE_TPL("Check eve::gather behavior with 32 bits indexes", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  alignas(sizeof(T)) v_t data[T::size()];

  for( std::size_t i = 0; i < T::size(); ++i ) data[i] = v_t(1) + i;

  eve::wide<std::int32_t, eve::fixed<T::size()>> maps([](auto i, auto c)
                                                      { return i % 3 ? i : c - i - 1; });
  T ref([&](auto i, auto) { return data[maps.get(i)]; });

  const v_t *cdata = &data[0];
  TTS_EQUAL(ref, eve::gather(eve::as_aligned(cdata, eve::cardinal_t<T> {}), maps));
  TTS_EQUAL(ref, eve::gather(eve::as_aligned(&data[0], eve::cardinal_t<T> {}), maps));
};

TTS_CASE_TPL("Check eve::gather behavior with 64 bits indexes", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  alignas(sizeof(T)) v_t data[T::size()];

  for( std::size_t i = 0; i < T::size(); ++i ) data[i] = v_t(1) + i;

  eve::wide<std::int64_t, eve::fixed<T::size()>> maps([](auto i, auto c)
                                                      { return i % 3 ? i : c - i - 1; });
  T ref([&](auto i, auto) { return data[maps.get(i)]; });

  const v_t *cdata = &data[0];
  TTS_EQUAL(ref, eve::gather(eve::as_aligned(cdata, eve::cardinal_t<T> {}), maps));
  TTS_EQUAL(ref, eve::gather(eve::as_aligned(&data[0], eve::cardinal_t<T> {}), maps));
};

TTS_CASE_TPL("Check unaligned eve::gather behavior with 32 bits indexes",
             eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  v_t data[T::size()];
  for( std::size_t i = 0; i < T::size(); ++i ) data[i] = v_t(1) + i;

  eve::wide<std::int32_t, eve::fixed<T::size()>> maps([](auto i, auto c)
                                                      { return i % 3 ? i : c - i - 1; });
  T ref([&](auto i, auto) { return data[maps.get(i)]; });

  const v_t *cdata = &data[0];
  TTS_EQUAL(ref, eve::gather(cdata, maps));
  TTS_EQUAL(ref, eve::gather(&data[0], maps));
};

TTS_CASE_TPL("Check unaligned eve::gather behavior with 64 bits indexes",
             eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  v_t data[T::size()];
  for( std::size_t i = 0; i < T::size(); ++i ) data[i] = v_t(1) + i;

  eve::wide<std::int64_t, eve::fixed<T::size()>> maps([](auto i, auto c)
                                                      { return i % 3 ? i : c - i - 1; });
  T ref([&](auto i, auto) { return data[maps.get(i)]; });

  const v_t *cdata = &data[0];
  TTS_EQUAL(ref, eve::gather(cdata, maps));
  TTS_EQUAL(ref, eve::gather(&data[0], maps));
};
