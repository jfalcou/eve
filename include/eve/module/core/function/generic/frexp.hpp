//==================================================================================================
/**
   EVE - Expressive Vector Engine
   Copyright 2020 Jean-Thierry LAPRESTE
   Copyright 2020 Joel FALCOU

   Licensed under the MIT License <http://opensource.org/licenses/MIT>.
   SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_FREXP_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_FREXP_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/function/ifrexp.hpp>
#include <eve/function/convert.hpp>
#include <eve/concept/vectorizable.hpp>
#include <eve/concept/value.hpp>
#include <eve/function/regular.hpp>
#include <tuple>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
  // -----------------------------------------------------------------------------------------------
  // tagged cases
  template<floating_real_value T, typename TAG>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                       , TAG const &
                                       , T const & a0) noexcept
  {
    if constexpr(native<T>)
    {
      auto [m, e] = TAG()(ifrexp)(a0);
      return  std::make_tuple(m, convert(e, as<element_type_t<T>>()));
    }
    else apply_over2(TAG()(frexp), a0);
  }

  // -----------------------------------------------------------------------------------------------
  // Regular case
  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto frexp_(EVE_SUPPORTS(cpu_)
                                       , T const & a0) noexcept
  {
    return frexp(regular_type(), a0);
  }
}

#endif
