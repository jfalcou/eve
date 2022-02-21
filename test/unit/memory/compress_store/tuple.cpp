//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================

#include "test.hpp"

#include <eve/module/core/regular/compress_store.hpp>
#include <eve/memory/soa_ptr.hpp>

#include <random>

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

EVE_TEST_TYPES( "Check compress store behaviour with tuples ", eve::test::simd::all_types)
<typename T>(eve::as<T>)
{
  using N   = eve::fixed<T::size()>;
  using e_t = eve::element_type_t<T>;
  using s_t = tuple_t<e_t>;
  using w_t = eve::wide<s_t, N>;

  const w_t x{
    [](auto i, auto)  { return s_t{ static_cast<std::int8_t>('a'+i)
                                  , static_cast<e_t>(i + 1)
                                  , 1.5*(1+i)
                                  };
    }
  };

  alignas(w_t::size() * sizeof(std::int8_t)) std::array<std::int8_t, w_t::size()> data0;
  alignas(w_t::size() * sizeof(e_t        )) std::array<e_t        , w_t::size()> data1;
  alignas(w_t::size() * sizeof(double     )) std::array<double     , w_t::size()> data2;

  using u_ptr = eve::soa_ptr<std::int8_t*, e_t*, double*>;

  auto test = [&](auto ptr, auto mask, auto ignore) {
    data0.fill(0);
    data1.fill(0);
    data2.fill(0);

    u_ptr res = eve::unsafe(eve::compress_store[ignore])(x, mask, ptr);

    int f_i = ignore.offset(eve::as(mask));
    int l_i = f_i + ignore.count(eve::as(mask));
    int o = f_i;
    for (int i = f_i; i != l_i; ++i) {
      if (mask.get(i)) {
        s_t elem = x.get(i);
        TTS_EQUAL(data0[o], get<0>(elem));
        TTS_EQUAL(data1[o], get<1>(elem));
        TTS_EQUAL(data2[o], get<2>(elem));
        ++o;
      }
    }

    TTS_EQUAL(o, (get<0>(res) - data0.data()));
    TTS_EQUAL(o, (get<1>(res) - data1.data()));
    TTS_EQUAL(o, (get<2>(res) - data2.data()));
  };

  eve::soa_ptr ptr1{ data0.data(), data1.data(), data2.data() };
  eve::soa_ptr ptr2{ data0.data(), eve::as_aligned(data1.data(), N{}), data2.data() };

  constexpr auto seed = sizeof(e_t) + T::size();
  std::mt19937 g(seed);
  std::uniform_int_distribution<short> d(0, 1);

  auto random_mask = [&]() mutable
  {
    eve::logical<eve::wide<e_t, N>> m {false};
    for( int i = 0; i != N{}(); ++i ) { m.set(i, d(g) == 1); }
    return m;
  };

  for (int i = 0; i < 100; ++i) {
    test(ptr1, random_mask(), eve::ignore_none);
    test(ptr2, random_mask(), eve::ignore_none);
    test(ptr1, random_mask(), eve::ignore_first(1));
    test(ptr1, random_mask(), eve::ignore_extrema(0, 1));
  }
};

TTS_CASE( "explicit test case")
{
  std::array<std::int32_t, 2> out_ints {0, 0};
  std::array<std::uint8_t, 2> out_bytes {0, 0};
  using s_t = kumi::tuple<std::int32_t, std::uint8_t>;

  eve::wide<s_t, eve::fixed<4>> x {
    s_t{1, (std::uint8_t)2},
    s_t{3, (std::uint8_t)4},
    s_t{5, (std::uint8_t)6},
    s_t{7, (std::uint8_t)8},
  };

  eve::logical<eve::wide<std::int16_t, eve::fixed<4>>> m { true, false, true, false};

  auto r = eve::safe(eve::compress_store)(x, m, eve::soa_ptr{out_ints.data(), out_bytes.data()});
  TTS_EQUAL(get<0>(r), out_ints.end());
  TTS_EQUAL((std::ptrdiff_t)get<1>(r), (std::ptrdiff_t)out_bytes.end());

  TTS_EQUAL(out_ints[0], 1);
  TTS_EQUAL(out_ints[1], 5);
  TTS_EQUAL(out_bytes[0], 2);
  TTS_EQUAL(out_bytes[1], 6);
};
