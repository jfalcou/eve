
#include <eve/wide.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/store.hpp>

#include <algorithm>
#include <bit>
#include <concepts>
#include <cstdint>

#include <type_traits>

#if defined(EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)

namespace eve_extra {
namespace _reverse {

template <typename T, typename N, eve::x86_abi ABI>
eve::wide<T, N, ABI> actual_reverse(eve::wide<T, N, ABI> x) requires(sizeof(T) == 8)
{
       if constexpr(std::same_as<ABI, eve::x86_128_>) return {_mm_shuffle_epi32(x.storage(), _MM_SHUFFLE(1, 0, 3, 2))};
  else if constexpr(std::same_as<ABI, eve::x86_256_>) return {_mm256_permutevar8x32_epi32(x.storage(), _MM_SHUFFLE(3, 2, 1, 0))};
}

template <typename N>
constexpr std::uint32_t mm_shuffle() {
  if constexpr(N() == 4) return _MM_SHUFFLE(0, 1, 2, 3);
  if constexpr(N() == 2) return _MM_SHUFFLE(3, 2, 0, 1);
}

template <typename T, typename N, eve::x86_abi ABI>
eve::wide<T, N, ABI> actual_reverse(eve::wide<T, N, ABI> x) requires(sizeof(T) == 4)
{
  auto raw = x.storage();

       if constexpr(std::same_as<ABI, eve::x86_128_>) return {_mm_shuffle_epi32(raw, mm_shuffle<N>())};
  else if constexpr(std::same_as<ABI, eve::x86_256_>)
  {
    using mask_type = eve::wide<int, eve::fixed<8>>;
    auto mask = mask_type([](int i, int) { return 7 - i; }).storage();

    return {_mm256_permutevar8x32_epi32(raw, mask)};
  }
}

inline __m256i reverse_256_using_128_mask(__m256i x, __m128i mask_128)
{
  __m256i mask_256 = _mm256_set_m128i(mask_128, mask_128);
  __m256i each_half = _mm256_shuffle_epi8(x, mask_256);

  return {_mm256_permute4x64_epi64(each_half, _MM_SHUFFLE(1, 0, 3, 2))};
}

template <typename N>
inline __m128i reverse_8_shorts_mask() {
  return eve::wide<short, eve::fixed<8>>([](int i, int) {
    auto as_chars_idx = [](int i) { return (i * 2 + 1) << 8 | (i * 2); };
    return as_chars_idx(i >= N() ? i : (N() - i - 1));
  }).storage();
}

template <typename T, typename N, eve::x86_abi ABI>
eve::wide<T, N, ABI> actual_reverse(eve::wide<T, N, ABI> x) requires(sizeof(T) == 2)
{
  auto raw = x.storage();

       if constexpr(N() < 8) return {_mm_shufflelo_epi16(raw, mm_shuffle<N>())};
  else if constexpr(eve::current_api <= eve::sse3)  // N == 8
  {
     raw = _mm_shufflehi_epi16(raw, _MM_SHUFFLE(0, 1, 2, 3));
     raw = _mm_shufflelo_epi16(raw, _MM_SHUFFLE(0, 1, 2, 3));
     raw = _mm_shuffle_epi32(raw, _MM_SHUFFLE(1, 0, 3, 2));

     return {raw};
  }
  else if constexpr(std::same_as<ABI, eve::x86_128_>) return {_mm_shuffle_epi8(raw, reverse_8_shorts_mask<N>())};
  else if constexpr(std::same_as<ABI, eve::x86_256_>) return {reverse_256_using_128_mask(raw, reverse_8_shorts_mask<N>())};
}

template <typename N>
__m128i reverse_16_chars_mask()
{
  return eve::wide<char, eve::fixed<16>>(
    [](int i, int) { return i >= N() ? i : N() - 1 - i; }
  ).storage();
}

template <typename T, typename N, eve::x86_abi ABI>
eve::wide<T, N, ABI> actual_reverse(eve::wide<T, N, ABI> x)
  requires(sizeof(T) == 1 && eve::current_api > eve::sse3)
{
  auto raw = x.storage();

       if constexpr(std::same_as<ABI, eve::x86_128_>) return {_mm_shuffle_epi8(raw, reverse_16_chars_mask<N>())};
  else if constexpr(std::same_as<ABI, eve::x86_256_>) return {reverse_256_using_128_mask(raw, reverse_16_chars_mask<N>())};
}

template <eve::simd_value Wide>
constexpr bool treat_like_aggregated()
{
  using ABI = typename Wide::abi_type;

       if constexpr(eve::has_aggregated_abi_v<Wide>)        return true;
  else if constexpr(eve::current_api == eve::avx &&
                    std::same_as<ABI, eve::x86_256_> &&
                    sizeof(eve::element_type_t<Wide>) <= 4) return true;
  else                                                      return false;
}

template <typename N>
auto convert_epu8_epu16(eve::wide<std::uint8_t, N> x)
{
  __m128i zeroes = _mm_setzero_si128();

  if constexpr (N() <= 8)
  {
    return eve::wide<std::uint16_t, N>{_mm_unpacklo_epi8(x.storage(), zeroes)};
  }
  else
  {
    using wide_8_epu8 = eve::wide<std::uint16_t, eve::fixed<8>>;
    wide_8_epu8 hi {_mm_unpackhi_epi8(x.storage(), zeroes)};
    wide_8_epu8 lo {_mm_unpacklo_epi8(x.storage(), zeroes)};
    return eve::wide<std::uint16_t, N>{lo, hi};
  }
}

template <typename N>
inline auto convert_epu16_epu8(eve::wide<std::uint16_t, N> x)
{
  if constexpr (N() <= 8)
  {
    __m128i zeroes = _mm_setzero_si128();
    __m128i packed = _mm_packus_epi16(x.storage(), zeroes);
    return eve::wide<std::uint8_t, N>(packed);
  }
  else
  {
    auto [l, h] = x.slice();
    __m128i packed = _mm_packus_epi16(l.storage(), h.storage());
    return eve::wide<std::uint8_t, N>{packed};
  }
}

}  // namespace _reverse

template <typename T, typename N, typename ABI>
eve::wide<T, N, ABI> reverse(eve::wide<T, N, ABI> x) {
  using Wide = eve::wide<T, N, ABI>;

       if constexpr(Wide::static_size == 1) return x;
  else if constexpr(_reverse::treat_like_aggregated<Wide>())
  {
    auto [l, h] = x.slice();
    l = eve_extra::reverse(l);
    h = eve_extra::reverse(h);
    return Wide(h, l);
  }
  else if constexpr(std::same_as<T, float>)
  {
    auto as_ints = eve::bit_cast(x, eve::as_<eve::wide<std::int32_t, N>>{});
    as_ints = eve_extra::reverse(as_ints);
    return eve::bit_cast(as_ints, eve::as_<Wide>{});
  }
  else if constexpr(std::same_as<T, double>)
  {
    auto as_ints = eve::bit_cast(x, eve::as_<eve::wide<std::int64_t, N>>{});
    as_ints = eve_extra::reverse(as_ints);
    return eve::bit_cast(as_ints, eve::as_<Wide>{});
  }
  else if constexpr(sizeof(T) == 1 && eve::current_api <= eve::sse3)
  {
    auto as_epu8 = eve::bit_cast(x, eve::as_<eve::wide<std::uint8_t, N>>{});
    auto as_epu16 = _reverse::convert_epu8_epu16(as_epu8);
    as_epu16 = eve_extra::reverse(as_epu16);
    as_epu8 =_reverse::convert_epu16_epu8(as_epu16);
    return eve::bit_cast(as_epu8, eve::as_<Wide>{});
  }
  else return _reverse::actual_reverse(x);
}

}  // namespace eve_extra


template<typename T, typename Test>
void for_all_test_pack_sizes(Test test)
{
  constexpr int number_of_packs = std::countr_zero(256u >> sizeof(T)) + 2;

  [&]<int... idx>(std::integer_sequence<int, idx...>)
  {
    (test(eve::wide<T, eve::fixed<static_cast<size_t>(1 << idx)>> {}), ...);
  } (std::make_integer_sequence<int, number_of_packs>());
}

template <typename Test>
void for_all_test_packs(Test test)
{
  [&]<typename...T>(T...) { (for_all_test_pack_sizes<T>(test), ...); }
  (std::int8_t{},  std::uint8_t{},
   std::int16_t{}, std::uint16_t{},
   std::int32_t{}, std::uint32_t{},
   std::int64_t{}, std::uint64_t{},
   float{},        double{});
}

int main()
{
  auto test = []<typename wide>(wide) {
    wide input([](int i, int) { return i ; });
    input.set(0, std::numeric_limits<typename wide::value_type>::min());
    input.set(wide::static_size - 1, std::numeric_limits<typename wide::value_type>::max());

    wide expected([](int i, int size) { return size - 1 - i; });
    expected.set(wide::static_size - 1, std::numeric_limits<typename wide::value_type>::min());
    expected.set(0, std::numeric_limits<typename wide::value_type>::max());

    wide actual = eve_extra::reverse(input);

    if (eve::all(expected == actual)) return;

    std::cerr << "wide: element_size: " << sizeof(eve::element_type_t<wide>) << " N: " << wide::static_size << std::endl;
    std::cerr << "expected != actual \n  expected: " << expected << "\n  actual:   " << actual << std::endl;
    std::terminate();
  };

  for_all_test_packs(test);
}
#else

int main() {}

#endif  // (EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)
