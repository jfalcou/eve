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
  struct rsqrt_2pi_t : constant_callable<rsqrt_2pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.988454p-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.988452p-2};
        else                                      return T{0x1.988454p-2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.9884533d43651p-2};
        else if constexpr (Opts::contains(lower)) return T{0x1.9884533d4365p-2};
        else                                      return T{0x1.9884533d43651p-2};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(rsqrt_2pi_t, rsqrt_2pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var rsqrt_2pi
  //!   @brief Callable object computing the constant \f$1/\sqrt{2\pi}\f$.
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
  //!      T rsqrt_2pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::rsqrt_2pi(as<T>())` returns the inverse of \f$\sqrt{2\pi}\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/rsqrt_2pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto rsqrt_2pi = functor<rsqrt_2pi_t>;
}
