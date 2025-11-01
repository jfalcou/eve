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
#include <eve/module/core/regular/sum_of_prod.hpp>
#include <eve/module/core/regular/two_fma_approx.hpp>
#include <eve/module/core/regular/fma.hpp>

namespace eve
{

  namespace detail
  {
    template<floating_value T> struct welford_result
    {
      using type = T;
      operator T()   const noexcept { return average; };
      auto upgrade() const noexcept { return welford_result<upgrade_t<T>>(upgrade(count), count); };

      T average = 0;
      std::size_t count = 1;
    };

    template<typename>    struct is_welford_result_helper                      : public std::false_type{};
    template<typename T>  struct is_welford_result_helper<welford_result<T>>   : public std::true_type{};
    template<typename T>  struct is_welford_result                             : public is_welford_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_result_v =  is_welford_result<T>::value;

    // helper to treat in the same way values and welford results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford                    { using type = T;  };
    template < typename T> struct internal_welford<welford_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_t = typename internal_welford<T>::type;
  }

  template<typename Options>
  struct welford_average_t : callable<welford_average_t, Options, widen_option>
  {

//     template<typename... Ts>
//     requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>  && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr detail::welford_result<common_value_t<detail::internal_welford_t<Ts>...>>
//     operator()(Ts...ts) const noexcept
//     {
//       return EVE_DISPATCH_CALL(ts...);
//     }

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_t<Ts>...>)//  && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_result<upgrade_if_t<Options, common_value_t<detail::internal_welford_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

   template<kumi::non_empty_product_type Tup>
   requires(eve::same_lanes_or_scalar_tuple<Tup>)// && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_result<upgrade_if_t<Options, kumi::apply_traits_t<eve::common_value,Tup>>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

//     template<kumi::non_empty_product_type Tup>
//     requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
//       EVE_FORCEINLINE constexpr
//     detail::welford_result<kumi::apply_traits_t<eve::common_value,Tup>>
//     operator()(Tup const& t) const noexcept
//     { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(welford_average_t, welford_average_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_average
//!   @brief `tuple_callable` computing the arithmetic mean of its arguments.
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
//!      constexpr auto welford_average(auto ... xs)                        noexcept; //1
//!      constexpr auto welford_average(non_empty_product_type xs)          noexcept; //2
//!
//!      //Semantic options
//!      constexpr auto welford_average[widen](/*any previous overload*/)   noexcept; //3
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * ``xs...`:the parameters can be a mix of floating values and previous results of calls to `welford_average`
//!
//!    **Return value**
//!
//!       1. A struct containing The value of the arithmetic mean and the number
//!          of elements on which the mean was calculated is returned.
//!
//!          This struct is convertible to the average floating value. and possess two fields `average` and `count`.
//!       2. The computation on the tuple elements
//!       3. The computation and result use the upgraded data type if available
//!
//!  @note The Welford algorithm does not provides as much option as the [`average`](@ref average) function, but is a quite stable algorithm
//!        that have the advantage to allow spliting the computation of the average in
//!        multiple calls.  For instance: the call with two tuples:<br/>
//!        &nbsp;   `wavg = welford_average(kumi::cat(xs, ys))`<br/>
//!        is equivalent to the sequence:<br/>
//!        &nbsp;  `wxs =  welford_average(xs);  wys = welford_average(xs); wavg = welford_average(wxs, wys);`<br/>
//!        But the first two instructions can easily be executed in parallel.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!   *  [Wikipedia Variance](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/welford_average.cpp}
//================================================================================================
  inline constexpr auto welford_average = functor<welford_average_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{

  template<scalar_value T0, scalar_value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_average_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  requires(sizeof...(Ts)+1 >= wide<common_value_t<T0, Ts...>>::size())
  {
    using r_t =  common_value_t<T0, Ts...>;
    auto tup = kumi::make_tuple(a0, args...);
    constexpr auto siz = sizeof...(Ts)+1;
    constexpr auto nblanes = wide<r_t>::size();
    constexpr auto remain = siz % nblanes;
    auto [car, cdr] = kumi::split(tup,  kumi::index<remain>);
    auto head = as_wides(eve::zero(eve::as<r_t>()), cdr);
    auto s = eve::welford_average[o](head);
    auto wavg1 = welford_result(sum(s.average)/nblanes, s.count*nblanes);
    if constexpr(remain != 0)
      return eve::welford_average(welford_average(car), wavg1);
    else
      return wavg1;
  }


  template<typename T0, typename ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_average_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  {
    using r_t =  common_value_t<detail::internal_welford_t<T0>,  detail::internal_welford_t<Ts>...>;
    if constexpr(O::contains(widen))
    {
      auto up_it = [](auto a){
        if constexpr(requires { a.up(); }) return a.up();
        else return eve::upgrade(a);
      };
      return welford_average[o.drop(widen)](up_it(a0), up_it(args)...);
    }
    else
    {
      if constexpr(sizeof...(Ts) == 0)
      {
        if constexpr(value<T0>)
          return welford_result<r_t>(a0);
        else
          return a0;
      }
      else if constexpr(value<T0>)
      {
        auto wa0 = welford_result<r_t>(a0, 1u);
        return welford_average[o](wa0, args...);
      }
      else
      {
        auto na0 = welford_result<r_t>(a0.average, a0.count);
        auto doit = [&na0](auto... as){
          auto welfordstep = [&na0](auto a)
          {
            if constexpr(value<decltype(a)>)
            {
              ++na0.count;
              na0.average += (a-na0.average)/na0.count;
              return na0;
            }
            else
            {
              auto nab = na0.count+a.count;
              auto avg = sum_of_prod(r_t(na0.count), na0.average, r_t(a.count), a.average)/nab;
              return  welford_result<r_t>(avg, nab);
            }
          };
          ((na0 = welfordstep(as)),...);
          return na0;
        };
        return  doit(args...);
      }
    }
  }

  template< kumi::non_empty_product_type T, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_average_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
  {
    return kumi::apply([o](auto... m){return welford_average[o](m...); }, t);
  }
}
