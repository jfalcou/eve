//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/wide_forward.hpp>
#include <cstddef>

namespace eve
{
  template<typename Type> struct pointer_alignment : std::integral_constant<std::size_t,0ULL>
  {};

  template<typename Type>
  struct  pointer_alignment<Type*>
        : std::integral_constant<std::size_t,alignof(Type)>
  {};

  template<typename Type>
  struct  pointer_alignment<Type const*>
        : std::integral_constant<std::size_t,alignof(Type)>
  {};

  template<typename Type>
  using pointer_alignment_t = typename pointer_alignment<Type>::type;

  template<typename Type>
  inline constexpr auto pointer_alignment_v = pointer_alignment<Type>::value;

  template<typename Type>
  struct alignment : std::integral_constant<std::size_t,alignof(Type)>
  {};

  template<typename Type, typename Size>
  struct  alignment<wide<Type, Size>>
        : std::integral_constant<std::size_t,wide<Type, Size>::alignment()>
  {};

  template<typename Type>
  struct alignment<logical<Type>> : alignment<Type>
  {
  };

  template<typename Type, typename Size>
  struct  alignment<logical<wide<Type, Size>>>
        : std::integral_constant<std::size_t,logical<wide<Type, Size>>::alignment()>
  {};

  template<typename Type>
  using alignment_t = typename alignment<Type>::type;

  template<typename Type>
  inline constexpr auto alignment_v = alignment<Type>::value;
}
