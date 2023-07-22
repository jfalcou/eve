//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>

#include <concepts>

namespace eve::detail
{

struct no_matching_shuffle_t
{};
constexpr no_matching_shuffle_t no_matching_shuffle;

template<typename T>
concept matched_shuffle = !std::same_as<no_matching_shuffle_t, std::remove_cvref_t<T>>;

EVE_FORCEINLINE auto
invoke_shuffle(auto sh, auto p, auto g, auto... xs)
{
  if constexpr( requires { sh(p, g, xs...); } ) { return sh(p, g, xs...); }
  else return no_matching_shuffle;
}

}
