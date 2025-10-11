//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/arch.hpp>
#include <eve/detail/overload.hpp>
#include <eve/module/core/regular/dot.hpp>
#include <eve/module/core/decorator/core.hpp>

namespace eve
{

  namespace detail
  {
    template<floating_value T> struct welford_covariance_result
    {
      using type = T;
      operator T()   const noexcept { return covariance; };
      auto upgrade() const noexcept { return welford_covariance_result<upgrade_t<T>>(upgrade(count), count); };

      T averagex         = T(0);
      T averagey         = T(0);
      std::size_t count  = 0;
      T mxy              = T(0);
      T covariance       = T(0);
    };

    template<typename>    struct is_welford_covariance_result_helper                               : public std::false_type{};
    template<typename T>  struct is_welford_covariance_result_helper<welford_covariance_result<T>> : public std::true_type{};
    template<typename T>  struct is_welford_covariance_result                                      : public is_welford_covariance_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_covariance_result_v =  is_welford_covariance_result<T>::value;

    // helper to treat in the same way values and welford_covariance results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford_covariance                               { using type = T;  };
    template < typename T> struct internal_welford_covariance<welford_covariance_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_covariance_t = typename internal_welford_covariance<T>::type;
  }

  template<typename Options>
  struct welford_covariance_t : callable<welford_covariance_t, Options, widen_option, unbiased_option>
  {

    template<typename... Ts>
    requires(simd_value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(simd_value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && Options::contains(widen))
       EVE_FORCEINLINE constexpr detail::welford_covariance_result<upgrade_t<common_value_t<detail::internal_welford_covariance_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(scalar_value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires(scalar_value<common_value_t<Ts...>> && (sizeof...(Ts) !=  0) && Options::contains(widen))
       EVE_FORCEINLINE constexpr detail::welford_covariance_result<upgrade_t<common_value_t<detail::internal_welford_covariance_t<Ts>...>>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires((detail::is_welford_covariance_result_v<Ts > && ...) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename... Ts>
    requires((detail::is_welford_covariance_result_v<Ts> && ...) && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<common_value_t<detail::internal_welford_covariance_t<Ts>...>>
    operator()(Ts...ts) const noexcept
     {
      return EVE_DISPATCH_CALL(ts...);
    }

    template<typename T>
    requires(detail::is_welford_covariance_result_v<T> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<element_type_t<detail::internal_welford_covariance_t<T>>>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    template<typename T>
    requires(detail::is_welford_covariance_result_v<T> && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_covariance_result<detail::internal_welford_covariance_t<element_type_t<upgrade_t<T>>>>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_covariance_result<kumi::apply_traits_t<eve::common_value, Tup1>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept
    { return EVE_DISPATCH_CALL(t1, t2); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_covariance_result<upgrade_t<kumi::apply_traits_t<eve::common_value, Tup1>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept
    { return EVE_DISPATCH_CALL(t1, t2); }



    EVE_CALLABLE_OBJECT(welford_covariance_t, welford_covariance_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_covariance
//!   @brief `elementwise_callable` object computing the elementwise  welford_covariance product
//!     of the vector of the first half parameter by thevector of the last half.
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
//!      constexpr auto welford_covariance(auto value ... xs, auto value ... ys)      noexcept; // 1
//!      constexpr auto welford_covariance(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!      constexpr auto welford_covariance(auto wcs...)                               noexcept; // 3
//!      constexpr auto welford_covariance(kumi;::tuple wcs)                          noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto welford_covariance[widen]   (/*any of the above overloads*/)  noexcept; // 5
//!      constexpr auto welford_covariance[unbiased](/*any of the above overloads*/)  noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  : [arguments](@ref eve::value) or tuple of them.
//!     * `wcs`       : [arguments](@ref eve::value) or tuple of them. The arguments must all be results
//!                      of previous `welford_covariance` calls,
//!    **Return value**
//!
//!      1. A struct containing The value of the arithmetic means (`averagex` and `averagey` ),
//!         the centered cross moment of order 2 (`mxy`), the (sample) covariance value
//!         normalized by the number of elements involved (`covariance`)
//!         and the number of elements (`count`) involved is returned.<br/>
//!         This struct is convertible to the covariance floating value. and possess four fields `covariance`,
//!          `averagex`, `averagey`, `mxy` and `count`.
//!      2. The computation is made on the tuples elements.
//!      3. The parameters are composed in a unique covariance struct as if the covariance was  computed on the whole original data set.
//!         Moreover if only one covariance result simd parameter is present, the the lanes individual corariance are grouped in an unique
//!         scalar covariance result, computed from all the datas of all the lanes.
//!      4. same as 3. on the tuple elements.
//!      5. the computation is done in the upgraded element type.
//!      6. with this option the normalisation is done by the number of elements involved, minus one.
//!
//!  @note The Welford algorithm does not provides as much option as the [`covariance`](@ref covariance) function, but is a quite stable algorithm
//!        that have the advantage to allow spliting the computation of the covariance in
//!        multiple calls.  For instance: the call with four tuples:<br/>
//!        &nbsp;   `cwv = welford_corariance(kumi::cat(xs, ys), kumi::cat(ws, zs))`<br/>
//!        is equivalent to the sequence:<br/>
//!        &nbsp;  `cwxs =  welford_covariance(xs, ws);  cwys = welford_covariance(ys, zs)); cwv = welford_covariance(wxs, wys);`<br/>
//!        But the first two instructions can easily be executed in parallel.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/welford_covariance.cpp}
//================================================================================================
  inline constexpr auto welford_covariance = functor<welford_covariance_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    // this call computes the welford covariance from a sequence of floating values xs then ys parameters
    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    welford_covariance_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    requires( (sizeof...(Ts) > 0) &&
              (sizeof...(Ts)%2 == 0) &&
              (simd_value<eve::common_value_t<Ts...>> ||
               (scalar_value<eve::common_value_t<Ts...>>  && (sizeof...(Ts) < 2*wide<common_value_t<Ts...>>::size()))
              )
            )
    {
      constexpr auto siz = sizeof...(Ts)/2;
      using r_t =  eve::common_value_t<Ts...>;
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_covariance[o.drop(widen)](up_it(args)...);
      }
      else
      {
        auto[f,s]   = kumi::split(kumi::make_tuple(args...), kumi::index<siz>);
        auto ncov = welford_covariance_result<r_t>();
        auto doit = [&ncov, &f, &s](){
          auto welford_covariancestep = [&ncov](auto xnyn)
          {
            auto [xn, yn] = xnyn;
            ++ncov.count;
            auto deltay = yn-ncov.averagey;
            ncov.averagey  += deltay/ncov.count;
            ncov.mxy += (xn-ncov.averagex)*(yn-ncov.averagey);
            auto deltax = xn-ncov.averagex;
            ncov.averagex  += deltax/ncov.count;
            return ncov;
          };
          auto r = kumi::map([](auto xs,  auto ys){return eve::zip(xs, ys); }, f, s);
          kumi::apply([welford_covariancestep](auto ... xsys){((welford_covariancestep(xsys)), ...); }, r);
          if constexpr(O::contains(unbiased)) ncov.covariance = ncov.mxy/dec(ncov.count);
          else                                ncov.covariance = ncov.mxy/ncov.count;
          return ncov;
        };
        return  doit();
      }
    }

    // This call compute the join covariance from previously computed welford covariances
    template<typename T, typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_covariance_(EVE_REQUIRES(cpu_), O const & o, T t, Ts... args) noexcept
    requires((sizeof...(Ts)!= 0) && detail::is_welford_covariance_result_v<T> && (detail::is_welford_covariance_result_v<Ts> && ...))
    {
      using r_t =  common_value_t<detail::internal_welford_covariance_t<T>, detail::internal_welford_covariance_t<Ts>...>;
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_covariance[o.drop(widen)](up_it(t), up_it(args)...);
      }
      else
      {
        T ncov = t;
        auto doit = [ & ](){
          auto welford_covariancestep = [&](auto cov)
          {
            auto nab = ncov.count+cov.count;
            auto avgx = sum_of_prod(r_t(ncov.count), ncov.averagex, r_t(cov.count), cov.averagex)/nab;
            auto avgy = sum_of_prod(r_t(ncov.count), ncov.averagey, r_t(cov.count), cov.averagey)/nab;
            auto mxy = cov.mxy+ncov.mxy+((ncov.averagex-cov.averagex)*(ncov.averagey-cov.averagey)*cov.count*ncov.count)/nab;
            ncov = welford_covariance_result(avgx, avgy, nab, mxy);
            return ncov;
          };
          ((ncov = welford_covariancestep(args)),...);
          if constexpr(O::contains(unbiased)) ncov.covariance = ncov.mxy/dec(ncov.count);
          else                                ncov.covariance = ncov.mxy/ncov.count;
          return ncov;
        };
        return  doit();
      }
    }

    // This call 'scalarize' a welford covariance
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_covariance_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
    requires(detail::is_welford_covariance_result_v<T>)
    {
      auto scalarize = []<typename U>(U w){
        using e_t =  element_type_t<typename U::type>;
        auto getit = [w](auto i){return welford_covariance_result<e_t>(w.averagex.get(i), w.averagey.get(i), w.count, w.mxy.get(i), w.covariance.get(i)); };
        return kumi::generate<w.averagex.size()>(getit);
      };
      if constexpr(scalar_value<typename T::type>)
        return t;
      else
      {
        auto tpsc =  scalarize(t);
        return kumi::apply([o](auto... m){return welford_covariance[o](m...); }, tpsc);
      }
    }

    // This call treat the case wher all enties are scalar values and numerous enough by chunking
    template<scalar_value ... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto
    welford_covariance_(EVE_REQUIRES(cpu_), O const & o, Ts const &... args) noexcept
    requires( (sizeof...(Ts) > 0) && (sizeof...(Ts)%2 == 0) && (sizeof...(Ts) >= 2*wide<common_value_t<Ts...>>::size()))
    {
      auto scalarize = []<typename T>(T w){
        using e_t  =  element_type_t<typename T::type>;
        auto getit = [w](auto i){return welford_covariance_result<e_t>(w.averagex.get(i), w.averagey.get(i), w.count, w.mxy.get(i), w.covariance.get(i)); };
        return kumi::generate<w.averagex.size()>(getit);
      };

      using r_t =  common_value_t<Ts...>;
      auto tup = kumi::make_tuple(args...);
      constexpr auto siz = sizeof...(Ts)/2;
      constexpr auto nblanes = wide<r_t>::size();
      constexpr auto remain = siz % nblanes;
      auto [tup1, tup2] = kumi::split(tup,  kumi::index<siz>);
      auto [car1, cdr1] = kumi::split(tup1,  kumi::index<remain>);
      auto [car2, cdr2] = kumi::split(tup2,  kumi::index<remain>);
      auto head1 = as_wides(eve::zero(eve::as<r_t>()), cdr1);
      auto head2 = as_wides(eve::zero(eve::as<r_t>()), cdr2);
      auto wc = eve::welford_covariance[o](head1, head2);
      auto swc = scalarize(wc);
      auto wcov1 = kumi::apply([](auto...m){return welford_covariance(m...);}, swc);
      if constexpr(remain != 0)
        return eve::welford_covariance(welford_covariance(car1, car2), wcov1);
      else
        return wcov1;
    }


    template< kumi::non_empty_product_type T1,  kumi::non_empty_product_type T2, callable_options O>
    EVE_FORCEINLINE constexpr auto
    welford_covariance_(EVE_REQUIRES(cpu_), O const & o, T1 t1, T2 t2) noexcept
    {
      return kumi::apply([o](auto... m){return welford_covariance[o](m...); }, kumi::cat(t1, t2));
    }
  }
}
