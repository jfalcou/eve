//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
#include <eve/function/bit_cast.hpp>
#include <eve/function/bit_shl.hpp>
#include <eve/function/rshl.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/is_flint.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/constant/limitexponent.hpp>
#include <eve/constant/minexponent.hpp> 
#include <eve/constant/maxexponent.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/platform.hpp>
#include <type_traits>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto ldexp_(EVE_SUPPORTS(cpu_)
                                    , T const &a0
                                    , U const &a1) noexcept
  requires(T, floating_point<T>, vectorizable<U>)
  {
    if constexpr(std::is_floating_point_v<U>)
    {
      using i_t =  as_integer_t<U, signed>; 
      return ldexp(a0, i_t(trunc(a1))); // TODO itrunc
    }
    else 
    {
      using i_t = detail::as_integer_t<T>;
      i_t ik =  a1+Maxexponent<T>();
      ik = bit_shl(ik, Nbmantissabits<T>());
      return a0*bit_cast(ik, as(T()));
    }
  }
  
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto ldexp_(EVE_SUPPORTS(cpu_)
                                    , regular_type const &    
                                    , T const &a0
                                    , U const &a1) noexcept
  {
    return ldexp(a0, a1); 
  }
  
  // -----------------------------------------------------------------------------------------------
  // Pedantic case
  template<typename T, typename U>
  EVE_FORCEINLINE constexpr auto ldexp_(EVE_SUPPORTS(cpu_)
                                    , pedantic_type const & 
                                    , T const &a0
                                    , U const &a1) noexcept
  requires(T, floating_point<T>, vectorizable<U>)
  {
    if constexpr(std::is_floating_point_v<U>)
    {
      using i_t =  as_integer_t<U, signed>; 
      return pedantic_(ldexp)(a0, i_t(trunc(a1))); //TODO itrunc(a1)
    }
    else
    {
      using i_t = as_integer_t<T>;
      i_t e =  static_cast<i_t>(a1);
      T f = One<T>();
      if constexpr(eve::platform::supports_denormals)
      {
        if (e < Minexponent<T>())   //(BOOST_UNLIKELY
        {
          e -= Minexponent<T>();
          f = Smallestposval<T>();
        }
      }
      i_t b = (e == Limitexponent<T>());
      f += static_cast<T>(b);
      e -= b;
      e += Maxexponent<T>();
      e = bit_shl(e, Nbmantissabits<T>());
      return a0*bit_cast(e, as(T()))*f;
    }
  }
}

#endif
