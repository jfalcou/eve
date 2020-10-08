//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE
  Copyright 2020 Denis YAROSHEVSKIY

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/has_abi.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/as.hpp>
#include <optional>
#include <array>
#include <bit>

namespace eve::detail
{
  template<typename Pack, bool isAggregated = has_aggregated_abi_v<Pack> >
  struct top_bits;

  //================================================================================================
  // Non-aggregate case - stores a simple uint32
  //================================================================================================
  template<typename Pack> struct top_bits<Pack,false>
  {
    std::uint32_t raw;

    top_bits() {}

    top_bits(const Pack& x)
    {
      if constexpr( std::same_as<typename Pack::abi_type,x86_128_>)
      {
        raw = _mm_movemask_epi8((__m128i)(x.storage()));
      }
      else if constexpr( std::same_as<typename Pack::abi_type,x86_256_>)
      {
        raw = _mm256_movemask_epi8((__m256i)(x.storage()));
      }
    }

    top_bits(const Pack& x, top_bits<Pack> ignore) : top_bits(x)
    {
      *this &= ignore;
    }

    explicit operator bool() const { return raw; }

    top_bits operator|(top_bits const& other) const { return {raw  | other.raw};  }
    top_bits operator&(top_bits const& other) const { return {raw  & other.raw};  }
    top_bits operator~()                      const { return {~raw};              }

    top_bits& operator&=(top_bits const& other)
    {
      raw &= other.raw;
      return *this;
    }

    top_bits& operator|=(top_bits const& other)
    {
      raw |= other.raw;
      return *this;
    }

    std::optional<std::uint32_t> first_true() const
    {
      if(!raw) return std::nullopt;

      return std::countr_zero(raw) / sizeof(element_type_t<Pack>);
    }
  };

  //================================================================================================
  // Aggregate case - stores an array of top_bits<smallest_pack>
  //================================================================================================
  template<typename Pack> struct top_bits<Pack, true>
  {
    using value_type                  = element_type_t<Pack>;
    static constexpr auto replication = Pack::storage_type::replication;

    using wide_t = as_wide_t<value_type>;
    using raw_t  = std::array<top_bits<wide_t>,replication>;
    raw_t raw;

    top_bits() {}

    top_bits(const Pack& x)
    {
      [&]<std::size_t... I>(auto const& s, std::index_sequence<I...> const&)
      {
        ((raw[replication - 1 - I] = top_bits<wide_t>(s.template get<I>()) ),...);
      }(x.storage(), std::make_index_sequence<replication>{});
    }

    top_bits(const Pack& x, top_bits<Pack> ignore) : top_bits(x)
    {
      *this &= ignore;
    }

    explicit operator bool() const
    {
      bool r = true;
      for(auto const& b : raw) r = r && static_cast<bool>(b);
      return r;
    }

    top_bits operator|(top_bits const& other) const
    {
      top_bits r(*this);
      r |= other;
      return r;
    }

    top_bits operator&(top_bits const& other) const
    {
      top_bits r(*this);
      r &= other;
      return r;
    }

    top_bits operator~() const
    {
      top_bits r;
      [&]<std::size_t... I>(std::index_sequence<I...> const&)
      {
        ((r.raw[I] = ~raw[I]),...);
      }(std::make_index_sequence<replication>{});

      return r;
    }

    top_bits& operator&=(top_bits const& other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...> const&)
      {
        ((raw[I] &= other.raw[I] ),...);
      }(std::make_index_sequence<replication>{});

      return *this;
    }

    top_bits& operator|=(top_bits const& other)
    {
      [&]<std::size_t... I>(std::index_sequence<I...> const&)
      {
        ((raw[I] |= other.raw[I] ),...);
      }(std::make_index_sequence<replication>{});

      return *this;
    }

    std::optional<std::uint32_t> first_true() const
    {
      std::uint32_t r = cardinal_v<Pack>;

      for(auto e : raw)
      {
        auto ft = e.first_true();
        r -= cardinal_v<wide_t>;
        if(ft) return {*ft + r};
      }

      return std::nullopt;
    }
  };

  template<typename Pack>
  bool operator==(top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw == rhs.raw;
  }

  template<typename Pack>
  bool operator!=(top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw != rhs.raw;
  }

  template<typename Pack>
  bool operator< (top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw  < rhs.raw;
  }

  template<typename Pack>
  bool operator> (top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw  > rhs.raw;
  }

  template<typename Pack>
  bool operator<=(top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw <= rhs.raw;
  }

  template<typename Pack>
  bool operator>=(top_bits<Pack> const& lhs, top_bits<Pack> const& rhs)
  {
    return lhs.raw >= rhs.raw;
  }

/*
  template <typename Pack>
  top_bits<Pack> ignore_first_n_mask() {
    return top_bits<Pack>{set_lower_n_bits(sizeof(Pack))};
  }

  template <typename Pack>
  top_bits<Pack> ignore_first_n_mask(std::uint32_t n) {
    return top_bits<Pack>{~set_lower_n_bits(n * sizeof(scalar_t<Pack>))};
  }

  template <typename Pack>
  top_bits<Pack> ignore_first_n(const top_bits<Pack>& x) {
    return x;
  }

  template <typename Pack>
  top_bits<Pack> ignore_first_n(const top_bits<Pack>& x, std::uint32_t n) {
    return x & ignore_first_n_mask<Pack>(n);
  }

  template <typename Pack>
  top_bits<Pack> ignore_last_n_mask() {
    return ignore_first_n_mask<Pack>();
  }

  template <typename Pack>
  top_bits<Pack> ignore_last_n_mask(std::uint32_t n) {
    return top_bits<Pack>{
        set_lower_n_bits(sizeof(Pack) - n * sizeof(scalar_t<Pack>))};
  }

  template <typename Pack>
  top_bits<Pack> ignore_last_n(const top_bits<Pack>& x) {
    return x;
  }

  template <typename Pack>
  top_bits<Pack> ignore_last_n(const top_bits<Pack>& x, std::uint32_t n) {
    return x & ignore_last_n_mask<Pack>(n);
  }

  template <typename Pack>
  top_bits<Pack> combine_ignore(const top_bits<Pack>& x) {
    return x;
  }

  template <typename Pack>
  top_bits<Pack> combine_ignore(const top_bits<Pack>& x, const top_bits<Pack>& ignore) {
    return x & ignore;
  }
*/

  template <typename Pack> auto first_true(const top_bits<Pack>& x)
  {
    return x.first_true();
  }

/*
  template <typename Pack>
  bool all_true(const top_bits<Pack>& x) {
    return x.raw == set_lower_n_bits(sizeof(Pack));
  }
*/
}
