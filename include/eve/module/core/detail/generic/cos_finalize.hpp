//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_DETAIL_GENERIC_COS_KERNEL_HPP_INCLUDED
#define EVE_MODULE_CORE_DETAIL_GENERIC_COS_KERNEL_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/meta.hpp>
#include <eve/detail/abi.hpp>
#include <eve/tags.hpp>
#include <eve/function/fma.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/oneminus.hpp>
#include <eve/function/sqr.hpp>
#include <eve/constant/mhalf.hpp>
#include <type_traits>


namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto cos_finalize( T  z) noexcept
  {
 
  }
}

#endif
