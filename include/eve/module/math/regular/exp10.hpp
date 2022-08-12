//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math/constant/maxlog10.hpp>

namespace eve
{
  //================================================================================================
  //! @addtogroup math_exp
  //! @{
  //! @var exp10
  //!
  //! @brief Callable object computing  \f$10^x\f$.
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
  //!      T exp10(T x) noexcept;
  //!   }
  //!   @endcode
  //!
  //! **Parameters**
  //!
  //!    `x`:   [floating real value](@ref eve::floating_real_value).
  //!
  //! **Return value**
  //!
  //!    Returns the [elementwise](@ref glossary_elementwise) exponential of base 10 of the input.
  //!    In particular, for floating inputs:
  //!
  //!     * If the element is \f$\pm0\f$, \f$1\f$ is returned
  //!     * If the element is \f$-\infty\f$, \f$+0\f$ is returned
  //!     * If the element is \f$\infty\f$, \f$\infty\f$ is returned
  //!     * If the element is a `NaN`, `NaN` is returned
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/math/exp10.cpp}
  //!
  //!  @groupheader{Semantic Modifiers}
  //!
  //!   * Masked Call
  //!
  //!     The call `eve::exp10[mask](x)` provides a masked version of `eve::exp10` which is
  //!     equivalent to `if_else (mask, exp10(x), x)`.
  //!
  //!      **Example**
  //!
  //!        @godbolt{doc/math/masked/exp10.cpp}
  //!  @}
  //================================================================================================
  namespace tag { struct exp10_; }

  namespace detail
  {
    template<typename T, typename S>
    EVE_FORCEINLINE void check(EVE_MATCH_CALL(eve::tag::exp10_), T const&, [[maybe_unused]] S const& s)
    {
      using vt_t = element_type_t<T>;
      if constexpr(std::is_integral_v<vt_t>)
      {
        EVE_ASSERT( eve::all(is_gez(s)),
                    "[eve::exp10] - with integral entries the parameter element(s) must be greater then 0"
                  );
        EVE_ASSERT( eve::all(is_less(s, maxlog10(eve::as<T>()))),
                    "[eve::exp10]  - overflow caused by too large integral entry"
                  );
      }
    }
  }

  EVE_MAKE_CALLABLE(exp10_, exp10);
}

#include <eve/module/math/regular/impl/exp10.hpp>
