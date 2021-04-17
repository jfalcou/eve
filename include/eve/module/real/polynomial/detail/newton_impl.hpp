#pragma once

#include <eve/traits/common_compatible.hpp>
#include <eve/concept/compatible.hpp>
#include <eve/concept/value.hpp>
#include <eve/detail/apply_over.hpp>
#include <eve/detail/concepts.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/decorator.hpp>
#include <eve/function/fma.hpp>
#include <eve/constant/one.hpp>
#include <eve/concept/range.hpp>
#include <iterator>
#include <initializer_list>

namespace eve::detail
{


//   //================================================================================================
//   //== N+ 1  parameters (((..(a*x+b)*x+c)*x + ..)..)
//   //================================================================================================
//   //==  N = 0
//   template<decorator D,  value T0>
//   EVE_FORCEINLINE constexpr auto newton_impl(D const &, T0 const &) noexcept
//   {
//     return T0(0);
//   }

//   //==  N = 1
//   template<decorator D, value T0, value T1>
//   EVE_FORCEINLINE constexpr auto newton_impl(D const &
//                                             , T0 const &, T1 const &a) noexcept
//   requires compatible_values<T0, T1>
//   {
//     using r_t = common_compatible_t<T0, T1>;
//     return r_t(a);
//   }

//   //==  N = 2
//   template<decorator D, value T0, value T1, value T2>
//   EVE_FORCEINLINE constexpr auto newton_impl(D const &
//                                             , T0 const &x, T1 const &a, T2 const &b) noexcept
//   requires compatible_values<T0, T1> &&compatible_values<T1, T2>
//   {
//     using r_t = common_compatible_t<T0, T1, T2>;
//     return D()(fma)(r_t(x), a, b);
//   }

//   //==  N >= 3
//   template<decorator D,
//            value T0,
//            value T1,
//            value T2,
//            value ...Ts>
//   EVE_FORCEINLINE constexpr
//   auto newton_impl(D const & d
//                   , T0 xx, T1 a, T2 b, Ts... args) noexcept
//   {
//     using r_t = common_compatible_t<T0, T1, T2, Ts...>;
//     auto x =  r_t(xx);
//     auto dfma = d(fma);
//     r_t that(dfma(x, a, b));
//     [[maybe_unused]] auto next = [&](auto that, auto arg){
//       return dfma(x, that, arg);
//     };
//     ((that = next(that, args)),...);
//     return that;
//   }

  //================================================================================================
  //== Newton with iterators
  //================================================================================================
  template<decorator D, value T0, std::input_iterator IT1
                                , std::input_iterator IT2>
  EVE_FORCEINLINE constexpr auto newton_impl( D const & d
                                            , T0 xx
                                            , IT1 const & firstc
                                            , IT1 const & lastc
                                            , IT2 const & firstn
                                            , IT2 const & lastn
                                             ) noexcept
  requires (compatible_values<T0, typename std::iterator_traits<IT1>::value_type> &&
            compatible_values<T0, typename std::iterator_traits<IT2>::value_type>)

  {
    EVE_ASSERT_MSG( (std::distance(firstc, lastc) ==
                     std::distance(firstn, lastn)+1
                    , "size of nodes and coefs iterator are not coherent");
    using r_t = common_compatible_t<T0, typename std::iterator_traits<IT1>::value_type
                                      , typename std::iterator_traits<IT2>::value_type>;
    auto x =  r_t(xx);
    if (firstc = lastc) return r_t(0);
    if (std::distance(firstc, lastc) == 1) return r_t(*firstc);
    else
    {
      using std::advance;
      auto curc = firstc;
      auto curn = firstn;
      advance(curc, 1);
      auto dfma = d(fma);
      r_t that(dfma(x-*firstn, *firstc, *curc));
      auto step = [&](auto that, auto argc, auto argn){
        return dfma(x-argn, that, argc);
      };
      for (advance(curc, 1); cur != last; advance(curc, 1), advance(curn, 1))
        that = step(that, *curc, *curn);
      return that;
    }
  }

  //================================================================================================
  //== Newton with ranges
  //================================================================================================
  template<decorator D, value T0, range R1, Range R2>
  EVE_FORCEINLINE constexpr auto newton_impl(D const & d
                                        , T0 xx, R const & rc, Range rn) noexcept
  requires (compatible_values<T0, typename R1::value_type> && (!simd_value<R1>)
                                , typename R2::value_type> && (!simd_value<R2>))
  {
    return newton_impl(d, xx, std::begin(rc), std::end(rc), std::begin(rn), std::end(rn));
  }
}
