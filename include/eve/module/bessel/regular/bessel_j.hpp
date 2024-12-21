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
#include <eve/module/bessel/detail/csb_j.hpp>

namespace eve
{

  template<typename Options>
  struct bessel_j_t : eve::strict_elementwise_callable<bessel_j_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::value N, eve::floating_value Z>
    EVE_FORCEINLINE constexpr Z  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(Options::contains(eve::spherical))
        return detail::sb_j(n, z);
      else
        return detail::cb_j(n, z);
    }

    EVE_CALLABLE_OBJECT(bessel_j_t, bessel_j_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_j
//!   @brief Computes the spherical or cylindrical Bessel functions of the first kind,
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
//!      constexpr auto bessel_j(value auto n, floating_value auto z)                  noexcept; // 1
//!
//!      // Semantic modifier
//!      constexpr auto bessel_j[cylindrical](value auto n, floating_value auto z)     noexcept; // 1
//!      constexpr auto bessel_j[spherical](value auto n, floating_value auto z)       noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bessel_j[conditional_expr auto c](/*any previous overload*/)   noexcept; // 3
//!      constexpr auto bessel_j[logical_value auto m](/*any previous overload*/)      noexcept; // 3
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
//!     1. returns \f$J_n\f$(z) (cylindrical).
//!     2. returns \f$j_n\f$(z) (spherical).
//!     3. [The operation is performed conditionally](@ref conditional).
//!
//!  @note if n is not integral nor flint negative z entries produce NaN outputs as the correct result is not real. You may want
//!       to use **KYOSU** to avoid this behavior and produce complex outputs (that are not available in **EVE**).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Bessel Function of the First Kind](https://mathworld.wolfram.com/BesselFunctionoftheFirstKind.html)
//!   *  [Wolfram MathWorld: Spherical Bessel Function of the First Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheFirstKind.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel functions](https://dlmf.nist.gov/10.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel/bessel_j.cpp}
//======================================================================================================================
  inline constexpr auto bessel_j = eve::functor<bessel_j_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
