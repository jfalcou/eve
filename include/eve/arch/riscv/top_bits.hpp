//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/meta.hpp>
namespace eve
{

template<logical_simd_value Logical>
requires(current_api == rvv && !has_aggregated_abi_v<Logical>)
struct top_bits<Logical>
{
  using logical_type = Logical;
  using scalar_type  = typename as_arithmetic_t<logical_type>::value_type;
  using abi_type     = typename as_arithmetic_t<logical_type>::abi_type;

  static constexpr std::ptrdiff_t static_size   = logical_type::size();
  static constexpr bool           is_aggregated = false;

  static constexpr auto half_size = (static_size / 2 > 0) ? static_size / 2 : 1;
  using half_logical              = logical<wide<scalar_type, eve::fixed<half_size>>>;
  using storage_type              = Logical;

  static constexpr std::ptrdiff_t bits_per_element = 1;
  static constexpr std::ptrdiff_t static_bits_size = static_size * bits_per_element;
  static constexpr bool           is_cheap         = true;

  storage_type storage;

  // constructors ---------------------------------

  EVE_FORCEINLINE constexpr top_bits() = default;

  EVE_FORCEINLINE constexpr explicit top_bits(storage_type storage) : storage(storage) {}

  EVE_FORCEINLINE constexpr explicit top_bits(logical_type p)
  requires(!std::same_as<storage_type, logical_type>)
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
  static constexpr std::ptrdiff_t size() { return static_size; }

  EVE_FORCEINLINE constexpr void set(std::ptrdiff_t i, bool x) { storage.set(i, x); }
  EVE_FORCEINLINE constexpr bool get(std::ptrdiff_t i) const { return storage.get(i); }

  EVE_FORCEINLINE constexpr explicit operator bool()
  {
    return __riscv_vcpop(storage, static_size) != 0;
  }

  EVE_FORCEINLINE constexpr auto as_int() const
  requires(static_bits_size <= 64)
  {
    constexpr unsigned byte_size = std::max<std::ptrdiff_t>(1, static_bits_size / 8);
    using u_type                 = detail::make_integer_t<byte_size, unsigned>;
    auto raw_value               = std::bit_cast<u_type>(storage);
    if constexpr( static_bits_size >= 8 ) return raw_value;
    else
    {
      // if static_bit_size < 8, we have some dirty bits in resulted unsigned,
      // so cleanning them.
      u_type mask = raw_value & detail::set_lower_n_bits<u_type>(static_bits_size);
      return mask;
    }
  }

  EVE_FORCEINLINE constexpr bool operator==(top_bits const& x) const
  {
    // we find any place that have not equal elements.
    auto neq_res = top_bits(storage != x.storage);
    // if we find any place, top_bit will be true, so negate it.
    return !neq_res;
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
    return o << x.storage << "\n";
  }
};
}
