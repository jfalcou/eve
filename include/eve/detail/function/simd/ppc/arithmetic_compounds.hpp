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
  // +=
  //================================================================================================
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_add( wide<T, N>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T, N>, U> ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
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
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_sub( wide<T,N>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T, N>,U> ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
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
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_mul( wide<T,N>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T, N>,U> ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
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
  template<plain_scalar_value T, value U, typename N>
  EVE_FORCEINLINE decltype(auto) self_div( wide<T, N>& self, U const& other )
  requires( scalar_value<U> || std::same_as<wide<T, N>,U> ) && ppc_abi<abi_t<T, N>>
  {
    using type = wide<T, N>;

    if constexpr( plain_scalar_value<U> )
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
