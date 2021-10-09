//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/function/reduce.hpp>
#include <eve/function/splat.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/any.hpp>
#include <eve/function/add.hpp>
#include <eve/constant/zero.hpp>

namespace eve::detail
{
  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto sum_ ( EVE_SUPPORTS(cpu_)
                            , splat_type const&, wide<T,N> const &v
                            ) noexcept
  {
          if constexpr( N::value == 1 )               return v;
    else  if constexpr( is_emulated_v<abi_t<T, N>>  ) return wide<T,N>( eve::detail::sum(v) );
    else  if constexpr( is_aggregated_v<abi_t<T, N>>)
    {
      auto[l,h] = v.slice();
      auto r = splat(sum)( l + h );
      return eve::combine(r,r);
    }
    else return butterfly_reduction(v, eve::add);
  }

  template<simd_value T>
  EVE_FORCEINLINE auto sum_ ( EVE_SUPPORTS(cpu_)
                            , splat_type const&, logical<T> const &v
                            ) noexcept
  {
    return logical<T>(eve::any(v));
  }

  template<real_scalar_value T>
  EVE_FORCEINLINE auto sum_(EVE_SUPPORTS(cpu_), T const &v) noexcept
  {
    return v;
  }

  template<real_scalar_value T, typename N>
  EVE_FORCEINLINE auto sum_(EVE_SUPPORTS(cpu_), wide<T,N> const &v) noexcept
  {
          if constexpr( N::value == 1 )         return v.get(0);
    else  if constexpr( is_emulated_v<abi_t<T, N>> )
    {
      return [&]<std::size_t... I>(std::index_sequence<I...>)
      {
        T r = 0;
        ((r += v.get(I)),...);
        return r;
      }(std::make_index_sequence<N::value>{});
    }
    else  if constexpr( is_aggregated_v<abi_t<T, N>> )
    {
      auto[l,h] = v.slice();
      return  sum( l+h );
    }
    else return butterfly_reduction(v, eve::add).get(0);
  }

  template<simd_value T>
  EVE_FORCEINLINE auto sum_(EVE_SUPPORTS(cpu_), logical<T> const &v) noexcept
  {
    return eve::any(v);
  }

  // -----------------------------------------------------------------------------------------------
  // Masked case
  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto sum_(EVE_SUPPORTS(cpu_), C const &cond, U const &t) noexcept
  {
    return sum(if_else(cond, t, eve::zero));
  }

  template<conditional_expr C, real_value U>
  EVE_FORCEINLINE auto sum_(EVE_SUPPORTS(cpu_), C const &cond
                               , splat_type const&, U const &t) noexcept
  {
    return splat(sum)(if_else(cond, t, eve::zero));
  }
}
