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
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vmul(self, other, N::value);
  }
  if constexpr( match(c, category::float_) ) return self = __riscv_vfmul(self, other, N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_mul(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vmul(self, static_cast<T>(other), N::value);
  }
  if constexpr( match(c, category::float_) )
    return self = __riscv_vfmul(self, static_cast<T>(other), N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_add(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vadd(self, other, N::value);
  }
  if constexpr( match(c, category::float_) ) return self = __riscv_vfadd(self, other, N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_add(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vadd(self, static_cast<T>(other), N::value);
  }
  if constexpr( match(c, category::float_) )
    return self = __riscv_vfadd(self, static_cast<T>(other), N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_sub(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vsub(self, other, N::value);
  }
  if constexpr( match(c, category::float_) ) return self = __riscv_vfsub(self, other, N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_sub(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::integer_) )
  {
    return self = __riscv_vsub(self, static_cast<T>(other), N::value);
  }
  if constexpr( match(c, category::float_) )
    return self = __riscv_vfsub(self, static_cast<T>(other), N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_div(wide<T, N>& self, U const& other) noexcept
requires std::same_as<wide<T, N>, U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::int_) ) { return self = __riscv_vdiv(self, other, N::value); }
  if constexpr( match(c, category::uint_) ) { return self = __riscv_vdivu(self, other, N::value); }
  if constexpr( match(c, category::float_) ) return self = __riscv_vfdiv(self, other, N::value);
}
template<plain_scalar_value T, value U, typename N>
EVE_FORCEINLINE auto&
self_div(wide<T, N>& self, U const& other) noexcept
requires scalar_value<U> && rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::int_) )
  {
    return self = __riscv_vdiv(self, static_cast<T>(other), N::value);
  }
  if constexpr( match(c, category::uint_) )
  {
    return self = __riscv_vdivu(self, static_cast<T>(other), N::value);
  }
  if constexpr( match(c, category::float_) )
    return self = __riscv_vfdiv(self, static_cast<T>(other), N::value);
}

#ifdef RVV_BIT
#  error RVV_BIT defined
#endif
#define RVV_BIT(eve_name, intrinsic)                                                               \
  template<plain_scalar_value T, typename N, plain_scalar_value U, typename M>                     \
  EVE_FORCEINLINE auto& eve_name(wide<T, N>& self, wide<U, M> const& other) noexcept               \
  requires rvv_abi<abi_t<T, N>> && (sizeof(T) * N::value == sizeof(U) * M::value)                  \
  {                                                                                                \
    using wide_t = wide<T, N>;                                                                     \
    if constexpr( std::is_floating_point_v<T> )                                                    \
    {                                                                                              \
      using i_t                 = wide_t::template rebind<as_integer_t<T, unsigned>, N>;           \
      constexpr auto tgt        = as<i_t>();                                                       \
      auto           other_cast = bit_cast(other, tgt);                                            \
      auto           self_cast  = bit_cast(self, tgt);                                             \
      self                      = bit_cast(eve_name(self_cast, other_cast), as(self));             \
      return self;                                                                                 \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
      using i_t                 = wide_t::template rebind<as_integer_t<T, unsigned>, N>;           \
      constexpr auto tgt        = as<i_t>();                                                       \
      auto           other_cast = bit_cast(other, tgt);                                            \
      auto           self_cast  = bit_cast(self, tgt);                                             \
      self = bit_cast(i_t(intrinsic(self_cast, other_cast, N::value)), as(self));                  \
      return self;                                                                                 \
    }                                                                                              \
  }                                                                                                \
  template<plain_scalar_value T, typename N, plain_scalar_value P>                                 \
  EVE_FORCEINLINE auto& eve_name(wide<T, N>& self, P const& other) noexcept                        \
  requires rvv_abi<abi_t<T, N>> && (sizeof(T) == sizeof(P))                                        \
  {                                                                                                \
    using wide_t = wide<T, N>;                                                                     \
    if constexpr( std::is_floating_point_v<T> )                                                    \
    {                                                                                              \
      using scalar_t            = as_integer_t<P, unsigned>;                                       \
      using i_t                 = wide_t::template rebind<scalar_t, N>;                            \
      constexpr auto tgt        = as<i_t>();                                                       \
      auto           other_cast = std::bit_cast<scalar_t>(other);                                  \
      auto           self_cast  = bit_cast(self, tgt);                                             \
      self                      = bit_cast(eve_name(self_cast, other_cast), as(self));             \
      return self;                                                                                 \
    }                                                                                              \
    else                                                                                           \
    {                                                                                              \
      using scalar_t            = as_integer_t<P, unsigned>;                                       \
      using i_t                 = wide_t::template rebind<scalar_t, N>;                            \
      constexpr auto tgt        = as<i_t>();                                                       \
      auto           other_cast = std::bit_cast<scalar_t>(other);                                  \
      auto           self_cast  = bit_cast(self, tgt);                                             \
      self = bit_cast(i_t(intrinsic(self_cast, other_cast, N::value)), as(self));                  \
      return self;                                                                                 \
    }                                                                                              \
  }

RVV_BIT(self_bitand, __riscv_vand)
RVV_BIT(self_bitxor, __riscv_vxor)
RVV_BIT(self_bitor, __riscv_vor)

#undef RVV_BIT

template<plain_scalar_value T, typename N>
EVE_FORCEINLINE auto&
self_bitnot(wide<T, N>& self)
requires rvv_abi<abi_t<T, N>>
{
  using wide_t = wide<T, N>;
  if constexpr( std::is_floating_point_v<T> )
  {
    using i_t                 = wide_t::template rebind<as_integer_t<T, unsigned>, N>;
    constexpr auto tgt        = as<i_t>();
    auto           self_cast  = bit_cast(self, tgt);
    i_t            not_casted = __riscv_vnot(self_cast, N::value);
    self                      = bit_cast(not_casted, as(self));
    return self;
  }
  else
  {
    using scalar_t             = as_integer_t<T, unsigned>;
    using i_t                  = wide_t::template rebind<scalar_t, N>;
    constexpr auto tgt         = as<i_t>();
    auto           self_cast   = bit_cast(self, tgt);
    i_t            to_cast_res = __riscv_vnot(self_cast, N::value);
    self                       = bit_cast(to_cast_res, as(self));
    return self;
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
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::uint_) )
  {
    auto shift_casted = convert(shift, as<as_integer_t<U, unsigned>>());
    self              = __riscv_vsrl(self, shift_casted, N::value);
    return self;
  }
  if constexpr( match(c, category::int_) )
  {
    auto shift_casted = convert(shift, as<as_integer_t<U, unsigned>>());
    self              = __riscv_vsra(self, shift_casted, N::value);
    return self;
  }
}

template<integral_scalar_value T, typename N, integral_scalar_value U>
EVE_FORCEINLINE auto&
self_shr(wide<T, N>& self, U shift) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::uint_) )
  {
    self = __riscv_vsrl(self, shift, N::value);
    return self;
  }
  if constexpr( match(c, category::int_) )
  {
    self = __riscv_vsra(self, shift, N::value);
    return self;
  }
}

template<integral_scalar_value T, typename N, std::ptrdiff_t U>
EVE_FORCEINLINE auto&
self_shr(wide<T, N>& self, index_t<U> const&) noexcept
requires rvv_abi<abi_t<T, N>>
{
  constexpr auto c = categorize<wide<T, N>>();
  if constexpr( match(c, category::uint_) )
  {
    self = __riscv_vsrl(self, U, N::value);
    return self;
  }
  if constexpr( match(c, category::int_) )
  {
    self = __riscv_vsra(self, U, N::value);
    return self;
  }
}

}
