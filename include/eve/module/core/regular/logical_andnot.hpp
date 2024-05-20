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
#include <eve/module/core/constant/false.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/bit_cast.hpp>

namespace eve
{
  template<typename Options>
  struct logical_andnot_t : strict_elementwise_callable<logical_andnot_t, Options>
  {
    template<logical_value T, logical_value U>
    constexpr EVE_FORCEINLINE auto operator()(T a, U b) const -> as_logical_t<decltype(a && !b)>
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value U>
    constexpr EVE_FORCEINLINE auto  operator()(bool a, U b) const -> as_logical_t<decltype(U(a) && b)>
    { return EVE_DISPATCH_CALL(a, b); }

    template<logical_value T>
    constexpr EVE_FORCEINLINE auto  operator()(T a, bool b) const -> as_logical_t<decltype(a && T(b))>
    { return EVE_DISPATCH_CALL(a, b); }

    constexpr EVE_FORCEINLINE bool operator()(bool a, bool b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(logical_andnot_t, logical_andnot_);
  };

//================================================================================================
//! @addtogroup core_logical
//! @{
//!   @var logical_andnot
//!   @brief Computes the logical ANDNOT of its arguments.
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
//!      auto logical_andnot(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!
//!    **Return value**
//!
//!     Returns the logical ANDNOT of the two parameters following the
//!     [logical operations semantic](@ref glossary_logical).
//!
//!     The call `logical_andnot(x, y)` is semantically equivalent to `x && !y`
//!     if `x` or  `y` is an  [simd value](@ref eve::simd_value) and  does not shortcut.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/logical_andnot.cpp}
//! @}
//================================================================================================
  inline constexpr auto logical_andnot = functor<logical_andnot_t>;

  namespace detail
  {
    template<typename T, typename U, callable_options O>
    EVE_FORCEINLINE constexpr auto logical_andnot_(EVE_REQUIRES(cpu_),
                                                O const & ,
                                                T a, U b) noexcept
    {
      using r_t = as_logical_t<decltype(a && b)>;
      if constexpr( scalar_value<T> && scalar_value<U> )
        return r_t(a && !b);
      else
        return a && !b;
    }
  }
}
