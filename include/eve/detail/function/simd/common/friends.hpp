//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/module/core/constant/allbits.hpp>
#include <eve/module/core/constant/signmask.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/function/bit_cast.hpp>
#include <eve/detail/is_native.hpp>
#include <eve/traits/product_type.hpp>
#include <eve/as_element.hpp>
#include <eve/forward.hpp>

// Register tag here so we can use them in tagged_dispatch situation
namespace eve
{
  EVE_REGISTER_CALLABLE(is_equal_)
  EVE_REGISTER_CALLABLE(is_not_equal_)
}

namespace eve::detail
{
  //================================================================================================
  template<simd_value Wide>
  EVE_FORCEINLINE auto self_eq(Wide const& v,Wide const& w) noexcept
  requires( kumi::product_type<element_type_t<Wide>> )
  {
    if constexpr( detail::tag_dispatchable<tag::is_equal_,Wide,Wide> )
    {
      return tagged_dispatch(tag::is_equal_{}, v, w);
    }
    else
    {
      return v.storage() == w.storage();
    }
  }

  template<simd_value Wide>
  EVE_FORCEINLINE auto self_eq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto eq = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e == f); };

    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr(is_logical_v<Wide>)  return bit_cast(v.bits() == w.bits(), as(v));
      else                              return apply_over(eq, v, w);
    }
    else
    {
      return apply_over(eq, v, w);
    }
  }

  //================================================================================================
  template<simd_value Wide>
  EVE_FORCEINLINE auto self_neq(Wide const& v,Wide const& w) noexcept
  requires( kumi::product_type<element_type_t<Wide>> )
  {
    if constexpr( detail::tag_dispatchable<tag::is_not_equal_,Wide,Wide> )
    {
      static_assert ( detail::tag_dispatchable<tag::is_equal_,Wide,Wide>
                    , "[EVE] User defined type defines != but no == specialization."
                    );
      return tagged_dispatch(tag::is_not_equal_{}, v, w);
    }
    else if constexpr( detail::tag_dispatchable<tag::is_equal_,Wide,Wide> )
    {
      return !tagged_dispatch(tag::is_equal_{}, v, w);
    }
    else
    {
      return v.storage() != w.storage();
    }
  }

  template<simd_value Wide>
  EVE_FORCEINLINE auto self_neq(Wide const& v,Wide const& w) noexcept
  {
    constexpr auto eq = []<typename E>(E const& e, E const& f) { return as_logical_t<E>(e != f); };

    if constexpr(has_native_abi_v<Wide>)
    {
      if constexpr(is_logical_v<Wide>)  return bit_cast(v.bits() != w.bits(), as(v));
      else                              return apply_over(eq, v, w);
    }
    else
    {
      return apply_over(eq, v, w);
    }
  }
}
