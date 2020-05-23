//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_SIGNNZ_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_SIGNNZ_HPP_INCLUDED

#include <eve/concept/value.hpp>
#include <eve/constant/one.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/function/bit_or.hpp>
#include <eve/function/bitofsign.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_nan.hpp>
#include <eve/function/pedantic.hpp>
#include <eve/function/regular.hpp>
#include <eve/function/shr.hpp>
#include <eve/platform.hpp>

namespace eve::detail
{
  template<real_value T, decorator D>
  EVE_FORCEINLINE T signnz_(EVE_SUPPORTS(cpu_), D const &, T const &a) noexcept
  {
    if constexpr( has_native_abi_v<T> )
    {
      if constexpr( unsigned_value<T> )
      {
        return One(as(a));
      }
      else if constexpr( floating_value<T> )
      {
        auto r = bit_or(One(as(a)), bitofsign(a));
        if constexpr( eve::platform::supports_nans && std::is_same_v<D, pedantic_type> )
        {
          if constexpr( scalar_value<T> )
          {
            return is_nan(a) ? a : r;
          }
          else
          {
            return if_else(is_nan(a), eve::allbits_, r);
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

  template<real_value T> EVE_FORCEINLINE T signnz_(EVE_SUPPORTS(cpu_), T const &a) noexcept
  {
    return signnz(regular_type(), a);
  }

}

#endif
