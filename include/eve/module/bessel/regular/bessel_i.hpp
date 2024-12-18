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
#include <eve/module/bessel/detail/csb_i.hpp>

namespace eve
{

  template<typename Options>
  struct bessel_i_t : eve::strict_elementwise_callable<bessel_i_t, Options, eve::spherical_option, eve::cylindrical_option>
  {
    template<eve::value N, eve::floating_value Z>
    EVE_FORCEINLINE constexpr Z  operator()(N const& n, Z const & z) const noexcept
    {
      if constexpr(Options::contains(eve::spherical))
        return detail::sb_i(n, z);
      else
        return detail::cb_i(n, z);
    }

    EVE_CALLABLE_OBJECT(bessel_i_t, bessel_i_);
  };

//======================================================================================================================
//! @addtogroup functions
//! @{
//!   @var  bessel_i
//!   @brief Computes the spherical or cylindrical Modified Bessel functions of the first kind,
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
//!      constexpr auto bessel_i(value auto n, floating_value auto z)                noexcept; // 1
//!
//!      // Semantic modifier
//!      constexpr auto bessel_i[spherical](value auto n, floating_value auto z)     noexcept; // 2
//!
//!      // Lanes masking
//!      constexpr auto bessel_i[conditional_expr auto c](/*any previous overload*/) noexcept; // 3
//!      constexpr auto bessel_i[logical_value auto m](/*any previous overload*/)    noexcept; // 3
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
//!  @note  `cylindical` option can be used and its result is identical to the regular call (no option).
//!
//!  @groupheader{External references}
//!   *  [Wolfram MathWorld: Bessel Function of the Second Kind](https://mathworld.wolfram.com/BesselFunctionoftheSecondKind.html)
//!   *  [Wolfram MathWorld: Spherical Bessel Function of the Second Kind](https://mathworld.wolfram.com/SphericalBesselFunctionoftheSecondKind.html)
//!   *  [Wikipedia: Bessel function](https://en.wikipedia.org/wiki/Bessel_function)
//!   *  [DLMF: Bessel functions](https://dlmf.nist.gov/10.2)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/bessel_i.cpp}
//======================================================================================================================
  inline constexpr auto bessel_i = eve::functor<bessel_i_t>;
//======================================================================================================================
//! @}
//======================================================================================================================
}
