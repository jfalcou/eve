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
#include <eve/concept/rebindable.hpp>
#include <type_traits>
#include <cstddef>
#include <utility>
#include <array>

namespace eve
{
  template<std::ptrdiff_t Cardinal>
  struct fixed : std::integral_constant<std::ptrdiff_t, Cardinal>
  {
    static_assert(Cardinal % 2 == 0, "Cardinal must be a power of 2");
    static constexpr bool is_default = false;
    using split_type                 = fixed<Cardinal / 2>;
    using combined_type              = fixed<Cardinal * 2>;
  };

  template<>
  struct fixed<1ULL> : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    static constexpr bool is_default = false;
    using combined_type              = fixed<2>;
  };

  struct scalar_cardinal : std::integral_constant<std::ptrdiff_t, 1ULL>
  {
    static constexpr bool is_default = false;
    using combined_type              = fixed<2>;
  };

  template<typename Type, typename ABI = EVE_CURRENT_ABI>
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

  template<typename Type, typename ABI>
  requires( rebindable<Type> )
  struct expected_cardinal<Type,ABI> : detail::scard_t<ABI,Type>
  {
    using type = detail::scard_t<ABI,Type>;
  };

  template<typename Type, typename ABI = EVE_CURRENT_ABI>
  using expected_cardinal_t = typename expected_cardinal<Type, ABI>::type;

  template<typename Type, typename ABI = EVE_CURRENT_ABI>
  constexpr inline auto expected_cardinal_v = expected_cardinal<Type, ABI>::value;
}

