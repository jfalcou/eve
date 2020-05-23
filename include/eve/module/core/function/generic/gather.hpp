//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_GATHER_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_GATHER_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/zero.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/if_else.hpp>
#include <eve/memory/aligned_ptr.hpp>

namespace eve::detail
{
  //================================================================================================
  // Unaligned pointer
  template<typename U, integral_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_(EVE_SUPPORTS(cpu_), U const *ptr, wide<T, N, ABI> const &v) noexcept
  {
    wide<U, N> that;
    apply<N::value>([&](auto... I) { ((that[I] = ptr[v[I]]),...); });
    return that;
  }

  template<typename U, value X, integral_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_(EVE_SUPPORTS(cpu_),
                               logical<X> const &     cond,
                               U const *              ptr,
                               wide<T, N, ABI> const &v) noexcept
  {
    return if_else(cond, gather(ptr, v), zero_);
  }

  //================================================================================================
  // Aligned pointer
  template<typename U, std::size_t S, integral_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto
  gather_(EVE_SUPPORTS(cpu_), aligned_ptr<U, S> ptr, wide<T, N, ABI> const &v) noexcept
  {
    return gather(ptr.get(), v);
  }

  template<typename U, std::size_t S, value X, integral_scalar_value T, typename N, typename ABI>
  EVE_FORCEINLINE auto gather_(EVE_SUPPORTS(cpu_),
                               logical<X> const &     cond,
                               aligned_ptr<U, S>      ptr,
                               wide<T, N, ABI> const &v) noexcept
  {
    return if_else(cond, gather(ptr.get(), v), zero_);
  }
}

#endif
