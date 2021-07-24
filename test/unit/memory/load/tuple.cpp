//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include "unit/memory/page.hpp"
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>

#include <array>
#include <numeric>
#include <utility>

namespace
{

template<typename T>
using tuple_t = kumi::tuple<std::int8_t,T,double>;

//==================================================================================================
// Load tests
//==================================================================================================
EVE_TEST_TYPES( "Check load behavior with tuple of pointers", eve::test::scalar::all_types)
<typename T>(eve::as<T>)
{
  using s_t   = tuple_t<T>;
  using w_t   = eve::wide<tuple_t<T>>;
  using w8_t  = eve::wide<tuple_t<T>, eve::fixed<8>>;

  auto const filler = [](auto i, auto)  { return s_t{ static_cast<std::int8_t>(1+i)
                                                    , static_cast<T>(i)
                                                    , 1.+i
                                                    };
                                        };

  w_t   reference   = filler;
  w8_t  reference8  = filler;

  auto il         = eve::ignore_last(w_t::size()/4);
  auto ireference = w_t{kumi::map ( [=]<typename M>(M m){ return m & il.mask(eve::as(m)).mask(); }
                              , reference.storage()
                              )};

  auto [data0,idx0] = page<std::int8_t  , typename w8_t::cardinal_type >();
  auto [data1,idx1] = page<T            , typename w8_t::cardinal_type >();
  auto [data2,idx2] = page<double       , typename w8_t::cardinal_type >();

  auto src = kumi::make_tuple ( eve::as_aligned(&data0[idx0],typename w8_t::cardinal_type{})
                              , &data1[idx1] - 1
                              , eve::as_aligned(&data2[idx2],typename w8_t::cardinal_type{})
                              );


  w_t constructed(src);
  TTS_EQUAL(constructed                                , reference   );
  TTS_EQUAL(eve::load(src)                             , reference   );
  TTS_EQUAL(eve::load(src, eve::lane<8>)               , reference8  );
  TTS_EQUAL(eve::unsafe(eve::load)(src)                , reference   );
  TTS_EQUAL(eve::unsafe(eve::load)(src, eve::lane<8>)  , reference8  );

  auto loaded = eve::load[il](src);
  eve::for_each( [=]<typename M>(M& m){ m &= il.mask(eve::as(m)).mask(); }, loaded);

  TTS_EQUAL(loaded, ireference);

  // else_
  {
    auto else_reference = ireference;
    eve::for_each( [=]<typename M>(M& m) { m = eve::if_else[il](m, eve::zero); }, else_reference );

    s_t scalar_zero {(std::uint8_t) 0, (T) 0, (double) 0};
    w_t wide_zeroes { scalar_zero };

    auto loaded_scalar_alt = eve::load[il.else_(scalar_zero)](src);
    TTS_EQUAL(loaded_scalar_alt, else_reference);

    auto loaded_wide_alt = eve::load[il.else_(wide_zeroes)](src);
    TTS_EQUAL(loaded_wide_alt, else_reference);
  }
};

}
