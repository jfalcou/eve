//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_IS_PACK_HPP_INCLUDED
#define EVE_EXT_IS_PACK_HPP_INCLUDED

#include <type_traits>
#include <eve/forward.hpp>

namespace eve { namespace ext
{
  template<typename Type>
  struct is_pack : std::false_type
  {};

  template<typename Type>
  struct is_pack<Type&> : is_pack<Type>
  {};

  template<typename Type>
  struct is_pack<Type const> : is_pack<Type>
  {};

  template<typename Type>
  struct is_pack<Type const&> : is_pack<Type>
  {};

  template<typename Type>
  struct is_pack<Type &&> : is_pack<Type>
  {};

  template<typename Type, typename Size, typename ABI>
  struct is_pack<pack<Type,Size,ABI>> : std::true_type
  {};

  template<typename Type> using is_pack_t = typename is_pack<Type>::type;

  template<typename Type> inline constexpr bool is_pack_v = is_pack_t<Type>::value;
} }

#endif
