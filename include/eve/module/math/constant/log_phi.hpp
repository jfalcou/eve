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
  struct log_phi_t : constant_callable<log_phi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.ecc2ccp-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.ecc2cap-2};
        else                                      return T{0x1.ecc2cap-2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.ecc2caec5160ap-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.ecc2caec51609p-2};
        else                                      return T{0x1.ecc2caec5160ap-2};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(log_phi_t, log_phi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var log_phi
  //!   @brief Callable object computing the logarithm of the golden ratio : \f$\log((1+\sqrt5)/2)\f$.
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
  //!      T log_phi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::log_phi(as<T>())` returns  the logarithm of the golden ratio.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/log_phi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto log_phi = functor<log_phi_t>;
}
