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
#include <eve/module/core.hpp>

namespace eve
{
  template<typename Options>
  struct lentz_b_t : strict_elementwise_callable<lentz_b_t, Options>
  {
    template<typename G, floating_scalar_value T>
    constexpr EVE_FORCEINLINE auto operator()(G g, T e, std::size_t m) const noexcept
      -> as_wide_as_t<T, decltype(get<0>(g()))>
        requires (kumi::sized_product_type<decltype(g()), 2>)
    {
      return this->behavior(as<as_wide_as_t<T, decltype(get<0>(g()))>>{}, eve::current_api, this->options(), g, e, m);
    }

    template<typename G, floating_scalar_value T>
    constexpr EVE_FORCEINLINE auto operator()(G g, T e, std::size_t m) const noexcept
      -> as_wide_as_t<T, decltype(g())>
        requires (!kumi::product_type<decltype(g())>)
    {
      return this->behavior(as<as_wide_as_t<T, decltype(g())>>{}, eve::current_api, this->options(), g, e, m);
    }

    EVE_CALLABLE_OBJECT(lentz_b_t, lentz_b_);
  };

  //================================================================================================
  //! @addtogroup contfrac
  //! @{
  //!   @var lentz_b
  //!   @brief Implement the lentz scheme to evaluate continued fractions
  //!
  //!   **Defined in header**
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
  //!     template< typename Gen, eve::floating_value T> auto lentz_b(Gen g, const T& tol, size_t & max_terms) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `g`   : generator function.
  //!     * `tol` : tolerance value. If negative the effective tolerance will be abs(tol)*eve::eps(as(< u_t>)
  //!               where u_t is the underlying floating type associated to the return type of the invocable g.
  //!     * `max_terms` : no more than max_terms calls to the generator will be made.
  //!
  //!   The generator type should be an invocable  which supports the following operations:
  //!   *  The call to g()  returns a floating  value or a pair (kumi::tuple) of such.
  //!      Each time this operator is called then the next pair of a and b values  has to be returned,
  //!      or, if result_type is not a pair type, then the next b value
  //!       has to be returned and all the a values are assumed to be equal to one.
  //!
  //!   * In all the continued fraction evaluation functions the  effective tol parameter
  //!     is the relative precision desired in the result,
  //!     The evaluation of the fraction will continue until the last term evaluated leaves
  //!     the relative error in the result less than tolerance or the max_terms iteration is reached.
  //!
  //!   **Return value**
  //!
  //!     The value of the continued fraction is returned.
  //!     \f$\displaystyle b_0+\frac{a_1}{b_1+\frac{a_2}{b_2+\frac{a_3}{b_3+\cdots\vphantom{\frac{1}{1}} }}}\f$
  //!
  //!     Note that the the first a value (a0) generated is not used here.
  //!
  //!   @note the implementation is largely inspired by the boost/math/fraction one, with less requirements on the invocable.
  //!         Peculiarly lambda functions can be used.
  //!
  //!   @groupheader{Example}
  //!
  //!   @godbolt{doc/math/lentz_b.cpp}
  //!
  //================================================================================================
  inline constexpr auto lentz_b = functor<lentz_b_t>;
  //================================================================================================
  //! @}
  //================================================================================================
}

#include <eve/module/math/regular/impl/lentz.hpp>
