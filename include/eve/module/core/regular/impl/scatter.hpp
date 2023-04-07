//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/conditional.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/module/core/constant/zero.hpp>
#include <eve/module/core/regular/if_else.hpp>

namespace eve::detail
{
//================================================================================================
// Unaligned pointer
  template<typename U, integral_scalar_value I, scalar_value T, typename N>
  EVE_FORCEINLINE void
  scatter_(EVE_SUPPORTS(cpu_), U  *ptr, wide<I, N> const& idx, wide<T, N> const& a) noexcept
  {
    for(std::ptrdiff_t i=0; i < N::value; ++i)
    {
      *(ptr+idx.get(i)) = a.get(i);
    }
  }

  template<typename U, conditional_expr C, integral_scalar_value I, scalar_value T, typename N>
  EVE_FORCEINLINE auto
  scatter_(EVE_SUPPORTS(cpu_), C cx, U *ptr, wide<I, N> const& idx, wide<T, N> const& a ) noexcept
  {
    auto src = alternative(cx, wide<U, N> {}, as<wide<U, N>> {});
    auto m   = expand_mask(cx, as<wide<U, N>> {});

    for(size_t i=0; i < N::value; ++i)
    {
      if(m.get(i)) *(ptr+idx.get(i)) = a.get(i);
    }

  }

//================================================================================================
// Aligned pointer
  template<typename U, typename S, integral_scalar_value I, scalar_value T, typename N>
  EVE_FORCEINLINE void
  scatter_(EVE_SUPPORTS(cpu_), aligned_ptr<U, S> ptr, wide<I, N> const& idx, wide<T, N> const& a) noexcept
  {
    scatter(ptr.get(), idx, a);
  }

  template<typename U, typename S, conditional_expr C, integral_scalar_value I, scalar_value T, typename N>
  EVE_FORCEINLINE void
  scatter_(EVE_SUPPORTS(cpu_), C cx, aligned_ptr<U, S> ptr, wide<T, N> const& idx, wide<T, N> const& a) noexcept
  {
    scatter[cx](ptr.get(), idx, a);
  }

  //////////////////////////////////////////////////////////////////////////////////////////////////
  // scalar index for genericity
  //================================================================================================
  //  Unaligned pointer
  template<typename U, integral_scalar_value I, scalar_value T>
  EVE_FORCEINLINE void
  scatter_(EVE_SUPPORTS(cpu_), U const *ptr, I const & idx, T const& v) noexcept
  {
     *(ptr + idx) = v;
  }

  template<typename U, value X, integral_scalar_value I , scalar_value T>
  EVE_FORCEINLINE auto
  scatter_(EVE_SUPPORTS(cpu_), logical<X> const& cond, U const *ptr, I const & idx, T const& v) noexcept
  {
    if (cond) *(ptr + idx) = v ;
  }

  //================================================================================================
  //  Aligned pointer
  template<typename U, typename S, integral_scalar_value I, scalar_value T>
  EVE_FORCEINLINE auto
  scatter_(EVE_SUPPORTS(cpu_), aligned_ptr<U, S> ptr, I const & idx, T const& v) noexcept
  {
     *(ptr + idx) = v;
  }

  template<typename U, typename S, value X, integral_scalar_value I, scalar_value T>
  EVE_FORCEINLINE auto
  scatter_(EVE_SUPPORTS(cpu_), logical<X> const& cond, aligned_ptr<U, S> ptr, I const & idx, T const& v) noexcept
  {
    if (cond) *(ptr + idx) = v ;
  }
}
