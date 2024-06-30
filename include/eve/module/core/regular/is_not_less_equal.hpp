/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/module/core/regular/fam.hpp>
#include <eve/module/core/regular/next.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_less_equal_t : strict_elementwise_callable<is_not_less_equal_t, Options, definitely_option>
  {
   template<value T,  value U>
   requires(eve::same_lanes_or_scalar<T, U>)
   constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_not_less_equal] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_not_less_equal_t, is_not_less_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_less_equal
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          not less or equal to the second one.
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
//!      eve::as_logical<T> is_not_less_equal(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_not_less_equal(x,y)`  is semantically  equivalent to `!(x <= y)`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_less_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_less_equal[mask](x,y)` provides a masked version of `eve::is_not_less_equal`
//!     which is equivalent to `if_else (mask, is_not_less_equal(x), eve::false( eve::as(x,y)))`.
//!
//!   * `definitely`
//!
//!     The expression `definitely(is_not_less_equal)(x, y, t)` where `x` and `y` must be
//!     floating point values, evaluates to true if and only if and only if `x` is definitely not less
//!     or equal to `y`.
//!
//!     This means that the pair `x, y` is unordered:
//!       - if `t` is a floating_value then  \f$(x \ge y + t \max(|x|, |y|))\f$
//!       - if `t` is a positive integral_value then \f$(x \ge \mbox{next}(y, t)\f$;
//!       - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_less_equal = functor<is_not_less_equal_t>;


  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_not_less_equal_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<U> b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a > b);
      else                                              return a > b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_not_less_equal_(EVE_REQUIRES(cpu_), O const & o, T const& aa, U const& bb) noexcept
    {
      if constexpr(O::contains(definitely))
      {
        using w_t = common_value_t<T, U>;
        auto a = w_t(aa);
        auto b = w_t(bb);

        auto tol = o[definitely].value(w_t{});
        if constexpr(integral_value<decltype(tol)>) return is_not_less_equal(a, eve::next(b, tol));
        else              return is_not_less_equal(a, fam(b, tol, eve::max(eve::abs(a), eve::abs(b))));
      }
      else
      {
        if constexpr(scalar_value<U> && scalar_value<T>)  return common_logical_t<T,U>(aa > bb || is_unordered(aa, bb));
        else                                              return aa > bb || is_unordered(aa, bb);
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_less_equal.hpp>
#endif
