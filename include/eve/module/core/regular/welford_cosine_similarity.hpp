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
#include <iostream>

namespace eve
{

  namespace detail
  {
    template<floating_value T> struct welford_cosine_similarity_result
    {
      using type = T;
//      operator T()   const noexcept { return cosine_similarity; };
      auto upgrade() const noexcept { return welford_cosine_similarity_result<upgrade_t<T>>(); };

      T sumx2         = T(0);
      T sumy2         = T(0);
      T sumxy         = T(0);
      T cosine_similarity = T(0);
    };

    template < typename T>
    std::ostream& operator << (std::ostream& os,welford_cosine_similarity_result<T> const & v){
      os << '['
         << ".sumx2 = " << v.sumx2
         << ", .sumy2 = " << v.sumy2
         << ", .sumxy = " << v.sumxy
         << ", .cosine_similarity = "<< v.cosine_similarity
         << ']';
      return os;
    }

    template<typename>    struct is_welford_cosine_similarity_result_helper                                      : public std::false_type{};
    template<typename T>  struct is_welford_cosine_similarity_result_helper<welford_cosine_similarity_result<T>> : public std::true_type{};
    template<typename T>  struct is_welford_cosine_similarity_result                                             : public is_welford_cosine_similarity_result_helper<std::remove_cv_t<T>>::type{};
    template<typename T> constexpr auto is_welford_cosine_similarity_result_v =  is_welford_cosine_similarity_result<T>::value;

    // helper to treat in the same way values and welford_cosine_similarity results to compute common_value_t
    // without duplicating code
    template < typename T> struct internal_welford_cosine_similarity                                      { using type = T;  };
    template < typename T> struct internal_welford_cosine_similarity<welford_cosine_similarity_result<T>> { using type = T;  };
    template < typename T> using  internal_welford_cosine_similarity_t = typename internal_welford_cosine_similarity<T>::type;
  }

  template<typename Options>
  struct welford_cosine_similarity_t : callable<welford_cosine_similarity_t, Options, widen_option, unbiased_option>
  {
    // sequences of welford_cosine_similarity_result_t
    template<typename... Ts>
    requires((detail::is_welford_cosine_similarity_result_v<Ts > && ...) && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_cosine_similarity_result<common_value_t<detail::internal_welford_cosine_similarity_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

   template<typename... Ts>
    requires((detail::is_welford_cosine_similarity_result_v<Ts> && ...) && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_cosine_similarity_result<common_value_t<detail::internal_welford_cosine_similarity_t<Ts>...>>
    operator()(Ts...ts) const noexcept
    {
      return EVE_DISPATCH_CALL(ts...);
    }

    // tuples of floating_value
    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_cosine_similarity_result<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept
    { return EVE_DISPATCH_CALL(t1, t2); }

    template<kumi::non_empty_product_type Tup1, kumi::non_empty_product_type Tup2>
    requires(eve::same_lanes_or_scalar_tuple<Tup1> && eve::same_lanes_or_scalar_tuple<Tup2> && Options::contains(widen))
      EVE_FORCEINLINE constexpr
    detail::welford_cosine_similarity_result<upgrade_t<kumi::apply_traits_t<eve::common_value, kumi::result::cat_t<Tup1, Tup2>>>>
    operator()(Tup1 const& t1, Tup2 const& t2) const noexcept
    { return EVE_DISPATCH_CALL(t1, t2); }

    //scalarization
    template<typename T>
    requires(detail::is_welford_cosine_similarity_result_v<T> && !Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_cosine_similarity_result<element_type_t<typename T::type>>
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    template<typename T>
    requires(detail::is_welford_cosine_similarity_result_v<T> && Options::contains(widen))
      EVE_FORCEINLINE constexpr detail::welford_cosine_similarity_result<upgrade_t<element_type_t<typename T::type>> >
    operator()(T t) const noexcept
    {
      return EVE_DISPATCH_CALL(t);
    }

    EVE_CALLABLE_OBJECT(welford_cosine_similarity_t, welford_cosine_similarity_);
  };

//================================================================================================
//! @addtogroup core_arithmetic
//! @{
//!   @var welford_cosine_similarity
//!   @brief `elementwise_callable` object computing the elementwise  cosine_similarity
//!     of the vector of the first half parameters by the vector of the last half.
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
//!      constexpr auto welford_cosine_similarity(auto value ... xs, auto value ... ys)      noexcept; // 1
//!      constexpr auto welford_cosine_similarity(kumi::tuple xs, kumi::tuple ys)            noexcept; // 2
//!      constexpr auto welford_cosine_similarity(auto wcs...)                               noexcept; // 3
//!      constexpr auto welford_cosine_similarity(kumi;::tuple wcs)                          noexcept; // 4
//!
//!      // Semantic options
//!      constexpr auto welford_cosine_similarity[widen]   (/*any of the above overloads*/)  noexcept; // 5
//!      constexpr auto welford_cosine_similarity[unbiased](/*any of the above overloads*/)  noexcept; // 6
//!   }
//!   @endcode
//!
//!   **Parameters**
//!
//!     * `xs`, `ys`  : [arguments](@ref eve::value) or tuple of them.
//!     * `wcs`       : [arguments](@ref eve::value) or tuple of them. The arguments must all be results
//!                      of previous `welford_cosine_similarity` calls,
//!    **Return value**
//!
//!      1. A struct containing The value of the sum of squares (`sumx2` and `sumy2` ),
//!         the dot product (`sumxy`), and the cosine_similarity value `sumxy/sqrt(sumx2*sumy2)
//!         This struct is convertible to the cosine_similarity floating value. and possess three fields `cosine_similarity`,
//!          `summxy`, `sumx2` and `sumy2`.
//!      2. The computation is made on the tuples elements.
//!      3. The parameters are composed in a unique cosine_similarity struct as if the cosine_similarity was  computed on the whole original data set.
//!         Moreover if only one cosine_similarity result simd parameter is present, the the lanes individual corariance are grouped in an unique
//!         scalar cosine_similarity result, computed from all the datas of all the lanes.
//!      4. same as 3. on the tuple elements.
//!      5. the computation is done in the upgraded element type.
//!
//!  @note The Welford algorithm has the advantage to allow spliting the computation of the cosine_similarity in
//!        multiple calls.  For instance: the call with four tuples:<br/>
//!        &nbsp;   `cwv = welford_corariance(kumi::cat(xs, ys), kumi::cat(ws, zs))`<br/>
//!        is equivalent to the sequence:<br/>
//!        &nbsp;  `cwxs =  welford_cosine_similarity(xs, ws);  cwys = welford_cosine_similarity(ys, zs)); cwv = welford_cosine_similarity(wxs, wys);`<br/>
//!        But the first two instructions can easily be executed in parallel.
//!
//!  @groupheader{Example}
//!  @godbolt{doc/core/welford_cosine_similarity.cpp}
//================================================================================================
  inline constexpr auto welford_cosine_similarity = functor<welford_cosine_similarity_t>;
//================================================================================================
//! @}
//================================================================================================

  namespace detail
  {

    template<kumi::non_empty_product_type PT1, kumi::non_empty_product_type PT2, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, PT1 f, PT2 s) noexcept
    requires (kumi::as_tuple_t<PT1>::size() == kumi::as_tuple_t<PT2>::size())
    {
      if constexpr(O::contains(widen)) {
        auto up = [](auto tup){
          auto upg = [](auto t){return eve::upgrade(t); };
          return kumi::map(upg, tup);
        };
        return welford_cosine_similarity[o.drop(widen)](up(f), up(s));
      }
      else
      {
        using Tup1 = kumi::as_tuple_t<PT1>;
        using Tup2 = kumi::as_tuple_t<PT2>;
        using r1_t = kumi::apply_traits_t<eve::common_value, Tup1>;
        using r2_t = kumi::apply_traits_t<eve::common_value, Tup2>;
        using r_t =  eve::common_value_t<r1_t, r2_t>;

        auto nsim = welford_cosine_similarity_result<r_t>();
        auto doit = [&nsim, &f, &s](){
          auto wcs_step = [&nsim](auto xnyn)
          {
            auto [xn, yn] = xnyn;
            auto rxn = xn;
            auto ryn = yn;
            nsim.sumx2 = eve::fam(nsim.sumx2, rxn, rxn);
            nsim.sumy2 = eve::fam(nsim.sumy2, ryn, ryn);
            nsim.sumxy = eve::fam(nsim.sumxy, rxn, ryn);
            return nsim;
          };
          auto r = kumi::map([](auto xs,  auto ys){return eve::zip(r_t(xs), r_t(ys)); }, f, s);
          kumi::apply([wcs_step](auto ... xsys){((wcs_step(xsys)), ...); }, r);
          nsim.cosine_similarity = nsim.sumxy*eve::rsqrt(nsim.sumx2*nsim.sumy2);
          return nsim;
        };
        return  doit();
      }
    }

    // This call compute the join cosine_similarity from previously computed welford cosine similarities
    template<typename... Ts, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, Ts... args) noexcept
    requires((sizeof...(Ts) > 1) && (detail::is_welford_cosine_similarity_result_v<Ts> && ...))
    {
      if constexpr(O::contains(widen))
      {
        auto up_it = [](auto a){
          if constexpr(requires { a.up(); }) return a.up();
          else return eve::upgrade(a);
        };
        return welford_cosine_similarity[o.drop(widen)](up_it(args)...);
      }
      else
      {
        using r_t = typename detail::welford_cosine_similarity_result<common_value_t<detail::internal_welford_cosine_similarity_t<Ts>...>>;
        using v_t = r_t::type;
        auto nsim = welford_cosine_similarity_result<v_t>();
//        return nsim;
        auto doit = [ & ](){
          auto wcs_step = [&](auto sim)
          {
            nsim.sumx2 += sim.sumx2;
            nsim.sumy2 += sim.sumy2;
            nsim.sumxy += sim.sumxy;
            return nsim;
          };
          ((nsim = wcs_step(args)),...);
          nsim.cosine_similarity = nsim.sumxy*eve::rsqrt(nsim.sumx2*nsim.sumy2);
          return nsim;
        };
        return  doit();
      }
    }

    // This call 'scalarize' a welford cosine_similarity
    template<typename T, callable_options O>
    EVE_FORCEINLINE constexpr auto welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
    requires(detail::is_welford_cosine_similarity_result_v<T>)
    {
      auto scalarize = []<typename U>(U w){
        using e_t =  element_type_t<typename U::type>;
        auto getit = [w](auto i){return welford_cosine_similarity_result<e_t>(w.sumx2.get(i), w.sumy2.get(i), w.sumxy.get(i), w.cosine_similarity.get(i)); };
        return kumi::generate<w.sumxy.size()>(getit);
      };
      if constexpr(scalar_value<typename T::type>)
        return t;
      else
      {
        auto tpsc =  scalarize(t);
        return kumi::apply([o](auto... m){return welford_cosine_similarity[o](m...); }, tpsc);
      }
    }
  }
}



//         using r_t = eve::common_value_t<detail::internal_welford_cosine_similarity_t<Ts>, ...> > ;

//         auto nsim = welford_cosine_similarity_result<r_t>();
//         auto doit = [ & ](){
//           auto wcs_step = [&](auto sim)
//           {
//             nsim.sumx2 += sim.sumx2;
//             nsim.sumy2 += sim.sumy2;
//             nsim.sumxy += sim.sumxy;
//             return nsim;
//           };
//           ((nsim = wcs_step(args)),...);
//           nsim.cosine_similarity = nsim.sumxy*eve::rsqrt(nsim.sumx2*nsim.sumy2);
//           return nsim;
//         };
//         return  doit();
//       }
//     }



// //     // This call 'scalarize' a welford cosine_similarity
// //     template<typename T, callable_options O>
// //     EVE_FORCEINLINE constexpr auto welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, T t) noexcept
// //     requires(detail::is_welford_cosine_similarity_result_v<T>)
// //     {
// //       auto scalarize = []<typename U>(U w){
// //         using e_t =  element_type_t<typename U::type>;
// //         auto getit = [w](auto i){return welford_cosine_similarity_result<e_t>(w.sumx2.get(i), w.sumy2.get(i), w.sumxy.get(i), w.cosine_similarity.get(i)); };
// //         return kumi::generate<w.mxy.size()>(getit);
// //       };
// //       if constexpr(scalar_value<typename T::type>)
// //         return t;
// //       else
// //       {
// //         auto tpsc =  scalarize(t);
// //         return kumi::apply([o](auto... m){return welford_cosine_similarity[o](m...); }, tpsc);
// //       }
// //     }

// //     // This call treat the case where all entries are scalar values and numerous enough by chunking
// //     template<scalar_value ... Ts, callable_options O>
// //     EVE_FORCEINLINE constexpr auto
// //     welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, Ts const &... args) noexcept
// //     requires( (sizeof...(Ts) > 0) && (sizeof...(Ts)%2 == 0) && (sizeof...(Ts) >= 2*wide<common_value_t<Ts...>>::size()))
// //     {
// //       auto scalarize = []<typename T>(T w){
// //         using e_t  =  element_type_t<typename T::type>;
// //         auto getit = [w](auto i){return welford_cosine_similarity_result<e_t>(w.sumx2.get(i), w.sumy2.get(i), w.sumxy.get(i), w.cosine_similarity.get(i)); };
// //         return kumi::generate<w.sumxy.size()>(getit);
// //       };

// //       using r_t =  common_value_t<Ts...>;
// //       auto tup = kumi::make_tuple(args...);
// //       constexpr auto siz = sizeof...(Ts)/2;
// //       auto [tup1, tup2] = kumi::split(tup,  kumi::index<siz>);
// //       auto head1 = as_wides(eve::zero(eve::as<r_t>()), tup1);
// //       auto head2 = as_wides(eve::zero(eve::as<r_t>()), tup2);
// //       auto wc = eve::welford_cosine_similarity[o](head1, head2);
// //       auto swc = scalarize(wc);
// //       auto wsim1 = kumi::apply([](auto...m){return welford_cosine_similarity(m...);}, swc);
// //       return wsim1;
// //     }


// //     template< kumi::non_empty_product_type T1,  kumi::non_empty_product_type T2, callable_options O>
// //     EVE_FORCEINLINE constexpr auto
// //     welford_cosine_similarity_(EVE_REQUIRES(cpu_), O const & o, T1 t1, T2 t2) noexcept
// //     {
// //       return kumi::apply([o](auto... m){return welford_cosine_similarity[o](m...); }, kumi::cat(t1, t2));
// //     }
// //   }
// }
