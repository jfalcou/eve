//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_CONCEPT_VECTORIZED_HPP_INCLUDED
#define EVE_CONCEPT_VECTORIZED_HPP_INCLUDED

#include <eve/forward.hpp>
#include <eve/cardinal.hpp>

namespace eve::detail
{
  template<typename Type>
  struct is_vectorized : std::false_type
  {
  };

  template<typename Type>
  struct is_vectorized<Type &> : is_vectorized<Type>
  {
  };

  template<typename Type>
  struct is_vectorized<Type const> : is_vectorized<Type>
  {
  };

  template<typename Type>
  struct is_vectorized<Type const &> : is_vectorized<Type>
  {
  };

  template<typename Type>
  struct is_vectorized<Type &&> : is_vectorized<Type>
  {
  };

  template<typename Type, typename Size, typename ABI>
  struct is_vectorized<wide<Type, Size, ABI>> : std::true_type
  {
  };

  template<typename Type>
  struct is_vectorized<logical<Type>> : is_vectorized<Type>
  {
  };
}

namespace eve
{
  template<typename Type>
  struct is_vectorized : detail::is_vectorized<Type>
  {
  };

  template<typename Type>
  using is_vectorized_t = typename is_vectorized<Type>::type;

  template<typename Type>
  inline constexpr bool is_vectorized_v = is_vectorized_t<Type>::value;

  template<typename Type>
  using vectorized = std::enable_if_t<is_vectorized_v<Type>>;

  template<typename T, typename U>
  using equal_cardinal = std::enable_if_t<cardinal_v<T> == cardinal_v<U>>;

  template<typename N, typename... Us>
  using has_compatible_cardinal =
      std::enable_if_t<(((cardinal_v<Us> == N::value) || (cardinal_v<Us> == 1)) && ...)>;
}

#endif
