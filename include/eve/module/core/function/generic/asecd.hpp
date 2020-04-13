//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ASECD_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ASECD_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/asec.hpp>
#include <eve/function/indeg.hpp>
#include <eve/function/raw.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{
 template<floating_real_value T, typename D>
  EVE_FORCEINLINE constexpr auto asecd_(EVE_SUPPORTS(cpu_)
                                       , D const &
                                       , T const &a) noexcept
  requires std::same_as<D,  regular_type> || std::same_as<D,  raw_type>
  {
    if constexpr(native<T>) return indeg(D()(asec)(a));
    else                    return apply_over(D()(asecd), a);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asecd_ ( EVE_SUPPORTS(cpu_)
                                        , T const &a
                                        ) noexcept
  {
    return asecd(regular_type(), a);
  }
}

#endif
