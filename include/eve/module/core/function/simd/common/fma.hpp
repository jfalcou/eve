//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FMA_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/add.hpp>
#include <eve/function/two_prod.hpp>
#include <eve/function/two_mul.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/minmag.hpp>
#include <eve/function/maxmag.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fma_(EVE_SUPPORTS(cpu_), T const &a, U const &b, V const &c) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>)
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;

    if constexpr(vT && !vU && !vV)
      return fma(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return fma(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return fma(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return fma(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return fma(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return fma(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(eve::fma, a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(eve::fma, a, b, c);
        else
          return a * b + c;
      }
      return  T();
    }
  }
  ///////////////////////////////////////////////////////////////////////////////////////////////////
  /// pedantic version
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fma_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a, U const &b, V const &c) noexcept requires(
      std::conditional_t<!is_vectorized_v<T>, std::conditional_t<is_vectorized_v<U>, U, V>, T>,
      detail::either<is_vectorized_v<T>, is_vectorized_v<U>, is_vectorized_v<V>>)
  {
    static constexpr auto vT = is_vectorized_v<T>;
    static constexpr auto vU = is_vectorized_v<U>;
    static constexpr auto vV = is_vectorized_v<V>;

    if constexpr(vT && !vU && !vV)
      return pedantic_(fma)(a, T{b}, T{c});
    else if constexpr(vT && vU && !vV)
      return pedantic_(fma)(a, b, T{c});
    else if constexpr(vT && !vU && vV)
      return pedantic_(fma)(a, T{b}, c);
    else if constexpr(!vT && vU && !vV)
      return pedantic_(fma)(U{a}, b, U{c});
    else if constexpr(!vT && vU && vV)
      return pedantic_(fma)(U{a}, b, c);
    else if constexpr(!vT && !vU && vV)
      return pedantic_(fma)(V{a}, V{b}, c);
    else
    {
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(pedantic_(eve::fma), a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(pedantic_(eve::fma), a, b, c);
        else if constexpr(std::is_same_v<value_type_t<T>, float>)
        {
          return convert(convert(a0, as<double>())*convert(a1, as<double>())
                         + convert(a2, as<double>()), as<float>());
        }
        else    if constexpr(std::is_same_v<T, double>)
        {
          T p, rp, s, rs;
#ifndef EVE_DONT_CARE_PEDANTIC_FMA_OVERFLOW
          using iT = bd::as_integer_t<T>;
          T amax =  maxmag(a0, a1);
          T amin =  minmag(a0, a1);
          iT e0 = -shr(exponent(amax), 1);
          amax = pedantic_(ldexp)(amax, e0);
          T a02 = pedantic_(ldexp)(a2, e0);
          std::tie(p, rp) = two_prod(amax, amin);
          std::tie(s, rs) = two_add(p, a02);
          return pedantic_(ldexp)(s+(rp+rs), -e0);
#else
          auto [p, rp] = two_prod(a0, a1);
          auto [s, rs] = two_add(p, a2);
          return s+(rp+rs);
#endif
        }
        else  constexpr(std::is_integral_v<T>)
        {
          // pedantic fma has to ensure "no intermediate overflow".
          // This is done in the case of signed integers by transtyping to unsigned type
          // to perform the computations in a guaranted 2-complement environment
          // since signed integer overflows in C++ produce "undefined results"
          using u_t = as_integer_t<T, unsigned>;
          return static_cast<T>(fma( bit_cast(a0, as<u_t>()),  bit_cast<u_t>(a1, as<u_t>())
                                   ,  bit_cast<u_t>(a2, as<u_t>())));
        }
      }
      return  T();
    }
  }
}

#endif
