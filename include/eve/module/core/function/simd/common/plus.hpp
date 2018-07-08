//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_PLUS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_PLUS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve { namespace detail
{
  // -----------------------------------------------------------------------------------------------
  // Support for mixed type with auto-splat
  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE pack<T,N,ABI> plus_ ( EVE_SUPPORTS(simd_)
                                      , pack<T,N,ABI> const& v0, U const& v1
                                      , requires(Convertible<U,T>)
                                      ) noexcept
  {
    return eve::plus( v0, pack<T,N,ABI>(static_cast<T>(v1)) );
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE pack<T,N,ABI> plus_ ( EVE_SUPPORTS(simd_)
                                      , U const& v0, pack<T,N,ABI> const& v1
                                      , requires(Convertible<U,T>)
                                      ) noexcept
  {
    return eve::plus( pack<T,N,ABI>(static_cast<T>(v0)), v1 );
  }

  // -----------------------------------------------------------------------------------------------
  // Aggregation
  template<typename T, typename N>
  EVE_FORCEINLINE pack<T,N,aggregated_> plus_ ( EVE_SUPPORTS(simd_)
                                              , pack<T,N,aggregated_> const& v0
                                              , pack<T,N,aggregated_> const& v1
                                              ) noexcept
  {
    return aggregate( eve::plus, v0, v1);
  }

  // -----------------------------------------------------------------------------------------------
  // Emulation with auto-splat inside map for performance purpose
  template<typename T, typename N>
  EVE_FORCEINLINE pack<T,N,emulated_> plus_ ( EVE_SUPPORTS(simd_)
                                            , pack<T,N,emulated_> const& v0
                                            , pack<T,N,emulated_> const& v1
                                            ) noexcept
  {
    return map( eve::plus, v0, v1);
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE pack<T,N,emulated_> plus_ ( EVE_SUPPORTS(simd_)
                                            , pack<T,N,emulated_> const& v0, U const& v1
                                            , requires(Convertible<U,T>)
                                            ) noexcept
  {
    return map( eve::plus, v0, static_cast<T>(v1));
  }

  template<typename T, typename N, typename U>
  EVE_FORCEINLINE pack<T,N,emulated_> plus_ ( EVE_SUPPORTS(simd_)
                                            , U const& v0, pack<T,N,emulated_> const& v1
                                            , requires(Convertible<U,T>)
                                            ) noexcept
  {
    return map( eve::plus, static_cast<T>(v0), v1);
  }
} }

// -------------------------------------------------------------------------------------------------
// Infix operator support
namespace eve
{
  template<typename T, typename N, typename ABI> EVE_FORCEINLINE
  auto operator+( pack<T,N,ABI> const& v0, pack<T,N,ABI> const& v1) noexcept
  {
    return eve::plus(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE requires_type(detail::Convertible<U,T,pack<T,N,ABI>>)
  operator+ ( pack<T,N,ABI> const& v0, U const& v1 ) noexcept
  {
    return eve::plus(v0, v1);
  }

  template<typename T, typename N, typename ABI, typename U>
  EVE_FORCEINLINE requires_type(detail::Convertible<U,T,pack<T,N,ABI>>)
  operator+ ( U const& v0, pack<T,N,ABI> const& v1) noexcept
  {
    return eve::plus(v0, v1);
  }
}

#endif
