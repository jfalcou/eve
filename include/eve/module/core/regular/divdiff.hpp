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
  struct divdiff_t : callable<divdiff_t, Options, widen_option>
  {

    template<typename F, eve::floating_value T0, floating_value... Ts>
    requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
      EVE_FORCEINLINE auto constexpr operator()(F f, T0 t0, Ts...ts) const -> decltype(kumi::tuple{ts...})// const noexcept
    { return EVE_DISPATCH_CALL(f, t0, ts...); }

//     template<typename F, eve::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup>) EVE_FORCEINLINE constexpr
//     kumi::apply_traits_t<eve::common_value_t, Tup>  operator()(F f, Tup const& x) const  noexcept
//     { return EVE_DISPATCH_CALL(f, x); }

    //    template<size_t N, eve::floating_value T0, floating_value... Ts>
//     requires(eve::same_lanes_or_scalar<Ts...> && (sizeof...(Ts) > 1))
//       EVE_FORCEINLINE auto constexpr operator()(kumi::index_t<N> n, T0 t0, Ts...ts) const
//       -> decltype(kumi::split(kumi::tuple(t0, ts...), sizeof...(ts)-N+1))//  noexcept
//     { return EVE_DISPATCH_CALL(n, t0, ts...); }

//     template<size_t N, eve::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup>)
//       EVE_FORCEINLINE constexpr
//     auto  operator()( kumi::index_t<N>, Tup  y,Tup x) const
//       -> std::decay_t<decltype(get<0>(kumi::split(y, kumi::index_t<kumi::size_v<Tup>-N>{})))> const// noexcept
//     { return EVE_DISPATCH_CALL(kumi::index_t<N>{}, y, x); }

    EVE_CALLABLE_OBJECT(divdiff_t, divdiff_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var divdiff
//!   @brief `tuple_callable` computing the nth  adjacent divdifferences of its arguments.
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
//!      constexpr auto divdiff(eve::floating_value auto const& xs...)                                        noexcept; // 1
//!      constexpr auto divdiff(eve::non_empty_product_type auto const& x)                                    noexcept; // 1
//!      typename<auto N> constexpr auto divdiff(kumi::index_t<N>, eve::floating_value auto const& xs...)     noexcept; // 2
//!      typename<auto N> constexpr auto divdiff(kumi::index_t<N>,eve::non_empty_product_type auto const& x)  noexcept; // 2
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs ...` : [real](@ref eve::floating values) arguments
//!     * `x`      : kumi::tuple of arguments
//!
//!    **Return value**
//!
//!      * 1. Return a tuple containing the elementwise adjacent divdifferences of the parameters or of the elements of the tuple.
//!      * 2. Return a tuple containing the elementwise Nth adjacent divdifferences of the parameters or of the elements of the tuple.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia divided divdifferences](https://en.cppreference.com/w/cpp/types/integral_constant.html)
//!  @groupheader{Example}
//!  @godbolt{doc/core/divdiff.cpp}
//================================================================================================
  inline constexpr auto divdiff = functor<divdiff_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {
 //    template<typename F, eve::non_empty_product_type PT , callable_options O>
//     EVE_FORCEINLINE constexpr auto
//     divdiff_(EVE_REQUIRES(cpu_), O const & o, F f, PT t) noexcept
//     {
//       if constexpr(O::contains(widen))
//         return divdiff[o.drop(widen)](f, kumi::map(upgrade, t));
//       else
//       {
//         using e_t = decltype(get<0>(t));
//         if constexpr (kumi::size_v<PT> == 1) return zero(as<e_t>());
//         else if constexpr (kumi::size_v<PT> == 2)
//         {
//           auto t0 =  get<0>(t);
//           auto t1 =  get<0>(t);
//           return  (f(t0) - f(t1)) / (t0 - t1);
//         }
//         else
//         {
//           auto inner =  [f]<typename Tup, std::size_t...Is>(Tup tup, std::index_sequence<Is...>){
//             return divdiff(f, kumi::tuple(std::get<Is...>(tup)));
//           };
//           using next_index_sequence = std::make_index_sequence<kumi::size_v<PT>-1>;
//           auto t0 = std::get<0>(t);
//           auto tn = std::get<kumi::size_v<PT>-1>(t);
//           return (inner(t, next_index_sequence{}) - divdiff(f, kumi::pop_front(t)))/(t0 - tn);
//         }
//       }

    template <typename F, typename T, std::size_t... Is>
    auto inner(F f, T arg_tuple, std::index_sequence<Is...>) {
      return divdiff(f, kumi::get<Is>(arg_tuple)...);
    }

    template<typename F, floating_value T0, floating_value... Ts,  callable_options O>
    EVE_FORCEINLINE constexpr auto
    divdiff_(EVE_REQUIRES(cpu_), O const & o, F f, T0 t0, Ts... ts) noexcept
    {
      using r_t =  eve::common_value_t<T0, Ts...>;
      if constexpr(O::contains(widen))
        return divdiff[o.drop(widen)](upgrade(r_t(ts))...);
      else
      {
        constexpr auto siz = sizeof...(Ts);
        if constexpr(siz == 0) return zero(as<r_t>());
        else if constexpr(siz == 1)
        {
          auto t1 =  get<0>(ts...);
          return  (f(t0) - f(t1)) / (t0 - t1);
        }
        else
        {
          auto ts_tuple = kumi::make_tuple(t0, ts...);
//           auto inner =  [f, ts_tuple]<std::size_t...Is>(std::index_sequence<Is...>){
//             return divdiff(f, kumi::get<Is>(ts_tuple)...);
//           };

          using next_index_sequence = std::make_index_sequence<siz>;
          auto tn = kumi::get<siz>(ts_tuple);
          return (inner(f, ts_tuple, next_index_sequence{}) - divdiff(f,ts...))/(t0 - tn);
        }
      }
    }

//     template<size_t N, eve::non_empty_product_type PT , callable_options O>
//     EVE_FORCEINLINE constexpr auto
//     divdiff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, PT & x) noexcept
//     {
//       if constexpr(O::contains(widen))
//         return divdiff[o.drop(widen)](n, kumi::map(upgrade, x));
//       else
//         if constexpr(N >= kumi::size_v<PT>) return kumi::tuple{};
//         else if constexpr(N == 0)           return x;
//         else if constexpr(N == 1)           return divdiff(x);
//         else                                return divdiff(kumi::index_t<N-1>{}, divdiff(x));
//     }

//     template<size_t N, floating_value... Ts, callable_options O>
//     EVE_FORCEINLINE constexpr auto
//     divdiff_(EVE_REQUIRES(cpu_), O const & o, kumi::index_t<N> n, Ts... args) noexcept
//     {
//       using r_t =  eve::common_value_t<Ts...>;
//       if constexpr(O::contains(widen))
//         return divdiff[o.drop(widen)](upgrade(r_t(args))...);
//       else
//         return eve::divdiff[o](n, kumi::make_tuple(args...));
//     }
//    }

  }
}
