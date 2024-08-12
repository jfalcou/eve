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
struct log10_e_t : constant_callable<log10_e_t, Options, downward_option, upward_option>
{
  template<typename T, typename Opts>
  static EVE_FORCEINLINE constexpr T value(eve::as<T> const&, Opts const&)
  {
    if constexpr(std::same_as<element_type_t<T>, float>)
    {
      if constexpr(Opts::contains(upward))        return T(0x1.bcb7b2p-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.bcb7bp-2 );
      else                                         return T(0x1.bcb7b2p-2);
    }
    else
    {
      if constexpr(Opts::contains(upward))        return T(0x1.bcb7b1526e50fp-2);
      else if constexpr(Opts::contains(downward)) return T(0x1.bcb7b1526e50ep-2);
      else                                         return T(0x1.bcb7b1526e50ep-2);
    }
  }

  template<floating_value T>
  EVE_FORCEINLINE constexpr T operator()(as<T> const& v) const { return EVE_DISPATCH_CALL(v); }

  EVE_CALLABLE_OBJECT(log10_e_t, log10_e_);
};

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var log10_e
//!   @brief Callable object computing the constant \f$\log_{10}e\f$.
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
//!      T log10_e(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::log10_e(as<T>())` returns \f$\log_{10}e\f$.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/log10_e.cpp}
//! @}
//================================================================================================
inline constexpr auto log10_e = functor<log10_e_t>;
}
