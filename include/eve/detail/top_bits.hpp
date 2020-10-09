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
  //================================================================================================
  // Store the top bots of a logical Pack to optimize some boolean processing
  //================================================================================================
  template<typename Pack>
  struct top_bits
  {
    // Do we have more than one block of bits ?
    static constexpr auto replications()
    {
      if constexpr( has_aggregated_abi_v<Pack> )  return Pack::storage_type::replication;
      else                                        return 1ULL;
    }

    using replications_t = std::make_index_sequence<replications()>;

    // Compute proper storage
    using wide_t        = as_wide_t<element_type_t<Pack>>;
    using raw_t = std::conditional_t< has_aggregated_abi_v<Pack>
                                    , std::array< top_bits<wide_t> , replications()>
                                    , std::uint32_t
                                    >;

    raw_t raw;

    //----------------------------------------------------------------------------------------------

    top_bits() {}

    explicit top_bits(const Pack& x)
    {
      if constexpr( has_aggregated_abi_v<Pack> )
      {
        static constexpr auto rep = replications() - 1;

        [&]<std::size_t... I>(auto const& s, std::index_sequence<I...> const&)
        {
          ((raw[rep - I] = top_bits<wide_t>(s.template get<I>()) ),...);
        }(x.storage(), replications_t{});
      }
      else
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
    }

    // top_bits(const Pack& x, top_bits<Pack> ignore) : top_bits(x)
    // {
    //   *this &= ignore;
    // }

    explicit operator bool() const
    {
      if constexpr( has_aggregated_abi_v<Pack> )
      {
        bool r = true;
        for(auto const& b : raw) r = r && static_cast<bool>(b);
        return r;
      }
      else
      {
        return raw;
      }
    }

    //----------------------------------------------------------------------------------------------
    friend bool operator==(top_bits const& lhs, top_bits const& rhs) { return lhs.raw == rhs.raw; }
    friend bool operator!=(top_bits const& lhs, top_bits const& rhs) { return lhs.raw != rhs.raw; }
    friend bool operator< (top_bits const& lhs, top_bits const& rhs) { return lhs.raw  < rhs.raw; }
    friend bool operator> (top_bits const& lhs, top_bits const& rhs) { return lhs.raw  > rhs.raw; }
    friend bool operator<=(top_bits const& lhs, top_bits const& rhs) { return lhs.raw <= rhs.raw; }
    friend bool operator>=(top_bits const& lhs, top_bits const& rhs) { return lhs.raw >= rhs.raw; }

    // top_bits operator|(top_bits const& other) const { return {raw  | other.raw};  }
    // top_bits operator&(top_bits const& other) const { return {raw  & other.raw};  }
    // top_bits operator~()                      const { return {~raw};              }

    // top_bits& operator&=(top_bits const& other)
    // {
    //   raw &= other.raw;
    //   return *this;
    // }

    // top_bits& operator|=(top_bits const& other)
    // {
    //   raw |= other.raw;
    //   return *this;
    // }
  };

/*
  //================================================================================================
  // Aggregate case - stores an array of top_bits<smallest_pack>
  //================================================================================================
  template<typename Pack> requires(has_aggregated_abi_v<Pack>)
  struct top_bits<Pack>
  {
    using value_type                  = element_type_t<Pack>;
    static constexpr auto replication = replications();

    using wide_t = as_wide_t<value_type>;
    using raw_t  = std::array<top_bits<wide_t>,replication>;
    raw_t raw;

    top_bits() {}

    explicit top_bits(const Pack& x)
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
  };
*/


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

  template <typename Pack>
  std::optional<std::size_t> first_true(const top_bits<Pack>& x)
  {
    if constexpr( has_aggregated_abi_v<Pack> )
    {
      std::uint32_t offset = x.raw.size();
      std::uint32_t mask;

      constexpr auto rep = top_bits<Pack>::replications() - 1;
      [&]<std::size_t... I>(auto r, std::index_sequence<I...> const&)
      {
        bool status;

        ((
            status = !r[rep-I]
          , offset = status ? offset  : rep-I
          , mask   = status ? mask    : r[rep-I].raw
        ),...);

      }(x.raw, typename top_bits<Pack>::replications_t{});

      if(offset < x.raw.size())
      {
        offset = x.raw.size() - 1 - offset;
        offset *=  cardinal_v<typename top_bits<Pack>::wide_t>;
        return offset + std::countr_zero(mask) / sizeof(element_type_t<Pack>);
      }
      else
      {
        return std::nullopt;
      }
    }
    else
    {
      if(!x.raw) return std::nullopt;
      return std::countr_zero(x.raw) / sizeof(element_type_t<Pack>);
    }
  }


/*
  template <typename Pack>
  bool all_true(const top_bits<Pack>& x) {
    return x.raw == set_lower_n_bits(sizeof(Pack));
  }
*/
}
