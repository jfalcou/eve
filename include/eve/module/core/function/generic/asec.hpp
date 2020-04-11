//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_ASEC_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_ASEC_HPP_INCLUDED

#include <eve/detail/overload.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/function/acos.hpp>
#include <eve/function/raw.hpp>
#include <eve/function/rec.hpp>
#include <eve/concept/value.hpp>

namespace eve::detail
{
  template<floating_real_value T, decorator D>
  EVE_FORCEINLINE constexpr auto asec_(EVE_SUPPORTS(cpu_)
                                       , D const &
                                       , T const &a) noexcept
  requires std::same_as<D,  regular_type> || std::same_as<D,  raw_type>
  {
    if constexpr(native<T>) return D()(acos)(rec(a));
    else                    return apply_over(D()(asec), a);
  }

  template<floating_real_value T>
  EVE_FORCEINLINE constexpr auto asec_ ( EVE_SUPPORTS(cpu_)
                                        , T const &a
                                        ) noexcept
  {
    return asec(regular_type(), a);
  }
}

#endif
