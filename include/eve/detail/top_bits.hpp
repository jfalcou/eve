
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
#include <compare>
#include <ostream>

#include <iostream>

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

// movemask_raw --------------------

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
    else if constexpr( current_api == avx )
    {
      auto [l, h] = p.slice();
      auto s = h.size();
      if constexpr(sizeof(e_t) == 2) s *= 2;

      auto top = (std::uint32_t)movemask_raw(h);
      auto bottom = movemask_raw(l);

      return (top << s) | bottom;
    }
  }
}

// top_bits ---------------------------------

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

    // basic constructors ---------------------------------

    constexpr top_bits() = default;

    constexpr explicit top_bits(storage_type storage) : storage(storage) {}

    explicit top_bits(const logical_type& p)
    {
        if constexpr ( is_aggregated )
        {
          using half_logical = typename logical_type::storage_type::subvalue_type;
          auto [l, h] = p.slice();

          storage = {{ top_bits<half_logical>(l), top_bits<half_logical>(h) }};
        }
        else
        {
          if constexpr ( is_avx512_logical ) storage = p.storage();
          else                               storage = movemask_raw(p);

          *this &= top_bits(ignore_none_{});
        }
    }

    constexpr explicit top_bits(ignore_none_)
    {
      if constexpr( is_aggregated )
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;
        top_bits<half_logical> half {ignore_none_{}};
        storage[0] = half;
        storage[1] = half;
      }
      else storage = set_lower_n_bits<storage_type>(static_size * bits_per_element);
    }

    constexpr explicit top_bits(ignore_all_)
    {
      if constexpr( is_aggregated )
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;
        top_bits<half_logical> half {ignore_all_{}};
        storage[0] = half;
        storage[1] = half;
      }
      else storage = 0;
    }

    constexpr bool get(std::ptrdiff_t i) const
    {
      if constexpr ( !is_aggregated ) return storage & (1 << (i * bits_per_element));
      else
      {
        if (i < static_size / 2) return storage[0].get(i);
        else                     return storage[1].get(i - static_size / 2);
      }
    }

    // ordering
    std::strong_ordering operator<=>(const top_bits&) const = default;

    // bit operators =============================================

    constexpr top_bits& operator&=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] &= x.storage[0];
        storage[1] &= x.storage[1];
      }
      else storage &= x.storage;
      return *this;
    }

    constexpr friend top_bits operator&(const top_bits& x, const top_bits& y) {
      top_bits tmp(x);
      tmp &= y;
      return tmp;
    }

    constexpr top_bits& operator|=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] |= x.storage[0];
        storage[1] |= x.storage[1];
      }
      else storage |= x.storage;
      return *this;
    }

    constexpr friend top_bits operator|(const top_bits& x, const top_bits& y)
    {
      top_bits tmp(x);
      tmp |= y;
      return tmp;
    }

    constexpr top_bits& operator^=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] ^= x.storage[0];
        storage[1] ^= x.storage[1];
      }
      else storage ^= x.storage;
      return *this;
    }

    constexpr friend top_bits operator^(const top_bits& x, const top_bits& y)
    {
      top_bits tmp(x);
      tmp ^= y;
      return tmp;
    }

    constexpr friend top_bits operator~(const top_bits& x)
    {
      if constexpr ( !is_aggregated ) return top_bits{(storage_type)~x.storage} & top_bits{ignore_none_{}};
      else return top_bits{{ ~x.storage[0], ~x.storage[1] }};
    }

    // streaming ==============================================

    friend std::ostream& operator<<(std::ostream& o, const top_bits& x)
    {
      if constexpr ( is_aggregated ) return o << '[' << x.storage[0] << ", " << x.storage[1] << ']';
      else                           return o << x.storage;
    }
};

// ---------------------------------------------------------------------------------
// spread(top_bits)
//
// relevant stack overflow:
//   https://stackoverflow.com/a/24242696/5021064
//   https://stackoverflow.com/a/36491672/5021064

template <typename Logical>
EVE_FORCEINLINE Logical spread_one_bit_per_element(top_bits<Logical> mmask)
{
  using bits_wide = typename Logical::bits_type;

  // For non chars this will just spread mmask everywhere.
  // For chars each 8 bits of mmask go into their part
  const bits_wide spread_mask([&](int i, int) {
    int shift = 0;
    shift += (i >= 8);
    shift += (i >= 16);
    shift += (i >= 24);
    return (uint8_t)(mmask.storage >> (shift * 8));
  });

  // For not chars this just returns i.
  // For chars index computation is more complex.
  const bits_wide each_element_idx([&](int i, int) {
    int shift = 0;
    shift += (i >= 8);
    shift += (i >= 16);
    shift += (i >= 24);
    return (uint8_t) (1 << (i - 8 * shift));
  });

  const bits_wide bit_mask = spread_mask & each_element_idx;
  return Logical{(each_element_idx == bit_mask).storage()};
}

template <logical_simd_value Logical>
Logical spread(top_bits<Logical> mmask)
{
       if constexpr ( top_bits<Logical>::is_aggregated )         return Logical{{spread(mmask.storage[0]), spread(mmask.storage[1])}};
  else if constexpr ( top_bits<Logical>::is_avx512_logical )     return Logical(mmask.storage);
  else if constexpr ( top_bits<Logical>::bits_per_element == 1 ) return spread_one_bit_per_element(mmask);
}

// ---------------------------------------------------------------------------------

}  // namespace eve::detail
