//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once
#include <eve/module/core.hpp>

namespace eve::detail
{

    auto process(auto const& t, auto xx, auto xn)
    {
      return kumi::get<1>(kumi::fold_right( [&](auto acc, auto e)
                                            {
                                              auto[x,r] = acc;
                                              return kumi::tuple{x*xn,kumi::push_back(r, x*e)};
                                            }
                                          , t
                                          , kumi::tuple{xx,kumi::tuple<>{}}
                                          ));
    }

  template<scalar_value X,  scalar_value C, scalar_value... Cs, callable_options O>
  auto chunked_reverse_horner(O const & o, X xx, C c0, Cs... cs)
  {
//     auto process = [](auto const& t, auto y, auto xn){
//       return kumi::get<1>(kumi::fold_right( [&](auto acc, auto e)
//                                             {
//                                               auto[y,r] = acc;
//                                               return kumi::tuple{y*xn,kumi::push_back(r, y*e)};
//                                             }
//                                           , t
//                                           , kumi::tuple{xx,kumi::tuple<>{}}
//                                           ));
//     };
    using e_t =  eve::common_value_t<X, C, Cs...>;
    using w_t = eve::wide<e_t>;
    auto t = kumi::make_tuple(c0, cs...);
    constexpr auto nblanes = w_t::size();
    auto head = eve::as_wides(eve::zero(eve::as<e_t>()), t);
    w_t zz([xx](auto i, auto){return i == 0 ? e_t(1) : e_t(xx); });
    auto xxx =  eve::scan(zz, eve::mul[o], e_t(1));
    e_t xn = std::pow(xx, nblanes);
    auto res =  process(head, xxx, xn);
    return eve::detail::sum(eve::add[o](res));
  }
}
