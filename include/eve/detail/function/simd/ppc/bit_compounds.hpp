//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_BIT_COMPOUNDS_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_BIT_COMPOUNDS_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>

// TODO: std:bitcast instead
#include <eve/module/core/function/generic/bit_cast.hpp>

namespace eve::detail
{
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

#endif
