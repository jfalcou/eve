//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

namespace eve::_
{
  // instance concept
  template <typename T, template <typename ...> class Templ>
  inline constexpr bool instance_of_impl = false;

  template <typename ...Args, template <typename ...> class Templ>
  inline constexpr bool instance_of_impl<Templ<Args...>, Templ> = true;

  template <typename T, template <typename ...> class Templ>
  concept instance_of = instance_of_impl<std::remove_cvref_t<T>, Templ>;

  // one_of concept
  template<typename T, typename... Ts>
  concept one_of = (std::same_as<T,Ts> || ... || false);

  template <bool>
  struct conditional_impl_ {
      template <typename T, typename U>
      using type = U;
  };

  template <>
  struct conditional_impl_<true> {
      template <typename T, typename U>
      using type = T;
  };

  template <bool test, typename T, typename U>
  using conditional_t = conditional_impl_<test>:: template type<T, U>;
}