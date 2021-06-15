//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/memory/aligned_ptr.hpp>
#include <eve/detail/kumi.hpp>

#include <concepts>

namespace eve
{
  template<typename T, typename Enable=void> struct pointer_traits;

  template<typename T> struct pointer_traits<T*>        { using value_type = T;       };
  template<typename T> struct pointer_traits<T const*>  { using value_type = T const; };

  template<typename T>
  struct pointer_traits<T, std::void_t<typename T::value_type>>
  {
    using value_type = typename T::value_type;
  };
}

namespace eve::detail
{
  template <typename T>
  EVE_FORCEINLINE auto as_raw_pointer(T p)
  {
    if constexpr ( !std::is_pointer_v<T> ) return p.get();
    else                                   return p;
  }

  template <typename U, typename T, typename Lanes>
  EVE_FORCEINLINE auto ptr_cast(eve::aligned_ptr<T, Lanes> p)
  {
    return aligned_ptr<U, eve::fixed<Lanes() * sizeof(T) / sizeof(U)>>{(U*)(p.get())};
  }

  template <typename U, typename T>
  EVE_FORCEINLINE auto ptr_cast(T* p)
  {
    return (U*)p;
  }
}
