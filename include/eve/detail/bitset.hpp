//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_BITSET_HPP_INCLUDED
#define EVE_DETAIL_BITSET_HPP_INCLUDED

#include <eve/function/scalar/popcnt.hpp>
#include <eve/detail/meta.hpp>
#include <type_traits>
#include <cstddef>
#include <cstdint>
#include <bitset>

namespace eve::detail
{
  // Round to next power of 2
  constexpr std::size_t nextpow2(std::size_t N)
  {
    std::size_t v0 = N - 1;
    std::size_t v1 = v0 | v0 >> 1;
    std::size_t v2 = v1 | v1 >> 2;
    std::size_t v3 = v2 | v2 >> 4;
    std::size_t v4 = v3 | v3 >> 8;
    std::size_t v5 = v4 | v4 >> 16;

    return v0 ? v5 + 1 : 1;
  };

  // Compute how many bytes is N bits
  constexpr std::size_t bitset_size(std::size_t N)
  {
    return nextpow2((N < 8) ? 1 : (N / 8 + (N % 8 ? 1 : 0)));
  };

  // Small N optimized bitset implementation
  template<std::size_t N>
  struct bitset
  {
    static constexpr std::size_t bitmask = (N == 64) ? ~0ULL : (1ULL << N) - 1;
    using bits_type                      = make_integer_t<bitset_size(N), unsigned>;

    constexpr bitset() noexcept
        : bits_{}
    {
    }
    constexpr bitset(bitset const &v) noexcept
        : bits_{v.bits_}
    {
    }
    constexpr bitset(std::size_t n) noexcept
        : bits_{static_cast<bits_type>(n & bitmask)}
    {
    }

    bitset &reset() noexcept
    {
      bits_ = 0U;
      return *this;
    }
    bitset &reset(std::size_t p) noexcept
    {
      bits_ = bits_ & ~((1ULL << p));
      return *this;
    }

    bitset &set() noexcept
    {
      bits_ = ~0ULL;
      return *this;
    }
    bitset &set(std::size_t p, bool v = true) noexcept
    {
      reset(p);
      bits_ |= (std::size_t(v) << p);
      return *this;
    }

    bitset &flip()
    {
      bits_ = ~bits_;
      return *this;
    }
    bitset &flip(std::size_t p)
    {
      bits_ ^= (1ULL << p);
      return *this;
    }

    constexpr bool operator[](std::size_t p) const noexcept { return bits_ & (1ULL << p); }

    constexpr bool test(std::size_t p) const
    {
      if(p > N) throw std::out_of_range{"Bit index is out of range"};
      return this->operator[](p);
    }

    static constexpr std::size_t size() noexcept { return N; }

    std::size_t    count() const noexcept { return boost::simd::popcnt(bits_); }
    constexpr bool all() const noexcept { return bits_ == bitmask; }
    constexpr bool any() const noexcept { return bits_ != 0; }
    constexpr bool none() const noexcept { return bits_ == 0; }

    constexpr bool operator==(bitset const &other) const noexcept { return bits_ == other.bits_; }
    constexpr bool operator!=(bitset const &other) const noexcept { return bits_ != other.bits_; }

    constexpr bitset operator>>(std::size_t pos) const { return bitset{bits_ >> pos}; }
    constexpr bitset operator<<(std::size_t pos) const { return bitset{bits_ << pos}; }

    constexpr bitset &operator<<=(std::size_t pos)
    {
      bits_ <<= pos;
      return *this;
    }
    constexpr bitset &operator>>=(std::size_t pos)
    {
      bits_ >>= pos;
      return *this;
    }

    constexpr bitset &operator&=(const bitset<N> &other) noexcept
    {
      bits_ &= other.bits_;
      return *this;
    }

    constexpr bitset &operator|=(const bitset<N> &other) noexcept
    {
      bits_ |= other.bits_;
      return *this;
    }

    constexpr bitset &operator^=(const bitset<N> &other) noexcept
    {
      bits_ ^= other.bits_;
      return *this;
    }

    constexpr bitset operator~() const noexcept { return bitset(~bits_); }

    constexpr operator std::bitset<N>() noexcept { return std::bitset<N>{bits_}; }

    constexpr unsigned long      to_ulong() const noexcept { return bits_; }
    constexpr unsigned long long to_ullong() const noexcept { return bits_; }

  private:
    bits_type bits_;
  };

  template<std::size_t N>
  std::ostream &operator<<(std::ostream &os, bitset<N> const &b)
  {
    os << b.to_ullong();
    return os;
  }

  template<std::size_t N>
  struct select_bitset : std::conditional<(N > 64), std::bitset<N>, bitset<N>>
  {
  };
}

namespace eve
{
  // Optimize small bitset if N <= 64bits - else use std::bitset
  template<std::size_t N>
  using bitset = typename detail::select_bitset<N>::type;
}

#endif
