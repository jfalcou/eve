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
#include <eve/function/two_prod.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/convert.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/ldexp.hpp>
#include <eve/function/max.hpp>
#include <eve/function/minmag.hpp>
#include <eve/function/maxmag.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/numeric.hpp>
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
  template<typename D, typename T, typename U, typename V>
  EVE_FORCEINLINE auto
  fma_(EVE_SUPPORTS(cpu_), D const & deco, T const &a, U const &b, V const &c) noexcept requires(
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
      using v_t =  value_type_t<T>; 
      if constexpr(std::is_same_v<T, U> && std::is_same_v<T, V>)
      {
        using abi_t = typename T::abi_type;
        if constexpr(is_aggregated_v<abi_t>)
          return aggregate(deco(eve::fma), a, b, c);
        else if constexpr(is_emulated_v<abi_t>)
          return map(deco(eve::fma), a, b, c);
        else if constexpr(std::is_same_v<value_type_t<v_t>, float>)
        {
          return convert(convert(a, as<double>())*convert(b, as<double>())
                         + convert(c, as<double>()), as<float>());
        }
        else if constexpr(std::is_same_v<v_t, double>)
        {
          if constexpr(std::is_same_v<D, numeric_type>)
          {
            auto amax =  maxmag(a, b);
            auto amin =  minmag(a, b);
            auto e0 = -shr(exponent(amax), 1);
            amax = pedantic_(ldexp)(amax, e0);
            auto c0 = pedantic_(ldexp)(c, e0);
            auto [p, rp] = two_prod(amax, amin);
            auto [s, rs] = two_add(p, c0);
            return pedantic_(ldexp)(s+(rp+rs), -e0);
          }
          else if constexpr(std::is_same_v<D, pedantic_type>)
          {
            auto [p, rp] = two_prod(a, b);
            auto [s, rs] = two_add(p, c);
            return s+(rp+rs);
          }
        }
        else if constexpr(std::is_integral_v<v_t>)
        {
          // correct fma has to ensure "no intermediate overflow".
          // This is done in the case of signed integers by transtyping to unsigned type
          // to perform the computations in a guaranted 2-complement environment
          // since signed integer overflows in C++ produce "undefined results"
          using u_t = as_integer_t<T, unsigned>;
          return bit_cast(fma( bit_cast(a, as<u_t>()),  bit_cast(b, as<u_t>())
                             ,  bit_cast(c, as<u_t>())), as<T>());
        }
      }
      return  T();
    }
  }
}

#endif
