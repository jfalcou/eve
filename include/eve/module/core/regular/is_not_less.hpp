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

namespace eve
{
  template<typename Options>
  struct is_not_less_t : elementwise_callable<is_not_less_t, Options, definitely_option>
  {
    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(logical<T> a, logical<U> b) const
    {
//      static_assert( valid_tolerance<common_value_t<T, U>, Options>::value, "[eve::is_not_less] simd tolerance requires at least one simd parameter." );
      return EVE_DISPATCH_CALL(a, b);
    }

    template<value T,  value U>
    constexpr EVE_FORCEINLINE as_logical_t<common_value_t<T, U>> operator()(T a, U b) const
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(is_not_less_t, is_not_less_);
  };

//================================================================================================
//! @addtogroup core_predicates
//! @{
//!   @var is_not_less
//!   @brief Returns a logical true  if and only if the element value of the first parameter is
//!          not less  than the second one.
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
//!      The expression `almost(is_not_less)(x, y, t)` where `x` and `y` must be
//!      floating point values, evals to true if and only if and only if `x` is not almost less than
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
    EVE_FORCEINLINE constexpr as_logical_t<common_value_t<T, U>>
    is_not_less_(EVE_REQUIRES(cpu_),
                  O const & o,
                  logical<T> const& a, logical<U> const& b) noexcept
    {
      if constexpr( scalar_value<U> &&  scalar_value<T>)
      {
        using r_t =  common_value_t<T, U>;
        return as_logical_t<r_t>(a >=  b);
      }
      else return a >=   b;
    }

    template<value T, value U, callable_options O>
    EVE_FORCEINLINE constexpr as_logical_t<common_value_t<T, U>>
    is_not_less_(EVE_REQUIRES(cpu_),
                  O const & o,
                  T const& aa, U const& bb) noexcept
    {
      using w_t =  common_value_t<T, U>;
      using r_t =  as_logical_t<w_t>;
      auto a = w_t(aa);
      auto b = w_t(bb);
      if constexpr(O::contains(definitely2))
      {
        auto tol = o[definitely2].value(w_t{});
        if constexpr(integral_value<decltype(tol)>)
          return is_not_less(a,  eve::prev(b, tol));
        else
          return is_not_less(a, fam(b, -tol, max(eve::abs(a), eve::abs(b))));
      }
      else
      {
        if constexpr( scalar_value<U> &&  scalar_value<T>)
          return as_logical_t<w_t>(a >=  b);
        else
          return (a >= b) || is_unordered(a, b);;
      }
    }
  }

}

#include <eve/module/core/regular/impl/is_not_less.hpp>

#if defined(EVE_INCLUDE_X86_HEADER)
#  include <eve/module/core/regular/impl/simd/x86/is_not_less.hpp>
#endif
