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
#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct is_equal_t : elementwise_callable<is_equal_t, Options, numeric_option, almost_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(logical<T> a, logical<U> b) const
    // constexpr EVE_FORCEINLINE auto  operator()(logical<T> a, logical<U> b) const -> as_logical_t<decltype(a == b)>
    {
//      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_equal] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b); }

    template<value T,  value U>
    //    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(T a, U b) const
    constexpr EVE_FORCEINLINE auto  operator()(T a, U b) const -> as_logical_t<decltype(a == b)>
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(is_equal_t, is_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_equal
//!   @brief Returns a logical true  if and only if the element value are equal.
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
//!      auto is_equal(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  arguments
//!
//!   **Return value**
//!
//!     Returns the logical value containing the [elementwise](@ref glossary_elementwise) equality
//!     test result between `x` and `y`. The infix notation `x == y` can also be used.
//!
//!   @note
//!      Although the infix notation with `==` is supported, the `==` operator on
//!      standard scalar types is the original one and so returns bool result, not `eve::logical`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve::is_equal[mask](x)` provides a masked version of `eve::is_equal` which is
//!     equivalent to `if_else (mask, is_equal(x, y), false_)
//!
//!   * eve::numeric
//!
//!     The expression `is_equal[numeric](x,y)` considers that Nan values are equal.
//!
//!   * `tolerance`
//!
//!     The expression `is_equal[tolerance = t)(x, y)` where `x` and `y` must be floating point values,
//!     evals to true if and only if `x` is almost equal to `y`.
//!      This means that:
//!
//!      - if `t` is a floating_value then the relative error of confusing is `x` and `y` is less
//!      than `t` \f$(|x-y| \le t \max(|x|, |y|))\f$.
//!      - if `t` is a positive integral_value then there are not more than `t` values of the type
//!      of `x` representable in the interval \f$[x,y[\f$.
//!      - the call `is_equal[tolerant](x, y)` takes tol as  3 times
//!      the machine \f$\epsilon\f$ in the `x` type (`3*eps(as(x))`).
//!      - if t is an simd value x or y must also be simd.
//!
//! @}
//================================================================================================
  inline constexpr auto is_equal = functor<is_equal_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_equal_(EVE_REQUIRES(cpu_),
              O const & o,
              logical<T> const& a, logical<U> const& b) noexcept
    {
      if constexpr( scalar_value<U> &&  scalar_value<T>)
      {
        using r_t =  common_value_t<T, U>;
        return as_logical_t<r_t>(a == b);
      }
      else return a == b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr auto
    is_equal_(EVE_REQUIRES(cpu_),
              O const & o,
              T const& a, U const& b) noexcept
    {
      using w_t = as_logical_t<decltype(a == b)>;
      if constexpr(O::contains(almost2))
      {
        using e_t =  element_type_t<w_t>;
        auto tol = o[almost2].value(w_t{});
        if constexpr(integral_value<decltype(tol)>)
          return if_else(nb_values(a, b) <= tol, true_(as<w_t>()), false_(as<w_t>())) ;
        else
          return dist[pedantic](a, b) <= tol * max(eve::abs(a), eve::abs(b));
      }
      else if constexpr(O::contains(numeric2))
      {
        auto tmp = is_equal(a, b);
        using r_t =  common_value_t<T, U>;
        if constexpr( floating_value<r_t> )
          return tmp || (is_nan(a) && is_nan(b));
        else
          return tmp;
      }
      else
      {
        if constexpr( scalar_value<U> &&  scalar_value<T>)
        {
          using r_t =  common_value_t<T, U>;
          return as_logical_t<r_t>(a == b);
        }
        else
          return a == b;
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_equal.hpp>
#endif
