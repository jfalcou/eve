//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SATURATE_HPP_INCLUDED

#include <eve/detail/overload.hpp>
// #include <boost/simd/function/scalar/clamp.hpp>
// #include <boost/simd/function/scalar/is_inf.hpp>
#include <eve/function/saturated.hpp>
// #include <boost/simd/constant/valmin.hpp>
// #include <boost/simd/constant/valmax.hpp>
#include <eve/as.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Identity case
  template<typename T>
  EVE_FORCEINLINE constexpr T saturate_(EVE_SUPPORTS(cpu_), T const &a0, as_<T> const &) noexcept
  {
    return a0;
  }

#if 0
  // -----------------------------------------------------------------------------------------------
  // double saturated as float -> clamp unless inf
  EVE_FORCEINLINE
  double saturate_(EVE_SUPPORTS(cpu_), double a0, as_<float> const&) noexcept
  {
    auto mn = static_cast<double>(Valmin<float>());
    auto mx = static_cast<double>(Valmax<float>());
    return is_inf(a0) ? a0 : clamp(a0,mn,mx);
  }



  // -----------------------------------------------------------------------------------------------
  // float saturated as double -> identity
  EVE_FORCEINLINE
  float saturate_(EVE_SUPPORTS(cpu_), float a0, as_<double> const&) noexcept
  {
    return a0;
  }



  // -----------------------------------------------------------------------------------------------
  // integer saturated as floating -> identity
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<T>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<std::is_floating_point<U>::value>::type* = 0
                                ) noexcept
  {
    return a0;
  }


  // -----------------------------------------------------------------------------------------------
  // floating saturated as integer
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<U>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<std::is_floating_point<T>::value>::type* = 0
                                ) noexcept
  {
    return select_c<(sizeof(T)<=sizeof(U))>
                                    ( [&]() { return a0; }
                                    , [&]() { return clamp(a0 , static_cast<T>(Valmin<U>())
                                                              , static_cast<T>(Valmax<U>())
                                                          );
                                            }
                                    )();
  }

  // -----------------------------------------------------------------------------------------------
  // unsigned integer saturated as unsigned integer
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<T>::value>::type
          , typename = typename std::enable_if<std::is_integral<U>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<!std::is_signed<T>::value>::type* = 0
                                , typename std::enable_if<!std::is_signed<U>::value>::type* = 0
                                ) noexcept
  {
    return select_c<(sizeof(T)<sizeof(U))>( [&]() { return a0; }
                                          , [&]() { return std::min(a0,static_cast<T>(Valmax<U>())); }
                                          )();
  }

  // -----------------------------------------------------------------------------------------------
  // unsigned integer saturated as signed integer
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<T>::value>::type
          , typename = typename std::enable_if<std::is_integral<U>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<!std::is_signed<T>::value>::type* = 0
                                , typename std::enable_if<std::is_signed<U>::value>::type* = 0
                                ) noexcept
  {
    return std::min(static_cast<T>(Valmax<U>()), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // signed integer saturated as unsigned integer
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<T>::value>::type
          , typename = typename std::enable_if<std::is_integral<U>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<std::is_signed<T>::value>::type* = 0
                                , typename std::enable_if<!std::is_signed<U>::value>::type* = 0
                                ) noexcept
  {
    return select_c<(sizeof(T)<=sizeof(U))>
                                    ( [&]() { return std::max(T(0), a0); }
                                    , [&]() { return clamp(a0,T(0),static_cast<T>(Valmax<U>())); }
                                    )();
  }

  // -----------------------------------------------------------------------------------------------
  // signed integer saturated as signed integer
  template< typename T, typename U
          , typename = typename std::enable_if<std::is_integral<T>::value>::type
          , typename = typename std::enable_if<std::is_integral<U>::value>::type
          >
  EVE_FORCEINLINE T saturate_ ( EVE_SUPPORTS(cpu_)
                                , T a0, as_<U> const&
                                , typename std::enable_if<std::is_signed<T>::value>::type* = 0
                                , typename std::enable_if<std::is_signed<U>::value>::type* = 0
                                ) noexcept
  {
    return select_c<(sizeof(T)<=sizeof(U))>
                                    ( [&]() { return a0; }
                                    , [&]() { return clamp(a0 , static_cast<T>(Valmin<U>())
                                                              , static_cast<T>(Valmax<U>())
                                                          );
                                            }
                                    )();
  }
#endif
}

#endif
