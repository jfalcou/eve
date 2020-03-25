//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_EPS_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_EPS_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/bit_cast.hpp>
#include <eve/function/exponent.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_not_finite.hpp>
#include <eve/function/is_less.hpp>
#include <eve/function/min.hpp>
#include <eve/function/add.hpp>
#include <eve/function/shl.hpp>
#include <eve/constant/allbits.hpp>
#include <eve/constant/mindenormal.hpp>
#include <eve/constant/nbmantissabits.hpp>
#include <eve/constant/smallestposval.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept
  Requires(T, behave_as<floating_point,T>)
  {
    using t_abi = abi_type_t<T>;
    if constexpr(is_aggregated_v<t_abi>)
    {
      return aggregate(eps, a0);
    }
    else if constexpr(is_emulated_v<t_abi>)
    {
      return map(eps, a0);
    }
    using i_t = as_integer_t<T>;
    using v_t = value_type_t<T>; 
    auto a = eve::abs(a0);
    auto e1 = exponent(a)-Nbmantissabits<T>();
    auto e = bit_cast(bit_cast(T(1), as<i_t>())+(shl(e1,Nbmantissabits<v_t>())), as<T>());
    e =  add[is_not_finite(a)](e, Nan<T>()); 
    if constexpr(eve::platform::supports_denormals)
    {
      return  if_else(is_less(a, Smallestposval<T>()), Mindenormal<T>(), e); 
    }
    else return e; 
  }
  
  template<typename T>
  EVE_FORCEINLINE constexpr auto eps_(EVE_SUPPORTS(cpu_)
                                     , T const &a) noexcept
  Requires(T, behave_as<integral,T>)
  {
    return T(1); 
  }
}

#endif
