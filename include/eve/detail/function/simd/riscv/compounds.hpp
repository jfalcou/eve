//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_mul(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) ) return self = __riscv_vmul(self, other, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfmul(self, other, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_mul(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  auto           y = static_cast<T>(other);
  if constexpr( match(c, category::integer_) ) return self = __riscv_vmul(self, y, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfmul(self, y, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_add(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) ) return self = __riscv_vadd(self, other, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfadd(self, other, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_add(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  auto           y = static_cast<T>(other);
  if constexpr( match(c, category::integer_) ) return self = __riscv_vadd(self, y, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfadd(self, y, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_sub(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) ) return self = __riscv_vsub(self, other, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfsub(self, other, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_sub(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  auto           y = static_cast<T>(other);
  if constexpr( match(c, category::integer_) ) return self = __riscv_vsub(self, y, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfsub(self, y, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_div(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::int_) ) return self = __riscv_vdiv(self, other, N::value);
  else if constexpr( match(c, category::uint_) ) return self = __riscv_vdivu(self, other, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfdiv(self, other, N::value);
}

template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_div(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  auto           y = static_cast<T>(other);
  if constexpr( match(c, category::int_) ) return self = __riscv_vdiv(self, y, N::value);
  else if constexpr( match(c, category::uint_) ) return self = __riscv_vdivu(self, y, N::value);
  else if constexpr( match(c, category::float_) ) return self = __riscv_vfdiv(self, y, N::value);
}

template<plain_scalar_value T, typename N, plain_scalar_value U, typename M>
EVE_FORCEINLINE auto&
self_bitand(wide<T, N>& self, wide<U, M> const& other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) * N::value == sizeof(U) * M::value)
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = eve::bit_cast(other, as<wide_t>());
    return self     = __riscv_vand(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    self                     = bit_cast(self_bitand(self_cast, other), as(self));
    return self;
  }
}

template<plain_scalar_value T, typename N, plain_scalar_value P>
EVE_FORCEINLINE wide<T, N>                &
self_bitand(wide<T, N>                &self, P const                &other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) == sizeof(P))
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = std::bit_cast<T>(other);
    return self     = __riscv_vand(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitand(self_cast, other), as(self));
  }
}

template<plain_scalar_value T, typename N, plain_scalar_value U, typename M>
EVE_FORCEINLINE wide<T, N>                &
self_bitxor(wide<T, N>                &self, wide<U, M> const                &other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) * N::value == sizeof(U) * M::value)
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = eve::bit_cast(other, as<wide_t>());
    return self     = __riscv_vxor(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitxor(self_cast, other), as(self));
  }
}

template<plain_scalar_value T, typename N, plain_scalar_value P>
EVE_FORCEINLINE auto&
self_bitxor(wide<T, N>& self, P const& other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) == sizeof(P))
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = std::bit_cast<T>(other);
    return self     = __riscv_vxor(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitxor(self_cast, other), as(self));
  }
}

template<plain_scalar_value T, typename N, plain_scalar_value U, typename M>
EVE_FORCEINLINE wide<T, N>                &
self_bitor(wide<T, N>                &self, wide<U, M> const                &other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) * N::value == sizeof(U) * M::value)
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = eve::bit_cast(other, as<wide_t>());
    return self     = __riscv_vor(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitor(self_cast, other), as(self));
  }
}

template<plain_scalar_value T, typename N, plain_scalar_value P>
EVE_FORCEINLINE wide<T, N>                &
self_bitor(wide<T, N>                &self, P const                &other) noexcept
requires rvv_abi<abi_t<T, N>> && (sizeof(T) == sizeof(P))
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) )
  {
    auto other_cast = std::bit_cast<T>(other);
    return self     = __riscv_vor(self, other_cast, N::value);
  }
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitor(self_cast, other), as(self));
  }
}

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE wide<T, N>                &
self_bitnot(wide<T, N>                &self)
requires rvv_abi<abi_t<T, N>>
{
  using wide_t       = wide<T, N>;
  constexpr auto cat = categorize<wide_t>();
  if constexpr( match(cat, category::unsigned_) ) return self = __riscv_vnot(self, N::value);
  else
  {
    using scalar_t           = as_integer_t<T, unsigned>;
    using i_t                = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt       = as<i_t>();
    auto           self_cast = bit_cast(self, tgt);
    return self              = bit_cast(self_bitnot(self_cast), as(self));
  }
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shl(wide<T, N>& self, wide<U, N> shift) noexcept
requires(rvv_abi<abi_t<T, N>> && sizeof(T) == sizeof(U))
{
  using i_t     = typename wide<T, N>::template rebind<as_integer_t<T, unsigned>, N>;
  auto const si = bit_cast(shift, as<i_t>());

  self = __riscv_vsll(self, si, N::value);
  return self;
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shl(wide<T, N>& self, U shift) noexcept
requires rvv_abi<abi_t<T, N>>
{
  self = __riscv_vsll(self, shift, N::value);
  return self;
}

template<integral_scalar_value T, typename N, std::ptrdiff_t U>
EVE_FORCEINLINE auto&
self_shl(wide<T, N>& self, index_t<U> const&) noexcept
requires rvv_abi<abi_t<T, N>>
{
  self = __riscv_vsll(self, U, N::value);
  return self;
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T, N>& self, wide<U, N> shift) noexcept
requires(rvv_abi<abi_t<T, N>> && sizeof(T) == sizeof(U))
{
  constexpr auto c            = categorize<wide<T, N>>();
  auto           shift_casted = convert(shift, as<as_integer_t<U, unsigned>>());
  if constexpr( match(c, category::uint_) )
    return self = __riscv_vsrl(self, shift_casted, N::value);
  else if constexpr( match(c, category::int_) ) return self = __riscv_vsra(self, shift_casted, N::value);
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T, N>& self, U shift) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::uint_) ) return self = __riscv_vsrl(self, shift, N::value);
  else if constexpr( match(c, category::int_) ) return self = __riscv_vsra(self, shift, N::value);
}

template<integral_scalar_value T, typename N, std::ptrdiff_t U>
EVE_FORCEINLINE auto&
self_shr(wide<T, N>& self, index_t<U> const&) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::uint_) ) return self = __riscv_vsrl(self, U, N::value);
  else if constexpr( match(c, category::int_) ) return self = __riscv_vsra(self, U, N::value);
}

}
