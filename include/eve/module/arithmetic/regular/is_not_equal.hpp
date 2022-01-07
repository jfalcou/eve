//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
//#include <eve/include/eve/detail/function/simd/common/friends.hpp>

// #include <eve/detail/implementation.hpp>
// #include <eve/traits/as_logical.hpp>
// #include <eve/concept/value.hpp>

// namespace eve
// {
//   EVE_MAKE_CALLABLE(is_not_equal_, is_not_equal);

//   namespace detail
//   {
//     template<value T, value U>
//     EVE_FORCEINLINE auto is_not_equal_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
//     {
//       if constexpr( scalar_value<T> && scalar_value<U> )  return as_logical_t<T>(a != b);
//       else                                                return a != b;
//     }
//   }
// }
