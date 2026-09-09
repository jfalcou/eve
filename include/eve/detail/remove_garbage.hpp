//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/traits.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/module/core/regular/slide_right.hpp>
#include <utility>

namespace eve::_
{
  template<typename W> auto remove_garbage(W v) noexcept
  {
    using v_t   = element_type_t<W>;

    constexpr auto c  = cardinal_v<W>;
    constexpr auto ec = expected_cardinal_v<v_t, typename W::abi_type>;

    if constexpr(c < ec)
    {
      auto const exact_mask = keep_first(c).mask(as<as_wide_t<v_t, ec>>{});
      if constexpr(is_logical_v<W>)
      {
        v = bit_cast(bit_cast(v,as<as_wide_t<v_t, ec>>()) && exact_mask, as(v));
      }
      else
      {
        v = bit_cast(bit_cast(v,as<as_wide_t<v_t, ec>>()) & exact_mask.mask(), as(v));
      }
    }

    return v;
  }

 template<typename W> auto slide_garbage(W v) noexcept
  {
    using v_t   = element_type_t<W>;
    constexpr auto c  = cardinal_v<W>;
    constexpr auto ec = expected_cardinal_v<v_t, typename W::abi_type>;

    if constexpr(c < ec)
    {
      v = bit_cast( slide_right ( bit_cast(v,as<wide<v_t, ec>>())
                                , index<ec - c>
                                )
                  , as(v)
                  );
    }

    return v;
  }

  //================================================================================================
  // Turn a conditional into a mask, ensure that all inactive lanes are set to false
  //================================================================================================
  template<conditional_expr C, typename Target>
  EVE_FORCEINLINE auto expand_mask_no_garbage(C const& c, as<Target> const&)
  {
    auto msk = c.mask(as<Target>{});
    if constexpr (relative_conditional_expr<C>) return as_logical_t<Target>(msk);
    else                                        return remove_garbage(as_logical_t<Target>(msk));
  }
}
