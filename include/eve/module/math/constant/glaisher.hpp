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

namespace eve
{
template<typename Options>
struct glaisher_t : constant_callable<glaisher_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T(0x1.484d26p+0);
      else if constexpr(Opts::contains(lower)) return T(0x1.484d24p+0);
      else                                         return T(0x1.484d24p+0);
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T(0x1.484d24f2fd874p+0);
      else if constexpr(Opts::contains(lower)) return T(0x1.484d24f2fd873p+0);
      else                                         return T(0x1.484d24f2fd873p+0);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(glaisher_t, glaisher_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var glaisher
//!   @brief Callable object computing the Glaisher-Kinkelin constant.
//!
//!   **Defined in Header**
//!
//!   @code
//!   #include <eve/module/math.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      template< eve::floating_value T >
//!      T glaisher(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::glaisher(as<T>())` returns the Glaisher-Kinkelin constant.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/glaisher.cpp}
//! @}
//================================================================================================
inline constexpr auto glaisher = functor<glaisher_t>;
}
