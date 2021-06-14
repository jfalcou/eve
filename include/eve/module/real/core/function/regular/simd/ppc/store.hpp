//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  template< scalar_value T, typename N
          , simd_compatible_ptr<wide<T, N>> Ptr
          >
  EVE_FORCEINLINE void store_(EVE_SUPPORTS(vmx_), wide<T, N> const &value, Ptr ptr) noexcept
    requires ppc_abi<abi_t<T, N>>
  {
    if constexpr( !std::is_pointer_v<Ptr> )
    {
      if constexpr( current_api == eve::vmx ) vec_st(value.storage(), 0, ptr.get());
      else                                    store(value, ptr.get());
    }
    else if constexpr( N::value * sizeof(T) == ppc_::bytes )
    {
      if constexpr( current_api == eve::vmx )
      {
        *((typename wide<T, N>::storage_type *)(ptr)) = value;
      }
      else if constexpr( current_api == eve::vsx )
      {
        // 64bits integrals are not supported by vec_vsx_st on some compilers
        if constexpr( sizeof(T) == 8 && std::is_integral_v<T> )
        {
          vec_vsx_st((__vector double)(value.storage()), 0, (double *)(ptr));
        }
        else
        {
          vec_vsx_st(value.storage(), 0, ptr);
        }
      }
    }
    else
    {
      memcpy(ptr, (T const*)(&value), N::value * sizeof(T));
    }
  }
}
