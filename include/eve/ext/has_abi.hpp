//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2018 Joel FALCOU

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_EXT_HAS_ABI_HPP_INCLUDED
#define EVE_EXT_HAS_ABI_HPP_INCLUDED

#include <type_traits>
#include <eve/forward.hpp>

namespace eve::ext
{
  template<typename Type, typename ABI>
  struct has_abi : std::false_type
  {
  };

  template<typename Type, typename ABI>
  struct has_abi<Type &, ABI> : has_abi<Type, ABI>
  {
  };

  template<typename Type, typename ABI>
  struct has_abi<Type const, ABI> : has_abi<Type, ABI>
  {
  };

  template<typename Type, typename ABI>
  struct has_abi<Type const &, ABI> : has_abi<Type, ABI>
  {
  };

  template<typename Type, typename ABI>
  struct has_abi<Type &&, ABI> : has_abi<Type, ABI>
  {
  };

  template<typename Type, typename Size, typename ABI>
  struct has_abi<wide<Type, Size, ABI>, ABI> : std::true_type
  {
  };

  template<typename Type, typename Size, typename ABI, typename ABI2>
  struct has_abi<wide<Type, Size, ABI>, ABI2> : std::false_type
  {
  };

  template<typename Type, typename ABI>
  using has_abi_t = typename has_abi<Type, ABI>::type;

  template<typename Type, typename ABI>
  inline constexpr bool has_abi_v = has_abi_t<Type, ABI>::value;
}

#endif
