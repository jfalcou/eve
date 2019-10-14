//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_GATHER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_GATHER_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/if_else.hpp>
#include <eve/constant/zero.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  //================================================================================================
  // Unaligned pointer
  template<typename U, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_(EVE_SUPPORTS(cpu_), U const* ptr, wide<T, N, ABI> const &v) noexcept
  requires( wide<U,N>, integral<T> )
  {
    return apply<N::value>( [&](auto... I)
                            {
                              return wide<U, N>{ ptr[ v[I] ]... };
                            }
                          );
  }

  template<typename U, typename X, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_( EVE_SUPPORTS(cpu_),
                                logical<X> const& cond, U const* ptr, wide<T, N, ABI> const &v
                              ) noexcept
  requires( wide<U,N>, integral<T> )
  {
    return if_else(cond, gather(ptr,v), Zero(as<wide<U,N>>()));
  }

  //================================================================================================
  // Aligned pointer
  template<typename U, std::size_t S, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_( EVE_SUPPORTS(cpu_),
                                aligned_ptr<U,S> ptr, wide<T, N, ABI> const &v
                              ) noexcept
  requires( wide<std::remove_const_t<U>,N>, integral<T> )
  {
    return gather(ptr.get(),v);
  }

  template<typename U, std::size_t S, typename X, typename T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_( EVE_SUPPORTS(cpu_),
                                logical<X> const& cond,
                                aligned_ptr<U,S> ptr, wide<T, N, ABI> const &v
                              ) noexcept
  requires( wide<std::remove_const_t<U>,N>, integral<T> )
  {
    return if_else(cond, gather(ptr.get(),v), Zero(as<wide<std::remove_const_t<U>,N>>()));
  }
}

#endif
