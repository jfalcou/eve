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
#include <eve/concept/stdconcepts.hpp>
#include <eve/element_type.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename Type>
  struct is_Vectorizable : std::is_arithmetic<Type>
  {
  };

  template<typename Type>
  struct is_Vectorizable<Type &> : is_Vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_Vectorizable<Type const> : is_Vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_Vectorizable<Type const &> : is_Vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_Vectorizable<Type &&> : is_Vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_Vectorizable<logical<Type>> : is_Vectorizable<Type>
  {
  };
}

namespace eve
{
  template<typename Type>
  struct is_Vectorizable : detail::is_Vectorizable<Type>
  {
  };

  template<typename Type>
  using is_Vectorizable_t = typename is_Vectorizable<Type>::type;

  template<typename Type>
  inline constexpr bool is_Vectorizable_v = is_Vectorizable_t<Type>::value;

  template<typename Type>
  using Vectorizable = std::enable_if_t<is_Vectorizable_v<Type>>;

  template<typename Type> concept vectorizable = is_Vectorizable_v<Type>;

  template<typename T> concept scalar_value                   = is_Vectorizable_v<T>;
  template<typename T> concept integral_scalar_value          = scalar_value<T> && std::integral<T>;
  template<typename T> concept signed_scalar_value            = scalar_value<T> && std::signed_type<T>;
  template<typename T> concept unsigned_scalar_value          = scalar_value<T> && std::unsigned_integral<T>;
  template<typename T> concept signed_integral_scalar_value   = scalar_value<T> && std::signed_integral<T>;
  template<typename T> concept floating_scalar_value          = scalar_value<T> && std::floating_point<T>;
  template<typename T> concept scalar_real_value              = scalar_value<T> && std::same_as< detail::value_type_t<T>, element_type_t<T>>;


}

#endif
