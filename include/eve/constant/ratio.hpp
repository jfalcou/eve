//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_RATIO_RATIO_HPP_INCLUDED
#define EVE_RATIO_RATIO_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/meta.hpp>
#include <eve/as.hpp>
#include <type_traits>
#include <cstdint>

namespace eve
{
  template<std::uintmax_t Num, std::uintmax_t Denum, typename Type>
  EVE_FORCEINLINE auto Ratio(as_<Type> const & = {})
  {
    return detail::constant ( detail::ratio< boost::dispatch::scalar_of_t<Type>, Num, Denum>{}
                            , boost::simd::as_<Type>{}
                            );
  }
}

#endif
