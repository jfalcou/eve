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
  struct cbrt_pi_t : constant_callable<cbrt_pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.76ef8p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.76ef7ep+0};
        else                                      return T{0x1.76ef7ep+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.76ef7e73104b8p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.76ef7e73104b7p+0};
        else                                      return T{0x1.76ef7e73104b8p+0};
      }
    }

    template<floating_value T>
    constexpr EVE_FORCEINLINE T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(cbrt_pi_t, cbrt_pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var cbrt_pi
  //!   @brief Callable object computing the constant \f$\sqrt[3]\pi\f$.
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
  //!      T cbrt_pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::cbrt_pi(as<T>())` returns  \f$\sqrt[3]\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/cbrt_pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto cbrt_pi = functor<cbrt_pi_t>;
}
