//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/traits/overload.hpp>
#include <eve/module/core/decorator/core.hpp>
#include <eve/module/bessel/detail/csb_y.hpp>

namespace eve
{

  template<typename Options>
  struct bessel_y_t : elementwise_callable<bessel_y_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::value N, eve::floating_value Z>
    EVE_FORCEINLINE constexpr Z  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(Options::contains(eve::spherical))
        return detail::sb_y(n, z);
      else
        return detail::cb_y(n, z);
    }
    EVE_CALLABLE_OBJECT(bessel_y_t, bessel_y_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_y
//!   @brief Computes the spherical or cylindrical Bessel functions of the second kind,
//!
//!   @code
//!   #include <eve/functions.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overload
//!      template<eve::floating_value T> constexpr auto bessel_y(value auto n, floating_value auto z)             noexcept; // 1
//!
//!      // Semantic modifyier
//!      template<eve::floating_value T> constexpr auto bessel_y[spherical](value auto n, floating_value auto z)  noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bessel_y[conditional_expr auto c](/*any previous overload*/)                              noexcept; // 3
//!      constexpr auto bessel_y[logical_value auto m](/*any previous overload*/)                                 noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `n`:  order (integral or floating)
//!     * `z`: Value to process.
//!     * `m`: [Logical value](@ref eve::logical_value) masking the operation.
//!
//!   **Return value**
//!
//!     1. returns \f$Y_n\f$(z) (cylindrical).
//!     2. returns \f$y_n\f$(z) (spherical).
//!     3. [The operation is performed conditionnaly](@ref conditional).
//!
//!  @note
//!   *  `cylindical` option can be used and its result is identical to the regular call (no option).
//!   *  if n is not integral nor flint negative z entries produce NaN outputs as the correct result is not real. You may want
//!       to use **KYOSU** to avoid this behavior and produce complex outputs (that are not available in **EVE**).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Bessel Function of the Second Kind](https://mathworld.wolfram.com/BesselFunctionoftheSecondKind.html)
//!   *  [Wolfram MathWorld: Spherical Bessel Function of the Second Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel functions](https://dlmf.nist.gov/10.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel_y.cpp}
//======================================================================================================================
  inline constexpr auto bessel_y = eve::functor<bessel_y_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
