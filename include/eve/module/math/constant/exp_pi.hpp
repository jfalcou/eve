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
  struct exp_pi_t : constant_callable<exp_pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.724048p+4};
        else if constexpr (Opts::contains(lower)) return T{0x1.724046p+4};
        else                                      return T{0x1.724046p+4};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.724046eb0933ap+4};
        else if constexpr (Opts::contains(lower)) return T{0x1.724046eb09339p+4};
        else                                      return T{0x1.724046eb0933ap+4};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(exp_pi_t, exp_pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var exp_pi
  //!   @brief Callable object computing the constant \f$e^\pi\f$.
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
  //!      T exp_pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::exp_pi(as<T>())` returns \f$e^\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/exp_pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto exp_pi = functor<exp_pi_t>;
}
