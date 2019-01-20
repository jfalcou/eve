//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MINUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_MINUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto  minus_( EVE_SUPPORTS(simd_), wide<T,N,ABI> const& v0, U const& v1) noexcept
                        requires( wide<T,N,ABI>, detail::Convertible<U,T> )
  {
    return eve::minus( v0, wide<T,N,ABI>(static_cast<T>(v1)) );
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto  minus_( EVE_SUPPORTS(simd_), U const& v0, wide<T,N,ABI> const& v1) noexcept
                        requires( wide<T,N,ABI>, detail::Convertible<U,T> )
  {
    return eve::minus( wide<T,N,ABI>(static_cast<T>(v0)), v1 );
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE wide<T,N,aggregated_> minus_( EVE_SUPPORTS(simd_)
                                              , wide<T,N,aggregated_> const& v0
                                              , wide<T,N,aggregated_> const& v1
                                              ) noexcept
  {
    return aggregate( eve::minus, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE auto minus_ ( EVE_SUPPORTS(simd_)
                              , wide<T,N,emulated_> const& v0, wide<T,N,emulated_> const& v1
                              ) noexcept
  {
    return map( eve::minus, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto  minus_( EVE_SUPPORTS(simd_)
                              , wide<T,N,emulated_> const& v0, U const& v1
                              ) noexcept
                        requires( wide<T,N,emulated_>, detail::Convertible<U,T> )
  {
    return map( eve::minus, v0, static_cast<T>(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE auto  minus_( EVE_SUPPORTS(simd_)
                              , U const& v0, wide<T,N,emulated_> const& v1
                              ) noexcept
                        requires( wide<T,N,emulated_>, detail::Convertible<U,T> )
  {
    return map( eve::minus, static_cast<T>(v0), v1);
  }
}

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI> EVE_FORCEINLINE
  auto operator-( wide<T,N,ABI> const& v0, wide<T,N,ABI> const& v1) noexcept
  {
    return eve::minus(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto  operator- ( wide<T,N,ABI> const& v0, U const& v1 ) noexcept
                        requires( wide<T,N,ABI>, detail::Convertible<U,T> )
  {
    return eve::minus(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE auto  operator- ( U const& v0, wide<T,N,ABI> const& v1) noexcept
                        requires( wide<T,N,ABI>, detail::Convertible<U,T> )
  {
    return eve::minus(v0, v1);
  }
}

#endif
