//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/detail/implementation.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mone.hpp>
#include <eve/constant/one.hpp>
#include <eve/constant/zero.hpp>
#include <eve/function/bit_andnot.hpp>
#include <eve/function/bit_mask.hpp>
#include <eve/function/bit_ornot.hpp>
#include <eve/function/bit_select.hpp>
#include <eve/function/convert.hpp>
#include <eve/traits/common_compatible.hpp>

namespace eve::detail
{
  template<scalar_value T, value U, value V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), T const & cond, U const & t, V const & f )
  requires compatible_values<U, V>
  {
          if constexpr(simd_value<U> && simd_value<V>)  return  cond ? t : f;
    else  if constexpr(simd_value<U>)                   return  cond ? t : U(f);
    else  if constexpr(simd_value<V>)                   return  cond ? V(t) : f;
    else                                                return  cond ? t : f;
  }

  template<simd_value T, value U, value V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), T const & cond, U const & t, V const & f )
  requires compatible_values<U, V>
  {
    if constexpr( !is_logical_v<T> )
    {
      return if_else(to_logical(cond),t,f);
    }
    else
    {
      using v_t = common_compatible_t<U, V>;
      using e_t = element_type_t<v_t>;
      using r_t = as_wide_t<e_t, cardinal_t<T>>;

      if constexpr(std::same_as<logical<e_t>,element_type_t<T>>)
      {
        return  bit_select(cond.mask(), r_t(t), r_t(f));
      }
      else if constexpr(has_emulated_abi_v<T>)
      {
        return map(if_else, cond, t, f);
      }
      else
      {
        return  if_else(convert(cond, as<as_logical_t<e_t>>()), r_t(t), r_t(f));
      }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Supports if_else(conditional_expr,a,b)
  template<conditional_expr C, value U, value V>
  EVE_FORCEINLINE auto if_else_(EVE_SUPPORTS(cpu_), C const& cond, U const& t, V const& f )
  requires compatible_values<U, V>
  {
    using r_t = std::conditional_t< simd_value<U>, U, V>;

    // If the ignore/keep is complete we can jump over if_else
    if constexpr( C::is_complete )
    {
      if constexpr(C::is_inverted)  { return r_t(t); }
      else                          { return r_t(f); }
    }
    else
    {
      auto const condition  = cond.mask(eve::as_<r_t>());

      if constexpr( C::is_inverted )  { return if_else(condition, f, t ); }
      else                            { return if_else(condition, t, f ); }
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,zero},{zero,t})
  template<value T, value U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_zero_ const
                                          &) noexcept
  {
          if constexpr(scalar_value<T>)             return static_cast<bool>(cond) ? t : U(0);
    else  if constexpr(current_api >= avx512)       return if_else(cond, t, U(0));
    else  if constexpr(bit_compatible_values<T, U>) return bit_and(t, bit_mask(cond));
    else
    {
      using elt_t = element_type_t<T>;
      using l_t = logical<elt_t>;
      return bit_and(convert(is_nez(cond), as<l_t>()), bit_mask(cond));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_zero_ const &,
                                          U const &t) noexcept
  {
          if constexpr(scalar_value<T>)             return static_cast<bool>(cond) ? U(0) : t;
    else  if constexpr(current_api >= avx512)       return if_else(cond, U(0), t);
    else  if constexpr(bit_compatible_values<T, U>) return bit_andnot(t, bit_mask(cond));
    else
    {
      using elt_t = element_type_t<T>;
      using l_t = logical<elt_t>;
      return bit_andnot(convert(is_nez(cond), as<l_t>()), bit_mask(cond));
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,allbits},{allbits,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          callable_allbits_ const
                                          &) noexcept
  {
          if constexpr(scalar_value<T>)             return static_cast<bool>(cond) ? t : allbits(eve::as(t));
    else  if constexpr(current_api >= avx512)       return if_else(cond, t, allbits(eve::as(t)));
    else  if constexpr(bit_compatible_values<T, U>) return bit_ornot(t, bit_mask(cond));
    else
    {
      using elt_t = element_type_t<T>;
      using l_t = as_logical_t<elt_t>;
      return bit_ornot(convert(is_nez(cond), as<l_t>()), bit_mask(cond));
    }
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          callable_allbits_ const &,
                                          U const &t) noexcept
  {
          if constexpr(scalar_value<T>)             return static_cast<bool>(cond) ? allbits(eve::as(t)) : t;
    else  if constexpr(current_api >= avx512)       return if_else(cond, allbits(eve::as(t)),t);
    else if constexpr(bit_compatible_values<T, U>)  return bit_or(t, bit_mask(cond));
    else
    {
      using elt_t = element_type_t<T>;
      using l_t = as_logical_t<elt_t>;
      return bit_or(convert(is_nez(cond), as<l_t>()), bit_mask(cond));
    }
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,mone},{mone,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_mone_ const
                                          &) noexcept
  {
          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? t : mone(eve::as(t));
    else  if constexpr(current_api >= avx512) return if_else(cond, t, U(-1));
    else  if constexpr(integral_value<U>)
    {
      if constexpr(bit_compatible_values<T, U>)
        return bit_ornot(t, bit_mask(cond));
      else
      {
        using elt_t = element_type_t<T>;
        using l_t = as_logical_t<elt_t>;
        return bit_ornot(t, convert(is_nez(cond), as<l_t>()));
      }
    }
    else
      return if_else(cond, t, eve::mone(eve::as<U>()));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_mone_ const &,
                                          U const &t) noexcept
  {
          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? mone(eve::as(t)) : t;
    else  if constexpr(current_api >= avx512) return if_else(cond, U(-1), t);
    else  if constexpr(integral_value<U>)
    {
      if constexpr(bit_compatible_values<T, U>)
        return bit_or(t, bit_mask(cond));
      else
      {
        using elt_t = element_type_t<T>;
        using l_t = as_logical_t<elt_t>;
        return bit_or(t, convert(is_nez(cond), as<l_t>()));
      }
    }
    else
      return if_else(cond, eve::mone(eve::as<U>()), t);
  }

  //------------------------------------------------------------------------------------------------
  // Optimizes if_else(c,{t,one},{one,t})
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          U const &t,
                                          eve::callable_one_ const
                                          &) noexcept
  {
          if constexpr(scalar_value<T>)       return static_cast<bool>(cond) ? t : one(eve::as(t));
    else  if constexpr(current_api >= avx512) return if_else(cond, t, U(1));
    else  if constexpr(integral_value<U>)
    {
      if constexpr(bit_compatible_values<T, U>)
        return -bit_ornot(-t, bit_mask(cond));
      else
      {
        using elt_t = element_type_t<T>;
        using l_t = as_logical_t<elt_t>;
        return -bit_ornot(-t, convert(is_nez(cond), as<l_t>()));
      }
    }
    else
      return if_else(cond, t, eve::one(eve::as<U>()));
  }

  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto if_else_(EVE_SUPPORTS(cpu_),
                                          T const &cond,
                                          eve::callable_one_ const &,
                                          U const &t) noexcept
  {
          if constexpr(scalar_value<T>) return static_cast<bool>(cond) ? one(eve::as(t)) : t;
    else  if constexpr(current_api >= avx512) return if_else(cond, U(1),t);
    else  if constexpr(integral_value<U>)
    {
      if constexpr(bit_compatible_values<T, U>)
        return -bit_or(-t, bit_mask(cond));
      else
      {
        using elt_t = element_type_t<T>;
        using l_t = as_logical_t<elt_t>;
        return -bit_or(-t, convert(is_nez(cond), as<l_t>()));
      }
    }
    else
      return if_else(cond, eve::one(eve::as<U>()),  t);
  }
}
