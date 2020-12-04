//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/forward.hpp>
#include <concepts>

namespace eve
{
  namespace detail
  {
    template<typename Wide, typename... ABI>
    struct  is_native_for_abi
          : std::bool_constant
            < ( std::is_same_v< Wide
                              , wide< element_type_t<Wide>
                                    , expected_cardinal_t<element_type_t<Wide>, ABI>
                                    , ABI
                                    >
                              >
              || ...
              )
            >
    {};

    template<typename Wide, typename... ABI>
    struct  is_native_for_abi<logical<Wide>,ABI...>
          : std::bool_constant
            < ( std::is_same_v< logical<Wide>
                              , logical < wide< element_type_t<Wide>
                                              , expected_cardinal_t < element_type_t<Wide>
                                                                    , ABI
                                                                    >
                                              , ABI
                                              >
                                        >
                              >
              || ...
              )
            >
    {};
  }

  template<typename Wide, typename... ABI>
  concept native_simd_for_abi = detail::is_native_for_abi<Wide,ABI...>::value;
}