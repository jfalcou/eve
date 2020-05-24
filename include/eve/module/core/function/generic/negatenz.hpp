//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_NEGATENZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_NEGATENZ_HPP_INCLUDED

#include <eve/concept/compatible.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/is_nez.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/signnz.hpp>

namespace eve::detail
{
  template<real_value T, real_value U, decorator D>
  EVE_FORCEINLINE auto negatenz_(EVE_SUPPORTS(cpu_), D const &, T const &a, U const &b) noexcept
      requires std::same_as<element_type_t<T>, element_type_t<U>>
  {
    return arithmetic_call(D()(negatenz), a, b);
  }

  template<real_value T, decorator D>
  EVE_FORCEINLINE T negatenz_(EVE_SUPPORTS(cpu_), D const &, T const &a, T const &b) noexcept
      requires has_native_abi_v<T>
  {
    if constexpr( signed_value<T> )
    {
      return a * D()(signnz)(b);
    }
    else
    {
      return a;
    }
  }

  template<real_value T, real_value U>
  EVE_FORCEINLINE auto negatenz_(EVE_SUPPORTS(cpu_), T const &a, U const &b) noexcept
      requires std::same_as<element_type_t<T>, element_type_t<U>>
  {
    return negatenz(regular_type(), a, b);
  }

}

#endif
