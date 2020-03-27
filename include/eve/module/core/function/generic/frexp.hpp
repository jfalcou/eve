//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU
   
   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SIMD_COMMON_FREXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/regular.hpp>
#include <tuple>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // tagged cases
  template<floating_real_value T, typename TAG>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                       , TAG const & 
                                       , T const & a0) noexcept
  {
    auto [m, e] = TAG()(ifrexp)(a0);
    return  std::make_tuple(m, convert(e, as<value_type_t<T>>()));
  }
  
  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                       , T const & a0) noexcept
  {
    auto [m, e] = ifrexp(a0);
    return  std::make_tuple(m, convert(e, as<value_type_t<T>>()));
  }
}

#endif
