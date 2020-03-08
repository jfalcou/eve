//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_REMPIO2_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_REMPIO2_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/function/all.hpp>
#include <eve/function/is_nltz.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/regular.hpp>
#include <eve/module/core/detail/scalar/rempio2_kernel.hpp>
#include <eve/module/core/detail/constant/rempio2_limits.hpp>
#include <eve/detail/abi.hpp>
#include <eve/assert.hpp>
#include <type_traits>
#include <tuple>


namespace eve::detail
{
  template <typename D, typename T>
  EVE_FORCEINLINE auto  rempio2_(EVE_SUPPORTS(cpu_)
                                , D const & deco
                                , T const &xx) noexcept
  requires(std::tuple<T, T, T>, vectorizable<T>)
  {
    if constexpr(std::is_same_v<D, eve::small_type>)
    {
      return rempio2_small(xx); 
    }
    else if constexpr(std::is_same_v<D, eve::medium_type>)
    {
      return rempio2_medium(xx); 
    }
    else if constexpr(std::is_same_v<D, eve::big_type>)
    {
      return rempio2_big(xx); 
    }
    else if constexpr(std::is_same_v<D, eve::regular_type>)
    {
      return rempio2(xx); 
    }
    else
    {
      EVE_ASSERT(false, "unsupported decorator for rempio2"); 
    }
  }
  
  template < typename T>
  EVE_FORCEINLINE auto  rempio2_(EVE_SUPPORTS(cpu_)
                                , T const &x) noexcept
  requires(std::tuple<T, T, T>, vectorizable<T>)
  {
    if (x < Rempio2_limit(restricted_type(), T()))  return  std::make_tuple(T(0), x, T(0)); 
    else if (x <= Rempio2_limit(small_type(), T()))  return small_(rempio2)(x); 
    else if (x <= Rempio2_limit(medium_type(), T())) return medium_(rempio2)(x); 
    else return big_(rempio2)(x); 
  }
}


#endif
 
