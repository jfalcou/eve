//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#include "test.hpp"

#include <eve/detail/category.hpp>

template<typename T, typename Cardinals> struct natives_impl;

template<typename T, std::size_t... N> struct natives_impl<T, std::index_sequence<N...>>
{
  using types_list = tts::types<eve::wide<T, eve::fixed<(1 << N)>>...>;
};

template<typename T>
struct natives
    : natives_impl<
          T,
          std::make_index_sequence<std::bit_width(std::size_t(eve::fundamental_cardinal_v<T>))>>
{};

TTS_CASE_TPL("Test category matching for double", natives<double>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes = static_cast<eve::detail::category>(eve::fundamental_cardinal_v<double>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), float_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size64_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), float64));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), float64 | lanes);
  }
  else { TTS_PASS("wide<double,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::int64", natives<std::int64_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::int64_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size64_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int64));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), int64 | lanes);
  }
  else { TTS_PASS("wide<int64,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::uint64", natives<std::uint64_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::uint64_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), unsigned_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size64_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint64));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), uint64 | lanes);
  }
  else { TTS_PASS("wide<uint64_t,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for float", natives<float>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes = static_cast<eve::detail::category>(eve::fundamental_cardinal_v<float>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), float_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size32_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), float32));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), float32 | lanes);
  }
  else { TTS_PASS("wide<float,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::int32", natives<std::int32_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::int32_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size32_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int32));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), int32 | lanes);
  }
  else { TTS_PASS("wide<int32,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::uint32", natives<std::uint32_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::uint32_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), unsigned_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size32_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint32));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), uint32 | lanes);
  }
  else { TTS_PASS("wide<uint32,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::int16", natives<std::int16_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::int16_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size16_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int16));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), int16 | lanes);
  }
  else { TTS_PASS("wide<int16,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::uint16", natives<std::uint16_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::uint16_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), unsigned_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size16_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint16));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), uint16 | lanes);
  }
  else { TTS_PASS("wide<uint16,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::int8", natives<std::int8_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::int8_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), signed_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size8_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), int8));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), int8 | lanes);
  }
  else { TTS_PASS("wide<int8,N> is not native and therefore can't be categorized."); }
};

TTS_CASE_TPL("Test category matching for std::uint8", natives<std::uint8_t>)
<typename T>(tts::type<T>)
{
  if constexpr( eve::has_native_abi_v<T> )
  {
    // All types below fundamental cardinal categorize with the same # of lanes
    using enum eve::detail::category;
    constexpr auto lanes =
        static_cast<eve::detail::category>(eve::fundamental_cardinal_v<std::uint8_t>);

    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), integer_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), unsigned_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), size8_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint_));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), uint8));
    TTS_CONSTEXPR_EXPECT(match(eve::detail::categorize<T>(), lanes));
    TTS_CONSTEXPR_EQUAL(eve::detail::categorize<T>(), uint8 | lanes);
  }
  else { TTS_PASS("wide<uint8,N> is not native and therefore can't be categorized."); }
};
