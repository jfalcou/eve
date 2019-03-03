//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2019 Joel FALCOU
  Copyright 2019 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#ifndef EVE_MODULE_CORE_FUNCTION_GENERIC_IF_ELSE_HPP_INCLUDED
#define EVE_MODULE_CORE_FUNCTION_GENERIC_IF_ELSE_HPP_INCLUDED

#include <eve/detail/abi.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/detail/overload.hpp>
#include <eve/detail/skeleton.hpp>
#include <eve/function/bitwise_mask.hpp>
#include <eve/function/bitwise_select.hpp>
#include <eve/is_logical.hpp>
#include <eve/is_wide.hpp>
#include <eve/logical.hpp>
#include <type_traits>

namespace eve::detail
{
  template<typename T, typename U, typename V>
  EVE_FORCEINLINE constexpr auto
  if_else_(EVE_SUPPORTS(cpu_), T const &cond, U const &t, V const &f) noexcept
  {
    // SIMD case
    if constexpr( is_wide_v<T> )
    {
      // Expels non-fully SIMD cases by recalling self with type-casted value
      if constexpr(is_wide_v<U> && !is_wide_v<V>)
      {
        return eve::if_else(cond, t, U(f));
      }
      else if constexpr(!is_wide_v<U> && is_wide_v<V>)
      {
        return eve::if_else(cond, V(t), f);
      }
      else if constexpr(!is_wide_v<U> && !is_wide_v<V>)
      {
        // Non-SIMD alternative must be of same type
        if constexpr( !std::is_same_v<U,V> )
        {
          static_assert( std::is_same_v<U,V>, "[eve::if_else] - Incompatible types.");
          return T{};
        }
        else
        {
          using t_t = as_wide_t<U,typename T::cardinal_type>;
          return eve::if_else(cond, t_t(t), t_t(f));
        }
      }
      else
      {
        // Native use bitwise_select on data
        if constexpr( is_native_v<typename T::abi_type> )
        {
          // Turn logical into bitmask before selection
          if constexpr( is_logical_v<U> )
          {
            return bitwise_cast<U>( bitwise_select( bitwise_mask(cond),
                                                    bitwise_mask(t),
                                                    bitwise_mask(f)
                                                  )
                                  );
          }
          else
          {
            // Regular case
            return bitwise_select( bitwise_mask(cond), t, f);
          }
        }
        else if constexpr( is_aggregated_v<typename T::abi_type> )
        {
          return aggregate( eve::if_else, cond, t, f);
        }
        else if constexpr( is_emulated_v<typename T::abi_type> )
        {
          return map( eve::if_else, cond, t, f);
        }
      }
    }
    else
    {
      if constexpr( is_logical_v<T> )
      {
        return cond.value() ? t : f;
      }
      else
      {
        return cond ? t : f;
      }
    }
  }
}

#endif
