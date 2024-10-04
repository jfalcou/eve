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
  struct inv_2pi_t : constant_callable<inv_2pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.45f308p-3};
        else if constexpr (Opts::contains(lower)) return T{0x1.45f306p-3};
        else                                      return T{0x1.45f306p-3};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.45f306dc9c883p-3};
        else if constexpr (Opts::contains(lower)) return T{0x1.45f306dc9c882p-3};
        else                                      return T{0x1.45f306dc9c883p-3};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(inv_2pi_t, inv_2pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var inv_2pi
  //!   @brief Callable object computing the constant \f$\frac{1}{2\pi}\f$.
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
  //!      T inv_2pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::inv_2pi(as<T>())` returns the inverse of \f$2\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/inv_2pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto inv_2pi = functor<inv_2pi_t>;
}
