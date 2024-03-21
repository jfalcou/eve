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
#include <eve/module/core/regular/is_unordered.hpp>
#include <eve/module/core/regular/is_nan.hpp>
#include <eve/module/core/regular/max.hpp>
#include <eve/module/core/regular/min.hpp>
#include <eve/module/core/constant/valmax.hpp>

namespace eve
{
 template<typename Options>
  struct dist_t : elementwise_callable<dist_t, Options, saturated_option,  pedantic_option>
  {
    template<value T,  value U>
    EVE_FORCEINLINE constexpr EVE_FORCEINLINE common_value_t<T, U> operator()(T a, U b) const noexcept
    { return EVE_DISPATCH_CALL(a, b); }

    EVE_CALLABLE_OBJECT(dist_t, dist_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var dist
//!   @brief Computes the distance of its arguments.
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
//!      eve::common_value_t<T, U> dist(T x, U y) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x`, `y` :   [real](@ref eve::value) arguments.
//!
//!    **Return value**
//!
//!    The value of the distance of the arguments is returned,  i.e. `eve::abs (x-y)`.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/core/regular/dist.cpp}
//!
//!  @groupheader{Semantic Modifiers}
//!
//!   * eve::saturated
//!
//!     The call `saturated(dist)(x, y)` computes a saturated distance.
//!     Contrary to the non decorated case, it guarantees
//!     that the result is always defined. If \f$|x-y|\f$ is not representable
//!     [the greatest representable positive value](@ref eve::valmax) is returned.
//!
//!   * eve::pedantic
//!
//!     The call `pedantic(dist)(x, y)` computes a distance wich is nan if and only
//!     if a or b is a Nan.
//!
//!      **Example**
//!
//!        @godbolt{doc/core/saturated/dist.cpp}
//! @}
//================================================================================================
  inline constexpr auto dist = functor<dist_t>;


  namespace detail
  {
    template<value T0,  value T1, callable_options O>
    constexpr common_value_t<T0, T1> dist_(EVE_REQUIRES(cpu_), O const&, T0 const& a,  T1 const & b)
    {
      using r_t = common_value_t<T0, T1>;
      auto d = eve::max(a, b) - eve::min(a, b);
      if constexpr(O::contains(saturated2) && signed_integral_value<r_t>)
        return if_else(is_ltz(d), valmax(eve::as(a)), d);
      else if constexpr(O::contains(pedantic2) && floating_value<r_t>)
        return if_else(is_unordered(a, b), allbits, if_else(is_nan(d), inf(as<r_t>()), d));
      else
        return d;
    }
  }
}
