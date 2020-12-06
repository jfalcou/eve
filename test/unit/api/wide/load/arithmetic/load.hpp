//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIEVE_TYPE License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once
#include <eve/memory/aligned_allocator.hpp>
#include <eve/memory/aligned_ptr.hpp>
#include <eve/function/load.hpp>
#include <eve/wide.hpp>
#include <vector>
#include <list>

template<typename T, typename N>
auto data_block()
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<eve::wide<T, N>>;
  using alloc_t = eve::aligned_allocator<T, algt>;

  auto nb_elem  = 4096/sizeof(T);
  auto start    = nb_elem - std::max(algt,N::value);
  std::vector<T, alloc_t> ref(nb_elem);

  T k = {1};
  for(std::size_t i=start;i<nb_elem;++i) ref[i] = k++;

  return std::pair{ref,start};
}

TTS_CASE_TPL("Check load for scalar", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<T>;

  auto [data,idx]             = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr               = &data[idx];
  auto* uref_ptr              = ref_ptr - 1;
  auto const* ref_const_ptr   = ref_ptr;
  auto const* uref_const_ptr  = uref_ptr;

  TTS_EQUAL((eve::load(uref_ptr                             , eve::scalar)) , *uref_ptr       );
  TTS_EQUAL((eve::load(uref_const_ptr                       , eve::scalar)) , *uref_const_ptr );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_ptr)       , eve::scalar)) , *ref_ptr        );
  TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_const_ptr) , eve::scalar)) , *ref_const_ptr  );
}

TTS_CASE_TPL("Check load from for wide", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<T>;
  auto [data,idx]               = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();

  TTS_WHEN("For some given relative data")
  {
    auto* ref_ptr               = &data[idx];
    auto* uref_ptr              = ref_ptr - 1;
    auto const* ref_const_ptr   = &data[idx];
    auto const* uref_const_ptr  = ref_const_ptr - 1;
    T ref, uref;

    for(std::size_t i=0;i<EVE_CARDINAL;++i)
    {
      ref.set (i, ref_ptr[i]);
      uref.set(i, uref_ptr[i]);
    }

    TTS_AND_THEN("we load from unaligned pointers")
    {
      TTS_EQUAL(T(uref_ptr)                                    , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from unaligned pointers to constant")
    {
      TTS_EQUAL(T(uref_const_ptr)                                    , uref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(uref_const_ptr)                          , uref);

      TTS_EQUAL((eve::load(uref_const_ptr, eve::lane<EVE_CARDINAL>)) , uref);
    }

    TTS_AND_THEN("we load from aligned pointers")
    {
      TTS_EQUAL(T(eve::as_aligned<algt>(ref_ptr))                                    , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from aligned pointers to constant")
    {
      TTS_EQUAL(T(eve::as_aligned<algt>(ref_const_ptr))                                    , ref);

      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
        TTS_EQUAL(eve::load(eve::as_aligned<algt>(ref_const_ptr))                          , ref);

      TTS_EQUAL((eve::load(eve::as_aligned<algt>(ref_const_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }
  }
}

TTS_CASE_TPL("Check conditional load from pointer for wide", EVE_TYPE)
{
  constexpr std::ptrdiff_t algt = eve::alignment_v<T>;
  auto [data,idx] = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr               = &data[idx];
  auto const* ref_const_ptr   = ref_ptr;
  auto* uref_ptr              = ref_ptr - 1;
  auto const* uref_const_ptr  = uref_ptr;

  TTS_WHEN("For some given relative masks")
  {
    // Conditional selectors
    auto il = eve::ignore_last(EVE_CARDINAL/4);
    auto i1 = eve::ignore_first(EVE_CARDINAL/4);
    auto kf = eve::keep_first(EVE_CARDINAL/4);
    auto kl = eve::keep_last(EVE_CARDINAL/4);
    auto kb = eve::keep_between ( std::min(0L,EVE_CARDINAL/3)
                                , std::max(0L,(EVE_CARDINAL*2)/3)
                                );
    auto ie = i1 && il;

    // Conditional selectors' masks
    auto ml   = il.mask( eve::as_<T>() );
    auto m1   = i1.mask( eve::as_<T>() );
    auto mkf  = kf.mask( eve::as_<T>() );
    auto mkl  = kl.mask( eve::as_<T>() );
    auto mkb  = kb.mask( eve::as_<T>() );
    auto mie  = ie.mask( eve::as_<T>() );
    auto mia  = eve::ignore_all.mask( eve::as_<T>() );

    // Reference values
    T full_ref(ref_ptr);
    T ignore_last_ref   = full_ref & ml.mask();
    T ignore_first_ref  = full_ref & m1.mask();
    T keep_first_ref    = full_ref & mkf.mask();
    T keep_last_ref     = full_ref & mkl.mask();
    T keep_between_ref  = full_ref & mkb.mask();
    T ignore_ext_ref    = full_ref & mie.mask();

    T full_uref(uref_ptr);
    T ignore_last_uref   = full_uref & ml.mask();
    T ignore_first_uref  = full_uref & m1.mask();
    T keep_first_uref    = full_uref & mkf.mask();
    T keep_last_uref     = full_uref & mkl.mask();
    T keep_between_uref  = full_uref & mkb.mask();
    T ignore_ext_uref    = full_uref & mie.mask();

    // lanes value
    auto lanes = eve::lane<EVE_CARDINAL>;

    TTS_AND_THEN("load is applied on unaligned pointer for default cardinal")
    {
      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
      {
      TTS_EQUAL(eve::load[eve::ignore_none](uref_ptr)              , full_uref        );
      TTS_EQUAL((eve::load[il](uref_ptr) & ml.mask() )             , ignore_last_uref );
      TTS_EQUAL((eve::load[i1](uref_ptr) & m1.mask() )             , ignore_first_uref);
      TTS_EQUAL((eve::load[kf](uref_ptr) & mkf.mask())             , keep_first_uref  );
      TTS_EQUAL((eve::load[kl](uref_ptr) & mkl.mask())             , keep_last_uref   );
      TTS_EQUAL((eve::load[kb](uref_ptr) & mkb.mask())             , keep_between_uref);
      TTS_EQUAL((eve::load[ie](uref_ptr) & mie.mask())             , ignore_ext_uref  );
      TTS_EQUAL((eve::load[eve::ignore_all](uref_ptr) & mia.mask()), T{0}             );
      }
    }

    TTS_AND_THEN("load is applied on unaligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](uref_ptr, lanes)               , full_uref        );
      TTS_EQUAL((eve::load[il](uref_ptr, lanes) & ml.mask() )              , ignore_last_uref );
      TTS_EQUAL((eve::load[i1](uref_ptr, lanes) & m1.mask() )              , ignore_first_uref);
      TTS_EQUAL((eve::load[kf](uref_ptr, lanes) & mkf.mask())              , keep_first_uref  );
      TTS_EQUAL((eve::load[kl](uref_ptr, lanes) & mkl.mask())              , keep_last_uref   );
      TTS_EQUAL((eve::load[kb](uref_ptr, lanes) & mkb.mask())              , keep_between_uref);
      TTS_EQUAL((eve::load[ie](uref_ptr, lanes) & mie.mask())              , ignore_ext_uref  );
      TTS_EQUAL((eve::load[eve::ignore_all](uref_ptr, lanes) & mia.mask()) , T{0}             );
    }

    TTS_AND_THEN("load is applied on unaligned constant pointer for default cardinal")
    {
      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
      {
        TTS_EQUAL(eve::load[eve::ignore_none](uref_const_ptr)              , full_uref        );
        TTS_EQUAL((eve::load[il](uref_const_ptr) & ml.mask() )             , ignore_last_uref );
        TTS_EQUAL((eve::load[i1](uref_const_ptr) & m1.mask() )             , ignore_first_uref);
        TTS_EQUAL((eve::load[kf](uref_const_ptr) & mkf.mask())             , keep_first_uref  );
        TTS_EQUAL((eve::load[kl](uref_const_ptr) & mkl.mask())             , keep_last_uref   );
        TTS_EQUAL((eve::load[kb](uref_const_ptr) & mkb.mask())             , keep_between_uref);
        TTS_EQUAL((eve::load[ie](uref_const_ptr) & mie.mask())             , ignore_ext_uref  );
        TTS_EQUAL((eve::load[eve::ignore_all](uref_const_ptr) & mia.mask()), T{0}             );
      }
    }

    TTS_AND_THEN("load is applied on unaligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](uref_const_ptr, lanes)               , full_uref        );
      TTS_EQUAL((eve::load[il](uref_const_ptr, lanes) & ml.mask() )              , ignore_last_uref );
      TTS_EQUAL((eve::load[i1](uref_const_ptr, lanes) & m1.mask() )              , ignore_first_uref);
      TTS_EQUAL((eve::load[kf](uref_const_ptr, lanes) & mkf.mask())              , keep_first_uref  );
      TTS_EQUAL((eve::load[kl](uref_const_ptr, lanes) & mkl.mask())              , keep_last_uref   );
      TTS_EQUAL((eve::load[kb](uref_const_ptr, lanes) & mkb.mask())              , keep_between_uref);
      TTS_EQUAL((eve::load[ie](uref_const_ptr, lanes) & mie.mask())              , ignore_ext_uref  );
      TTS_EQUAL((eve::load[eve::ignore_all](uref_const_ptr, lanes) & mia.mask()) , T{0}             );
    }

    // Aligned pointer
    auto algt_ptr       = eve::as_aligned<algt>(ref_ptr);
    auto algt_const_ptr = eve::as_aligned<algt>(ref_const_ptr);

    TTS_AND_THEN("load is applied on aligned pointer for default cardinal")
    {
      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
      {
        TTS_EQUAL(eve::load[eve::ignore_none](algt_ptr)               , full_ref        );
        TTS_EQUAL((eve::load[il](algt_ptr) & ml.mask() )              , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](algt_ptr) & m1.mask() )              , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](algt_ptr) & mkf.mask())              , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](algt_ptr) & mkl.mask())              , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](algt_ptr) & mkb.mask())              , keep_between_ref);
        TTS_EQUAL((eve::load[ie](algt_ptr) & mie.mask())              , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all](algt_ptr) & mia.mask()) , T{0}            );
      }
    }

    TTS_AND_THEN("load is applied on aligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](algt_ptr, lanes)              , full_ref        );
      TTS_EQUAL((eve::load[il](algt_ptr, lanes) & ml.mask() )             , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](algt_ptr, lanes) & m1.mask() )             , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](algt_ptr, lanes) & mkf.mask())             , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](algt_ptr, lanes) & mkl.mask())             , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](algt_ptr, lanes) & mkb.mask())             , keep_between_ref);
      TTS_EQUAL((eve::load[ie](algt_ptr, lanes) & mie.mask())             , ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all](algt_ptr, lanes) & mia.mask()), T{0}            );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
    {
      if constexpr(EVE_CARDINAL == eve::expected_cardinal_v<EVE_VALUE>)
      {
        TTS_EQUAL(eve::load[eve::ignore_none](algt_const_ptr)               , full_ref        );
        TTS_EQUAL((eve::load[il](algt_const_ptr) & ml.mask() )              , ignore_last_ref );
        TTS_EQUAL((eve::load[i1](algt_const_ptr) & m1.mask() )              , ignore_first_ref);
        TTS_EQUAL((eve::load[kf](algt_const_ptr) & mkf.mask())              , keep_first_ref  );
        TTS_EQUAL((eve::load[kl](algt_const_ptr) & mkl.mask())              , keep_last_ref   );
        TTS_EQUAL((eve::load[kb](algt_const_ptr) & mkb.mask())              , keep_between_ref);
        TTS_EQUAL((eve::load[ie](algt_const_ptr) & mie.mask())              , ignore_ext_ref  );
        TTS_EQUAL((eve::load[eve::ignore_all](algt_const_ptr) & mia.mask()) , T{0}            );
      }
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](algt_const_ptr, lanes)              , full_ref        );
      TTS_EQUAL((eve::load[il](algt_const_ptr, lanes) & ml.mask() )             , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](algt_const_ptr, lanes) & m1.mask() )             , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](algt_const_ptr, lanes) & mkf.mask())             , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](algt_const_ptr, lanes) & mkl.mask())             , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](algt_const_ptr, lanes) & mkb.mask())             , keep_between_ref);
      TTS_EQUAL((eve::load[ie](algt_const_ptr, lanes) & mie.mask())             , ignore_ext_ref  );
      TTS_EQUAL((eve::load[eve::ignore_all](algt_const_ptr, lanes) & mia.mask()), T{0}            );
    }
  }
}

TTS_CASE_TPL("Check load from range for wide", EVE_TYPE )
{
  std::list<EVE_VALUE> ref_ptr(EVE_CARDINAL);

  EVE_VALUE k = {};
  for(auto &e : ref_ptr) e = k++;

  T ref;

  k = {};

  for(std::size_t i=0;i<EVE_CARDINAL;++i)
    ref.set(i, k++);

  T from_range(ref_ptr);
  TTS_EQUAL(from_range, ref);

  T from_begin_end(ref_ptr.begin(), ref_ptr.end());
  TTS_EQUAL(from_begin_end, ref);
}