//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/two_prod.hpp>
#include <eve/function/two_add.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto
  fma_(EVE_SUPPORTS(cpu_), T const &a, T const &b, T const &c) noexcept
  requires(T, vectorizable<T>)
  {
    return a * b + c;
  }
  
  template<typename D, typename T>
  EVE_FORCEINLINE constexpr auto
  fma_(EVE_SUPPORTS(cpu_)
      , D const & 
      , T const &a0, T const &a1, T const &a2) noexcept
  requires(T, vectorizable<T>)
  {
    if constexpr(std::is_same_v<T, float>)
    {
      return static_cast<T>( static_cast<double>(a0)*static_cast<double>(a1)
                             + static_cast<double>(a2)
                           );
    }
    else if constexpr(std::is_same_v<T, double>)
    {
      if constexpr(std::is_same_v<D, numeric_type>)
      {
        using iT = as_integer_t<T>;
        iT e0 = exponent(a0);
        iT e1 = exponent(a1);
        iT e = -max(e0, e1)/2;
        T ae2  = ldexp(a2, e);
        auto choose = (e0 > e1);
        T amax = choose ? pedantic_(ldexp)(a0, e) : pedantic_(ldexp)(a1, e);
        T amin = choose ? a1 : a0;
        auto [p, rp] = two_prod(amax, amin);
        auto [s, rs] = two_add(p, ae2);
        return pedantic_(ldexp)(s+(rp+rs), -e);
      }
      else if constexpr(std::is_same_v<D, pedantic_type>)
      {
        auto [p, rp] = two_prod(a0, a1);
        auto [s, rs] = two_add(p, a2);
        return s+(rp+rs);
      }
    }
    else if constexpr(std::is_integral_v<T>)
    {
      // pedantic fma has to ensure "no intermediate overflow".
      // This is done in the case of signed integers by transtyping to unsigned type
      // to perform the computations in a guaranted 2-complement environment
      // since signed integer overflows in C++ produce "undefined results"
      using u_t = as_integer_t<T, unsigned>;
      return static_cast<T>( static_cast<u_t>(a0) * static_cast<u_t>(a1) + static_cast<u_t>(a2));
    }
  }
}

#endif
