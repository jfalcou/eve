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

#include <eve/as.hpp>
#include <eve/concept/memory.hpp>
#include <eve/detail/implementation.hpp>

namespace eve::detail
{
  //================================================================================================
  // Logical
  //================================================================================================
  template<value T, native ABI, simd_compatible_ptr<logical<T>> Ptr>
  EVE_FORCEINLINE auto load(eve::as_<logical<T>> const &,
                            ABI const & mode,
                            Ptr ptr) noexcept
  {
    using type = typename logical<T>::storage_type;

    if constexpr( !std::is_pointer_v<Ptr> )
    {
      using a_ptr_t = typename Ptr::template rebind<element_type_t<T>>;
      auto rawdata = load(eve::as_<T> {}, mode, a_ptr_t( (typename a_ptr_t::pointer)ptr.get() ));

      return type(rawdata);
    }
    else
    {
      auto raw_ptr = (element_type_t<T> const*)(ptr);
      auto rawdata = load(eve::as_<T> {}, mode, raw_ptr);

      return type(rawdata);
    }
  }
}

