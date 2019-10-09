//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_NEXT_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_NEXT_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/module/core/detail/generic/next_kernel.hpp>
#include <eve/function/saturated.hpp>
#include <eve/function/if_else.hpp
#include <eve/function/is_nan.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/add.hpp>
#include <eve/constant/nan.hpp>
#include <eve/concept/vectorizable.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      if constexpr(eve::platform::supports_nans)
      {
        auto z =  bitfloating(inc(bitinteger(a))); 
        return if_else(is_nan(a0), allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      return inc(a);
    }
  }

  template<typename T>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , T const &a
                                      , U const &n) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(!std::is_integral_v<value_type_t<U>)
    {
      static_assert(std::is_integral_v<value_type_t<U>, "[next] : second parameter must be of integral type");
    }
    else if constexpr(std::is_floating_point_v<T>)
    {
      EVE_ASSERT(all(isgez(n)), "[next] : second parameter must be positive");
      auto z =  bitfloating(bitinteger(a)+n); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a0), allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      return a+n;
    }
  }
  
  ////////////////////////////////////////////////
  // tagged case (saturated_)
  template<typename T,  typename TAG>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , TAG const & tag_
                                      , T const &a) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      if constexpr(eve::platform::supports_nans)
      {
        auto z =  bitfloating(tag_(inc)(bitinteger(a))); 
        return if_else(is_nan(a0), allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<value_type_t<T>>)
    {
      return tag_(inc)(a);
    }
  }
  
  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto next_(EVE_SUPPORTS(cpu_)
                                      , TAG const & tag_
                                      , T const &a
                                      , U const &n) noexcept
  requires(T, Vectorizable<T>)
  {
    if constexpr(!std::is_integral_v<value_type_t<U>)
    {
      static_assert(std::is_integral_v<value_type_t<U>, "[next] : second parameter must be of integral type");
    }
    else if constexpr(std::is_floating_point_v<value_type_t<T>>)
    {
      EVE_ASSERT(all(isgez(n)), "[next] : second parameter must be positive");
      auto z =  bitfloating(tag_(add)(bitinteger(a), n)); 
      if constexpr(eve::platform::supports_nans)
      {
        return if_else(is_nan(a0), allbits_, z);
      }
      else
      {
        return z; ;
      }
    }
    else // if constexpr(std::is_integral_v<T>)
    {
      return tag_(add)(a, n);
    }
  }
   
}

#endif
