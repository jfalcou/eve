//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ROUND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ROUND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ceil.hpp>
#include <eve/function/floor.hpp>
#include <eve/function/trunc.hpp>
#include <eve/function/nearest.hpp>
#include <eve/function/roundings.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  template<real_value T,  typename D>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_)
                                    , D const &
                                    , T const &a) noexcept
  {
    if constexpr(native<T>)
    {
      if constexpr(std::is_same_v<D, eve::upward_type>)      return eve::ceil(a);
      else if constexpr(std::is_same_v<D, eve::downward_type>)    return eve::floor(a);
      else if constexpr(std::is_same_v<D, eve::toward_zero_type>) return eve::trunc(a);
      else if constexpr(std::is_same_v<D, eve::to_nearest_type>)  return eve::nearest(a);
    }
    else                                                            return apply_over(D()(round), a);
  }

  template<real_value T>
  EVE_FORCEINLINE constexpr T round_(EVE_SUPPORTS(cpu_)
                                    , T const &a) noexcept
  {
    return eve::nearest(a);
  }



}

#endif
