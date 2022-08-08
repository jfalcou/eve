//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

namespace eve
{
template<logical_simd_value Logical>
requires(current_api >= avx512 && !has_aggregated_abi_v<Logical>) struct top_bits<Logical>
{
  using logical_type = Logical;
  using scalar_type  = typename as_arithmetic_t<logical_type>::value_type;
  using abi_type     = typename as_arithmetic_t<logical_type>::abi_type;

  static constexpr std::ptrdiff_t static_size   = logical_type::size();
  static constexpr bool           is_aggregated = false;

  using half_logical = logical<wide<scalar_type, eve::fixed<static_size / 2>>>;

  private:
  static constexpr std::ptrdiff_t storage_cardinal = []
  {
    std::ptrdiff_t min_size = sizeof(scalar_type) == 1 ? 16 : 8;
    return std::max(min_size, static_size);
  }();

  public:
  using storage_type = eve::logical<eve::wide<scalar_type, eve::fixed<storage_cardinal>>>;

  private:
  using raw_storage_type = typename storage_type::storage_type;

  public:
  static constexpr std::ptrdiff_t bits_per_element = 1;
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
  template<relative_conditional_expr C> EVE_FORCEINLINE constexpr explicit top_bits(C c)
  {
    storage = detail::cond_to_int<static_size, bits_per_element, raw_storage_type>(c);
  }

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
    return storage.storage() != raw_storage_type {0};
  }

  EVE_FORCEINLINE constexpr auto as_int() const { return storage.storage().value; }

  template<typename X> EVE_FORCEINLINE constexpr bool operator==(top_bits<X> const& x) const
  {
    return storage.storage() == x.storage.storage();
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
    storage.storage() ^= x.storage.storage();
    return *this;
  }

  EVE_FORCEINLINE constexpr top_bits operator~() const
  {
    return top_bits {!storage} & top_bits {ignore_none_ {}};
  }

  // streaming ----------------------------------

  EVE_FORCEINLINE friend std::ostream&
  operator<<(std::ostream& o,
             top_bits      x) requires(current_api >= avx512 && !has_aggregated_abi_v<Logical>)
  {
    return o << x.storage.storage();
  }
};

}
