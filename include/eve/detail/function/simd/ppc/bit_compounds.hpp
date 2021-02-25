//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/function/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // <<=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, ppc_abi ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shl(wide<T,N,ABI>& v, wide<U,N,ABI> s) noexcept
  {
    using i_t = typename wide<T,N,ABI>::template rebind <as_integer_t<T, unsigned>,N>;
    v = vec_sl(v.storage(), bit_cast(s,as_<i_t>()).storage());
    return v;
  }

  template<integral_real_scalar_value T, typename N, ppc_abi ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE auto self_shl(wide<T,N,ABI>& v, U s) noexcept
  {
    using i_t = typename wide<T,N,ABI>::template rebind <as_integer_t<T, unsigned>,N>;
    v <<= i_t(s);
    return v;
  }

  //================================================================================================
  // >>=
  //================================================================================================
  template<integral_real_scalar_value T, typename N, ppc_abi ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE decltype(auto) self_shr(wide<T,N,ABI>& v, wide<U,N,ABI> s) noexcept
  {
    using i_t = typename wide<T,N,ABI>::template rebind <as_integer_t<T, unsigned>,N>;

    if constexpr(std::is_signed_v<T>) v = vec_sra(v.storage(), bit_cast(s,as_<i_t>()).storage());
    else                              v = vec_sr (v.storage(), bit_cast(s,as_<i_t>()).storage());

    return v;
  }

  template<integral_real_scalar_value T, typename N, ppc_abi ABI, integral_real_scalar_value U>
  EVE_FORCEINLINE auto self_shr(wide<T,N,ABI>& v, U s) noexcept
  {
    using i_t = typename wide<T,N,ABI>::template rebind <as_integer_t<T, unsigned>,N>;
    v >>= i_t(s);
    return v;
  }

  //================================================================================================
  // &=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_bitand( wide<T,N,ppc_>& self, U const& other )
  requires( (sizeof(wide<T,N,ppc_>) == sizeof(U)) || (sizeof(T) == sizeof(U)) )
  {
    using type = wide<T,N,ppc_>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as_<T>{});
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
  EVE_FORCEINLINE decltype(auto) self_bitor( wide<T,N,ppc_>& self, U const& other )
  requires( (sizeof(wide<T,N,ppc_>) == sizeof(U)) || (sizeof(T) == sizeof(U)) )
  {
    using type = wide<T,N,ppc_>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as_<T>{});
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
  EVE_FORCEINLINE decltype(auto) self_bitxor( wide<T,N,ppc_>& self, U const& other )
  requires( (sizeof(wide<T,N,ppc_>) == sizeof(U)) || (sizeof(T) == sizeof(U)) )
  {
    using type = wide<T,N,ppc_>;

    if constexpr( element_bit_compatible_to<U,type> )
    {
      auto bit_other = detail::bit_cast_(EVE_RETARGET(cpu_), other , as_<T>{});
      self = vec_xor(self.storage(), type{bit_other}.storage());
    }
    else if constexpr( simd_value<U> && sizeof(self) == sizeof(other) )
    {
      self = vec_xor(self.storage(), (typename type::storage_type)(other.storage()) );
    }

    return self;
  }
}
