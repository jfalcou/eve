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
#include <eve/module/core/regular/add.hpp>
#include <eve/module/core/regular/sub.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/regular/average.hpp>

namespace eve
{

  template<typename Options>
  struct neville_t : callable<neville_t, Options, pedantic_option>
  {

    template<eve::floating_value T0, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
      EVE_FORCEINLINE common_value_t<T0,  Ts...> constexpr operator()(T0 t0, Ts...ts) const  noexcept
    { return EVE_DISPATCH_CALL(t0, ts...); }

    template<eve::floating_value T0, eve::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup>) EVE_FORCEINLINE constexpr
     common_value_t<T0, kumi::apply_traits_t<eve::common_value, Tup>>  operator()(T0 x, Tup const& tup) const  noexcept
    { return EVE_DISPATCH_CALL(x, tup); }

    template<eve::floating_value T0, eve::non_empty_product_type Tup0, eve::non_empty_product_type Tup1>
    requires(eve::same_lanes_or_scalar_tuple<Tup0> && eve::same_lanes_or_scalar_tuple<Tup1>)
      EVE_FORCEINLINE constexpr
    common_value_t<T0,
                   kumi::apply_traits_t<eve::common_value, Tup0>,
                   kumi::apply_traits_t<eve::common_value, Tup1>
    >
    operator()(T0 x, Tup0 const& tup0, Tup1 const& tup1) const  noexcept
    { return EVE_DISPATCH_CALL(x, tup0, tup1); }

    EVE_CALLABLE_OBJECT(neville_t, neville_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var neville
//!   @brief `callable` computing the value of the interpolation polynomial \f$p\f$ of degree n, satisfying:
//!   /f$ p(x_i) = y_i for i = 0..n\f$
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
//!      constexpr auto neville(auto x, auto const& xs..., auto const& ys...)                                                    noexcept; // 1
//!      constexpr auto neville(auto x, eve::non_empty_product_type auto const& xx,  eve::non_empty_product_type auto const& yy) noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...`, `ys ...: [real](@ref eve::floating values) arguments
//!     * `xx`, `yy`       : kumi::tuple of arguments
//!
//!    **Return value**
//!
//!      * 1. Return the value at x of the polynomial \f$p\f$ of degree n, atisfying: /f$ p(x_i) = y_i for i = 0..n\f$ where n+1 is the common number of `xs`, `ys`.
//!      * 2. Same as 1., using the tuple elements.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia  neville's algorithm](https://en.wikipedia.org/wiki/Neville%27s_algorithm)
//!  @groupheader{Example}
//!  @godbolt{doc/core/neville.cpp}
//================================================================================================
  inline constexpr auto neville = functor<neville_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<floating_value T, floating_value... XsYs,  callable_options O>
    EVE_FORCEINLINE constexpr auto
    neville_(EVE_REQUIRES(cpu_), O const & o, T x, XsYs... xsys) noexcept
    requires(sizeof...(XsYs)%2 == 0)
     {
      constexpr auto siz = sizeof...(XsYs);
      constexpr auto siz_2 = siz/2;
      if constexpr(siz == 0) return eve::zero(eve::as<T>());
      else
      {
        using t_t =  eve::common_value_t<T, XsYs...>;
        auto xsyst = eve::zip(t_t(xsys)...);
        if constexpr(siz == 2) return get<0>(xsyst);
        else if constexpr(siz == 4)
        {
          auto x0 = get<0>(xsyst);
          auto x1 = get<1>(xsyst);
          auto y0 = get<2>(xsyst);
          auto y1 = get<3>(xsyst);
          return  eve::sum_of_prod[o]((x - x1), y0, (x0 - x), y1)/ (x0-x1);
        }
        else
        {
          std::array<t_t, siz> xy{t_t(xsys)...};
          for(size_t k=1; k < siz_2; ++k)
          {
            for(size_t i=0, is2 = siz_2; i < siz_2-k; ++i, ++is2)
            {
              xy[is2] = sum_of_prod[o]((x - xy[i+k]), xy[is2], (xy[i] - x), xy[is2+1])/(xy[i]-xy[i+k]);
            }
          }
          return xy[siz_2];
        }
      }
    }

    template<floating_value T,  eve::non_empty_product_type PT , callable_options O>
    EVE_FORCEINLINE constexpr auto
    neville_(EVE_REQUIRES(cpu_), O const & o, T x, PT tup) noexcept
    {
      return kumi::apply([x, o](auto ... m){return neville[o](x, m...); }, tup);
    }


    template<floating_value T,  eve::non_empty_product_type PT0,  eve::non_empty_product_type PT1 , callable_options O>
    EVE_FORCEINLINE constexpr auto
    neville_(EVE_REQUIRES(cpu_), O const & o, T x, PT0 tx, PT1 ty) noexcept
    requires(PT1::size() == PT0::size())
    {
      return kumi::apply([x, o](auto ... m){return neville[o](x, m...); }, cat(tx, ty));
    }
  }
}
