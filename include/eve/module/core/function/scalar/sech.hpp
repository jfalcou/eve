//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_SECH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_SECH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/abs.hpp>
#include <eve/function/average.hpp>
#include <eve/function/exp.hpp>
#include <eve/function/mul.hpp>
#include <eve/function/div.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/maxlog.hpp>
#include <eve/constant/log_2.hpp>
#include <eve/constant/half.hpp>
#include <eve/constant/one.hpp>
#include <type_traits>

namespace eve::detail
{
  // Regular case
  template<typename T>
  EVE_FORCEINLINE constexpr auto sech_(EVE_SUPPORTS(cpu_)
                                     , T a0) noexcept
  requires(T, floating_point<T>)
  {
    T x = eve::abs(a0);
    auto test1 = (x > Maxlog<T>()-Log_2<T>());
    T fac = test1 ? Half<T>() : One<T>();
    T tmp1 = exp(-x*fac);
    T tmp = T(2)*tmp1;
    return test1 ? tmp1*tmp : tmp/fma(tmp1, tmp1, T(1)); 
  }
}

#endif
