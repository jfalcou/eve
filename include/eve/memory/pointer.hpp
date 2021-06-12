//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>

#include <concepts>

namespace eve::detail
{
  template <typename T>
  EVE_FORCEINLINE auto as_raw_pointer(T p)
  {
    if constexpr ( !std::is_pointer_v<T> ) return p.get();
    else                                   return p;
  }

  template <typename U, typename T, std::size_t size>
  EVE_FORCEINLINE auto ptr_cast(eve::aligned_ptr<T, size> p)
    requires (sizeof(U) == sizeof(T))
  {
    return aligned_ptr<U, size>{(U*)(p.get())};
  }

  template <typename U, typename T>
  EVE_FORCEINLINE auto ptr_cast(T* p)
    requires (sizeof(U) == sizeof(T))
  {
    return (U*)p;
  }
}
