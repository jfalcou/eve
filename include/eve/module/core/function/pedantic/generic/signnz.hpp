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
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/shr.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<real_value T, decorator D>
  EVE_FORCEINLINE T signnz_(EVE_SUPPORTS(cpu_), pedantic_type const &, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( unsigned_value<T> )
      {
        return one(eve::as(a));
      }
      else if constexpr( floating_value<T> )
      {
        auto r = bit_or(one(eve::as(a)), bitofsign(a));
        if constexpr( eve::platform::supports_nans)
        {
          if constexpr( scalar_value<T> )
          {
            return is_nan(a) ? a : r;
          }
          else
          {
            return if_else(is_nan(a), eve::allbits, r);
          }
        }
        else
        {
          return r;
        }
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

