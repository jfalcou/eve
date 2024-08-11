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
struct cos_1_t : constant_callable<cos_1_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.14a282p-1);
      else if constexpr(Opts::contains(downward)) return T(0x1.14a28p-1);
      else                                         return T(0x1.14a28p-1);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.14a280fb5068cp-1);
      else if constexpr(Opts::contains(downward)) return T(0x1.14a280fb5068bp-1);
      else                                         return T(0x1.14a280fb5068cp-1);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(cos_1_t, cos_1_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var cos_1
//!   @brief Callable object computing the constant \f$\cos1\f$.
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
//!      template< eve::value T >
//!      T cos_1(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::cos_1(as<T>())` returns the  cosine of 1.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/cos_1.cpp}
//! @}
//================================================================================================
inline constexpr auto cos_1 = functor<cos_1_t>;
}
