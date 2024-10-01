//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_less_equal_t : strict_elementwise_callable<is_less_equal_t, Options, almost_option>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const
      requires(eve::same_lanes_or_scalar<T, U>)
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_less_equal] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL_PT((as<common_logical_t<T, U>>{}), a, b);
    }

    EVE_CALLABLE_OBJECT(is_less_equal_t, is_less_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_less_equal
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          less or equal to the second one.
//!
//!   @groupheader{Header file}
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
//!      // Regular overload
//!      constexpr auto is_less_equal(value auto x, value auto y) noexcept;                          // 1
//!
//!      // Lanes masking
//!      constexpr auto is_less_equal[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
//!      constexpr auto is_less_equal[logical_value auto m](value auto x, value auto y) noexcept;    // 2
//!
//!      // Semantic option
//!      constexpr auto is_less_equal[almost](/*any of the above overloads*/)              noexcept; // 3
//!      constexpr auto is_less_equal[almost = tol](/*any of the above overloads*/)        noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`:  [arguments](@ref eve::value).
//!     * `c`: [Conditional expression](@ref conditional_expr) masking the operation.
//!     * `m`: [Logical value](@ref logical) masking the operation.
//!     * `tol`: [scalar value](@ref value) tolerance.
//!
//!   **Return value**
//!
//!     1. The call `eve::is_less_equal(x,y)`  is semantically  equivalent to `x <= y`:
//!     2. [The operation is performed conditionnaly](@ref conditional).
//!     3. The expression `is_less_equal[almost = tol](x, y)` where `x` and `y` must be
//!         floating point values, evaluates to true if and only if `x` is almost less than `y`.
//!         This means that:
//!            - if `tol` is a floating value then  \f$x \le y + \mbox{tol}\cdot \max(|x|, |y|)\f$
//!            - if `tol` is a positive integral value then \f$x \le \mbox{next}(y, \mbox{tol})\f$;
//!            - if `tol` is omitted then the tolerance `tol` default to `3*eps(as(x))`.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/is_less_equal.cpp}
//================================================================================================
  inline constexpr auto is_less_equal = functor<is_less_equal_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_less_equal_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<U> b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a <= b);
      else                                              return a <= b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_less_equal_(EVE_REQUIRES(cpu_), O const & o, T const& aa, U const& bb) noexcept
    {
      if constexpr(O::contains(almost))
      {
        using w_t = common_value_t<T, U>;
        auto a = w_t(aa);
        auto b = w_t(bb);

        auto tol = o[almost].value(w_t{});
        if constexpr(integral_value<decltype(tol)>) return a <=  eve::next(b, tol);
        else                                        return a <= fam(b, tol, eve::max(eve::abs(a), eve::abs(b)));
      }
      else
      {
        if constexpr(scalar_value<U> && scalar_value<T>)  return common_logical_t<T,U>(aa <= bb);
        else                                              return aa <= bb;
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_less_equal.hpp>
#endif
