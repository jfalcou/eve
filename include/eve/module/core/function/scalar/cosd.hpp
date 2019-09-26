//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_SCALAR_COSD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_SCALAR_COSD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/cos.hpp>
#include <eve/function/trigo_tags.hpp>
#include <eve/function/deginrad.hpp>
#include <type_traits>

namespace eve::detail
{

  template<typename T>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , T const &a0) noexcept

  {
    return cos(deginrad(a0)); 
  }
  
  template<typename T, typename TAG>
  EVE_FORCEINLINE constexpr auto cosd_(EVE_SUPPORTS(cpu_)
                                     , TAG const & tag
                                     , T const &a0) noexcept
  {
    if constexpr(eve::is_trigonometric_tag_v<TAG>)
      return cos(tag, deginrad(a0));
    else
    {
      static_assert(eve::is_trigonometric_tag_v<TAG>, "[tagged cosd ]: Used tag is unsupported"); 
    }
  }

}

#endif
