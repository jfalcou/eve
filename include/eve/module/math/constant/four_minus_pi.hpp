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
  struct four_minus_pi_t : constant_callable<four_minus_pi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.b7812cp-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.b7812ap-1};
        else                                      return T{0x1.b7812ap-1};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.b7812aeef4b9fp-1};
        else if constexpr (Opts::contains(lower)) return T{0x1.b7812aeef4b9ep-1};
        else                                      return T{0x1.b7812aeef4b9fp-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(four_minus_pi_t, four_minus_pi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var four_minus_pi
  //!   @brief Callable object computing the constant \f$4-\pi\f$.
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
  //!      T four_minus_pi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::four_minus_pi(as<T>())` returns \f$4-\pi\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/four_minus_pi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto four_minus_pi = functor<four_minus_pi_t>;
}
