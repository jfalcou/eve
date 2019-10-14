//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ATAND_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ATAND_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/atan.hpp>
#include <eve/function/indeg.hpp>
#include <eve/tags.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto atand_(EVE_SUPPORTS(cpu_)
                                  , T const &a0) noexcept
  requires(T, behave_as<floating,T>)
  {
    return indeg(atan(a0));
  }

}

#endif
