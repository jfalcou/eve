//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/prev.hpp>

#
namespace eve
{
  template<typename Options>
  struct nextafter_t : elementwise_callable<nextafter_t, Options, pedantic_option>
  {
    template<eve::value T, eve::value U>
    constexpr EVE_FORCEINLINE T operator()(T t, U u) const noexcept
    { return EVE_DISPATCH_CALL(t, u); }

    EVE_CALLABLE_OBJECT(nextafter_t, nextafter_);
  };

//================================================================================================
//! @addtogroup core_internal
//! @{
//!   @var nextafter
//!   @brief Computes the nth next representable element
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
//!      template< eve::value T, eve::value U >
//!      eve::common_value_t<T, U> nextafter(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!      The value of the next representable value greater than `x` in the `y` direction
//!      is returned.
//!      If `y == x` returns `x`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/nextafter.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * pedantic Call
//!
//!     The call `eve::nextafter[pedantic](x, ...)` provides a
//!     version of `nextafter` for which floating plus zero and minus zero are distinct
//!     for x.
//!
//!   * Masked Call
//!
//!     The call `eve::nextafter[mask](x, ...)` provides a masked
//!     version of `nextafter` which is
//!     equivalent to `if_else(mask, nextafter(x, ...), x)`
//!
//! @}
//================================================================================================
  inline constexpr auto nextafter = functor<nextafter_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr common_value_t<T, U>
    nextafter_(EVE_REQUIRES(cpu_), O const& o, T const& xx, U const & yy) noexcept
    {
      using r_t =  common_value_t<T, U>;
      auto x = r_t(xx);
      auto y = r_t(yy);
      if constexpr( scalar_value<T> )
        return (a < b) ? next[o](a) : ((a > b) ? prev[o](a) : a);
      else if constexpr( simd_value<T> )
        return if_else(a < b, next[o](a), if_else(a > b, prev[o](a), a));
    }
  }
}
