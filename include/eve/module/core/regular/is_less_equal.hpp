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
  struct is_less_equal_t : elementwise_callable<is_less_equal_t, Options, almost_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(logical<T> a, logical<U> b) const
    {
//      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_less_equal] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(is_less_equal_t, is_less_equal_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_less_equal
//!   @brief Returns a logical true  if and only if the element value of the first parameter is
//!          less or equal to the second one.
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
//!      eve::as_logical<T> is_less_equal(T x,U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :  [argument](@ref eve::value).
//!
//!   **Return value**
//!
//!    The call `eve::is_less_equal(x,y)`  is semantically  equivalent to `x >= y`:
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/is_less_equal.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * Masked Call
//!
//!     The call `eve;::is_less_equal[mask](x,y)` provides a masked version of `eve::is_less_equal`
//!     which is equivalent to `if_else (mask, is_less_equal(x), eve::false( eve::as(x,y)))`.
//!
//!   * `almost`
//!
//!     The expression `definitely(is_less_equal)(x, y, t)` where `x` and `y` must be
//!     floating point values, evaluates to true if and only if `x` is almost less than `y`.
//!     This means that:
//!
//!      - if `t` is a floating_value then  \f$x <  y + t \max(|x|, |y|)\f$
//!      - if `t` is a positive integral_value then \f$x <  \mbox{next}(y, t)\f$;
//!      - if `t` is omitted then the tolerance `t` default to `3*eps(as(x))`.
//!
//! @}
//================================================================================================
  inline constexpr auto is_less_equal = functor<is_less_equal_t>;

  namespace detail
  {
    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<common_value_t<T, U>>
    is_less_equal_(EVE_REQUIRES(cpu_),
                  O const & o,
                  logical<T> const& a, logical<U> const& b) noexcept
    {
      if constexpr( scalar_value<U> &&  scalar_value<T>)
      {
        using r_t =  common_value_t<T, U>;
        return as_logical_t<r_t>(a <= b);
      }
      else return a <=  b;
    }


    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<common_value_t<T, U>>
    is_less_equal_(EVE_REQUIRES(cpu_),
                  O const & o,
                  T const& aa, U const& bb) noexcept
    {
      using w_t =  common_value_t<T, U>;
      using r_t =  as_logical_t<w_t>;
      auto a = w_t(aa);
      auto b = w_t(bb);
      if constexpr(O::contains(almost2))
      {
        auto tol = o[definitely2].value(w_t{});
        if constexpr(integral_value<decltype(tol)>)
          return a <= eve::next(b, tol);
        else
          return a <=  fam(b, tol, max(eve::abs(a), eve::abs(b)));
      }
      else
      {
        if constexpr( scalar_value<U> &&  scalar_value<T>)
          return as_logical_t<w_t>(a <=  b);
        else
          return a <= b;
      }
    }
  }
}

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_less_equal.hpp>
#endif
