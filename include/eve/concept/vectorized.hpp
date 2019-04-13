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
  using Vectorized = std::enable_if_t<is_vectorized_v<Type>>;

  template<typename T, typename U>
  using EqualCardinal = std::enable_if_t<T::static_size == U::static_size>;
}

#endif
