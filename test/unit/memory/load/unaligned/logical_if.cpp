//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include "test.hpp"
#include <eve/module/core.hpp>
#include "unit/memory/page.hpp"

#include <array>
#include <list>

//==================================================================================================
// Conditionally load into wide from an unaligned pointer
//==================================================================================================
TTS_CASE_TPL( "Check load to wides from unaligned pointer", eve::test::simd::all_types)
<typename T>(tts::type<T>)
{
  using v_t = eve::element_type_t<T>;

  auto [ldata ,lidx ] = logical_page<v_t, eve::fixed<T::size()>>();

  auto* l_ptr             = &ldata[lidx] - 1;
  auto const* l_const_ptr = l_ptr;

  TTS_WHEN("For some given relative masks")
  {
    // Conditional selectors
    auto il = eve::ignore_last(T::size()/4);
    auto i1 = eve::ignore_first(T::size()/4);
    auto kf = eve::keep_first(T::size()/4);
    auto kl = eve::keep_last(T::size()/4);
    auto kb = eve::keep_between ( std::min(std::ptrdiff_t(0),std::ptrdiff_t(T::size()/3))
                                , std::max(std::ptrdiff_t(0),std::ptrdiff_t((T::size()*2)/3))
                                );

    auto ie = i1 && il;

    // Conditional selectors' masks
    auto ml   = il.mask( eve::as<T>() );
    auto m1   = i1.mask( eve::as<T>() );
    auto mkf  = kf.mask( eve::as<T>() );
    auto mkl  = kl.mask( eve::as<T>() );
    auto mkb  = kb.mask( eve::as<T>() );
    auto mie  = ie.mask( eve::as<T>() );
    auto mia  = eve::ignore_all.mask( eve::as<T>() );

    // Reference values
    eve::logical<T> l_full_ref(l_ptr);
    eve::logical<T> l_ignore_last_ref   = l_full_ref && ml;
    eve::logical<T> l_ignore_first_ref  = l_full_ref && m1;
    eve::logical<T> l_keep_first_ref    = l_full_ref && mkf;
    eve::logical<T> l_keep_last_ref     = l_full_ref && mkl;
    eve::logical<T> l_keep_between_ref  = l_full_ref && mkb;
    eve::logical<T> l_ignore_ext_ref    = l_full_ref && mie;

    // lanes value
    auto lanes = eve::lane<T::size()>;

    using eve::false_;

    TTS_AND_THEN("load is applied on unaligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](l_ptr, lanes)        , l_full_ref           );
      TTS_EQUAL((eve::load[il](l_ptr, lanes) && ml )             , l_ignore_last_ref    );
      TTS_EQUAL((eve::load[i1](l_ptr, lanes) && m1 )             , l_ignore_first_ref   );
      TTS_EQUAL((eve::load[kf](l_ptr, lanes) && mkf)             , l_keep_first_ref     );
      TTS_EQUAL((eve::load[kl](l_ptr, lanes) && mkl)             , l_keep_last_ref      );
      TTS_EQUAL((eve::load[kb](l_ptr, lanes) && mkb)             , l_keep_between_ref   );
      TTS_EQUAL((eve::load[ie](l_ptr, lanes) && mie)             , l_ignore_ext_ref     );
      TTS_EQUAL((eve::load[eve::ignore_all](l_ptr, lanes) && mia), false_(eve::as<T>()));
    }

    TTS_AND_THEN("load is applied on unaligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](l_const_ptr, lanes)         , l_full_ref            );
      TTS_EQUAL((eve::load[il](l_const_ptr, lanes) && ml  )             , l_ignore_last_ref     );
      TTS_EQUAL((eve::load[i1](l_const_ptr, lanes) && m1  )             , l_ignore_first_ref    );
      TTS_EQUAL((eve::load[kf](l_const_ptr, lanes) && mkf )             , l_keep_first_ref      );
      TTS_EQUAL((eve::load[kl](l_const_ptr, lanes) && mkl )             , l_keep_last_ref       );
      TTS_EQUAL((eve::load[kb](l_const_ptr, lanes) && mkb )             , l_keep_between_ref    );
      TTS_EQUAL((eve::load[ie](l_const_ptr, lanes) && mie )             , l_ignore_ext_ref      );
      TTS_EQUAL((eve::load[eve::ignore_all](l_const_ptr, lanes) && mia) , false_(eve::as<T>()) );
    }

    if constexpr(T::size() == eve::expected_cardinal_v<v_t>)
    {
      TTS_AND_THEN("load is applied on unaligned pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](l_ptr)        , l_full_ref           );
        TTS_EQUAL((eve::load[il](l_ptr) && ml )             , l_ignore_last_ref    );
        TTS_EQUAL((eve::load[i1](l_ptr) && m1 )             , l_ignore_first_ref   );
        TTS_EQUAL((eve::load[kf](l_ptr) && mkf)             , l_keep_first_ref     );
        TTS_EQUAL((eve::load[kl](l_ptr) && mkl)             , l_keep_last_ref      );
        TTS_EQUAL((eve::load[kb](l_ptr) && mkb)             , l_keep_between_ref   );
        TTS_EQUAL((eve::load[ie](l_ptr) && mie)             , l_ignore_ext_ref     );
        TTS_EQUAL((eve::load[eve::ignore_all](l_ptr) && mia), false_(eve::as<T>()));
      }

      TTS_AND_THEN("load is applied on unaligned constant pointer for default cardinal")
      {
        TTS_EQUAL(eve::load[eve::ignore_none](l_const_ptr)         , l_full_ref            );
        TTS_EQUAL((eve::load[il](l_const_ptr) && ml  )             , l_ignore_last_ref     );
        TTS_EQUAL((eve::load[i1](l_const_ptr) && m1  )             , l_ignore_first_ref    );
        TTS_EQUAL((eve::load[kf](l_const_ptr) && mkf )             , l_keep_first_ref      );
        TTS_EQUAL((eve::load[kl](l_const_ptr) && mkl )             , l_keep_last_ref       );
        TTS_EQUAL((eve::load[kb](l_const_ptr) && mkb )             , l_keep_between_ref    );
        TTS_EQUAL((eve::load[ie](l_const_ptr) && mie )             , l_ignore_ext_ref      );
        TTS_EQUAL((eve::load[eve::ignore_all](l_const_ptr) && mia) , false_(eve::as<T>()) );
      }
    }
  }
};
