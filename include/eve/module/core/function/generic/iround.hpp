//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IROUND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IROUND_HPP_INCLUDED

#include <eve/detail/implementation.hpp>
#include <eve/function/iceil.hpp>
#include <eve/function/ifloor.hpp>
#include <eve/function/itrunc.hpp>
#include <eve/function/inearest.hpp>
#include <eve/function/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T,  typename D>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_)
                                        , D const &
                                        , T const &a) noexcept
  {
    if constexpr(has_native_abi_v<T>)
    {
           if constexpr(std::is_same_v<D, eve::upward_type>)      return eve::iceil(a);
      else if constexpr(std::is_same_v<D, eve::downward_type>)    return eve::ifloor(a);
      else if constexpr(std::is_same_v<D, eve::toward_zero_type>) return eve::itrunc(a);
      else if constexpr(std::is_same_v<D, eve::to_nearest_type>)  return eve::inearest(a);
    }
    else                                                            return apply_over(D()(iround), a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr auto iround_(EVE_SUPPORTS(cpu_)
                                         , T const &a) noexcept
  {
    return eve::inearest(a);
  }



}

#endif
