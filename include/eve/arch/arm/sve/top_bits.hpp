//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/arm/sve/sve_true.hpp>
#include <eve/detail/meta.hpp>

namespace eve
{

template<logical_simd_value Logical>
requires(current_api >= sve && !has_aggregated_abi_v<Logical>) struct top_bits<Logical>
{
  using logical_type = Logical;
  using scalar_type  = typename as_arithmetic_t<logical_type>::value_type;
  using abi_type     = typename as_arithmetic_t<logical_type>::abi_type;

  static constexpr std::ptrdiff_t static_size   = logical_type::size();
  static constexpr bool           is_aggregated = false;

  using half_logical = logical<wide<scalar_type, eve::fixed<static_size / 2>>>;
  using storage_type = logical<wide<scalar_type>>;

  static constexpr std::ptrdiff_t bits_per_element = sizeof(scalar_type);
  static constexpr std::ptrdiff_t static_bits_size = static_size * bits_per_element;
  static constexpr bool           is_cheap         = true;

  storage_type storage;

  // constructors ---------------------------------

  EVE_FORCEINLINE constexpr top_bits() = default;

  EVE_FORCEINLINE constexpr explicit top_bits(storage_type storage) : storage(storage) {}

  EVE_FORCEINLINE constexpr explicit top_bits(logical_type p) requires(
      !std::same_as<storage_type, logical_type>)
      : storage {bit_cast(p, eve::as<storage_type> {})}
  {
    operator&=(top_bits(ignore_none_ {}));
  }

  // -- constructor(ignore)
  template<relative_conditional_expr C>
  EVE_FORCEINLINE constexpr explicit top_bits(C c) : storage {c.mask(eve::as<logical_type> {})}
  {}

  // -- constructor: logical + ignore

  EVE_FORCEINLINE explicit top_bits(logical_type p, relative_conditional_expr auto ignore)
      : top_bits(p)
  {
    operator&=(top_bits(ignore));
  }

  // -- slicing

  EVE_FORCEINLINE
  kumi::tuple<top_bits<half_logical>, top_bits<half_logical>> slice() const
      requires(Logical::size() > 1)
  {
    auto [l, h] = to_logical(*this).slice();
    return {top_bits<half_logical> {l}, top_bits<half_logical> {h}};
  }

  template<std::size_t Slice> EVE_FORCEINLINE top_bits<half_logical> slice(slice_t<Slice>) const
  {
    auto [l, h] = slice();

    if constexpr( Slice == 0 ) return l;
    else return h;
  }

  // getters/setter ----------------------

  EVE_FORCEINLINE constexpr void set(std::ptrdiff_t i, bool x) { storage.set(i, x); }
  EVE_FORCEINLINE constexpr bool get(std::ptrdiff_t i) const { return storage.get(i); }

  EVE_FORCEINLINE constexpr explicit operator bool()
  {
    return svptest_any(detail::sve_true<scalar_type>(), storage);
  }

  EVE_FORCEINLINE constexpr auto as_int() const requires(static_bits_size <= 64)
  {
    using uint_type = detail::make_integer_t < (static_bits_size<8) ? 1 : static_bits_size / 8>;
    uint_type raw;
    std::memcpy(&raw, &storage, sizeof(uint_type));

    uint_type r = raw;

    if constexpr( bits_per_element >= 8 ) r |= (raw << 4) | (raw << 5) | (raw << 6) | (raw << 7);
    if constexpr( bits_per_element >= 4 ) r |= (raw << 2) | (raw << 3);
    if constexpr( bits_per_element >= 2 ) r |= (raw << 1);

    return r;
  }

  EVE_FORCEINLINE constexpr bool operator==(top_bits const& x) const
  {
    return !svptest_any(detail::sve_true<scalar_type>(), storage != x.storage);
  }

  EVE_FORCEINLINE top_bits& operator&=(top_bits x)
  {
    storage = storage && x.storage;
    return *this;
  }

  EVE_FORCEINLINE top_bits& operator|=(top_bits x)
  {
    storage = storage || x.storage;
    return *this;
  }

  EVE_FORCEINLINE top_bits& operator^=(top_bits x)
  {
    storage = storage != x.storage;
    return *this;
  }

  EVE_FORCEINLINE constexpr top_bits operator~() const
  {
    return top_bits {!storage} & top_bits {ignore_none_ {}};
  }

  // streaming ----------------------------------

  EVE_FORCEINLINE friend std::ostream& operator<<(std::ostream& o, const top_bits& x)
  {
    if constexpr( static_bits_size <= 64 ) return o << x.as_int();
    else
    {
      auto [l, h] = slice();
      return o << '[' << l << ", " << h << ']';
    }
  }
};
}
