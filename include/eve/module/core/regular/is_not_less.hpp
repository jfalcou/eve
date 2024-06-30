//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/if_else.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/regular/fam.hpp>
#include <eve/module/core/regular/prev.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_less_t : strict_elementwise_callable<is_not_less_t, Options, almost_option>
  {
    template<value T,  value U>
    requires(eve::same_lanes_or_scalar<T, U>)
    constexpr EVE_FORCEINLINE common_logical_t<T,U> operator()(T a, U b) const
    {
      //      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_not_less] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    EVE_CALLABLE_OBJECT(is_not_less_t, is_not_less_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_less
//!   @brief `elementwise callable` returning a logical true  if and only if the element value of the first parameter is
//!          not less  than the second one.
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
//!      eve::as_logical<T> is_not_less(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_not_less(x,y)`  is semantically  equivalent to `!(x <  y)`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_not_less.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_not_less[mask](x,y)` provides a masked version of `eve::is_not_less`
//!     which is equivalent to `if_else (mask, is_not_less(x), eve::false( eve::as(x,y)))`.
//!
//!    * `almost`
//!
//!      The expression `is_not_less[almost](x, y, t)` where `x` and `y` must be
//!      floating point values, evaluates to true if and only if and only if `x` is not almost less than
//!      `y`. This means that the pair `x, y` is unordered or:
//!
//!      * if `t` is a floating_value then  \f$(x \ge y - t \max(|x|, |y|))\f$
//!      * if `t` is a positive integral_value then \f$(x \ge \mbox{prev}(y, t)\f$;
//!      * if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_not_less = functor<is_not_less_t>;

  namespace detail
  {

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_not_less_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<U> b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T,U>(a >= b);
      else                                              return a >= b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr common_logical_t<T,U>
    is_not_less_(EVE_REQUIRES(cpu_), O const & o, T const& aa, U const& bb) noexcept
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
        if constexpr(scalar_value<U> && scalar_value<T>)  return common_logical_t<T,U>(aa >=  bb || is_unordered(aa, bb));
        else                                              return aa >=  bb || is_unordered(aa, bb);
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_less.hpp>
#endif
