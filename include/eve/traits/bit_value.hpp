//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>

namespace eve
{
  namespace detail
  {
    template<typename T0, typename T1>
    static constexpr inline bool bit_compatibility = false;

    template<simd_value T0, simd_value T1>
    static constexpr inline bool bit_compatibility<T0,T1> = sizeof(T0) == sizeof(T1);

    template<simd_value T0, scalar_value T1>
    static constexpr inline bool bit_compatibility<T0,T1> = sizeof(T1) == sizeof(element_type_t<T0>);
  }

  template<typename... Ts>
  struct bit_value;

  template<scalar_value T0, scalar_value... Ts>
  requires( (sizeof(T0) == sizeof(Ts)) && ... )
  struct bit_value<T0,Ts...>
  {
    // First type is OK if all types are scalar and have same sizeof
    using type = T0;
  };

  template<simd_value T0, value... Ts>
  requires( (detail::bit_compatibility<T0,Ts>) && ... )
  struct bit_value<T0,Ts...>
  {
    using type = T0;
  };

  template<typename... Ts>
  using bit_value_t = typename bit_value<Ts...>::type;
}
