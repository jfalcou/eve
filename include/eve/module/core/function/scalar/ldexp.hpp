//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_LDEXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/tags.hpp>
#include <eve/function/wide_cast.hpp>
#include <eve/function/bitwise_cast.hpp>
#include <eve/function/bitwise_shl.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp> 
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , T const &a0
                                    , U const &a1) noexcept
  {
    if constexpr(std::is_integral_v<T>)
    {
      if constexpr(std::is_integral_v<U>)
        return (a1>0)?(a0<<a1):(a0>>a1);
      else
        EVE_ASSERT(false,
               "[ eve::ldexp] - If argument 1 is integral argument 2 must be integral." );
    }
    else
    {
      if constexpr(std::is_floating_point_v<U>)
      {
         BOOST_ASSERT_MSG(is_flint(a1)||is_invalid(a1), "argument 2 is not a flint nor is invalid");
         return ldexp(a0, itrunc(a1));
      }
      else 
      {
        using i_t = as_integer_t<T>;
        i_t ik =  a1+Maxexponent<T>();
        ik = bitwise_shl(ik, Nbmantissabits<T>());
        return a0*bitwise_cast<T>(ik);
      }
    }
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic case
  template<typename T>
  EVE_FORCEINLINE constexpr T ldexp_(EVE_SUPPORTS(cpu_)
                                    , pedantic_ const & 
                                    , T const &a0
                                    , U const &a1) noexcept
  {
    if constexpr(std::is_integral_v<T>)
    {
      return ldexp(a0, a1); 
    }
    else
    {
      if constexpr(std::is_floating_point_v<U>)
      {
         return ldexp[pedantic_](a0, itrunc(a1));
      }
      else
      {
        using i_t = as_integer_t<T>;
        i_t e =  static_cast<i_t>(a1);
        T f = One<T>();
#ifndef BOOST_SIMD_NO_DENORMALS
        if constexpr(platform::supports_denormals)
        {
          if (e < Minexponent<T>())   //(BOOST_UNLIKELY
          {
            e -= Minexponent<T>();
            f = Smallestposval<T>();
          }
        }
#endif
        i_t b = (e == Limitexponent<T>());
        f += static_cast<T>(b);
        e -= b;
        e += Maxexponent<T>();
        e = bitwise_shl(e, Nbmantissabits<T>());
        return a0*bitwise_cast<T>(e)*f;
      }
  }
}

#endif
