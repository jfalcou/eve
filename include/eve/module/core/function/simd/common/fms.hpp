//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/minus.hpp>
#include <eve/function/fma.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fms_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept Requires(
      std::conditional_t<!is_Vectorized_v<T>, std::conditional_t<is_Vectorized_v<U>, U, V>, T>,
      detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>, is_Vectorized_v<V>>)
  {
    static constexpr auto vT = is_Vectorized_v<T>;
    static constexpr auto vU = is_Vectorized_v<U>;
    static constexpr auto vV = is_Vectorized_v<V>;

    if constexpr(vT && !vU && !vV)
      return fms(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return fms(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return fms(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return fms(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return fms(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return fms(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::fms, a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::fms, a, b, c);
        else
          return eve::fma(a, b, -c);
      }
      return T();
    }
  }

  template<typename D, typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fms_(EVE_SUPPORTS(cpu_)
     ,  D const & deco
      , T const &a, U const &b, V const &c) noexcept Requires(
      std::conditional_t<!is_Vectorized_v<T>, std::conditional_t<is_Vectorized_v<U>, U, V>, T>,
      detail::either<is_Vectorized_v<T>, is_Vectorized_v<U>, is_Vectorized_v<V>>)
  {
    return deco(fma)(a, b, -c); 
  }
  
}

#endif
