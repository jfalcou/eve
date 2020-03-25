//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

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
  struct is_Vectorized : std::false_type
  {
  };

  template<typename Type>
  struct is_Vectorized<Type &> : is_Vectorized<Type>
  {
  };

  template<typename Type>
  struct is_Vectorized<Type const> : is_Vectorized<Type>
  {
  };

  template<typename Type>
  struct is_Vectorized<Type const &> : is_Vectorized<Type>
  {
  };

  template<typename Type>
  struct is_Vectorized<Type &&> : is_Vectorized<Type>
  {
  };

  template<typename Type, typename Size, typename ABI>
  struct is_Vectorized<wide<Type, Size, ABI>> : std::true_type
  {
  };

  template<typename Type>
  struct is_Vectorized<logical<Type>> : is_Vectorized<Type>
  {
  };
}

namespace eve
{
  template<typename Type>
  struct is_Vectorized : detail::is_Vectorized<Type>
  {
  };

  template<typename Type>
  using is_Vectorized_t = typename is_Vectorized<Type>::type;

  template<typename Type>
  inline constexpr bool is_Vectorized_v = is_Vectorized_t<Type>::value;

  template<typename Type>
  using Vectorized = std::enable_if_t<is_Vectorized_v<Type>>;

  template<typename T, typename U>
  using equal_cardinal = std::enable_if_t<cardinal_v<T> == cardinal_v<U>>;

  template<typename N, typename... Us>
  using has_compatible_cardinal =
      std::enable_if_t<(((cardinal_v<Us> == N::value) || (cardinal_v<Us> == 1)) && ...)>;

  template<typename Type> concept vectorized = is_Vectorized_v<Type>;

}

#endif
