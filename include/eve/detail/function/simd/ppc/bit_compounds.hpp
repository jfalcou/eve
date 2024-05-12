//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/function/bit_cast.hpp>

#include <concepts>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, wide<U,N> s) noexcept
  requires ppc_abi<abi_t<T, N>>
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v = vec_sl(v.storage(), bit_cast(s,as<i_t>()).storage());
    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N>& v, U s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v <<= i_t(s);
    return v;
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, wide<U,N> s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;

    if constexpr(std::is_signed_v<T>) v = vec_sra(v.storage(), bit_cast(s,as<i_t>()).storage());
    else                              v = vec_sr (v.storage(), bit_cast(s,as<i_t>()).storage());

    return v;
  }

  template<integral_scalar_value T, typename N, integral_scalar_value U>
  requires ppc_abi<abi_t<T, N>>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N>& v, U s) noexcept
  {
    using i_t = typename wide<T,N>::template rebind <as_integer_t<T, unsigned>,N>;
    v >>= i_t(s);
    return v;
  }

  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand( wide<T,N>& self, U const& other )
    requires( (sizeof(wide<T,N>) == sizeof(U)) || (sizeof(T) == sizeof(U)) ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T,N>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as<T>{});
      self = vec_and(self.storage(), type{bit_other}.storage());
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      self = vec_and(self.storage(), (typename type::storage_type)(other.storage()) );
    }

    return self;
  }

  //================================================================================================
  // |=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitor( wide<T,N>& self, U const& other )
  requires( (sizeof(wide<T,N>) == sizeof(U)) || (sizeof(T) == sizeof(U)) ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T,N>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as<T>{});
      self = vec_or(self.storage(), type{bit_other}.storage());
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      self = vec_or(self.storage(), (typename type::storage_type)(other.storage()) );
    }

    return self;
  }

  //================================================================================================
  // ^=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitxor( wide<T,N>& self, U const& other )
  requires( (sizeof(wide<T,N>) == sizeof(U)) || (sizeof(T) == sizeof(U)) ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T,N>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as<T>{});
      self = vec_xor(self.storage(), type{bit_other}.storage());
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      self = vec_xor(self.storage(), (typename type::storage_type)(other.storage()) );
    }

    return self;
  }
}
