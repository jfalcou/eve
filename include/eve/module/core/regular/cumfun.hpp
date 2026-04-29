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
#include <eve/module/core/detail/tuple_array_utils.hpp>
#include <eve/module/core/regular/scan.hpp>
#include <eve/module/core/regular/unfold.hpp>

namespace eve
{
  template<typename Options>
  struct cumfun_t : callable<cumfun_t, Options, widen_option, saturated_option>
  {
    template<typename T>
    using return_type = eve::upgrade_if_t<Options,T>;

    template<value... Ts>
    using result = kumi::result::fill_t<sizeof...(Ts), return_type<eve::common_value_t<Ts...>>>;

    template<product_type T>
    using tuple_result = kumi::result::fill_t< T::size() , return_type<kumi::apply_traits_t<eve::common_value, T>>>;

    template<typename F, value T, value ...Ts>
    EVE_FORCEINLINE constexpr result<T, Ts...>
    operator()(F f, T t, Ts ... ts) const noexcept
    {
      return EVE_DISPATCH_CALL(f, t, ts...);
    }

    template<typename F, non_empty_product_type PT>
    EVE_FORCEINLINE constexpr tuple_result<PT>
    operator()(  F f, PT t) const noexcept
    {
      return EVE_DISPATCH_CALL(f, t);
    }

    EVE_CALLABLE_OBJECT(cumfun_t, cumfun_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var cumfun
///!   @brief `callable` converting a pack of values into
//!     a tuple of the cumulative application of a two parameter function to its values.
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
//!      constexpr auto cumfun(typename f, eve::value auto ... xs)     noexcept; // 1
//!      constexpr auto cumfun(typename f, non_empty_product_type tup) noexcept; // 2
//!
//!      // Semantic options
//!      constexpr auto cumfun[widen](/*any of the above overloads*/)  noexcept; // 3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `f`: invocable of two arguments.
//!     * `x`: [value](@ref eve::value) arguments.
//!     * `xs...`: [values](@ref eve::value) arguments.
//!     * `tup`: kumi tuple of values.
//!
//!    **Return value**
//!
//!     1. return a kumi tuple of the values of the cumulated values of all `xs` converted to
//!         the element type of the common value of the `xs` using f.
//!     2. same as 1., using the tuple elements.
//!     3. same of 1. or 2., but the computation is made on upgraded elements.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/cumfun.cpp}
//================================================================================================
  inline constexpr auto cumfun = functor<cumfun_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace _
  {

    template <typename F, eve::product_type PT, callable_options O>
    EVE_FORCEINLINE constexpr auto cumfun_(EVE_REQUIRES(cpu_), O const & o, F f, PT tup) noexcept
    {
      if constexpr(PT::size() == 0)
        return kumi::make_tuple();
      else if constexpr(O::contains(widen))
        return cumfun[o.drop(widen)](f, upg(tup));
      else
      {
        using e_t =  kumi::apply_traits_t<eve::common_value, PT>;
        auto n = neutral(f)(eve::as<e_t>());
        if constexpr(scalar_value<e_t>)
        {
          using w_t = eve::wide<e_t>;
          constexpr auto Last = w_t::size()-1;
          if constexpr((PT::size() > Last) && !O::contains(saturated))
          {
            auto head = eve::as_wides(eve::zero(eve::as<e_t>()), tup);
            auto sc =  [ n, f, o](auto h){return eve::scan(h, f[o], n); };
            auto xxx = kumi::map(sc, head);
            auto yyy = kumi::exclusive_scan_left([f, o](auto nn, auto x)
                                                 { return f[o](nn, x.get(Last)); }
                                                , xxx, n);
            auto r = kumi::map(f[o], xxx, yyy);
            return  kumi::extract(eve::unfold(r),  kumi::index_t<0>(), kumi::index_t<PT::size()>());;
          }
          else
          {
            return kumi::inclusive_scan_left(f[o], tup, n);
          }
        }
        else
        {
          return kumi::inclusive_scan_left(f[o], tup, n);
        }
      }
    }

    template<typename F, value T, value ...Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    cumfun_(EVE_REQUIRES(cpu_), O const & o, F f, T t0, Ts... ts) noexcept
    {
      return eve::cumfun[o](f, kumi::make_tuple(t0, ts...));
    }

  }
}
