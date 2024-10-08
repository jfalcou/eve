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
  struct log2_e_t : constant_callable<log2_e_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.715478p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.715476p+0};
        else                                      return T{0x1.715476p+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.71547652b82ffp+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.71547652b82fep+0};
        else                                      return T{0x1.71547652b82fep+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(log2_e_t, log2_e_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var log2_e
  //!   @brief Callable object computing the constant \f$\log_2 e\f$.
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
  //!      T log2_e(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::log2_e(as<T>())` returns \f$\log_2 e\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/log2_e.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto log2_e = functor<log2_e_t>;
}
