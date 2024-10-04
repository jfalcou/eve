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
  struct invsqrt_2_t : constant_callable<invsqrt_2_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr(Opts::contains(upper)) return T{0x1.6a09e8p-1};
        else if constexpr(Opts::contains(lower)) return T{0x1.6a09e6p-1};
        else                                     return T{0x1.6a09e6p-1};
      }
      else
      {
        if      constexpr(Opts::contains(upper)) return T{0x1.6a09e667f3bcdp-1};
        else if constexpr(Opts::contains(lower)) return T{0x1.6a09e667f3bccp-1};
        else                                     return T{0x1.6a09e667f3bcdp-1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(invsqrt_2_t, invsqrt_2_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var invsqrt_2
  //!   @brief Callable object computing the constant \f$2^{-1/2}\f$.
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
  //!      T invsqrt_2(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::invsqrt_2(as<T>())` returns the inverse of \f$\sqrt{2}\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/invsqrt_2.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto invsqrt_2 = functor<invsqrt_2_t>;
}
