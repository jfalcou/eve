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
#include <eve/arch/limits.hpp>
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

  template<typename Type, typename API = EVE_CURRENT_API>
  struct expected_cardinal
      : fixed<limits<API>::template expected_cardinal<Type>>
  {
    using type = fixed<limits<API>::template expected_cardinal<Type>>;
  };

  namespace detail
  {
    template<typename API, typename T>
    constexpr std::ptrdiff_t scard(always<T>) noexcept
    {
      auto cardinals = []<std::size_t... X>(std::index_sequence<X...> const&)
      {
        return  std::array<std::ptrdiff_t,sizeof...(X)>
                {
                  expected_cardinal< std::tuple_element_t<X,T>,API>::value...
                };
      }( std::make_index_sequence<std::tuple_size<T>::value>{} );

      std::ptrdiff_t r = cardinals[0];

      for(auto c : cardinals)
        r = std::min(r,c);

      return r;
    }

    template<typename API, typename T>
    using scard_t = fixed<scard<API>(always<T>{})>;
  }

  template<typename Type, typename API>
  requires( rebindable<Type> )
  struct expected_cardinal<Type,API> : detail::scard_t<API,Type>
  {
    using type = detail::scard_t<API,Type>;
  };

  template<typename Type, typename API = EVE_CURRENT_API>
  using expected_cardinal_t = typename expected_cardinal<Type, API>::type;

  template<typename Type, typename API = EVE_CURRENT_API>
  constexpr inline auto expected_cardinal_v = expected_cardinal<Type, API>::value;
}

