//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#include <eve/function/if_else.hpp>
#include <eve/constant/true.hpp>
#include <eve/constant/false.hpp>

TTS_CASE_TPL("Check eve::if_else return type", EVE_TYPE)
{
  using sT =  eve::element_type_t<T>;
  using eve::logical;

  // Condition is logical
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<T>(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<T>(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<T>(), sT()          , T()           ) , T          );

  // Condition is scalar logical
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<T>()  , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<T>()  , logical<sT>()) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), logical<sT>() , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), T()           , T()          ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), T()           , sT()         ) , T          );
  TTS_EXPR_IS( eve::if_else(logical<sT>(), sT()          , T()          ) , T          );

  // Condition is bool
  TTS_EXPR_IS( eve::if_else(bool(), logical<T>()  , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), logical<T>()  , logical<sT>()) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), logical<sT>() , logical<T>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(bool(), T()           , T()          ) , T          );
  TTS_EXPR_IS( eve::if_else(bool(), T()           , sT()         ) , T          );
  TTS_EXPR_IS( eve::if_else(bool(), sT()          , T()          ) , T          );

  // Condition is arithmetic
  TTS_EXPR_IS( eve::if_else(T(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(T(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(T(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(T(), sT()          , T()           ) , T          );

  // Condition is scalar arithmetic
  TTS_EXPR_IS( eve::if_else(sT(), logical<T>()  , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), logical<T>()  , logical<sT>() ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), logical<sT>() , logical<T>()  ) , logical<T> );
  TTS_EXPR_IS( eve::if_else(sT(), T()           , T()           ) , T          );
  TTS_EXPR_IS( eve::if_else(sT(), T()           , sT()          ) , T          );
  TTS_EXPR_IS( eve::if_else(sT(), sT()          , T()           ) , T          );
}

TTS_CASE_TPL("Check eve::if_else(logical,logical,logical) variants", EVE_TYPE)
{
  auto vt = eve::true_  (eve::as<T>());
  auto st = eve::true_  (eve::as<EVE_VALUE>());
  auto vf = eve::false_ (eve::as<T>());
  auto sf = eve::false_ (eve::as<EVE_VALUE>());

  TTS_EQUAL(eve::if_else(vt   , vt, vf), vt);
  TTS_EQUAL(eve::if_else(vt   , st, vf), vt);
  TTS_EQUAL(eve::if_else(vt   , vt, sf), vt);
  TTS_EQUAL(eve::if_else(vt   , st, sf), vt);
  TTS_EQUAL(eve::if_else(st   , vt, vf), vt);
  TTS_EQUAL(eve::if_else(st   , st, vf), vt);
  TTS_EQUAL(eve::if_else(st   , vt, sf), vt);
  TTS_EQUAL(eve::if_else(st   , st, sf), st);
  TTS_EQUAL(eve::if_else(true , vt, vf), vt);
  TTS_EQUAL(eve::if_else(true , st, vf), vt);
  TTS_EQUAL(eve::if_else(true , vt, sf), vt);
  TTS_EQUAL(eve::if_else(true , st, sf), st);

  TTS_EQUAL(eve::if_else(vf   , vt, vf), vf);
  TTS_EQUAL(eve::if_else(vf   , vt, sf), vf);
  TTS_EQUAL(eve::if_else(vf   , st, vf), vf);
  TTS_EQUAL(eve::if_else(vf   , st, sf), vf);
  TTS_EQUAL(eve::if_else(sf   , vt, vf), vf);
  TTS_EQUAL(eve::if_else(sf   , vt, sf), vf);
  TTS_EQUAL(eve::if_else(sf   , st, vf), vf);
  TTS_EQUAL(eve::if_else(sf   , st, sf), sf);
  TTS_EQUAL(eve::if_else(false, vt, vf), vf);
  TTS_EQUAL(eve::if_else(false, vt, sf), vf);
  TTS_EQUAL(eve::if_else(false, st, vf), vf);
  TTS_EQUAL(eve::if_else(false, st, sf), sf);

  #if defined(EVE_SIMD_TESTS)
  eve::logical<T> mask  = [](auto i, auto) { return i%2 == 0; };
  eve::logical<T> ref   = [](auto i, auto) { return i%2 == 0 ? false : true; };

  TTS_EQUAL(eve::if_else(mask,vf,vt), ref);
  TTS_EQUAL(eve::if_else(mask,vf,st), ref);
  TTS_EQUAL(eve::if_else(mask,sf,vt), ref);
  TTS_EQUAL(eve::if_else(mask,sf,st), ref);
  #endif
}

TTS_CASE_TPL("Check eve::if_else(logical,T,T) variants", EVE_TYPE)
{
  auto vt = eve::true_  (eve::as<T>());
  auto st = eve::true_  (eve::as<EVE_VALUE>());
  auto vf = eve::false_ (eve::as<T>());
  auto sf = eve::false_ (eve::as<EVE_VALUE>());

  T          wt{42};
  T          wf{69};
  EVE_VALUE swt{42};
  EVE_VALUE swf{69};

  TTS_EQUAL(eve::if_else(vt   , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(vt   , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(vt   , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(vt   , swt , swf),  wt);
  TTS_EQUAL(eve::if_else(st   , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(st   , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(st   , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(st   , swt , swf), swt);
  TTS_EQUAL(eve::if_else(true , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(true , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(true , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(true , swt , swf), swt);

  TTS_EQUAL(eve::if_else(vf   , wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(vf   , wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(vf   , swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(vf   , swt , swf),  wf);
  TTS_EQUAL(eve::if_else(sf   , wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(sf   , wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(sf   , swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(sf   , swt , swf), swf);
  TTS_EQUAL(eve::if_else(false, wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(false, wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(false, swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(false, swt , swf), swf);

  #if defined(EVE_SIMD_TESTS)
  eve::logical<T> mask  = [](auto i, auto) { return i%2 == 0; };
  T               ref   = [](auto i, auto) { return i%2 == 0 ? 42 : 69; };

  TTS_EQUAL(eve::if_else(mask, wt, wf), ref);
  TTS_EQUAL(eve::if_else(mask,swt, wf), ref);
  TTS_EQUAL(eve::if_else(mask, wt,swf), ref);
  TTS_EQUAL(eve::if_else(mask,swt,swf), ref);
  #endif
}

TTS_CASE_TPL("Check eve::if_else(T,logical,logical) variants", EVE_TYPE)
{
  T          wt{42};
  T          wf{0};
  EVE_VALUE swt{42};
  EVE_VALUE swf{0};

  auto vt = eve::true_  (eve::as<T>());
  auto st = eve::true_  (eve::as<EVE_VALUE>());
  auto vf = eve::false_ (eve::as<T>());
  auto sf = eve::false_ (eve::as<EVE_VALUE>());

  TTS_EQUAL(eve::if_else(wt  , vt, vf), vt);
  TTS_EQUAL(eve::if_else(wt  , st, vf), vt);
  TTS_EQUAL(eve::if_else(wt  , vt, sf), vt);
  TTS_EQUAL(eve::if_else(wt  , st, sf), vt);
  TTS_EQUAL(eve::if_else(swt , vt, vf), vt);
  TTS_EQUAL(eve::if_else(swt , st, vf), vt);
  TTS_EQUAL(eve::if_else(swt , vt, sf), vt);
  TTS_EQUAL(eve::if_else(swt , st, sf), st);
  TTS_EQUAL(eve::if_else(42  , vt, vf), vt);
  TTS_EQUAL(eve::if_else(42  , st, vf), vt);
  TTS_EQUAL(eve::if_else(42  , vt, sf), vt);
  TTS_EQUAL(eve::if_else(42  , st, sf), st);

  TTS_EQUAL(eve::if_else(wf  , vt, vf), vf);
  TTS_EQUAL(eve::if_else(wf  , st, vf), vf);
  TTS_EQUAL(eve::if_else(wf  , vt, sf), vf);
  TTS_EQUAL(eve::if_else(wf  , st, sf), vf);
  TTS_EQUAL(eve::if_else(swf , vt, vf), vf);
  TTS_EQUAL(eve::if_else(swf , st, vf), vf);
  TTS_EQUAL(eve::if_else(swf , vt, sf), vf);
  TTS_EQUAL(eve::if_else(swf , st, sf), sf);
  TTS_EQUAL(eve::if_else(0   , vt, vf), vf);
  TTS_EQUAL(eve::if_else(0   , st, vf), vf);
  TTS_EQUAL(eve::if_else(0   , vt, sf), vf);
  TTS_EQUAL(eve::if_else(0   , st, sf), sf);

  #if defined(EVE_SIMD_TESTS)
  T mask              = [](auto i, auto) { return i%2 == 0 ? 42 : 0; };
  eve::logical<T> ref = [](auto i, auto) { return i%2 == 0 ? true : false; };

  TTS_EQUAL(eve::if_else(mask,vt,vf), ref);
  TTS_EQUAL(eve::if_else(mask,vt,sf), ref);
  TTS_EQUAL(eve::if_else(mask,st,vf), ref);
  TTS_EQUAL(eve::if_else(mask,st,sf), ref);
  #endif
}

TTS_CASE_TPL("Check eve::if_else(logical,T,T) variants", EVE_TYPE)
{
  T         vt{42};
  T         vf{0};
  EVE_VALUE st{42};
  EVE_VALUE sf{0};

  T          wt{42};
  T          wf{69};
  EVE_VALUE swt{42};
  EVE_VALUE swf{69};

  TTS_EQUAL(eve::if_else(vt , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(vt , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(vt , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(vt , swt , swf),  wt);
  TTS_EQUAL(eve::if_else(st , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(st , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(st , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(st , swt , swf), swt);
  TTS_EQUAL(eve::if_else(1  , wt  ,  wf),  wt);
  TTS_EQUAL(eve::if_else(1  , wt  , swf),  wt);
  TTS_EQUAL(eve::if_else(1  , swt ,  wf),  wt);
  TTS_EQUAL(eve::if_else(1  , swt , swf), swt);

  TTS_EQUAL(eve::if_else(vf , wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(vf , wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(vf , swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(vf , swt , swf),  wf);
  TTS_EQUAL(eve::if_else(sf , wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(sf , wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(sf , swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(sf , swt , swf), swf);
  TTS_EQUAL(eve::if_else(0  , wt  ,  wf),  wf);
  TTS_EQUAL(eve::if_else(0  , wt  , swf),  wf);
  TTS_EQUAL(eve::if_else(0  , swt ,  wf),  wf);
  TTS_EQUAL(eve::if_else(0  , swt , swf), swf);

  #if defined(EVE_SIMD_TESTS)
  T mask  = [](auto i, auto) { return i%2 == 0 ? 1 : 0; };
  T ref   = [](auto i, auto) { return i%2 == 0 ? 42 : 69; };

  TTS_EQUAL(eve::if_else(mask, wt, wf), ref);
  TTS_EQUAL(eve::if_else(mask,swt, wf), ref);
  TTS_EQUAL(eve::if_else(mask, wt,swf), ref);
  TTS_EQUAL(eve::if_else(mask,swt,swf), ref);
  #endif
}
