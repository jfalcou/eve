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

#include <eve/as.hpp>
#include <eve/detail/has_abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/traits/cardinal.hpp>
#include <eve/traits/element_type.hpp>

#include <array>
#include <bit>
#include <optional>

namespace eve::detail
{
  //================================================================================================
  // Store the top bits of a logical Pack to optimize some boolean processing
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
    using wide_t  = as_wide_t<element_type_t<Pack>>;
    using raw_t   = std::conditional_t< has_aggregated_abi_v<Pack>
                                      , std::array< top_bits<wide_t> , replications()>
                                      , std::uint32_t
                                      >;

    raw_t raw;

    //----------------------------------------------------------------------------------------------
    // This helper simplify all aggregate implementation
    template<typename Operation>
    static constexpr void iterate( top_bits& dst, top_bits const& src, Operation op )
    {
      if constexpr( has_aggregated_abi_v<Pack> )
      {
        [&]<std::size_t... I>(std::index_sequence<I...> const&)
        {
          (op(dst.raw[I], src.raw[I]),...);
        }(std::make_index_sequence<replications()>{});
      }
      else
      {
        op(dst.raw, src.raw);
      }
    }

    //----------------------------------------------------------------------------------------------
    // Constructors
    constexpr top_bits() {}

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

        // Smaller cardinal need one more mask to remove unrequired bits
        constexpr auto ec = expected_cardinal_v<element_type_t<Pack>,typename Pack::abi_type>;
        if constexpr( cardinal_v<Pack> < ec )
        {
          constexpr std::uint32_t mask = (1ULL << cardinal_v<Pack>) - 1;
          raw &= mask;
        }
      }
    }

    //----------------------------------------------------------------------------------------------
    // Non-0 top_bits is convertible to true
    explicit constexpr operator bool() const noexcept
    {
      if constexpr( has_aggregated_abi_v<Pack> )
      {
        for(auto const& b : raw)
          if(!static_cast<bool>(b)) return false;

        return true;
      }
      else
      {
        return raw;
      }
    }

    //----------------------------------------------------------------------------------------------
    // Comparison operators
    constexpr auto operator<=>(top_bits const&)const  noexcept = default;

    //----------------------------------------------------------------------------------------------
    // Bits manipulations
    friend constexpr top_bits operator|(top_bits const& l, top_bits const& r) noexcept
    {
      top_bits that(l);
      that |= r;
      return that;
    }

    friend constexpr top_bits operator&(top_bits const& l, top_bits const& r) noexcept
    {
      top_bits that(l);
      that &= r;
      return that;
    }

    constexpr top_bits operator~() const noexcept
    {
      top_bits r;
      iterate( r, *this, [](auto& dst, auto const& src) { dst = ~src; } );
      return r;
    }

    constexpr top_bits& operator&=(top_bits const& other) noexcept
    {
      iterate( *this, other, [](auto& dst, auto const& src) { dst &= src; } );
      return *this;
    }

    constexpr top_bits& operator|=(top_bits const& other) noexcept
    {
      iterate( *this, other, [](auto& dst, auto const& src) { dst |= src; } );
      return *this;
    }
  };

/*
  // TODO : functions ? constructors ?
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

  //------------------------------------------------------------------------------------------------
  // Find the index of the first true bit if any
  template <typename Pack>
  std::optional<std::size_t> first_true(const top_bits<Pack>& x) noexcept
  {
    if constexpr( has_aggregated_abi_v<Pack> )
    {
      std::uint32_t offset = x.raw.size();
      std::uint32_t mask;

      [&]<std::size_t... I>(auto r, std::index_sequence<I...> const&)
      {
        bool status;

        ((
            status = !r[I]
          , offset = status ? offset  : I
          , mask   = status ? mask    : r[I].raw
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

  //------------------------------------------------------------------------------------------------
  // Checks everything is set in a given top_bits
  template <typename Pack> bool all_true(const top_bits<Pack>& x) noexcept
  {
    if constexpr( has_aggregated_abi_v<Pack> )
    {
      for(auto const& b : x.raw)
        if(!all_true(b)) return false;

      return true;
    }
    else
    {
      constexpr std::uint32_t mask = (1ULL << cardinal_v<Pack>) - 1ULL;
      return x.raw == mask;
    }
  }
}
