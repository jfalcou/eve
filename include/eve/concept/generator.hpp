//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/as.hpp>
#include <eve/concept/invocable.hpp>
#include <eve/detail/kumi.hpp>

#include <type_traits>

namespace eve
{
namespace detail
{
  // Can I pass Type to a constant ?
  template<typename Constant, typename Type>
  struct is_generator : std::bool_constant<eve::invocable<Constant, as<Type>>>
  {};

  template<typename Constant, typename Type, typename Index> struct is_generator_impl;

  template<typename Constant, typename Type, std::size_t... I>
  struct is_generator_impl<Constant, Type, std::index_sequence<I...>>
      : std::bool_constant<(is_generator<Constant, std::tuple_element_t<I, Type>>::value && ...)>
  {};

  template<typename Constant, kumi::product_type Type>
  struct is_generator<Constant, Type>
      : is_generator_impl<Constant, Type, std::make_index_sequence<std::tuple_size<Type>::value>>
  {};
}

//==================================================================================================
//! @concept generator
//! The concept `generator<Constant,Type>` is satisfied if `Constant{}( eve::as<Type>() )` is
//! well formed.
//!
//! @groupheader{Examples}
//!   - `eve::callable_one_`
//==================================================================================================
template<typename Constant, typename Type>
concept generator = !kumi::product_type<Constant> && detail::is_generator<Constant, Type>::value;
}
