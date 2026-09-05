//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits/element_type.hpp>
#include <eve/traits/as_wide.hpp>
#include <eve/detail/wide_forward.hpp>
#include <concepts>

namespace eve
{
  namespace _
  {
    template<typename Wide, typename... ABI>
    inline constexpr bool is_native_for_abi_v = ( (std::is_same_v<typename Wide::abi_type, ABI> &&
                                                  Wide::size() == expected_cardinal_v<element_type_t<Wide>, ABI> )
                                                || ...);

    template<typename Wide, typename... ABI>
    inline constexpr bool is_native_for_abi_v<logical<Wide>, ABI...> = is_native_for_abi_v<Wide, ABI...>;
  }

  template<typename Wide, typename... ABI>
  concept native_simd_for_abi = _::is_native_for_abi_v<Wide, ABI...>;
}
