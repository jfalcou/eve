//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/arch/spec.hpp>
#include <eve/detail/meta.hpp>
#include <eve/arch/cardinals.hpp>
#include <eve/concept/rebindable.hpp>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <array>

namespace eve
{
  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  struct expected_cardinal
      : fixed<ABI::template expected_cardinal<Type>>
  {
    using type = fixed<ABI::template expected_cardinal<Type>>;
  };

  namespace detail
  {
    template<typename ABI, typename T>
    constexpr std::ptrdiff_t scard(always<T>) noexcept
    {
      auto cardinals = []<std::size_t... X>(std::index_sequence<X...> const&)
      {
        return  std::array<std::ptrdiff_t,sizeof...(X)>
                {
                  expected_cardinal< std::tuple_element_t<X,T>,ABI>::value...
                };
      }( std::make_index_sequence<std::tuple_size<T>::value>{} );

      std::ptrdiff_t r = cardinals[0];

      for(auto c : cardinals)
        r = std::min(r,c);

      return r;
    }

    template<typename ABI, typename T>
    using scard_t = fixed<scard<ABI>(always<T>{})>;
  }

  template<typename Type, regular_abi ABI>
  requires( rebindable<Type> )
  struct expected_cardinal<Type,ABI> : detail::scard_t<ABI,Type>
  {
    using type = detail::scard_t<ABI,Type>;
  };

  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  using expected_cardinal_t = typename expected_cardinal<Type, ABI>::type;

  template<typename Type, regular_abi ABI = EVE_CURRENT_ABI>
  constexpr inline auto expected_cardinal_v = expected_cardinal<Type, ABI>::value;

  //================================================================================================
  // Cardinal template inline object for passing cardinal values to functions like load/store
  //================================================================================================
  template<typename Type, typename API = EVE_CURRENT_API>
  inline constexpr expected_cardinal<Type,API> const expected = {};
}

