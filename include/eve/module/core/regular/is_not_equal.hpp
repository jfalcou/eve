//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/function/friends.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/is_not_nan.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/nb_values.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/detail/tolerance.hpp>

namespace eve
{
  template<typename Options>
  struct is_not_equal_t : strict_elementwise_callable<is_not_equal_t, Options, numeric_option, definitely_option>
  {
    template<value T, value U>
    constexpr EVE_FORCEINLINE common_logical_t<T, U> operator()(T a, U b) const
      requires(eve::same_lanes_or_scalar<T, U>)
    {
//      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_not_equal] simd tolerance requires at least one simd parameter." );
      return this->behavior(as<common_logical_t<T, U>>{}, eve::current_api, this->options(), a, b);
    }


    EVE_CALLABLE_OBJECT(is_not_equal_t, is_not_equal_);
  };

  //================================================================================================
  //! @addtogroup core_predicates
  //! @{
  //!   @var is_not_equal
  //!   @brief `elementwise callable` returning a logical true  if and only if the element values are not equal.
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
  //!      constexpr auto is_not_equal(value auto x, value auto y) noexcept;                          // 1
  //!
  //!      // Lanes masking
  //!      constexpr auto is_not_equal[conditional_expr auto c](value auto x, value auto y) noexcept; // 2
  //!      constexpr auto is_not_equal[logical_value auto m](value auto x, value auto y) noexcept;    // 2
  //!
  //!      // Semantic option
  //!      constexpr auto is_not_equal[numeric](/*any of the above overloads*/)             noexcept; // 3
  //!      constexpr auto is_not_equal[definitely](/*any of the above overloads*/)          noexcept; // 4
  //!      constexpr auto is_not_equal[definitely = tol](/*any of the above overloads*/)    noexcept; // 4
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
  //!      1. Returns the logical value containing the [elementwise](@ref glossary_elementwise) inequality
  //!        test result between `x` and `y`.
  //!      2. [The operation is performed conditionnaly](@ref conditional).
  //!      3. The expression `is_not_equal[numeric](x,y)` considers that `Nan` values are not equal.
  //!      4. The expression `is_not_equal[definitely = tol](x, y)` where `x` and `y` must be
  //!         floating point values, evaluates to true if and only if `x` is definitely not equal to `y`.
  //!         This means that:
  //!            - if `tol` is a floating value then  \f$|x - y| \ge \mbox{tol}\cdot \max(|x|, |y|)\f$
  //!            - if `tol` is a positive integral value then there are more than `tol` values of the type
  //!               of `x` representable in the interval \f$[x, y[\f$.
  //!            - if `tol` is omitted then the tolerance `tol` default to `3*eps(as{x})`.
  //!
  //!   @note Although the infix notation with `!=` is supported, the `!=` operator on
  //!      standard scalar types is the original one and so returns bool result, not `eve::logical`.
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/core/is_not_equal.cpp}
  //================================================================================================
  inline constexpr auto is_not_equal = functor<is_not_equal_t>;
  //================================================================================================
  //! @}
  //================================================================================================

  namespace detail
  {

    template<callable_options O, value T, value U>
    EVE_FORCEINLINE constexpr common_logical_t<T, U> is_not_equal_(EVE_REQUIRES(cpu_), O const&, logical<T> a, logical<U> b) noexcept
    {
      if constexpr( scalar_value<U> && scalar_value<T>) return common_logical_t<T, U>(a != b);
      else                                              return a != b;
    }

    template<callable_options O, value T, value U>
    EVE_FORCEINLINE constexpr common_logical_t<T, U> is_not_equal_(EVE_REQUIRES(cpu_),O const& o, T const& a, U const& b) noexcept
    {
      if constexpr (O::contains(definitely))
      {
        using w_t = common_logical_t<T, U>;
        using r_t = common_value_t<T, U>;

        auto tol = o[definitely].value(r_t{});

        if constexpr(integral_value<decltype(tol)>)
          return if_else(nb_values(a, b) > tol, true_(as<w_t>{}), false_(as<w_t>{})) ;
        else
          return dist[pedantic](a, b) > tol * max(eve::abs(a), eve::abs(b));
      }
      else if constexpr (O::contains(numeric))
      {
        using r_t = common_value_t<T, U>;
        auto tmp  = is_not_equal(a, b);
        if constexpr (floating_value<r_t>) return tmp && (is_not_nan(a) || is_not_nan(b));
        else                               return tmp;
      }
      else
      {
        if constexpr (scalar_value<U> && scalar_value<T>) return common_logical_t<T, U>(a != b);
        else                                              return a != b;
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_equal.hpp>
#endif
