//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/memory/soa_ptr.hpp>

#include <eve/memory/aligned_ptr.hpp>

#include <array>

TTS_CASE("soa_ptr types")
{
  using i_s_ptr = eve::soa_ptr<int*, short*>;

  TTS_CONSTEXPR_EXPECT(kumi::product_type<i_s_ptr>);
  TTS_CONSTEXPR_EQUAL(std::tuple_size_v<i_s_ptr>, 2u);
  TTS_TYPE_IS((std::tuple_element_t<0, i_s_ptr>), int*);
  TTS_TYPE_IS((std::tuple_element_t<1, i_s_ptr>), short*);
  TTS_TYPE_IS(eve::value_type_t<i_s_ptr>, (kumi::tuple<int, short>));
};

TTS_CASE("soa_ptr, constructors")
{
  using u_p  = int*;
  using a_p  = eve::aligned_ptr<short, eve::fixed<4>>;
  using s_p  = eve::soa_ptr<u_p, a_p>;
  using ss_p = eve::soa_ptr<a_p, s_p>;

  std::array<int, 4> ints;
  alignas(8) std::array<short, 4> shorts;

  u_p ints_p {ints.data()};
  a_p shorts_p{shorts.data()};

  // Default constructor
  {
    TTS_CONSTEXPR_EXPECT(std::is_default_constructible_v<s_p>);
    TTS_CONSTEXPR_EXPECT(std::is_default_constructible_v<ss_p>);
  }

  // ptrs constructible
  {
    s_p part {ints_p, shorts_p};
    TTS_EQUAL(get<0>(part), ints_p);
    TTS_EQUAL(get<1>(part), shorts_p);

    ss_p full{shorts_p, part};

    TTS_EQUAL(get<0>(full), shorts_p);
    TTS_EQUAL(get<1>(full), part);
  }

  // tuple constructible
  {
    s_p soa {kumi::tuple{ints_p, shorts_p}};

    TTS_EQUAL(get<0>(soa), ints_p);
    TTS_EQUAL(get<1>(soa), shorts_p);
  }
};

TTS_CASE("soa_ptr, conversions")
{
  using u_p  = int*;
  using uc_p = int const*;
  using a_p = eve::aligned_ptr<short,        eve::fixed<4>>;
  using ac_p = eve::aligned_ptr<short const, eve::fixed<4>>;
  using s_p  = eve::soa_ptr<u_p,  a_p>;
  using sc_p = eve::soa_ptr<uc_p, ac_p>;

  std::array<int, 4> ints;
  alignas(8) std::array<short, 4> shorts;

  u_p ints_p {ints.data()};
  a_p shorts_p{shorts.data()};

  // basic conversion
  {
    s_p  from{ints_p, shorts_p};
    sc_p to{from};

    TTS_EQUAL(get<0>(to), get<0>(from));
    TTS_EQUAL(get<1>(to), get<1>(from));
  }

  // other conversions
  {
    TTS_CONSTEXPR_EXPECT((std::assignable_from<sc_p&, s_p>));
    TTS_CONSTEXPR_EXPECT((std::constructible_from<sc_p, s_p::tuple_type>));
    TTS_CONSTEXPR_EXPECT((std::totally_ordered_with<sc_p, s_p>));
  }
};

TTS_CASE("soa_ptr, +-<>")
{
  std::array<int, 4> ints;
  std::array<short, 4> shorts;

  eve::soa_ptr a{ints.data(), shorts.data()};
  eve::soa_ptr b{ints.data() + 1, shorts.data() + 1};

  TTS_LESS         (a, b);
  TTS_LESS_EQUAL   (a, b);
  TTS_LESS_EQUAL   (a, a);
  TTS_EQUAL        (a, a);
  TTS_NOT_EQUAL    (a, b);
  TTS_GREATER_EQUAL(b, b);
  TTS_GREATER      (b, a);

  TTS_EQUAL(-1, a - b);
  TTS_EQUAL(1,  b - a);
  TTS_EQUAL(0,  a - a);

  TTS_EQUAL((a + 1),  b);
  ++a;
  TTS_EQUAL(a, b);
  --a;
  TTS_EQUAL((a + 1),  b);

  TTS_EQUAL(a,  b - 1);
};
