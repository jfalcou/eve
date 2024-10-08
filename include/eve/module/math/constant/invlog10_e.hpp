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
  struct invlog10_e_t : constant_callable<invlog10_e_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.26bb1cp+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.26bb1ap+1};
        else                                      return T{0x1.26bb1cp+1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.26bb1bbb55516p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.26bb1bbb55515p+1};
        else                                      return T{0x1.26bb1bbb55516p+1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(invlog10_e_t, invlog10_e_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var invlog10_e
  //!   @brief Callable object computing the constant \f$1/\log_{10}e\f$.
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
  //!      T invlog10_e(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::invlog10_e(as<T>())` returns the inverse of \f$\log_{10}e\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/invlog10_e.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto invlog10_e = functor<invlog10_e_t>;
}
