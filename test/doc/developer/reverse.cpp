#include "test.hpp"
#include "reverse.hpp"

TTS_CASE("Check for reverse behavior")
{
  #if defined(EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)

  #endif
}

// template<typename T, typename Test>
// void for_all_test_pack_sizes(Test test)
// {
//   constexpr int number_of_packs = std::countr_zero(256u >> sizeof(T)) + 2;

//   [&]<int... idx>(std::integer_sequence<int, idx...>)
//   {
//     (test(eve::wide<T, eve::fixed<static_cast<size_t>(1 << idx)>> {}), ...);
//   } (std::make_integer_sequence<int, number_of_packs>());
// }

// template <typename Test>
// void for_all_test_packs(Test test)
// {
//   [&]<typename...T>(T...) { (for_all_test_pack_sizes<T>(test), ...); }
//   (std::int8_t{},  std::uint8_t{},
//    std::int16_t{}, std::uint16_t{},
//    std::int32_t{}, std::uint32_t{},
//    std::int64_t{}, std::uint64_t{},
//    float{},        double{});
// }

// int main()
// {
//   auto test = []<typename wide>(wide) {
//     wide input([](int i, int) { return i ; });
//     input.set(0, std::numeric_limits<typename wide::value_type>::min());
//     input.set(wide::static_size - 1, std::numeric_limits<typename wide::value_type>::max());

//     wide expected([](int i, int size) { return size - 1 - i; });
//     expected.set(wide::static_size - 1, std::numeric_limits<typename wide::value_type>::min());
//     expected.set(0, std::numeric_limits<typename wide::value_type>::max());

//     wide actual = eve_extra::reverse(input);

//     if (eve::all(expected == actual)) return;

//     std::cerr << "wide: element_size: " << sizeof(eve::element_type_t<wide>) << " N: " << wide::static_size << std::endl;
//     std::cerr << "expected != actual \n  expected: " << expected << "\n  actual:   " << actual << std::endl;
//     std::terminate();
//   };

//   for_all_test_packs(test);
// }

#endif  // (EVE_HW_X86) && !defined(SPY_SIMD_IS_X86_AVX512)
