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
  struct phi_t : constant_callable<phi_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.9e377cp+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.9e377ap+0};
        else                                      return T{0x1.9e377ap+0};
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.9e3779b97f4a8p+0};
        else if constexpr (Opts::contains(lower)) return T{0x1.9e3779b97f4a7p+0};
        else                                      return T{0x1.9e3779b97f4a8p+0};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return EVE_DISPATCH_CALL_PT(T, v);
    }

    EVE_CALLABLE_OBJECT(phi_t, phi_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var phi
  //!   @brief Callable object computing the golden ratio : \f$\frac{1+\sqrt5}2\f$.
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
  //!      T phi(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::phi(as<T>())` returns the golden ratio.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/phi.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto phi = functor<phi_t>;
}
