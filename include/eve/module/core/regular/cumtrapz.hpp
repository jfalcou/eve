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
#include <eve/traits/updown.hpp>
#include <eve/module/core/regular/average.hpp>
#include <eve/module/core/regular/cumsum.hpp>
#include <iostream>

namespace eve
{
  template<typename Options>
  struct cumtrapz_t : callable<cumtrapz_t, Options, widen_option>
  {
    template<typename T>
    using return_type = eve::element_type_t<eve::upgrade_if_t<Options,T>>;

    template<value... Ts>
    using result = kumi::result::fill_t<sizeof...(Ts), return_type<eve::common_value_t<Ts...>>>;

    template<product_type T>
    using tuple_result = kumi::result::fill_t< T::size() , return_type<kumi::apply_traits_t<eve::common_value, T>>>;

    template<value T, value ...Ts>
    EVE_FORCEINLINE constexpr result<T, Ts...>
    operator()(T t, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(t, ts...);
    }

    template<non_empty_product_type T>
    EVE_FORCEINLINE constexpr tuple_result<T>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(cumtrapz_t, cumtrapz_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cumtrapz
///!   @brief `callable` converting a pack of values into
//!     a tuple of the cumulative trapz of its values.
//!
//!   @groupheader{Header file}
//!
//!   @code
//!   #include <eve/module/core.hpp>
//!   @endcode
//!
//!   @groupheader{Callable Signatures}
//!
//!   @code
//!   namespace eve
//!   {
//!      // Regular overloads
//!      constexpr auto trapz(eve::non_empty_product_type auto const& x,
//!                           eve::non_empty_product_type auto const& y)                   noexcept; // 1
//!      constexpr auto trapz(floating_value auto ... ys)                                   noexcept; // 2
//!      constexpr auto trapz(eve::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(floating_value h,
//!                           eve::non_empty_product_type auto const& y)                   noexcept; // 2
//!      constexpr auto trapz(eve::invocable f, floating_value auto ... xs)                 noexcept; // 4
//!      constexpr auto trapz(eve::invocable f, eve::non_empty_product_type auto const& x) noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto trapz[widen](/*any of the above overloads*/)                        noexcept; // 4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `x`,     : [tuple of real](@ref eve::floating values) ordered arguments in increasing order.
//!     * `y`      : tuple of real arguments
//!     * `h`      : floating value scaling the abscissas
//!     * `f`      : invocable
//!
//!
//!    **Return value**
//!
//!     1. return a kumi tuple of the values of the cumulated trapz of all `xs` converted to
//!         the element type of the common value of the `xs`. the xs have to be sorted in ascending order.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but upgrading the elements of the result.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cumtrapz.cpp}
//================================================================================================
  inline constexpr auto cumtrapz = functor<cumtrapz_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template <eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumtrapz_(EVE_REQUIRES(cpu_), O const & , PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else
      {
        if constexpr(PT::size() == 0)
          return kumi::make_tuple();
        else
        {
          using c_t = kumi::apply_traits_t<eve::common_value, PT>;
          using r_t = eve::upgrade_if_t<O, c_t>;
          auto constexpr SZ = PT::size();
          using a_t = std::array<r_t, SZ>;
          auto cvt =  []<typename Y>(Y y){
            if constexpr(O::contains(widen)) return upgrade(r_t(y));
            else                             return r_t(y);
          };
          a_t a =  std::bit_cast<a_t>(tup);
          a_t b;
          b[0] = 0;
          for(std::size_t i=1; i < SZ; ++i) b[i] = b[i-1]+eve::average(a[i-1], a[i]);
          return (std::bit_cast<PT>(b));
        }
      }
    }

    template<value T, value ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cumtrapz_(EVE_REQUIRES(cpu_), O const & o, T t0, Ts... ts) noexcept
    {
      return eve::cumtrapz[o](kumi::make_tuple(t0, ts...));
    }

  }
}
