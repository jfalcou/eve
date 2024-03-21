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

  /// Checks if the type associated to a given Keyword in a Option pack is equal to Type
  template<auto Keyword, typename Opts,typename Type>
  concept match_option =  std::same_as<Type, rbr::result::fetch_t<Keyword,Opts>>;

  /// Checks if the type is one of the Choices
  template<typename T, typename... Choices>
  concept only_if = detail::is_one_of<T>(detail::types<Choices...> {});

}
