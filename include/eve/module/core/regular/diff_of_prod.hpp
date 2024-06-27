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
#include <eve/module/core/regular/is_finite.hpp>
#include <eve/module/core/regular/fma.hpp>
#include <eve/module/core/regular/fms.hpp>
#include <eve/module/core/regular/fnma.hpp>

namespace eve
{
  template<typename Options>
  struct diff_of_prod_t : elementwise_callable<diff_of_prod_t, Options, raw_option, pedantic_option>
  {
    template<value T,  value U, value V,  value W>
    requires(eve::same_lanes_or_scalar<T, U, V, W>)
    constexpr EVE_FORCEINLINE common_value_t<T, U, V, W> operator()(T a, U b, V c, W d) const
    { return EVE_DISPATCH_CALL(a, b, c, d); }

    EVE_CALLABLE_OBJECT(diff_of_prod_t, diff_of_prod_);
  };

//================================================================================================
//! @addtogroup core_accuracy
//! @{
//!   @var diff_of_prod
//!   @brief `elementwise_callable` object computing the difference of products operation with better accuracy
//!   than the naive formula.
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
//!      constexpr auto diff_of_prod(floating_value auto x, floating_value auto y
//!                                                floating_value auto z, floating_value auto t) noexcept; // 1
//!
//!      // Lanes masking
//!      constexpr auto diff_of_prod[conditional_expr auto c](floating_value auto x, floating_value auto y
//!                                                floating_value auto z, floating_value auto t) noexcept; // 2
//!
//!      // Semantic exclusive options
//!      constexpr auto diff_of_prod[raw](floating_value auto x, floating_value auto y,
//!                                       floating_value auto z, floating_value auto t) noexcept;          // 3
//!      constexpr auto diff_of_prod[pedantic](floating_value auto x, floating_value auto y,
//!                                       floating_value auto z, floating_value auto t) noexcept;          // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`, `t`:  [floating values](@ref floating_value).
//!
//!    **Return value**
//!
//!      1. The value of `x*y-z*t`,  with better precision if correct fma is available,
//!        is returned.
//!      2. [The operation is performed conditionnaly](@ref conditional).
//!      3. computes a raw  version of diff_of_prod,  i.e. the naive formula (in fact  `fms(x, y, z*t)`)
//!      4. computes a pedantic version of `diff_of_prod` ensuring better accuracy in any case.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/diff_of_prod.cpp}
//! @}
//================================================================================================
 inline constexpr auto diff_of_prod = functor<diff_of_prod_t>;

  namespace detail
  {
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto
    diff_of_prod_(EVE_REQUIRES(cpu_), O const & o,
                  T const &a,  T const &b,
                  T const &c,  T const &d) noexcept
    {
      auto cd =  c*d;
      if constexpr(O::contains(raw2))
      {
        return fms(a, b, cd);
      }
      else
      {
        auto err = fnma[o](c, d, cd);
        auto dop = fms[o](a, b, cd);
        return add[is_finite(err)](dop, err);
      }
    }
  }
}
