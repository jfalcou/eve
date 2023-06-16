//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

namespace
{

template<typename T>
void
for_each_group_size(auto op)
{
  constexpr auto ssz = std::bit_width(std::size_t(T::size()));
  [&]<std::size_t... I>(std::index_sequence<I...>) { (op(eve::lane<1 << I>), ...); }
  (std::make_index_sequence<ssz> {});
};

template<typename... Ts>
auto
to_array(kumi::tuple<Ts...> x)
{
  return [&]<std::size_t... i>(std::index_sequence<i...>)
  {
    return std::array {kumi::get<i>(x)...};
  }
  (std::index_sequence_for<Ts...> {});
}

TTS_CASE_TPL("Check behavior of try_each_group_position simplest", eve::test::scalar::all_types)
<typename T>(tts::type<T>) {
  using T2 = eve::wide<T, eve::fixed<2>>;

  T2 x = {0, 1};
  kumi::tuple<T2, T2> expected{ T2{0, 1}, T2{1, 0} };
  kumi::tuple<T2, T2> actual = eve::try_each_group_position(x, eve::lane<1>);

  TTS_EQUAL(get<0>(expected), get<0>(actual));
  TTS_EQUAL(get<1>(expected), get<1>(actual));
};

TTS_CASE_TPL("Check behavior of try_each_group_position", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  for_each_group_size<T>(
      [&]<std::ptrdiff_t G>(eve::fixed<G> g)
      {
        T x {[](int i, int) { return i / G; }};

        auto r = to_array(eve::try_each_group_position(x, g));

        TTS_EQUAL(std::ssize(r), T::size() / G);

        for (int i = 0; i != T::size() / G; ++i) {
          T to_offset {0};
          for (auto permutation : r) {
            to_offset += eve::if_else(permutation == i, T{1}, T{0});
          }
          TTS_EXPECT(eve::all(to_offset == 1)) << to_offset << " " << i;
        }
      });
};

TTS_CASE_TPL("Check behavior of try_each_group_position_logical", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  for_each_group_size<T>(
      [&]<std::ptrdiff_t G>(eve::fixed<G> g)
      {
        T x = [](int i, int) { return i / G; };

        // Check that the group will be everywhere.
        for (int group_num = 0; group_num != T::size() / G; ++group_num) {
          auto r = to_array(eve::try_each_group_position(x == group_num, g));
          TTS_EQUAL(std::ssize(r), T::size() / G);

          int count = 0;
          for (auto permutation : r) {
            count += eve::count_true(permutation);
          }
          TTS_EQUAL(count, T::size());
        }
      });
};

} // namespace
