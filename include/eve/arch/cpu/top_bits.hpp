//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/logical.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/conditional.hpp>
#include <eve/detail/bits.hpp>
#include <eve/detail/function/movemask.hpp>
#include <eve/detail/function/slice.hpp>
#include <eve/detail/meta.hpp>
#include <eve/traits/as_arithmetic.hpp>

#include <array>
#include <bit>
#include <compare>
#include <optional>
#include <ostream>

namespace eve
{
namespace detail
{
  template<std::ptrdiff_t size,
           std::ptrdiff_t bits_per_e,
           typename Int,
           relative_conditional_expr C>
  EVE_FORCEINLINE constexpr Int cond_to_int(C ignore)
  {
    constexpr std::ptrdiff_t static_bits_size = bits_per_e * size;
    if constexpr( C::is_complete && C::is_inverted )
    {
      return detail::set_lower_n_bits<Int>(static_bits_size);
    }
    else if constexpr( C::is_complete && !C::is_inverted ) return Int {0};
    else if constexpr( std::same_as<C, keep_last> )
    {
      Int res = ~detail::set_lower_n_bits<Int>((size - ignore.count_) * bits_per_e);
      res &= detail::set_lower_n_bits<Int>(static_bits_size);
      res &= cond_to_int<size, bits_per_e, Int>(ignore_none);
      return res;
    }
    else if constexpr( std::same_as<C, keep_first> )
    {
      Int res = ~detail::set_lower_n_bits<Int>(0);
      res &= detail::set_lower_n_bits<Int>(ignore.count_ * bits_per_e);
      res &= cond_to_int<size, bits_per_e, Int>(ignore_none);
      return res;
    }
    else if constexpr( std::same_as<C, ignore_first> )
    {
      return cond_to_int<size, bits_per_e, Int>(keep_last {size - ignore.count_});
    }
    else if constexpr( std::same_as<C, ignore_last> )
    {
      return cond_to_int<size, bits_per_e, Int>(keep_first {size - ignore.count_});
    }
    else if constexpr( std::same_as<C, keep_between> )
    {
      Int res = cond_to_int<size, bits_per_e, Int>(ignore_first(ignore.begin_));
      res &= cond_to_int<size, bits_per_e, Int>(ignore_last(size - ignore.end_));
      res &= cond_to_int<size, bits_per_e, Int>(ignore_none);
      return res;
    }
    else if constexpr( std::same_as<C, ignore_extrema> )
    {
      return cond_to_int<size, bits_per_e, Int>(
          keep_between(ignore.first_count_, size - ignore.last_count_));
    }
  }
}

  template <logical_simd_value Logical>
  struct top_bits
  {
    //! The associated wide logical.
    using logical_type = Logical;

    //! For top_bits<logical<wide<T, N>>> this is T;
    using scalar_type = typename as_arithmetic_t<logical_type>::value_type;

    //! ABI of the underlying simd value
    using abi_type = typename as_arithmetic_t<logical_type>::abi_type;

    //! logical_type::size();
    static constexpr std::ptrdiff_t static_size = logical_type::size();

    //! is stored as an array of 2 halves
    static constexpr bool is_aggregated = has_aggregated_abi_v<logical_type> ||
                                          (has_emulated_abi_v<logical_type> && static_size > 64);

    static constexpr auto half_size = (static_size/2 > 0) ? static_size/2 : 1;

    //! logical or half size
    using half_logical = logical<wide<scalar_type, eve::fixed<half_size>>>;

   private:
    EVE_FORCEINLINE static auto storage_type_impl()
    {
      if constexpr ( is_aggregated )  return std::array<top_bits<half_logical>, 2>{};
      else                            return movemask(logical_type{}).first;
    }

    EVE_FORCEINLINE static constexpr std::ptrdiff_t bits_per_element_impl()
    {
      if constexpr ( is_aggregated ) return top_bits<half_logical>::bits_per_element;
      else                           return decltype(movemask(logical_type{}).second){}();
    }

    static constexpr bool is_cheap_impl()
    {
      if ( has_emulated_abi_v<logical_type> ) return true;
      if constexpr ( is_aggregated ) return top_bits<half_logical>::is_cheap;

      if ( x86_abi<abi_type> ) return true;

      if ( arm_abi<abi_type> )
      {
        if ( static_size == 1 ) return true;
        if ( static_size * sizeof(scalar_type) <= 4 ) return true;
        if ( current_api >= eve::asimd )
        {
          if ( sizeof(scalar_type) >= 2 ) return true;
          return static_size <= 8;  // 16 chars is expensive
        }
        return false;
      }
      return false;
    }

   public:
    //! type of the underlying storage
    using storage_type = decltype(top_bits::storage_type_impl());

    //! how many bits do we store per one element
    static constexpr std::ptrdiff_t bits_per_element = bits_per_element_impl();

    //! how many bits are used
    static constexpr std::ptrdiff_t static_bits_size = static_size * bits_per_element;

    //! is it considered a cheap operation (~1 instruction) to get top_bits from a logical.
    static constexpr bool is_cheap = is_cheap_impl();

    storage_type storage;

    // constructors ---------------------------------

    EVE_FORCEINLINE constexpr top_bits() = default;

    EVE_FORCEINLINE constexpr explicit top_bits(storage_type storage) : storage(storage) {}

    // -- constructor(logical)

    EVE_FORCEINLINE explicit top_bits(const logical_type& p)
    {
      if constexpr ( is_aggregated )
      {
        auto [l, h] = p.slice();

        storage = {{ top_bits<half_logical>(l), top_bits<half_logical>(h) }};
      }
      else
      {
        storage = movemask(p).first;
        operator&=(top_bits(ignore_none_{}));
      }
    }

    // -- constructor(ignore)

    template<relative_conditional_expr C>
    EVE_FORCEINLINE constexpr explicit top_bits(C c)
    {
      if constexpr( !is_aggregated )
        storage = detail::cond_to_int<static_size, bits_per_element, storage_type>(c);
      else if constexpr( C::is_complete ) storage[0] = storage[1] = top_bits<half_logical> {c};
      else if constexpr( std::same_as<C, keep_last> )
      {
        constexpr std::ptrdiff_t card = half_logical::size();
        constexpr std::ptrdiff_t z    = 0;
        storage[0] = top_bits<half_logical> {keep_last {std::max(z, c.count_ - card)}};
        storage[1] = top_bits<half_logical> {keep_last {std::min(card, c.count_)}};
      }
      else if constexpr( std::same_as<C, keep_first> )
      {
        constexpr std::ptrdiff_t card = half_logical::size();
        constexpr std::ptrdiff_t z    = 0;
        storage[0] = top_bits<half_logical> {keep_first {std::min(card, c.count_)}};
        storage[1] = top_bits<half_logical> {keep_first {std::max(z, c.count_ - card)}};
      }
      else if constexpr( std::same_as<C, ignore_first> )
      {
        *this = top_bits {keep_last {static_size - c.count_}};
      }
      else if constexpr( std::same_as<C, ignore_last> )
      {
        *this = top_bits {keep_first {static_size - c.count_}};
      }
      else if constexpr( std::same_as<C, keep_between> )
      {
        constexpr std::ptrdiff_t card = half_logical::size();
        using tb_t                    = top_bits<half_logical>;
        constexpr std::ptrdiff_t z    = 0;
        storage[0] = tb_t {keep_between {std::min(c.begin_, card), std::min(card, c.end_)}};
        storage[1] = tb_t {keep_between {std::max(z, c.begin_ - card), std::max(z, c.end_ - card)}};
      }
      else if constexpr( std::same_as<C, ignore_extrema> )
      {
        *this = top_bits {keep_between(c.first_count_, static_size - c.last_count_)};
      }
    }

    // -- constructor: logical + ignore

    EVE_FORCEINLINE explicit top_bits(const logical_type &p, relative_conditional_expr auto ignore) : top_bits(p)
    {
      operator&=(top_bits(ignore));
    }

    // -- slicing

    EVE_FORCEINLINE
    kumi::tuple<top_bits<half_logical>, top_bits<half_logical>>
    slice() const
      requires ( Logical::size() > 1 )
             && (bits_per_element == top_bits<half_logical>::bits_per_element)
    {
      if constexpr ( is_aggregated     ) return {storage[0], storage[1]};
      else
      {
        top_bits<half_logical> l, h;
        using half_storage = typename top_bits<half_logical>::storage_type;

        l.storage = detail::set_lower_n_bits<half_storage>(static_bits_size / 2) & storage;
        h.storage = storage >> (static_bits_size / 2);

        return {l, h};
      }
    }

    template<std::size_t Slice>
    EVE_FORCEINLINE
    top_bits<half_logical> slice(slice_t<Slice>) const
    {
      auto [l, h] = slice();

      if constexpr (Slice == 0) return l;
      else                      return h;
    }

    // getters/setter ----------------------

    static constexpr std::ptrdiff_t size() { return static_size; }

    //! setter
    EVE_FORCEINLINE constexpr void set(std::ptrdiff_t i, bool x)
    {
      if constexpr ( !is_aggregated )
      {
        storage_type bit_mask = detail::set_lower_n_bits<storage_type>(bits_per_element) << (i * bits_per_element);
        if ( x ) storage |= bit_mask;
        else     storage &= ~bit_mask;
      }
      else
      {
        if ( i < static_size / 2 ) storage[0].set(i, x);
        else                       storage[1].set(i - static_size / 2, x);
      }
    }

    // getter
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

    // test
    EVE_FORCEINLINE constexpr explicit operator bool()
    {
      if constexpr ( !is_aggregated ) return storage != storage_type{0};
      else
      {
        return (bool)storage[0] || (bool)storage[1];
      }
    }

    // if possible, return top_bits as an int.
    EVE_FORCEINLINE constexpr auto as_int() const
      requires (static_bits_size <= 64)
    {
      if constexpr ( is_aggregated )
      {
        std::uint64_t lo = storage[0].as_int();
        std::uint64_t hi = storage[1].as_int();
        hi <<=  (static_bits_size / 2);
        std::uint64_t res = hi | lo;

        if constexpr ( static_bits_size < 64 ) return (std::uint32_t) res;
        else                                   return res;
      }
      else return storage;
    }

    EVE_FORCEINLINE constexpr std::strong_ordering operator<=>(const top_bits&) const = default;

    EVE_FORCEINLINE bool operator==(top_bits const& b) const
    {
      if constexpr ( !is_aggregated ) return storage == b.storage;
      else
      {
        return (storage[0] == b.storage[0]) &&  (storage[1] == b.storage[1]);
      }
    }

    // bit operators ------------------------------

    EVE_FORCEINLINE constexpr top_bits& operator&=(top_bits x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] &= x.storage[0];
        storage[1] &= x.storage[1];
      }
      else storage &= x.storage;
      return *this;
    }

    EVE_FORCEINLINE constexpr top_bits& operator|=(top_bits x)
    {
      if constexpr ( is_aggregated )
      {
        storage[0] |= x.storage[0];
        storage[1] |= x.storage[1];
      }
      else storage |= x.storage;
      return *this;
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

    EVE_FORCEINLINE constexpr top_bits operator~() const
    {
      if constexpr( !is_aggregated ) { return top_bits {(storage_type)~storage} & top_bits {ignore_none_ {}}; }
      else return top_bits {{~storage[0], ~storage[1]}};
    }

    // streaming ----------------------------------

    EVE_FORCEINLINE friend std::ostream& operator<<(std::ostream& o, const top_bits& x)
    {
      if constexpr( is_aggregated ) return o << '[' << x.storage[0] << ", " << x.storage[1] << ']';
      else return o << x.storage;
    }
  };

  template<logical_simd_value L>
  EVE_FORCEINLINE auto
  operator&(top_bits<L> x, top_bits<L> y)
  {
    x &= y;
    return x;
  }

  template <logical_simd_value L>
  EVE_FORCEINLINE auto
  operator|(top_bits<L> x, top_bits<L> y)
  {
    x |= y;
    return x;
  }

  template<logical_simd_value L>
  EVE_FORCEINLINE auto
  operator^(top_bits<L> x, top_bits<L> y)
  {
    x ^= y;
    return x;
  }
} // namespace eve

// ---------------------------------------------------------------------------------
// to_logical(top_bits)
//

namespace eve::detail {

template <logical_simd_value Logical>
EVE_FORCEINLINE Logical to_logical(eve::top_bits<Logical> mmask) noexcept
{
  using abi = typename eve::top_bits<Logical>::abi_type;

       if constexpr ( top_bits<Logical>::is_aggregated ) return Logical{to_logical(mmask.storage[0]), to_logical(mmask.storage[1])};
  else if constexpr ( current_api >= avx512            ) return Logical(mmask.storage);
  else if constexpr ( x86_abi<abi> )
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

    //  Use the most full type to be sure to fill outside values of small wide with false
    using abi_t     = typename bits_wide::abi_type;
    using fit_wide  = wide<bits_et, expected_cardinal_t<bits_et, abi_t>>;

    static constexpr auto bits_per_element = top_bits<Logical>::bits_per_element;
    static constexpr auto element_mask = detail::set_lower_n_bits<bits_et>(bits_per_element);

    fit_wide true_mmask([&](int i, int) {
      int shift = 0;

      shift += (i >= 8);   // only true for short on avx (second uint16_t) and chars (second uint8_t)
      shift += (i >= 16);  // only true for chars on avx (third uint8_t)
      shift += (i >= 24);  // only true for chars on avx (4th uint8_t)

      i -= 8 * shift;

      return (bits_et)(element_mask << (i * bits_per_element));
    });

    fit_wide actual_mmask([&](int i, int) {
      int shift = 0;

      shift += (i >= 8);  // second uint16_t or uint8_t
      shift += (i >= 16); // third uint8_t
      shift += (i >= 24); // 4th uint8_t

      shift *= 8 * bits_per_element;

      return (bits_et)(mmask.storage >> shift);
    });

    auto test = actual_mmask & true_mmask;
    auto res  = test == true_mmask;

    return bit_cast( res, as<Logical>{} );
  }
  else
  {
    // For arm and power we can likely do better, but we didn't care thus far.
    //  Use the most full type to be sure to fill outside values of small wide with false
    using bits_wide = typename Logical::bits_type;
    using abi_t     = typename bits_wide::abi_type;

    if constexpr ( !is_native_v<abi_t> )
    {
      Logical mask([&](int i, int) { return i < Logical::size() ? mmask.get(i) : false; });
      return mask;
    }
    else
    {
      using bits_et   = element_type_t<bits_wide>;
      using fit_wide  = logical<wide<bits_et, expected_cardinal_t<bits_et, abi_t>>>;
      fit_wide mask([&](int i, int) { return i < Logical::size() ? mmask.get(i) : false; });
      return bit_cast( mask, as<Logical>{} );
    }
  }
}

}  // namespace eve::detail
