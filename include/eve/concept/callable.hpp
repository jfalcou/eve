//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <type_traits>
#include <concepts>

template<typename Func, auto Callable>
concept same_callable = std::same_as<std::remove_cvref_t<Func>, std::remove_cvref_t<decltype(Callable)>>;
