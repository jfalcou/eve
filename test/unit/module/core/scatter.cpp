//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>
#include <algorithm>

template<typename Index, typename T>
void test_scatter(T const& values, auto ptr)
{
  using e_t = eve::element_type_t<T>;
  eve::wide<Index, eve::fixed<T::size()>> indexes = [](auto i, auto) { return 2*i; };

  e_t ref [2*T::size()];
  auto base = eve::unalign(ptr);
  std::copy(base,base+2*T::size(),&ref[0]);
  for( std::size_t i = 0; i < T::size(); ++i ) ref[indexes.get(i)] = values.get(i);

  eve::scatter(values, ptr, indexes);

  TTS_EXPECT(std::equal(&ref[0],&ref[0]+2*T::size(),base));
}

TTS_CASE_TPL("Check eve::scatter behavior with pointer", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  e_t data[2*T::size()];
  for( std::size_t i = 0; i < 2*T::size(); ++i ) data[i] = e_t(99);
  T values = [](auto i, auto) { return 2*i+1; };

  test_scatter<std::int32_t >(values,&data[0]);
  test_scatter<std::uint32_t>(values,&data[0]);
  test_scatter<std::int64_t >(values,&data[0]);
  test_scatter<std::uint64_t>(values,&data[0]);
};

TTS_CASE_TPL("Check eve::scatter behavior with aligned_ptr", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using e_t = eve::element_type_t<T>;
  alignas(T::alignment()) e_t data[2*T::size()];
  for( std::size_t i = 0; i < 2*T::size(); ++i ) data[i] = e_t(99);
  T values = [](auto i, auto) { return 2*i+1; };

  test_scatter<std::int32_t >(values,eve::as_aligned(&data[0],typename T::cardinal_type{}));
  test_scatter<std::uint32_t>(values,eve::as_aligned(&data[0],typename T::cardinal_type{}));
  test_scatter<std::int64_t >(values,eve::as_aligned(&data[0],typename T::cardinal_type{}));
  test_scatter<std::uint64_t>(values,eve::as_aligned(&data[0],typename T::cardinal_type{}));
};
