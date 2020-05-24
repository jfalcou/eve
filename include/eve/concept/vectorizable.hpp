//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_VECTORIZABLE_HPP_INCLUDED
#define EVE_CONCEPT_VECTORIZABLE_HPP_INCLUDED

#include <eve/forward.hpp>
#include <eve/concept/rebindable.hpp>
#include <eve/concept/std_replacements.hpp>
#include <eve/detail/is_wide.hpp>
#include <eve/traits/element_type.hpp>
#include <eve/traits/is_logical.hpp>

#include <concepts>
#include <type_traits>

namespace eve::detail
{
  //==============================================================================================
  // Check if something is a scalar_value
  //==============================================================================================
  template<typename T> struct is_scalar_value : std::is_arithmetic<T>
  {};

  template<typename T>
  struct is_scalar_value<eve::logical<T>> : std::is_arithmetic<T>
  {};

  template<typename Type>
  requires( rebindable<Type> && !detail::is_wide<Type>::value )
  struct is_scalar_value<Type>
  {
    template<typename Idx>      struct eval_n;
    template<std::size_t... N>  struct eval_n<std::index_sequence<N...>>
    {
      static constexpr bool value = (is_scalar_value<std::tuple_element_t<N,Type>>::value && ...);
    };

    using size = std::tuple_size<Type>;
    static constexpr bool value = eval_n<std::make_index_sequence<size::value>>::value;
  };
}

namespace eve
{
  template<typename T> concept scalar_value                   = detail::is_scalar_value<T>::value;

  template<typename T> concept integral_scalar_value          = scalar_value<T> && integral<T>;
  template<typename T> concept signed_scalar_value            = scalar_value<T> && std::is_signed_v<T>;
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && unsigned_integral<T>;
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && signed_integral<T>;
  template<typename T> concept floating_scalar_value          = scalar_value<T> && floating_point<T>;
  template<typename T> concept logical_scalar_value           = scalar_value<T> && is_logical_v<T>;
  template<typename T> concept real_scalar_value              = scalar_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;
  template<typename T> concept floating_real_scalar_value     = real_scalar_value<T> && floating_point<detail::value_type_t<T>>;
  template<typename T> concept integral_real_scalar_value     = real_scalar_value<T> && integral<detail::value_type_t<T>>;
}

#endif
