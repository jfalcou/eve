
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

#include <eve/arch/logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/detail/meta.hpp>

#include <array>

namespace eve::detail
{

//================================================================================================

  // Abstraction representing getting bits from logical on x86
  // For most cases - it's just 1 bit per value.
  // For shorts before AVX512 - it's 2 bits per value.

//================================================================================================

// bit utilities ---------------------

template <typename N>
constexpr std::uint32_t set_lower_n_bits(std::ptrdiff_t n) {
  std::uint64_t res{1};
  res <<= n;
  res -= 1;
  return static_cast<N>(res);
}

// ~bit utilities --------------------

template <logical_simd_value Logical>
struct top_bits
{
  static constexpr bool is_aggregated = has_aggregated_abi_v<Logical>;
  static constexpr bool is_avx512_logical = !abi_type_t<Logical>::is_wide_logical;
  static constexpr std::ptrdiff_t static_size = Logical::static_size;
  static constexpr std::ptrdiff_t bits_per_element =
    sizeof(element_type_t<Logical>) == 2 ? 2 : 1;

  private:
    static auto storage_type_impl()
    {
      using ABI = abi_type_t<Logical>;

      if constexpr ( is_aggregated )
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;
        return std::array<top_bits<half_logical>, 2>{};
      }
      else if constexpr ( is_avx512_logical )            return typename Logical::storage_type{};
      else if constexpr ( std::same_as<ABI, x86_128_> )  return std::uint16_t{};
      else                                               return std::uint32_t{};
    }

  public:

    using logical_type = Logical;
    using storage_type = decltype(top_bits::storage_type_impl());

    storage_type storage;

    constexpr bool get(std::ptrdiff_t i) const
    {
      if constexpr ( !is_aggregated ) return storage & (1 << (i * bits_per_element));
      else
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;

        if (i < static_size / 2) return storage[0].get(i);
        else                     return storage[1].get(i - static_size / 2);
      }
    }

    constexpr top_bits& operator&=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] &= x.storage[0];
        storage[1] &= x.storage[1];
      }
      else
      {
        storage &= x.storage;
      }
      return *this;
    }

    constexpr friend top_bits operator&(const top_bits& x, const top_bits& y) {
      top_bits tmp(x);
      tmp &= y;
      return tmp;
    }
};

template <logical_simd_value Logical>
constexpr top_bits<Logical> ignore_to_top_bits(ignore_none_)
{
  if constexpr ( top_bits<Logical>::is_aggregated )
  {
    using half_logical = typename Logical::storage_type::subvalue_type;
    auto half = ignore_to_top_bits<half_logical>(ignore_none_{});
    return { half, half };
  }
  else
  {
    using storage_type = typename top_bits<Logical>::storage_type;
    return { set_lower_n_bits<storage_type>(
      top_bits<Logical>::static_size * top_bits<Logical>::bits_per_element)
    };
  }
}

template <logical_simd_value Logical>
auto movemask_raw(Logical p)
{
  using ABI = abi_type_t<Logical>;
  using e_t = element_type_t<Logical>;

  if constexpr( std::same_as<ABI, x86_128_>)
  {
         if constexpr( std::is_same_v<e_t, float > ) return (std::uint16_t)_mm_movemask_ps(p.storage());
    else if constexpr( std::is_same_v<e_t, double> ) return (std::uint16_t)_mm_movemask_pd(p.storage());
    else if constexpr( sizeof(e_t) == 8 )            return (std::uint16_t)_mm_movemask_pd((__m128d)p.storage());
    else if constexpr( sizeof(e_t) == 4 )            return (std::uint16_t)_mm_movemask_ps((__m128)p.storage());
    else                                             return (std::uint16_t)_mm_movemask_epi8(p.storage());
  }
  else if constexpr( std::same_as<ABI ,x86_256_>)
  {
         if constexpr( std::is_same_v<e_t, float > ) return (std::uint32_t)_mm256_movemask_ps(p.storage());
    else if constexpr( std::is_same_v<e_t, double> ) return (std::uint32_t)_mm256_movemask_pd(p.storage());
    else if constexpr( sizeof(e_t) == 8 )            return (std::uint32_t)_mm256_movemask_pd((__m256d)p.storage());
    else if constexpr( sizeof(e_t) == 4 )            return (std::uint32_t)_mm256_movemask_ps((__m256)p.storage());
    else if constexpr( current_api >= avx2 )         return (std::uint32_t)_mm256_movemask_epi8(p.storage());
    else if constexpr( current_api == avx ) {
      auto [l, h] = p.slice();
      auto s = h.size();
      if constexpr(sizeof(e_t) == 2) s *= 2;
      return  {(movemask(h) << s) | movemask(l)};
    }
  }
}

template <logical_simd_value Logical>
top_bits<Logical> movemask(Logical p)
{
  if constexpr ( top_bits<Logical>::is_aggregated )
  {
    auto [l, h] = p.slice();
    return {{ movemask(l), movemask(h) }};
  }
  else
  {
    top_bits<Logical> mmask;

    if constexpr ( top_bits<Logical>::is_avx512_logical ) mmask = { p.storage() };
    else                                                  mmask = { movemask_raw(p)} ;

    // clearing the garbage for smaller than expected wides.
    return mmask & ignore_to_top_bits<Logical>(ignore_none_{});
  }
}

}  // namespace eve::detail
