//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_IF_ELSE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/vectorized.hpp>
#include <eve/function/bit_select.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_and.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/zero.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/ext/as_wide.hpp>
#include <eve/as_logical.hpp>
#include <eve/forward.hpp>
#include <type_traits>

namespace eve::detail
{
  //------------------------------------------------------------------------------------------------
  // Basic case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           U const &t,
           V const &f) noexcept Requires(std::conditional_t<is_Vectorized_v<U>, U, V>,
                                         Vectorized<T>,
                                         detail::either<is_Vectorized_v<U>, is_Vectorized_v<V>>,
                                         has_compatible_cardinal<typename T::cardinal_type, U, V>
                                        )
  {
    auto cond_mask = bit_mask(cond);
    return bit_select(cond_mask, t, f);
  }

  //------------------------------------------------------------------------------------------------
  // Logical case
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &         cond,
           logical<U> const &t,
           logical<V> const
               &f) noexcept Requires(std::conditional_t<is_Vectorized_v<U>, logical<U>, logical<V>>,
                                     Vectorized<T>,
                                     detail::either<is_Vectorized_v<U>, is_Vectorized_v<V>>,
                                     has_compatible_cardinal<typename T::cardinal_type, U, V>)
  {
    using t_t      = std::conditional_t<is_Vectorized_v<U>, logical<U>, logical<V>>;
    auto cond_mask = bit_mask(cond);
    return bit_cast(bit_select(cond_mask, t.mask(), f.mask()), as_<t_t>());
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,zero},{zero,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           U const &t,
           eve::callable_zero_ const
               &) noexcept Requires(U,
                                    Vectorized<T>,
                                    Vectorized<U>,
                                    has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    return bit_and(t, bit_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_zero_ const &,
           U const &t) noexcept Requires(U,
                                         Vectorized<T>,
                                         Vectorized<U>,
                                         has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    return bit_andnot(t, bit_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,allbits},{allbits,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           U const &t,
           eve::callable_allbits_ const
               &) noexcept Requires(U,
                                    Vectorized<T>,
                                    Vectorized<U>,
                                    has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    return bit_ornot(t, bit_mask(cond));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_allbits_ const &,
           U const &t) noexcept Requires(U,
                                         Vectorized<T>,
                                         Vectorized<U>,
                                         has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    return bit_or(t, bit_mask(cond));
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,one},{one,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           U const &t,
           eve::callable_one_ const
               &) noexcept Requires(U,
                                    Vectorized<T>,
                                    Vectorized<U>,
                                    has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    if constexpr(std::is_integral_v<U>)
    { return minus(bit_ornot(minus(t), bit_mask(cond))); }
    else
    {
      return if_else(cond, t, eve::One<U>());
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_one_ const &,
           U const &t) noexcept Requires(U,
                                         Vectorized<T>,
                                         Vectorized<U>,
                                         has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    if constexpr(std::is_integral_v<U>)
    { return minus(bit_or(minus(t), bit_mask(cond))); }
    else
    {
      return if_else(cond, eve::One<U>(), t);
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,mone},{mone,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           U const &t,
           eve::callable_mone_ const
               &) noexcept Requires(U,
                                    Vectorized<T>,
                                    Vectorized<U>,
                                    has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    if constexpr(std::is_integral_v<U>) { return bit_ornot(t, bit_mask(cond)); }
    else
    {
      return if_else(cond, t, eve::Mone<U>());
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_),
           T const &cond,
           eve::callable_mone_ const &,
           U const &t) noexcept Requires(U,
                                         Vectorized<T>,
                                         Vectorized<U>,
                                         has_compatible_cardinal<typename T::cardinal_type, U>)
  {
    if constexpr(std::is_integral_v<U>) { return bit_or(t, bit_mask(cond)); }
    else
    {
      return if_else(cond, eve::Mone<U>(), t);
    }
  }
}

#endif
