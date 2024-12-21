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
#include <eve/module/bessel/detail/csb_k.hpp>

namespace eve
{

  template<typename Options>
  struct bessel_k_t : elementwise_callable<bessel_k_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::value N, eve::floating_value Z>
    EVE_FORCEINLINE constexpr Z  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(Options::contains(eve::spherical))
        return detail::sb_k(n, z);
      else
        return detail::cb_k(n, z);
    }
    EVE_CALLABLE_OBJECT(bessel_k_t, bessel_k_);
  };


//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_k
//!   @brief Computes the modified spherical or cylindrical Bessel functions of the second kind,
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
//!      constexpr auto bessel_k(value auto n, floating_value auto z)                  noexcept; // 1
//!
//!      // Semantic modifier
//!      constexpr auto bessel_k[spherical](value auto n, floating_value auto z)       noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bessel_k[conditional_expr auto c](/*any previous overload*/)   noexcept; // 3
//!      constexpr auto bessel_k[logical_value auto m](/*any previous overload*/)      noexcept; // 3
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
//!     3. [The operation is performed conditionally](@ref conditional).
//!
//!  @note
//!   *  `cylindical` option can be used and its result is identical to the regular call (no option).
//!   *  if n is not integral nor flint negative z entries produce NaN outputs as the correct result is not real. You may want
//!       to use **KYOSU** to avoid this behavior and produce complex outputs (that are not available in **EVE**).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Modified Bessel Function of the second Kind](https://mathworld.wolfram.com/BesselFunctionoftheSecondKind.html)
//!   *  [Wolfram MathWorld: Modified Spherical Bessel Function of the second Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Modified Bessel functions](https://dlmf.nist.gov/10.25)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel_k.cpp}
//======================================================================================================================
  inline constexpr auto bessel_k = eve::functor<bessel_k_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
