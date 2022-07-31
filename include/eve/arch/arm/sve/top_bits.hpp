//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>

namespace eve
{
template<logical_simd_value Logical>
requires(sve_abi<typename Logical::abi_type>) struct top_bits<Logical>
{
  //! The associated wide logical.
  using logical_type = Logical;

  //! type of the underlying storage
  using storage_type = logical_type;

  //! For top_bits<logical<wide<T, N>>> this is T;
  using scalar_type = typename as_arithmetic_t<logical_type>::value_type;

  //! ABI of the underlying simd value
  using abi_type = typename as_arithmetic_t<logical_type>::abi_type;

  //! is stored as an array of 2 halves
  static constexpr bool is_aggregated = false;

  //! Checks if current architecture is avx512
  static constexpr bool is_avx512_logical = false;

  //! logical_type::size();
  static constexpr std::ptrdiff_t static_size = logical_type::size();

  //! logical or half size
  using half_logical = logical<wide<scalar_type, eve::fixed<static_size / 2>>>;

  //! how many bits do we store per one element
  static constexpr std::ptrdiff_t bits_per_element = sizeof(scalar_type);

  //! how many bits are used
  static constexpr std::ptrdiff_t static_bits_size = static_size * bits_per_element;

  //! is it considered a cheap operation (~1 instruction) to get top_bits from a logical.
  static constexpr bool is_cheap = true;

  storage_type storage;

  // constructors ----------------------------------------------------------
  EVE_FORCEINLINE top_bits() = default;

  EVE_FORCEINLINE explicit top_bits(storage_type storage) : storage(storage) {}

  // -- constructor(ignore)
  EVE_FORCEINLINE explicit top_bits(relative_conditional_expr auto i)
  {
    storage = i.mask(as<logical_type> {});
  }
  // -- constructor: logical + ignore

  EVE_FORCEINLINE explicit top_bits(logical_type p, relative_conditional_expr auto ignore)
      : top_bits(p)
  {
    operator&=(top_bits(ignore));
  }

  EVE_FORCEINLINE void set(std::ptrdiff_t i, bool x) { storage.set(i, x); }
  EVE_FORCEINLINE bool get(std::ptrdiff_t i) const { return storage.get(i); }

  // miscellaneous -----------------------------------

  // test
  EVE_FORCEINLINE explicit operator bool() const
  {
    return svptest_any(detail::sve_true<scalar_type>(), storage);
  }

  bool operator==(const top_bits& x) const { return (bool)(*this ^ x); }

  // bit operators ------------------------------

  EVE_FORCEINLINE top_bits& operator&=(const top_bits& x)
  {
    storage = storage && x.storage;
    return *this;
  }

  EVE_FORCEINLINE friend top_bits operator&(const top_bits& x, const top_bits& y)
    requires sve_abi<typename Logical::abi_type>
  {
    top_bits tmp(x);
    tmp &= y;
    return tmp;
  }

  EVE_FORCEINLINE top_bits& operator|=(const top_bits& x)
  {
    storage = storage || x.storage;
    return *this;
  }

  EVE_FORCEINLINE friend top_bits operator|(const top_bits& x, const top_bits& y)
    requires sve_abi<typename Logical::abi_type>
  {
    top_bits tmp(x);
    tmp |= y;
    return tmp;
  }

  EVE_FORCEINLINE
  kumi::tuple<top_bits<half_logical>, top_bits<half_logical>> slice() const
      requires(Logical::size() > 1)
  {
    auto [lo, hi] = storage.slice();
    return {top_bits{lo}, top_bits{hi}};
  }

  template<std::size_t Slice> EVE_FORCEINLINE top_bits<half_logical> slice(slice_t<Slice> s) const
    requires(Logical::size() > 1)
  {
    return top_bits {storage.slice(s)};
  }

  EVE_FORCEINLINE top_bits& operator^=(const top_bits& x)
  {
    storage = storage != x.storage;
    return *this;
  }

  EVE_FORCEINLINE friend top_bits operator^(const top_bits& x, const top_bits& y)
    requires sve_abi<typename Logical::abi_type>
  {
    top_bits tmp(x);
    tmp ^= y;
    return tmp;
  }

  EVE_FORCEINLINE friend std::ostream& operator<<(std::ostream& o, const top_bits& x)
    requires sve_abi<typename Logical::abi_type>
  {
    return o << x.storage;
  }
};

}

namespace eve::detail
{
// ---------------------------------------------------------------------------------
// to_logical(top_bits)
//
template<logical_simd_value Logical>
EVE_FORCEINLINE Logical
to_logical(eve::top_bits<Logical> mmask) requires(sve_abi<typename Logical::abi_type>)
{
  return mmask.storage;
}
}
