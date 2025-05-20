//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch/as_register.hpp>
#include <eve/detail/abi.hpp>
#include <eve/detail/category.hpp>
#include <eve/forward.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve::detail
{
  template<typename T, typename N>
  EVE_FORCEINLINE auto to_logical(wide<T, N> const& v) noexcept
    requires sve_abi<abi_t<T, N>>
  {
    return v != 0;
  }

  template<relative_conditional_expr C, simd_value S>
  EVE_FORCEINLINE as_logical_t<S> to_logical_incomplete([[maybe_unused]] sve_ tag, C c, eve::as<S> tgt) noexcept
    requires sve_abi<typename S::abi_type>
  {
    using T = element_type_t<as_arithmetic_t<S>>;

    if constexpr (std::same_as<C, keep_first> || std::same_as<C, ignore_last>)
    {
      int count = c.count(tgt);

      if      constexpr (sizeof(T) == 1) return svwhilelt_b8(0, count);
      else if constexpr (sizeof(T) == 2) return svwhilelt_b16(0, count);
      else if constexpr (sizeof(T) == 4) return svwhilelt_b32(0, count);
      else if constexpr (sizeof(T) == 8) return svwhilelt_b64(0, count);
    }
    else if constexpr (std::same_as<C, ignore_first> || std::same_as<C, keep_last>)
    {
      int count = c.count(tgt);

      if constexpr (current_api >= sve2)
      {
        if      constexpr (sizeof(T) == 1) return svwhilegt_b8(count, 0);
        else if constexpr (sizeof(T) == 2) return svwhilegt_b16(count, 0);
        else if constexpr (sizeof(T) == 4) return svwhilegt_b32(count, 0);
        else if constexpr (sizeof(T) == 8) return svwhilegt_b64(count, 0);
      }
      else
      {
        return svnot_z(sve_true<T>(), to_logical_incomplete(tag, keep_first(c.offset(tgt)), tgt));
      }
    }
    else if constexpr (std::same_as<C, keep_between> || std::same_as<C, ignore_extrema>)
    {
      int first_count = c.offset(tgt);
      int last_count = c.roffset(tgt);

      return to_logical_incomplete(tag, ignore_first(first_count), tgt) && to_logical_incomplete(tag, ignore_last(last_count), tgt);
    }
    else
    {
      return to_logical_incomplete(cpu_{}, c, tgt);
    }
  }
}
