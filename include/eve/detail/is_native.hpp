//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_DETAIL_IS_NATIVE_HPP_INCLUDED
#define EVE_DETAIL_IS_NATIVE_HPP_INCLUDED

#include <eve/arch/tags.hpp>
#include <type_traits>

namespace eve { namespace detail
{
  template<typename X>
  struct is_native
        : std::integral_constant< bool
                                , !std::is_same_v<X,aggregated_> && !std::is_same_v<X,emulated_>
                                >
  {};
} }

#endif
