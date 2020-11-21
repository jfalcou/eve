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
  auto [data,idx]           = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr             = &data[idx];
  auto const* ref_const_ptr = &data[idx];

  TTS_EQUAL((eve::load(ref_ptr                        , eve::scalar)) , data[idx]);
  TTS_EQUAL((eve::load(ref_const_ptr                  , eve::scalar)) , data[idx]);
  TTS_EQUAL((eve::load(eve::as_aligned(ref_ptr)       , eve::scalar)) , data[idx]);
  TTS_EQUAL((eve::load(eve::as_aligned(ref_const_ptr) , eve::scalar)) , data[idx]);
}

TTS_CASE_TPL("Check load from for wide", EVE_TYPE)
{
  auto [data,idx]           = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();

  TTS_WHEN("For some given relative data")
  {
    auto* ref_ptr             = &data[idx];
    auto const* ref_const_ptr = &data[idx];
    T ref;

    for(std::size_t i=0;i<EVE_CARDINAL;++i)
      ref.set(i, data[idx+i]);

    TTS_AND_THEN("we load from unaligned pointers")
    {
      TTS_EQUAL(T(ref_ptr)                                    , ref);
      TTS_EQUAL(eve::load(ref_ptr)                            , ref);
      TTS_EQUAL((eve::load(ref_ptr, eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from unaligned pointers to constant")
    {
      TTS_EQUAL(T(ref_const_ptr)                                    , ref);
      TTS_EQUAL(eve::load(ref_const_ptr)                            , ref);
      TTS_EQUAL((eve::load(ref_const_ptr, eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from aligned pointers")
    {
      TTS_EQUAL(T(eve::as_aligned(ref_ptr))                                    , ref);
      TTS_EQUAL(eve::load(eve::as_aligned(ref_ptr))                            , ref);
      TTS_EQUAL((eve::load(eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }

    TTS_AND_THEN("we load from aligned pointers to constant")
    {
      TTS_EQUAL(T(eve::as_aligned(ref_const_ptr))                                    , ref);
      TTS_EQUAL(eve::load(eve::as_aligned(ref_const_ptr))                            , ref);
      TTS_EQUAL((eve::load(eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>)) , ref);
    }
  }
}

TTS_CASE_TPL("Check conditional load from unaligned pointer for wide", EVE_TYPE)
{
  auto [data,idx] = data_block<EVE_VALUE, eve::fixed<EVE_CARDINAL>>();
  auto* ref_ptr             = &data[idx];
  auto const* ref_const_ptr = &data[idx];

  TTS_WHEN("For some given relative masks")
  {
    // Conditional selectors
    auto il = eve::ignore_last(EVE_CARDINAL/4);
    auto i1 = eve::ignore_first(EVE_CARDINAL/4);
    auto kf = eve::keep_first(EVE_CARDINAL/4);
    auto kl = eve::keep_last(EVE_CARDINAL/4);
    auto kb = eve::keep_between(1,EVE_CARDINAL-2);

    // Conditional selectors' masks
    auto ml   = il.mask( eve::as_<T>() );
    auto m1   = i1.mask( eve::as_<T>() );
    auto mkf  = kf.mask( eve::as_<T>() );
    auto mkl  = kl.mask( eve::as_<T>() );
    auto mkb  = kb.mask( eve::as_<T>() );

    // Reference values
    T full_ref(ref_ptr);
    T ignore_last_ref   = full_ref & ml.mask();
    T ignore_first_ref  = full_ref & m1.mask();
    T keep_first_ref    = full_ref & mkf.mask();
    T keep_last_ref     = full_ref & mkl.mask();
    T keep_between_ref  = full_ref & mkb.mask();

    TTS_AND_THEN("load is applied on unaligned pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ref_ptr)  , full_ref        );
      TTS_EQUAL((eve::load[il](ref_ptr) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](ref_ptr) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](ref_ptr) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](ref_ptr) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](ref_ptr) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](ref_ptr)   , T{0}            );
    }

    TTS_AND_THEN("load is applied on unaligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ref_ptr, eve::lane<EVE_CARDINAL>)  , full_ref        );
      TTS_EQUAL((eve::load[il](ref_ptr, eve::lane<EVE_CARDINAL>) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](ref_ptr, eve::lane<EVE_CARDINAL>) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](ref_ptr, eve::lane<EVE_CARDINAL>) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](ref_ptr, eve::lane<EVE_CARDINAL>) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](ref_ptr, eve::lane<EVE_CARDINAL>) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](ref_ptr, eve::lane<EVE_CARDINAL>)   , T{0}            );
    }

    TTS_AND_THEN("load is applied on unaligned constant pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ref_const_ptr)  , full_ref        );
      TTS_EQUAL((eve::load[il](ref_const_ptr) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](ref_const_ptr) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](ref_const_ptr) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](ref_const_ptr) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](ref_const_ptr) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](ref_const_ptr)   , T{0}            );
    }

    TTS_AND_THEN("load is applied on unaligned constant pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](ref_const_ptr, eve::lane<EVE_CARDINAL>)  , full_ref        );
      TTS_EQUAL((eve::load[il](ref_const_ptr, eve::lane<EVE_CARDINAL>) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](ref_const_ptr, eve::lane<EVE_CARDINAL>) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](ref_const_ptr, eve::lane<EVE_CARDINAL>) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](ref_const_ptr, eve::lane<EVE_CARDINAL>) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](ref_const_ptr, eve::lane<EVE_CARDINAL>) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](ref_const_ptr, eve::lane<EVE_CARDINAL>)   , T{0}            );
    }

    TTS_AND_THEN("load is applied on aligned pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](eve::as_aligned(ref_ptr))  , full_ref        );
      TTS_EQUAL((eve::load[il](eve::as_aligned(ref_ptr)) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](eve::as_aligned(ref_ptr)) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](eve::as_aligned(ref_ptr)) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](eve::as_aligned(ref_ptr)) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](eve::as_aligned(ref_ptr)) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](eve::as_aligned(ref_ptr))   , T{0}            );
    }

    TTS_AND_THEN("load is applied on aligned pointer for a specific cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>)  , full_ref        );
      TTS_EQUAL((eve::load[il](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](eve::as_aligned(ref_ptr), eve::lane<EVE_CARDINAL>)   , T{0}            );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](eve::as_aligned(ref_const_ptr))  , full_ref        );
      TTS_EQUAL((eve::load[il](eve::as_aligned(ref_const_ptr)) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](eve::as_aligned(ref_const_ptr)) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](eve::as_aligned(ref_const_ptr)) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](eve::as_aligned(ref_const_ptr)) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](eve::as_aligned(ref_const_ptr)) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](eve::as_aligned(ref_const_ptr))   , T{0}            );
    }

    TTS_AND_THEN("load is applied on aligned constant pointer for default cardinal")
    {
      TTS_EQUAL(eve::load[eve::ignore_none](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>)  , full_ref        );
      TTS_EQUAL((eve::load[il](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>) & ml.mask() ) , ignore_last_ref );
      TTS_EQUAL((eve::load[i1](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>) & m1.mask() ) , ignore_first_ref);
      TTS_EQUAL((eve::load[kf](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>) & mkf.mask()) , keep_first_ref  );
      TTS_EQUAL((eve::load[kl](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>) & mkl.mask()) , keep_last_ref   );
      TTS_EQUAL((eve::load[kb](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>) & mkb.mask()) , keep_between_ref);
      TTS_EQUAL(eve::load[eve::ignore_all](eve::as_aligned(ref_const_ptr), eve::lane<EVE_CARDINAL>)   , T{0}            );
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