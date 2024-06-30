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
#include <eve/traits/as_logical.hpp>

namespace eve
{
  template<typename Options>
  struct is_greater_equal_t : strict_elementwise_callable<is_greater_equal_t, Options, almost_option>
  {
  template<value T,  value U>
  requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_greater_equal] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_greater_equal_t, is_greater_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_greater_equal
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          greater or equal to the second one.
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
//!      template< eve::value T, eve::value U >
//!      eve::as_logical<T> is_greater_equal(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_greater_equal(x,y)`  is semantically  equivalent to `x >= y`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_greater_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_greater_equal[mask](x,y)` provides a masked version of
//!     `eve::is_greater_equal` which is equivalent to `if_else (mask, is_greater_equal(x),
//!     eve::false( eve::as(x,y)))`.
//!
//!   * `almost`
//!
//!     The expression `definitely(is_greater_equal)(x, y, t)` where `x` and `y` must be
//!     floating point values, evals to true if and only if `x` is almost greater than `y`.
//!     This means that:
//!
//!       - if `t` is a floating_value then  \f$x > y - t \max(|x|, |y|)\f$
//!       - if `t` is a positive integral_value then \f$x > \mbox{prev}(y, t)\f$;
//!       - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_greater_equal = functor<is_greater_equal_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_greater_equal_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<U> b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a >= b);
      else                                              return a >= b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_greater_equal_(EVE_REQUIRES(cpu_), O const & o, T const& aa, U const& bb) noexcept
    {
      if constexpr(O::contains(almost))
      {
        using w_t = common_value_t<T, U>;
        auto a = w_t(aa);
        auto b = w_t(bb);

        auto tol = o[almost].value(w_t{});
        if constexpr(integral_value<decltype(tol)>) return a >=  eve::prev(b, tol);
        else              return a >= fam(b, -tol, eve::max(eve::abs(a), eve::abs(b)));
      }
      else
      {
        if constexpr(scalar_value<U> && scalar_value<T>)  return common_logical_t<T,U>(aa >= bb);
        else                                              return aa >= bb;
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_greater_equal.hpp>
#endif
