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
#include <bit>
#include <compare>
#include <optional>
#include <ostream>

namespace eve::detail
{

//================================================================================================

  // Abstraction representing getting bits from logical on x86
  // For most cases - it's just 1 bit per value.
  // For shorts before AVX512 - it's 2 bits per value.

//================================================================================================

template <typename N>
EVE_FORCEINLINE constexpr N set_lower_n_bits(std::ptrdiff_t n) {
  using uint_res = make_integer_t<sizeof(N), unsigned>;

  if constexpr (std::same_as<std::uint64_t, uint_res>) {
    if (n == 64) return { static_cast<std::uint64_t>(-1) };
  }

  std::uint64_t res{1};
  res <<= n;
  res -= 1;
  return { static_cast<uint_res>(res) };
}

// movemask_raw --------------------

template <logical_simd_value Logical>
EVE_FORCEINLINE auto movemask_raw(Logical p)
{
  using ABI = abi_type_t<Logical>;
  using e_t = element_type_t<Logical>;

       if constexpr( !ABI::is_wide_logical ) return p.storage();
  else if constexpr( std::same_as<ABI, x86_128_> )
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
    else if constexpr( current_api == avx2 )         return (std::uint32_t)_mm256_movemask_epi8(p.storage());
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
    sizeof(element_type_t<Logical>) == 2 && !is_avx512_logical ? 2 : 1;

  private:
    EVE_FORCEINLINE static auto storage_type_impl()
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

    // constructors ---------------------------------

    EVE_FORCEINLINE constexpr top_bits() = default;

    EVE_FORCEINLINE constexpr explicit top_bits(storage_type storage) : storage(storage) {}

    // -- constructor(logical)

    EVE_FORCEINLINE explicit top_bits(const logical_type& p)
    {
        if constexpr ( is_aggregated )
        {
          using half_logical = typename logical_type::storage_type::subvalue_type;
          auto [l, h] = p.slice();

          storage = {{ top_bits<half_logical>(l), top_bits<half_logical>(h) }};
        }
        else
        {
          storage = movemask_raw(p);
          operator&=(top_bits(ignore_none_{}));
        }
    }

    // -- constructor(ignore)

    EVE_FORCEINLINE constexpr explicit top_bits(ignore_none_)
    {
      if constexpr( !is_aggregated ) storage = set_lower_n_bits<storage_type>(static_size * bits_per_element);
      else
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;
        top_bits<half_logical> half {ignore_none_{}};
        storage[0] = half;
        storage[1] = half;
      }
    }

    EVE_FORCEINLINE constexpr explicit top_bits(ignore_all_)
    {
      if constexpr( !is_aggregated ) storage = storage_type{0};
      else
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;
        top_bits<half_logical> half {ignore_all_{}};
        storage[0] = half;
        storage[1] = half;
      }
    }

    EVE_FORCEINLINE constexpr explicit top_bits(ignore_extrema_ ignore)
    {
      if constexpr( !is_aggregated )
      {
        storage = ~set_lower_n_bits<storage_type>(ignore.first_count_ * bits_per_element);
        storage &= set_lower_n_bits<storage_type>((static_size - ignore.last_count_) * bits_per_element);
        operator&=(top_bits(ignore_none));
      }
      else
      {
        using half_logical = typename logical_type::storage_type::subvalue_type;

        if (ignore.first_count_ >= static_size / 2)
        {
          ignore.first_count_ -= static_size / 2;
          storage = { top_bits<half_logical>(ignore_all), top_bits<half_logical>(ignore) };
          return;
        }

        if (ignore.last_count_ >= static_size / 2)
        {
          ignore.last_count_ -= static_size / 2;
          storage = { top_bits<half_logical>(ignore), top_bits<half_logical>(ignore_all) };
          return;
        }

        storage = {
          top_bits<half_logical>(ignore_first(ignore.first_count_)),
          top_bits<half_logical>(ignore_last(ignore.last_count_))
        };
      }
    }

    template <relative_conditional_expr Ignore>
      requires(Ignore::is_complete && !Ignore::is_inverted)
    EVE_FORCEINLINE constexpr explicit top_bits(Ignore) : top_bits{ignore_all} {}

    template <relative_conditional_expr Ignore>
      requires(Ignore::is_complete && Ignore::is_inverted)
    EVE_FORCEINLINE constexpr explicit top_bits(Ignore) : top_bits{ignore_none} {}

    template <relative_conditional_expr Ignore>
    EVE_FORCEINLINE constexpr explicit top_bits(Ignore ignore):
      top_bits{
        ignore_extrema_(
          ignore.offset(eve::as_<logical_type>{}),
          ignore.roffset(eve::as_<logical_type>{}))
      }
    {}

    // -- constructor: logical + ignore

    EVE_FORCEINLINE explicit top_bits(const logical_type &p, relative_conditional_expr auto ignore) : top_bits(p)
    {
      operator&=(top_bits(ignore));
    }

    // getters/setter ----------------------

    EVE_FORCEINLINE constexpr void set(std::ptrdiff_t i, bool x)
    {
      if constexpr ( !is_aggregated )
      {
        storage_type bit_mask = set_lower_n_bits<storage_type>(bits_per_element) << (i * bits_per_element);
        if ( x ) storage |= bit_mask;
        else     storage &= ~bit_mask;
      }
      else
      {
        if ( i < static_size / 2 ) storage[0].set(i, x);
        else                       storage[1].set(i - static_size / 2, x);
      }
    }

    EVE_FORCEINLINE constexpr bool get(std::ptrdiff_t i) const
    {
      if constexpr ( !is_aggregated ) return (storage & (storage_type{1} << (i * bits_per_element))) != 0;
      else
      {
        if ( i < static_size / 2 ) return storage[0].get(i);
        else                       return storage[1].get(i - static_size / 2);
      }
    }

    // miscellaneous -----------------------------------

    EVE_FORCEINLINE constexpr explicit operator bool()
    {
      if constexpr ( !is_aggregated ) return storage != storage_type{0};
      else
      {
        return (bool)storage[0] || (bool)storage[1];
      }
    }

    EVE_FORCEINLINE constexpr std::strong_ordering operator<=>(const top_bits&) const = default;

    // bit operators ------------------------------

    EVE_FORCEINLINE constexpr top_bits& operator&=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] &= x.storage[0];
        storage[1] &= x.storage[1];
      }
      else storage &= x.storage;
      return *this;
    }

    EVE_FORCEINLINE constexpr friend top_bits operator&(const top_bits& x, const top_bits& y) {
      top_bits tmp(x);
      tmp &= y;
      return tmp;
    }

    EVE_FORCEINLINE constexpr top_bits& operator|=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] |= x.storage[0];
        storage[1] |= x.storage[1];
      }
      else storage |= x.storage;
      return *this;
    }

    EVE_FORCEINLINE constexpr friend top_bits operator|(const top_bits& x, const top_bits& y)
    {
      top_bits tmp(x);
      tmp |= y;
      return tmp;
    }

    EVE_FORCEINLINE constexpr top_bits& operator^=(const top_bits& x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] ^= x.storage[0];
        storage[1] ^= x.storage[1];
      }
      else storage ^= x.storage;
      return *this;
    }

    EVE_FORCEINLINE constexpr friend top_bits operator^(const top_bits& x, const top_bits& y)
    {
      top_bits tmp(x);
      tmp ^= y;
      return tmp;
    }

    EVE_FORCEINLINE constexpr friend top_bits operator~(const top_bits& x)
    {
      if constexpr ( !is_aggregated ) return top_bits{(storage_type)~x.storage} & top_bits{ignore_none_{}};
      else return top_bits{{ ~x.storage[0], ~x.storage[1] }};
    }

    // streaming ----------------------------------

    EVE_FORCEINLINE friend std::ostream& operator<<(std::ostream& o, const top_bits& x)
    {
      if constexpr ( is_aggregated ) return o << '[' << x.storage[0] << ", " << x.storage[1] << ']';
      else                           return o << x.storage;
    }
};

// ---------------------------------------------------------------------------------
// to_logical(top_bits)
//

template <logical_simd_value Logical>
EVE_FORCEINLINE Logical to_logical(top_bits<Logical> mmask)
{
       if constexpr ( top_bits<Logical>::is_aggregated )         return Logical{{to_logical(mmask.storage[0]), to_logical(mmask.storage[1])}};
  else if constexpr ( top_bits<Logical>::is_avx512_logical )     return Logical(mmask.storage);
  else
  {
    // Idea is: put a corresponding part of mmask in each element
    //          prepopulate an index in each element (as if true)
    //          bitwise &
    //
    // relevant stack overflow:
    //   https://stackoverflow.com/a/24242696/5021064
    //   https://stackoverflow.com/a/36491672/5021064
    using bits_wide = typename Logical::bits_type;
    using bits_et   = element_type_t<bits_wide>;

    static constexpr auto bits_per_element = top_bits<Logical>::bits_per_element;
    static constexpr auto element_mask = set_lower_n_bits<bits_et>(bits_per_element);

    bits_wide true_mmask([&](int i, int) {
      int shift = 0;

      shift += (i >= 8);   // only true for short on avx (second uint16_t) and chars (second uint8_t)
      shift += (i >= 16);  // only true for chars on avx (third uint8_t)
      shift += (i >= 24);  // only true for chars on avx (4th uint8_t)

      i -= 8 * shift;

      return (bits_et)(element_mask << (i * bits_per_element));
    });

    bits_wide actual_mmask([&](int i, int) {
      int shift = 0;

      shift += (i >= 8);  // second uint16_t or uint8_t
      shift += (i >= 16); // third uint8_t
      shift += (i >= 24); // 4th uint8_t

      shift *= 8 * bits_per_element;

      return (bits_et)(mmask.storage >> shift);
    });

    bits_wide test = actual_mmask & true_mmask;
    return bit_cast( test == true_mmask, as_<Logical>{} );
  }
}

// ---------------------------------------------------------------------------------
// all/any/first_true

template <logical_simd_value Logical>
EVE_FORCEINLINE bool all(top_bits<Logical> mmask)
{
  return mmask == top_bits<Logical>(ignore_none);
}

template <logical_simd_value Logical>
EVE_FORCEINLINE bool any(top_bits<Logical> mmask)
{
  return (bool)mmask;
}

template <logical_simd_value Logical>
EVE_FORCEINLINE std::ptrdiff_t first_true_guaranteed(top_bits<Logical> mmask)
{
  if constexpr ( !top_bits<Logical>::is_aggregated )
  {
    auto st = [](auto m)
    {
      if constexpr(!Logical::abi_type::is_wide_logical) return m.value; else return m;
    }(mmask.storage);

    return std::countr_zero(st) / top_bits<Logical>::bits_per_element;
  }
  else
  {
    auto half_mmask = mmask.storage[1];
    int offset = Logical::static_size / 2;

    // trying to make a cmove (otherwise does not cmove, I think I tested)
    if (mmask.storage[0])
    {
      offset = 0;
      half_mmask = mmask.storage[0];
    }

    return first_true_guaranteed(half_mmask) + offset;
  }
}

template <logical_simd_value Logical>
EVE_FORCEINLINE std::optional<std::ptrdiff_t> first_true(top_bits<Logical> mmask)
{
  if ( !detail::any(mmask) ) return {};
  return first_true_guaranteed(mmask);
}

}  // namespace eve::detail
