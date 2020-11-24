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

#include <eve/forward.hpp>
#include <eve/concept/rebindable.hpp>
#include <utility>

namespace eve::detail
{
  template<typename Type>
  struct is_wide : std::false_type
  {};

  template<typename Type, typename N>
  struct is_wide<eve::wide<Type,N>> : std::true_type
  {};

  template<typename Type>
  requires( rebindable<Type> )
  struct is_wide<Type>
  {
    template<typename Idx>      struct eval_n;
    template<std::size_t... N>  struct eval_n<std::index_sequence<N...>>
    {
      static constexpr bool value = (is_wide<std::tuple_element_t<N,Type>>::value && ...);
    };

    using size = std::tuple_size<Type>;
    static constexpr bool value = eval_n<std::make_index_sequence<size::value>>::value;
  };
}

