//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/core.hpp>
#include <eve/module/core/regular/sum_of_prod.hpp>
//#include <eve/module/core/pedantic/sum_of_prod.hpp>


namespace eve::detail
{
  template<int N, typename T0, typename T1, typename T2, typename T3, typename... Ts>
  auto sum_of_prod_(EVE_SUPPORTS(cpu_), diff_type<N>
             , T0 arg0, T1 arg1, T2 arg2, T3 arg3, Ts... args) noexcept
  {
    EVE_ASSERT(!(sizeof...(Ts))&1,"total number of parameters must be even");
    using r_t = common_compatible_t<T0,T1,T2,T3,Ts...>;
    if constexpr(N > sizeof...(Ts)+4)
    {
      return zero(as<r_t >());
    }
    else
    {
      if constexpr(N==1)       return arg1;
      else if constexpr(N==2)  return  arg0;
      if constexpr(N==3)       return arg3;
      else if constexpr(N==4)  return  arg2;
      else
      {
        constexpr int NN = (N&1) ? N+1 : N-1;
        auto getNNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
          {
            auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
            {
              if constexpr(J==NN) that = val;
            };

            ((iff(vs, std::integral_constant<std::size_t,I+5>{})),...);
          };
        r_t that(nan(as < r_t > ()));
        getNNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
        return that;
      }
    }
  }

//   template<int N, typename T0, typename T1, typename... Ts>
//   auto sum_of_prod_(EVE_SUPPORTS(cpu_), decorated<diff_<N>(pedantic_)> const &
//              , T0 arg0, T1 arg1, Ts... args) noexcept
//   {
//     using r_t = common_compatible_t<T0,T1, Ts...>;
//     if constexpr(N > sizeof...(Ts)+2)
//     {
//       return zero(as<r_t >());
//     }
//     else
//     {
//       if constexpr(N > sizeof...(Ts)+2) return zero(as<r_t>());
//       else
//       {
//         auto h = pedantic(sum_of_prod)(arg0, arg1, args...);
//         if constexpr(N==1)       return arg0/h;
//         else if constexpr(N==2)  return  arg1/h;
//         else
//         {
//           auto getNth = []<std::size_t... I>(std::index_sequence<I...>, auto& that, auto... vs)
//             {
//               auto iff = [&that]<std::size_t J>(auto val, std::integral_constant<std::size_t,J>)
//               {
//                 if constexpr(J==N) that = val;
//               };

//               ((iff(vs, std::integral_constant<std::size_t,I+3>{})),...);
//             };
//           r_t that(0);
//           getNth(std::make_index_sequence<sizeof...(args)>{},that,args...);
//           return that/h;
//         }
//       }
//     }
//   }

}
