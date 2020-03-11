//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Joel FALCOU
   Copyright 2020 Jean-Thierry LAPRESTE
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ACOTH_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ACOTH_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/atanh.hpp>
#include <eve/function/rec.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T>
  EVE_FORCEINLINE constexpr auto acoth_(EVE_SUPPORTS(cpu_)
                                       , T x) noexcept
  requires(T, floating_point<value_type_t<T>>)
  {
    return eve::atanh(rec(x));
  }
}

#endif
