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

#include <eve/concept/value.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/shr.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<real_value T, decorator D>
  EVE_FORCEINLINE T signnz_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( unsigned_value<T> )
      {
        return one(eve::as(a));
      }
      else if constexpr( floating_value<T> )
      {
        return bit_or(one(eve::as(a)), bitofsign(a));
      }
      else if constexpr( signed_value<T> )
      {
        using elt_t = element_type_t<T>;
        return (a >> (sizeof(elt_t) * 8 - 2)) | T(1);
      }
    }
    else
    {
      return apply_over(signnz, a);
    }
  }
}
