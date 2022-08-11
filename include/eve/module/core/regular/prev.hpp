//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/assert.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/decorator/pedantic.hpp>
#include <eve/module/core/decorator/saturated.hpp>
#include <eve/module/core/regular/all.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/is_gez.hpp>

#include <type_traits>

namespace eve
{
//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var prev
//!   @brief Computes the nth previous representable element
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::value T, eve::integral_value N >
//!      eve::common_compatible_t<T, U> prev(T x, N n = 1) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`:  [floating argument](@ref eve::floating_value).
//!
//!     * `n` :  [integral value argument](@ref eve::integral_value).
//!
//!    **Return value**
//!
//!    The value of the nth representable value less than `x` is returned.
//!    If `n` is zero returns `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/prev.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::prev[mask](x, ...)` provides a masked
//!     version of `prev` which is
//!     equivalent to `if_else(mask, prev(x, ...), x)`
//!
//!      **Example**
//!
//!        @godbolt{doc/core/masked/prev.cpp}
//!
//! @}
//================================================================================================
namespace tag
{
  struct prev_;
}

namespace detail
{
  template<conditional_expr C, value T, integral_value U>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(eve::tag::prev_), C const&, T const&, [[maybe_unused]] U const& n)
  {
    EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
  }
  template<value T, integral_value U>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::prev_), T const&, [[maybe_unused]] U const& n)
  {
    EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
  }

  template<conditional_expr C, value T, integral_value U>
  EVE_FORCEINLINE void check(EVE_MATCH_CALL(saturated_type, eve::tag::prev_),
                             C const&,
                             T const&,
                             [[maybe_unused]] U const& n)
  {
    EVE_ASSERT(eve::all(is_gez(n)), "[eve::prev] : second parameter must be positive");
  }
  template<value T, integral_value U>
  EVE_FORCEINLINE void
  check(EVE_MATCH_CALL(saturated_type, eve::tag::prev_), T const&, [[maybe_unused]] U const& n)
  {
    EVE_ASSERT(eve::all(is_gez(n)),
               "[[eve::saturated([eve::prev)] : second parameter must be positive");
  }
}

EVE_MAKE_CALLABLE(prev_, prev);
}

#include <eve/module/core/regular/impl/prev.hpp>
