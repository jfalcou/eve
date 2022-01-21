//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"

#include <eve/function/deinterleave_groups.hpp>

#include <array>
#include <numeric>

template <typename T, std::size_t how_many>
auto read_ts(eve::element_type_t<T> const* ptr)
{
  auto read_and_advance = [&] () mutable {
    T res{ptr};
    ptr += T::size();
    return res;
  };

  return [&]<std::size_t... i>(std::index_sequence<i...>) {
    return kumi::tuple{ ((void)i, read_and_advance()) ... };
  }(std::make_index_sequence<how_many>{});
}

template <std::ptrdiff_t G, std::ptrdiff_t FieldCount, typename T>
void deinterleave_groups_test()
{
  constexpr std::ptrdiff_t block_size = (G < T::size()) ? T::size() : G;
  constexpr std::ptrdiff_t total_size = block_size * FieldCount;

  using e_t = eve::element_type_t<T>;
  using data_t = std::array<e_t, total_size>;

  constexpr auto elem = [](int field_num, int in_field_num) {
    if constexpr ( FieldCount <= 6 ) field_num += 0xa;

    constexpr int field_offset = sizeof(e_t) > 1 ? 8 : 4;

    constexpr int in_field_num_mask = (1 << field_offset) - 1;

    return (field_num << field_offset) | (in_field_num_mask & in_field_num);
  };

  data_t const aos = [&]{
    data_t res;

    int i = 0;

    int field_num = 0;
    for (int group_num = 0; group_num != total_size / G; ++group_num)
    {
      for (int in_group_num = 0; in_group_num != G; ++in_group_num)
      {
        int field_repeat = group_num / FieldCount;
        int in_field_num = field_repeat * G + in_group_num;
        res[i++] = elem(field_num, in_field_num);
      }
      field_num = (field_num + 1) % FieldCount;
    }

    return res;
  }();

  data_t const soa = [&]{
    data_t res;

    int i = 0;

    for (int field_num = 0; field_num != FieldCount; ++field_num) {
      for (int in_field_num = 0; in_field_num != total_size / FieldCount; ++in_field_num) {
        res[i++] = elem(field_num, in_field_num);
      }
    }

    return res;
  }();

  auto const aos_ts = read_ts<T, total_size / T::size()>(aos.data());
  auto const soa_ts = read_ts<T, total_size / T::size()>(soa.data());

  auto const res =
    kumi::apply(
      [] (auto ... in) { return eve::deinterleave_groups(eve::lane<G>, in...); },
      aos_ts
    );

  TTS_EXPECT( eve::all(soa_ts == res) ) << std::hex
    <<   "aos: " << aos_ts
    << "\nsoa: " << soa_ts
    << "\nres: " << res << "\n";
}

EVE_TEST_TYPES( "Check behavior of deinterleave on arithmetic data"
              , eve::test::simd::all_types
              )
<typename T>(eve::as<T>)
{
  deinterleave_groups_test<1, 2, T>();
};
