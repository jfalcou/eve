//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/translation.hpp>
#include <eve/detail/wide_forward.hpp>
#include <eve/memory/pointer.hpp>
#include <eve/traits/value_type.hpp>

#include <bit>
#include <new>

namespace eve
{
  template <typename V>
  constexpr auto translate(V val)
  {
    if constexpr (has_plain_translation<element_type_t<V>>) return std::bit_cast<translate_t<V>>(val);
    else                                                    return val;
  }

  template <typename V>
  constexpr auto translate(as<V>)
  {
    return as<translate_t<V>>{};
  }

  template <detail::scalar_pointer Ptr>
  constexpr auto translate_ptr(Ptr ptr)
  {
    if constexpr (has_plain_translation<value_type_t<Ptr>>)
    {
      using trans_t = translate_t<value_type_t<Ptr>>;

      if constexpr (std::is_pointer_v<Ptr>)
      {
        return std::launder(reinterpret_cast<trans_t*>(ptr));
      }
      else
      {
        using r_t = typename Ptr::template rebind<trans_t>;
        return r_t { translate_ptr(ptr.get()) };
      }
    }
    else
    {
      return ptr;
    }
  }
}
