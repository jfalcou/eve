//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_FUNCTION_SIMD_PPC_ARITHMETIC_COMPOUNDS_HPP_INCLUDED
#define EVE_DETAIL_FUNCTION_SIMD_PPC_ARITHMETIC_COMPOUNDS_HPP_INCLUDED

#include <eve/concept/stdconcepts.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/abi.hpp>

// TODO: std:bitcast instead
#include <eve/module/core/function/generic/bit_cast.hpp>

namespace eve::detail
{
  //================================================================================================
  // +=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add( wide<T,N,ppc_>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ppc_>,U> )
  {
    using type = wide<T, N, ppc_>;

    if constexpr( scalar_value<U> )
    {
      self = vec_add(self.storage(), type{other}.storage());
    }
    else if constexpr( std::same_as<type,U> )
    {
      self = vec_add(self.storage(), other.storage());
    }

    return self;
  }

  //================================================================================================
  // -=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub( wide<T,N,ppc_>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ppc_>,U> )
  {
    using type = wide<T, N, ppc_>;

    if constexpr( scalar_value<U> )
    {
      self = vec_sub(self.storage(), type{other}.storage());
    }
    else if constexpr( std::same_as<type,U> )
    {
      self = vec_sub(self.storage(), other.storage());
    }

    return self;
  }

  //================================================================================================
  // *=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul( wide<T,N,ppc_>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ppc_>,U> )
  {
    using type = wide<T, N, ppc_>;

    if constexpr( scalar_value<U> )
    {
      self = self.storage() *  type{other}.storage();
    }
    else if constexpr( std::same_as<type,U> )
    {
      self = self.storage() * other.storage();
    }

    return self;
  }

  //================================================================================================
  // /=
  //================================================================================================
  template<scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div( wide<T,N,ppc_>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T,N,ppc_>,U> )
  {
    using type = wide<T, N, ppc_>;

    if constexpr( scalar_value<U> )
    {
      self = self.storage() / type{other}.storage();
    }
    else if constexpr( std::same_as<type,U> )
    {
      self = self.storage() / other.storage();
    }

    return self;
  }
}

#endif
