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

#include <eve/detail/abi.hpp>
#include <type_traits>
#include <utility>

namespace eve::detail
{
  // Tuple free apply
  template<typename Func, std::size_t... I>
  EVE_FORCEINLINE decltype(auto) apply_impl(Func &&f, std::index_sequence<I...> const &)
  {
    return std::forward<Func>(f)(std::integral_constant<std::size_t, I>{}...);
  }

  template<std::size_t Count, typename Func>
  EVE_FORCEINLINE decltype(auto) apply(Func &&f)
  {
    return apply_impl(std::forward<Func>(f), std::make_index_sequence<Count>{});
  }
}

