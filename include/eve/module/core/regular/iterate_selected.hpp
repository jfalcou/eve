//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/detail/overload.hpp>
#include <eve/forward.hpp>

namespace eve
{

template<typename Options>
struct iterate_selected_t
    : callable<iterate_selected_t, Options, relative_conditional_no_alternative_option>
{
  template<eve::logical_simd_value L, irregular_predicate<std::ptrdiff_t> F>
  EVE_FORCEINLINE bool operator()(L l, F&& f) const noexcept
  {
    return EVE_DISPATCH_CALL_PT(as<bool>{}, l, f);
  }

  template<eve::logical_simd_value L, irregular_predicate<std::ptrdiff_t> F>
  EVE_FORCEINLINE bool operator()(top_bits<L> l, F&& f) const noexcept
  {
    return EVE_DISPATCH_CALL_PT(as<bool>{}, l, f);
  }

  template<irregular_predicate<std::ptrdiff_t> F>
  EVE_FORCEINLINE bool operator()(bool l, F&& f) const noexcept
  {
    return EVE_DISPATCH_CALL_PT(as<bool>{}, l, f);
  }

  EVE_CALLABLE_OBJECT(iterate_selected_t, iterate_selected_);
};

//================================================================================================
//! @addtogroup core_simd
//! @{
//!    @var iterate_selected
//!    @brief a utility to do scalar iteration over all true elements in a `logical`.
//!
//!    @see eve::algo::for_each_selected
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   Sometimes (for example in parsing) you need to perform scalar operations for each
//!   element that matches a predicate. This is a low level utility to help you do that.
//!   The predicate for iteration should return `true` if you want to break, `false` otherwise.
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!     auto iterate_selected
//!                       [relative_conditional_expr auto ignore]
//!       <logical_simd_value L>(L l, irregular_predicate<std::ptrdiff_t> auto&& f) -> bool;              // (1)
//!       <logical_simd_value L>(top_bits<L> l, irregular_predicate<std::ptrdiff_t> auto&& f) -> bool;    // (2)
//!                             (bool l, irregular_predicate<std::ptrdiff_t> auto&& f) -> bool;           // (3)
//!   }
//!   @endcode
//!
//!  **Parameters**
//!
//!    * ignore - ignored elements are considered false
//!    * l - logical value (either logical_simd_value, top_bits or just 1 bool).
//!    * f - callback, that's invoked for every true index. Return false to break.
//!
//!  **Return value**
//!    * true iff the user broke the exuction (f returned true).
//!
//!  @groupheader {Example}
//!
//!  @godbolt{doc/core/iterate_selected.cpp}
//================================================================================================
  inline constexpr auto iterate_selected = functor<iterate_selected_t>;
//================================================================================================
//! @}
//================================================================================================

}

#include <eve/module/core/regular/impl/iterate_selected.hpp>

#if defined(EVE_INCLUDE_ARM_SVE_HEADER)
#  include <eve/module/core/regular/impl/simd/arm/sve/iterate_selected.hpp>
#endif
