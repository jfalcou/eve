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
  struct invlog10_2_t : constant_callable<invlog10_2_t, Options, lower_option, upper_option>
  {
    template<floating_value T, typename Opts>
    static EVE_FORCEINLINE constexpr T value(as<T>, Opts const&)
    {
      if constexpr (std::same_as<T, float>)
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.a934f2p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.a934fp+1 };
        else                                      return T{0x1.a934fp+1 };
      }
      else
      {
        if      constexpr (Opts::contains(upper)) return T{0x1.a934f0979a372p+1};
        else if constexpr (Opts::contains(lower)) return T{0x1.a934f0979a371p+1};
        else                                      return T{0x1.a934f0979a371p+1};
      }
    }

    template<floating_value T>
    EVE_FORCEINLINE constexpr T operator()(as<T> v) const
    {
      return this->behavior(as<T>{}, eve::current_api, this->options(), v);
    }

    EVE_CALLABLE_OBJECT(invlog10_2_t, invlog10_2_);
  };

  //================================================================================================
  //! @addtogroup math_constants
  //! @{
  //!   @var invlog10_2
  //!   @brief Callable object computing the constant \f$1/\log_{10}2\f$.
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
  //!      T invlog10_2(as<T> x) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `x` :  [Type wrapper](@ref eve::as) instance embedding the type of the constant.
  //!
  //!    **Return value**
  //!
  //!      The call `eve::invlog10_2(as<T>{})` returns the inverse of \f$\log_{10}2\f$.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/regular/invlog10_2.cpp}
  //! @}
  //================================================================================================
  inline constexpr auto invlog10_2 = functor<invlog10_2_t>;
}
