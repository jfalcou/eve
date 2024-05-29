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
//!   @brief Computes the difference of products operation with better accuracy
//!   than the naive formula.
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
//!      template< eve::floating_value T
//!              , eve::floating_value U
//!              , eve::floating_value V
//!              , eve::floating_value W>
//!      T diff_of_prod(T x, U y, V z, W t ) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y`, `z`, `t`:  [floating value arguments](@ref eve::floating_value).
//!
//!    **Return value**
//!
//!    The value of `x*y-z*t`,  with better precision if correct fma is available,
//!    is returned.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/diff_of_prod.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::raw
//!
//!     The call `eve::raw(eve::diff_of_prod)(x, y, z, t)` computes a raw
//!     version of eve::diff_of_prod,  i.e. the naive formula (in fact  `fms(x, y, z, t)`)
//!
//!   * eve::pedantic
//!
//!     The call `eve::pedantic(eve::diff_of_prod)(x, y, z, t)` computes a pedantic
//!     version of eve::diff_of_prod ensuring better accuracy in any case.
//!
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
