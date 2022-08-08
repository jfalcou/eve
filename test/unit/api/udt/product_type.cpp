//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0-1.0
**/
//==================================================================================================
#include "test.hpp"

#include <eve/product_type.hpp>

template <typename T>
struct wrapper
{
  using is_like = T;
};

template<> struct eve::supports_like<wrapper<int>, std::int64_t> : std::true_type {};

TTS_CASE("like concet")
{
  { eve::like<int> auto _ = 3; (void)_; }
  { eve::like<int> auto _ = wrapper<int>{}; (void)_; }

  TTS_CONSTEXPR_EXPECT_NOT((eve::like<wrapper<int>, char>));
  { eve::like<std::int64_t> auto _ = wrapper<int>{}; (void)_; }
};

struct supports_all_ops :
  eve::struct_support<supports_all_ops, int, std::int64_t>
{
  friend decltype(auto) m0(eve::like<supports_all_ops> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) m1(eve::like<supports_all_ops> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }

  friend auto& operator+=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) += m0(other);
    m1(self) += m1(other);
    return self;
  }

  friend auto& operator-=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) -= m0(other);
    m1(self) -= m1(other);
    return self;
  }

  friend auto& operator*=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) *= m0(other);
    m1(self) *= m1(other);
    return self;
  }

  friend auto& operator/=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) /= m0(other);
    m1(self) /= m1(other);
    return self;
  }

  friend auto& operator%=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) %= m0(other);
    m1(self) %= m1(other);
    return self;
  }

  friend auto& operator^=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) ^= m0(other);
    m1(self) ^= m1(other);
    return self;
  }

  friend auto& operator&=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) &= m0(other);
    m1(self) &= m1(other);
    return self;
  }

  friend auto& operator|=(eve::like<supports_all_ops> auto& self,
                          eve::like<supports_all_ops> auto const& other) {
    m0(self) |= m0(other);
    m1(self) |= m1(other);
    return self;
  }

  friend auto& operator<<=(eve::like<supports_all_ops> auto& self,
                          eve::integral_value auto s) {
    m0(self) <<= s;
    m1(self) <<= s;
    return self;
  }

  friend auto& operator>>=(eve::like<supports_all_ops> auto& self,
                           eve::integral_value auto s) {
    m0(self) >>= s;
    m1(self) >>= s;
    return self;
  }
};

struct supports_no_ops : eve::struct_support<supports_no_ops, int, std::int64_t>
{
  using eve_disable_ordering = void;

  friend decltype(auto) m0(eve::like<supports_no_ops> auto&& self)
  {
    return get<0>(std::forward<decltype(self)>(self));
  }

  friend decltype(auto) m1(eve::like<supports_no_ops> auto&& self)
  {
    return get<1>(std::forward<decltype(self)>(self));
  }
};

template <typename T>
concept operators_test = requires(T x, T y) {
  { x += y  } -> std::same_as<T&>;
  { x + y   } -> std::same_as<T>;
  { x -= y  } -> std::same_as<T&>;
  { x - y   } -> std::same_as<T>;
  { x *= y  } -> std::same_as<T&>;
  { x * y   } -> std::same_as<T>;
  { x /= y  } -> std::same_as<T&>;
  { x / y   } -> std::same_as<T>;
  { x %= y  } -> std::same_as<T&>;
  { x % y   } -> std::same_as<T>;
  { x ^= y  } -> std::same_as<T&>;
  { x ^ y   } -> std::same_as<T>;
  { x &= y  } -> std::same_as<T&>;
  { x & y   } -> std::same_as<T>;
  { x |= y  } -> std::same_as<T&>;
  { x | y   } -> std::same_as<T>;
  { x <<= 1 } -> std::same_as<T&>;
  { x << 1  } -> std::same_as<T>;
};

template <typename T>
concept eve_totally_ordered = requires(T x, T y) {
  { x < y  } -> eve::logical_value;
  { x <= y } -> eve::logical_value;
  { x == y } -> eve::logical_value;
  { x != y } -> eve::logical_value;
  { x >= y } -> eve::logical_value;
  { x >  y } -> eve::logical_value;
};

template <typename T>
concept supports_plus_test = requires(T x, T y) {
  { x + y };
};

TTS_CASE("struct_support")
{
  { eve::product_type    auto _ = supports_all_ops{}; (void)_; }
  { operators_test       auto _ = supports_all_ops{}; (void)_; }
  { std::regular         auto _ = supports_all_ops{}; (void)_; }
  { std::totally_ordered auto _ = supports_all_ops{}; (void)_; }
  { operators_test       auto _ = eve::wide<supports_all_ops>{}; (void)_; }
  { eve_totally_ordered  auto _ = eve::wide<supports_all_ops>{}; (void)_; }
  TTS_PASS("all types check out");

  { eve::product_type auto _ = supports_no_ops{}; (void)_; }
  { std::semiregular  auto _ = supports_no_ops{}; (void)_; }

  TTS_CONSTEXPR_EXPECT_NOT(supports_plus_test<supports_no_ops>);
  TTS_CONSTEXPR_EXPECT_NOT(std::totally_ordered<supports_no_ops>);
  // TTS_CONSTEXPR_EXPECT_NOT(supports_plus_test<eve::wide<supports_no_ops>>);
  TTS_CONSTEXPR_EXPECT_NOT(std::totally_ordered<eve::wide<supports_no_ops>>);
};

TTS_CASE("product_type construction")
{
  supports_all_ops a{0, 1};
  TTS_EQUAL(m0(a), 0);
  TTS_EQUAL(m1(a), 1);
};
