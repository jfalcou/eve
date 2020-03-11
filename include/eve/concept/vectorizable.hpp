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
#include <type_traits>

namespace eve::detail
{
  template<typename Type>
  struct is_vectorizable : std::is_arithmetic<Type>
  {
  };

  template<typename Type>
  struct is_vectorizable<Type &> : is_vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_vectorizable<Type const> : is_vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_vectorizable<Type const &> : is_vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_vectorizable<Type &&> : is_vectorizable<Type>
  {
  };

  template<typename Type>
  struct is_vectorizable<logical<Type>> : is_vectorizable<Type>
  {
  };
}

namespace eve
{
  template<typename Type>
  struct is_vectorizable : detail::is_vectorizable<Type>
  {
  };

  template<typename Type>
  using is_vectorizable_t = typename is_vectorizable<Type>::type;

  template<typename Type>
  inline constexpr bool is_vectorizable_v = is_vectorizable_t<Type>::value;

  template<typename Type>
  using vectorizable = std::enable_if_t<is_vectorizable_v<Type>>;
}

#endif
