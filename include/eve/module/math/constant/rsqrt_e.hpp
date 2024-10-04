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
struct rsqrt_e_t : constant_callable<rsqrt_e_t, Options, lower_option, upper_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
  {
    if constexpr(std::same_as<T, float>)
    {
      if constexpr(Opts::contains(upper))        return T{0x1.368b3p-1};
      else if constexpr(Opts::contains(lower)) return T{0x1.368b2ep-1};
      else                                         return T{0x1.368b3p-1};
    }
    else
    {
      if constexpr(Opts::contains(upper))        return T{0x1.368b2fc6f960ap-1};
      else if constexpr(Opts::contains(lower)) return T{0x1.368b2fc6f9609p-1};
      else                                         return T{0x1.368b2fc6f960ap-1};
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(rsqrt_e_t, rsqrt_e_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var rsqrt_e
//!   @brief Callable object computing the constant \f$1/\sqrt{e}\f$.
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
//!      T rsqrt_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::rsqrt_e(as<T>())` returns the inverse of the square root of the basis of
//!      natural logarithms.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/rsqrt_e.cpp}
//! @}
//================================================================================================
inline constexpr auto rsqrt_e = functor<rsqrt_e_t>;
}
