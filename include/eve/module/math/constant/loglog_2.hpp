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
  struct loglog_2_t : constant_callable<loglog_2_t, Options, lower_option, upper_option>
  {
    template<typename T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{-0x1.774f28p-2};
        else if constexpr (Opts::contains(lower)) return T{-0x1.774f2ap-2};
        else                                      return T{-0x1.774f2ap-2};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{-0x1.774f29bdd6b9ep-2};
        else if constexpr (Opts::contains(lower)) return T{-0x1.774f29bdd6b9fp-2};
        else                                      return T{-0x1.774f29bdd6b9fp-2};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(loglog_2_t, loglog_2_);
  };

//================================================================================================
//! @addtogroup math_constants
//! @{
//!   @var loglog_2
//!   @brief Callable object computing the constant \f$\log(\log2)\f$.
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
//!      T loglog_2(as<T> x) noexcept;
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
//!
//!    **Return value**
//!
//!      The call `eve::loglog_2(as<T>())` returns the logarithm of the logarithm of 2.
//!
//!  @groupheader{Example}
//!
//!  @godbolt{doc/math/regular/loglog_2.cpp}
//! @}
//================================================================================================
inline constexpr auto loglog_2 = functor<loglog_2_t>;
}
