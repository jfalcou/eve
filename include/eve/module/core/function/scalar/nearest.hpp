//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_NEAREST_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_NEAREST_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/constant/twotonmb.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/is_negative.hpp>
#include <type_traits>
#include <cmath>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto nearest_(EVE_SUPPORTS(cpu_),
                                          T const &a0) noexcept requires(T, Vectorizable<T>)
  {
    if constexpr(std::is_floating_point_v<T>)
    {
      const T v   = eve::abs(a0);
      const T t2n = Twotonmb<T>();
      T       d0  = (v + t2n);

      T d = (d0 - t2n);
      d   = (v < t2n) ? d : v;
      return is_negative(a0) ? -d : d;
    }
    else
      return a0;
  }

  //   template<typename T>
  //   EVE_FORCEINLINE constexpr auto nearest_(EVE_SUPPORTS(cpu_)
  //                                   , raw_type const &
  //                                   , T const &a0) noexcept
  //   {
  //     if constexpr(std::is_floating_point_v<T>) return nearest(a0);
  //     else return a0;
  //   }
}

#endif
