//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/raberu.hpp>

namespace eve
{
  template<typename T>
  concept callable_options = rbr::concepts::settings<T>;

  template<typename T>
  concept callable_option = rbr::concepts::option<T>;

  template<typename Option, auto Keyword>
  concept exactly = rbr::concepts::exactly<Option,Keyword>;

  template<typename Option, auto... Keyword>
  concept any_options_from = callable_option<Option> && (exactly<Option,Keyword> || ...);
}
