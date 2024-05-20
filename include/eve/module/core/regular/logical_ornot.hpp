//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct logical_ornot_t : elementwise_callable<logical_ornot_t, Options>
  {
    template<logical_value T, logical_value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE  auto operator()(T a, U b) const noexcept -> decltype(a && b)
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE auto operator()(T a, bool b) const noexcept -> decltype(a && b)
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE auto operator()(bool a, T b) const noexcept -> decltype(a && b)
    { return EVE_DISPATCH_CALL(a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(logical_ornot_t, logical_ornot_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_ornot
//!   @brief Computes the logical ORNOT of its arguments.
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
//!      auto logical_ornot(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical ORNOT of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!
//!     The call `logical_ornot(x, y)` is semantically equivalent to `x || !y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_ornot.cpp}
//! @}
//================================================================================================
  inline constexpr auto logical_ornot = functor<logical_ornot_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto logical_ornot_(EVE_REQUIRES(cpu_),
                                                O const & ,
                                                T a, U b) noexcept
    {
      using r_t = as_logical_t<decltype(a && b)>;
      if constexpr( scalar_value<T> && scalar_value<U> )
        return r_t(a || !b);
      else
        return a || !b;
    }
  }
}
