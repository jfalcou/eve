//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/module/core.hpp>

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

  TTS_EXPECT( eve::all(soa_ts == res) )
    << "\nG: "    << G
    << "\nFieldCount: " << FieldCount
     << std::hex
    << "\naos: " << aos_ts
    << "\nsoa: " << soa_ts
    << "\nres: " << res << "\n"
    << std::dec;

  if constexpr ( G == 1 )
  {
    auto back = kumi::apply(eve::interleave, res);
    TTS_EXPECT( eve::all(aos_ts == back) );
  }
}

// To increase the number of cases,
// since we don't have any intrinsics code at the moment.
using less_test_types =  eve::test::wides < tts::types< std::int8_t, std::uint16_t,
                                                        std::int32_t, float,
                                                        std::uint64_t, double
                                          >           >::type;

TTS_CASE_TPL( "Check behavior of deinterleave on arithmetic data", less_test_types)
<typename T>(tts::type<T>)
{
  static constexpr std::ptrdiff_t max_fields_count = 5;

  eve::detail::for_<1, 1, max_fields_count + 1>
  ( [&]<int Fields>(std::integral_constant<int, Fields>)
  {
    // maybe unused for gcc bug
    [[maybe_unused]] static constexpr std::size_t max_group_size = (T::size() >= 64) ? 4 : T::size();
    [[maybe_unused]] static constexpr auto nn = std::countr_zero(max_group_size) + 1;
    [[maybe_unused]] static constexpr std::ptrdiff_t fields = Fields;

    eve::detail::for_<0, 1, nn>
    (
      [&]<int Shift>(std::integral_constant<int, Shift>)
      {
        static constexpr auto gs = 1 << Shift;
        deinterleave_groups_test<gs, fields, T>();
      }
    );
  });
};
