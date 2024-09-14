//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

#include <string_view>

namespace
{

template<typename T, typename U>
constexpr bool is_castable = (std::invocable<decltype(eve::simd_cast), T, eve::as<U>>);

TTS_CASE("simd_cast: check is invocable tests")
{
  TTS_CONSTEXPR_EXPECT((is_castable<eve::wide<int>, eve::wide<std::int8_t>>));
  TTS_CONSTEXPR_EXPECT((is_castable<eve::wide<int>, eve::wide<std::int8_t, eve::fixed<1>>>));
  TTS_CONSTEXPR_EXPECT((!is_castable<eve::wide<int>, int>));
  TTS_CONSTEXPR_EXPECT((is_castable<eve::wide<kumi::tuple<int16_t, int64_t>>,
                                    eve::wide<kumi::tuple<int32_t, int32_t>, eve::fixed<16>>>));

  TTS_CONSTEXPR_EXPECT((!is_castable<eve::wide<kumi::tuple<int16_t, int16_t, int16_t>>,
                                     eve::wide<kumi::tuple<int32_t, int32_t>, eve::fixed<16>>>));

  TTS_CONSTEXPR_EXPECT(
      (is_castable<eve::logical<eve::wide<int>>, eve::logical<eve::wide<double>>>));

  if constexpr( eve::current_api == eve::avx512 )
  {
    TTS_CONSTEXPR_EXPECT((!is_castable<eve::logical<eve::wide<int>>, eve::wide<int>>));
  }

  if constexpr( EVE_CURRENT_ABI::is_wide_logical )
  {
    TTS_CONSTEXPR_EXPECT(
        (is_castable<eve::logical<eve::wide<int>>, eve::wide<std::int8_t, eve::fixed<1>>>));
  }
};

template<typename T, typename U>
void
simd_cast_test_one_way()
{
  T x(
      [](int i, int)
      {
        // messing fo logicals a bit
        if( i == 3 || i == 7 ) return 0;
        return i + 1;
      });

  U actual = eve::simd_cast(x, eve::as<U> {});

  // the bit nature of logicals on avx512 and rvv
  // makes the byte level comparisons not work,
  // because part of the byte be garbage we need to ignore.
  // That doesn't happen on other platfroms.
  if constexpr( eve::logical_simd_value<T>
                && (eve::current_api >= eve::avx512 || eve::current_api >= eve::rvv) )
  {
    std::ptrdiff_t min_len = std::min(T::size(), U::size());
    for( std::ptrdiff_t i = 0; i != min_len; ++i ) { TTS_EQUAL(x.get(i), actual.get(i)); }
    return;
  }

  if constexpr( eve::logical_simd_value<T> && eve::current_api >= eve::sve )
  {
    // on sve the convertion to logical<std::int8_t> should match before and after.
    auto           expected_logical_bytes = eve::convert(x, eve::as<eve::logical<std::uint8_t>> {});
    auto           actual_logical_bytes   = eve::convert(x, eve::as<eve::logical<std::uint8_t>> {});
    std::ptrdiff_t min_len                = std::min(T::size(), U::size());
    for( std::ptrdiff_t i = 0; i != min_len; ++i )
    {
      TTS_EQUAL(expected_logical_bytes.get(i), actual_logical_bytes.get(i));
    }
    return;
  }

  constexpr std::size_t t_size = sizeof(eve::element_type_t<T>) * T::size();
  constexpr std::size_t u_size = sizeof(eve::element_type_t<U>) * U::size();

  std::array<std::uint8_t, t_size> expected_buf;
  std::array<std::uint8_t, u_size> actual_buf;

  std::memcpy(expected_buf.data(), &x, t_size);
  std::memcpy(actual_buf.data(), &actual, u_size);

  std::size_t min_size = std::min(t_size, u_size);

  TTS_EQUAL(std::vector(expected_buf.data(), expected_buf.data() + min_size),
            std::vector(actual_buf.data(), actual_buf.data() + min_size),
            REQUIRED)
      << "from: " << tts::typename_<T> << " to: " << tts::typename_<U>;
}

template<typename T, typename U>
void
simd_cast_test()
{
  // saving compile time a bit
  if constexpr( T::size() * 2 <= U::size() )
  {
    simd_cast_test_one_way<T, U>();
    simd_cast_test_one_way<U, T>();
  }
}

template<typename T, typename U>
void
simd_cast_logical_test()
{
  simd_cast_test<eve::logical<T>, eve::logical<U>>();
}

TTS_CASE_TPL("simd_cast, plain", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  eve::detail::for_<0, 1, std::bit_width((std::size_t)T::size() * 2)>(
      []<typename Idx>(Idx)
      {
        simd_cast_test<T, eve::wide<std::uint8_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_test<T, eve::wide<std::uint16_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_test<T, eve::wide<std::uint32_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_test<T, eve::wide<std::uint64_t, eve::fixed<1 << Idx::value>>>();
      });
};

TTS_CASE_TPL("simd_cast, logical", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  eve::detail::for_<0, 1, std::bit_width((std::size_t)T::size() * 2)>(
      []<typename Idx>(Idx)
      {
        simd_cast_logical_test<T, eve::wide<std::uint8_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_logical_test<T, eve::wide<std::uint16_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_logical_test<T, eve::wide<std::uint32_t, eve::fixed<1 << Idx::value>>>();
        simd_cast_logical_test<T, eve::wide<std::uint64_t, eve::fixed<1 << Idx::value>>>();
      });
};

TTS_CASE("simd_cast, bundle")
{
  eve::wide<kumi::tuple<int, std::int8_t, kumi::tuple<std::int16_t>>> a {
      [](int i, int)
      {
        kumi::tuple inner_tuple = {(std::int16_t)(i + 2)};
        return kumi::tuple {i, (std::int8_t)('a' + i), inner_tuple};
      }};

  eve::wide<kumi::tuple<double, double, kumi::tuple<double>>> b;

  // Just checking that casting there and back was ok.
  TTS_EQUAL(a, eve::simd_cast(eve::simd_cast(a, eve::as(b)), eve::as(a)));
};

} // namespace
