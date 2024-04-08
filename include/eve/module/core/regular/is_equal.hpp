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
#include <eve/detail/overload.hpp>
#include <eve/traits/as_logical.hpp>
#include <eve/module/core/constant/eps.hpp>
#include <eve/module/core/regular/abs.hpp>
#include <eve/module/core/regular/convert.hpp>
#include <eve/module/core/regular/dist.hpp>
#include <eve/module/core/regular/is_less_equal.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/nb_values.hpp>

namespace eve
{
  template<typename Options>
  struct is_equal_t : elementwise_callable<is_equal_t, Options, numeric_option, tolerant_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(logical<T> a, logical<U> b) const
    { return EVE_DISPATCH_CALL(a, b); }

    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(T a, U b) const
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
//!     The expression `numeric(is_equal)(x,y)` considers that Nan values are equal.
//!
//!   * `almost`
//!
//!     The expression `almost(is_equal)(x, y, t)` where `x` and `y` must be floating point values,
//!     evals to
//!      true if and only if `x` is almost equal to `y`.
//!      This means that:
//!
//!      - if `t` is a floating_value then the relative error of confusing is `x` and `y` is less
//!      than `t` \f$(|x-y| \le t \max(|x|, |y|))\f$.
//!      - if `t` is a positive integral_value then there are not more than `t` values of the type
//!      of `x` representable in the interval \f$[x,y[\f$.
//!      - if `t` is omitted then the tolerance `t` is taken to 3 times the machine \f$\epsilon\f$
//!      in the `x` type (`3*eps(as(x))`).
//!
//! @}
//================================================================================================
  inline constexpr auto is_equal = functor<is_equal_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<common_value_t<T, U>>
    is_equal_(EVE_REQUIRES(cpu_),
              O const & o,
              T const& a, U const& b) noexcept
    {
      using w_t =  common_value_t<T, U>;
      if constexpr((is_logical_v<T> && is_logical_v<U>))
      {
        if constexpr( scalar_value<U> &&  scalar_value<T>)
        {
          using r_t =  common_value_t<T, U>;
          return as_logical_t<r_t>(a == b);
        }
        else return a == b;
      }
      else if constexpr(O::contains(tolerance))
      {
        using w_t =  common_value_t<T, U>;
        using e_t =  element_type_t<w_t>;
        using r_t = as_logical_t<w_t>;
        auto tol = [&]<typename V>(V const& t){
          if constexpr(std::same_as<V,default_tolerance>) return 3 * eps(as<e_t>());
          else if constexpr(integral_value<V>)            return t;
          else                                            return convert(t,as<e_t>());
        }(o[tolerance]);
        if constexpr(integral_value<decltype(tol)>)
          return if_else(nb_values(a, b) <= tol, true_(as<r_t>()), false_(as<r_t>())) ;
        else
        {
          return is_less_equal(dist[pedantic](a, b), tol * max(eve::abs(a), eve::abs(b)));
        }
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
