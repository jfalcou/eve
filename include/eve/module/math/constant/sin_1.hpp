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
  struct sin_1_t : constant_callable<sin_1_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.aed54ap-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.aed548p-1};
        else                                      return T{0x1.aed548p-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.aed548f090cefp-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.aed548f090ceep-1};
        else                                      return T{0x1.aed548f090ceep-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(sin_1_t, sin_1_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var sin_1
  //!   @brief Callable object computing the constant \f$\sin(1)\f$.
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
  //!      T sin_1(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::sin_1(as<T>())` returns the sine of 1.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/sin_1.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto sin_1 = functor<sin_1_t>;
}
