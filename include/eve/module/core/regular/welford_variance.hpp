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
    template<floating_value T> struct welford_variance_result
    {
      using type = T;
      operator T()   const noexcept { return variance; };
      auto upgrade() const noexcept { return welford_variance_result<upgrade_t<T>>(upgrade(count), count); };

      T average         = T(0);
      std::size_t count = 1;
      T m2              = T(0);
      T variance        = T(0);
    };

    template<typename>    struct is_welford_variance_result_helper                               :  std::false_type{};
    template<typename T>  struct is_welford_variance_result_helper<welford_variance_result<T>>   :  std::true_type{};
    template<typename T>  struct is_welford_variance_result                                      :  is_welford_variance_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_variance_result_v =  is_welford_variance_result<T>::value;

    // helper to treat in the same way values and welford_variance results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford_variance                             { using type = T;  };
    template < typename T> struct internal_welford_variance<welford_variance_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_variance_t = typename internal_welford_variance<T>::type;
  }

  template<typename Options>
  struct welford_variance_t : callable<welford_variance_t, Options, unbiased_option, widen_option>
  {

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_variance_t<Ts>...>  && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_variance_result<common_value_t<detail::internal_welford_variance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(sizeof...(Ts) !=  0 && eve::same_lanes_or_scalar<detail::internal_welford_variance_t<Ts>...>  && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_variance_result<upgrade_t<common_value_t<detail::internal_welford_variance_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

   template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_variance_result<upgrade_t<kumi::apply_traits_t<eve::common_value,Tup>>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    template<kumi::non_empty_product_type Tup>
    requires(eve::same_lanes_or_scalar_tuple<Tup> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_variance_result<kumi::apply_traits_t<eve::common_value,Tup>>
    operator()(Tup const& t) const noexcept
    { return EVE_DISPATCH_CALL(t); }

    EVE_CALLABLE_OBJECT(welford_variance_t, welford_variance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_variance
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
//!      constexpr auto welford_variance(auto x, auto ... xs)                  noexcept; /1
//!      constexpr auto welford_average(non_empty_product_type xs)             noexcept; /2
//!
//!      //Semantic options
//!      constexpr auto welford_variance[widen](/*any previous overloads*/)    noexcept; /3
//!      constexpr auto welford_variance[unbiased](/*any previous overloads*/) noexcept; /4
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`:the parameters can be a mix of floating values or previous results of calls to `welford_variance` or a tuple of them
//!
//!    **Return value**
//!
//!      1. A struct containing The value of the arithmetic mean (`average`), the centered  moment of order 2 (`m2`), the (sample) variance value
//!         normalized by the number of elements involved (`variance`)  and the number of elements (`count`) involved is returned.<br/>
//!         This struct is convertble to the variance floating value. and possess four fields `variance`, `average` `m2` and `count`.
//!      2. The computation is made on the tuples elements
//!      3. The computation and result use the upgraded data type if available
//!      4. with this option the normalisation is done by by the number of elements involved, minus one. This provides the
//!         best unbiased estimator of the variance (population variance).
//!
//!  @note The Welford algorithm does not provides as much option as the [`variance`](@ref variance) function, but is a quite stable algorithm
//!        that have the advantage to allow spliting the computation of the variance in
//!        multiple calls.  For instance: the call with two tuples:<br/>
//!        &nbsp;   `wv = welford_corariance(kumi::cat(xs, ys))`<br/>
//!        is equivalent to the sequence:<br/>
//!        &nbsp;  `wxs =  welford_variance(xs);  wys = welford_variance(xs); wv = welford_variance(wxs, wys);`<br/>
//!        But the first two instructions can easily be executed in parallel.
//!
//!  @groupheader{External references}
//!   *  [Wikipedia Mean](https://en.wikipedia.org/wiki/Mean)
//!   *  [Wikipedia Variance](https://en.wikipedia.org/wiki/Algorithms_for_calculating_variance)
//!   *  [E.Schubert and M. Gertz](https://ds.ifi.uni-heidelberg.de/files/Team/eschubert/publications/SSDBM18-covariance-authorcopy.pdf)
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/welford_variance.cpp}
//================================================================================================
  inline constexpr auto welford_variance = functor<welford_variance_t>;
//================================================================================================
//! @}
//================================================================================================

}

namespace eve::detail
{

  template<scalar_value T0, scalar_value ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_variance_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  requires(sizeof...(Ts)+1 >= wide<common_value_t<T0, Ts...>>::size())
  {
    auto scalarize = []<typename T>(T w){
      using e_t =  element_type_t<typename T::type>;
      auto getit = [w](auto i){return welford_variance_result<e_t>(w.average.get(i), w.count, w.m2.get(i), w.variance.get(i)); };
      return kumi::generate<w.average.size()>(getit);
    };

    using r_t =  common_value_t<T0, Ts...>;
    auto tup = kumi::make_tuple(a0, args...);
    constexpr auto siz = sizeof...(Ts)+1;
    constexpr auto nblanes = wide<r_t>::size();
    constexpr auto remain = siz % nblanes;
    auto [car, cdr] = kumi::split(tup,  kumi::index<remain>);
    auto head = as_wides(eve::zero(eve::as<r_t>()), cdr);
    auto wv = eve::welford_variance[o](head);
    auto swv = scalarize(wv);
    auto wvar1 = kumi::apply([](auto...m){return welford_variance(m...);}, swv);
    if constexpr(remain != 0)
      return eve::welford_variance(welford_variance(car), wvar1);
    else
      return wvar1;
  }

  template<typename T0, typename ... Ts, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_variance_(EVE_REQUIRES(cpu_), O const & o, T0 a0, Ts const &... args) noexcept
  {
    using r_t =  common_value_t<detail::internal_welford_variance_t<T0>,  detail::internal_welford_variance_t<Ts>...>;
    if constexpr(O::contains(widen))
    {
      auto up_it = [](auto a){
        if constexpr(requires { a.up(); }) return a.up();
        else return eve::upgrade(a);
      };
      return welford_variance[o.drop(widen)](up_it(a0), up_it(args)...);
    }
    else if constexpr(sizeof...(Ts) == 0)
    {
      if constexpr(value<T0>)
        return welford_variance_result<r_t>(a0);
      else
        return a0;
    }
    else if constexpr(value<T0>)
    {
      auto welford_a0 = welford_variance_result<r_t>(a0, 1);
      return welford_variance[o](welford_a0, args...);
    }
    else
    {
      auto na0 = welford_variance_result<r_t>(a0.average, a0.count, a0.m2, a0.variance);
      auto doit = [&na0](auto... as){
        auto welford_variancestep = [&na0](auto a)
        {
          if constexpr(value<decltype(a)>)
          {
            ++na0.count;
            auto delta = a-na0.average;
            na0.average  += delta/na0.count;
            na0.m2 += (a-na0.average)*delta;
            return na0;
          }
          else
          {
            auto nab = na0.count+a.count;
            auto avg = sum_of_prod(r_t(na0.count), na0.average, r_t(a.count), a.average)/nab;
            auto m2 = na0.m2+a.m2 + (na0.count*a.count)*eve::sqr(na0.average-a.average)/nab;
            return  welford_variance_result<r_t>(avg, nab, m2);
          }
        };
        ((na0 = welford_variancestep(as)),...);
        if constexpr(O::contains(unbiased))
          na0.variance = na0.m2/dec(na0.count);
        else
          na0.variance = na0.m2/na0.count;
        return na0;
      };
      return  doit(args...);
    }
  }


  template< kumi::non_empty_product_type T, callable_options O>
  EVE_FORCEINLINE constexpr auto
  welford_variance_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
  {
    return kumi::apply([o](auto... m){return welford_variance[o](m...); }, t);
  }
}
