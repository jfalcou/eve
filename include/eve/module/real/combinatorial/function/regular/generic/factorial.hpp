//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/concept/value.hpp>
#include <eve/detail/implementation.hpp>
#include <eve/detail/skeleton_calls.hpp>
#include <eve/function/all.hpp>
#include <eve/function/gather.hpp>
#include <eve/function/inc.hpp>
#include <eve/function/converter.hpp>
#include <eve/function/if_else.hpp>
#include <eve/function/is_gez.hpp>
#include <eve/constant/inf.hpp>
#include <eve/constant/valmax.hpp>

#include <type_traits>
#include <eve/detail/apply_over.hpp>

namespace eve::detail
{

  template<unsigned_value T>
  EVE_FORCEINLINE auto factorial_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    constexpr std::array<double, 171> dfactorials = { {
        0x1p+0,
        0x1p+0,
        0x1p+1,
        0x1.8p+2,
        0x1.8p+4,
        0x1.ep+6,
        0x1.68p+9,
        0x1.3bp+12,
        0x1.3bp+15,
        0x1.626p+18,
        0x1.baf8p+21,
        0x1.308a8p+25,
        0x1.c8cfcp+28,
        0x1.7328ccp+32,
        0x1.44c3b28p+36,
        0x1.30777758p+40,
        0x1.30777758p+44,
        0x1.437eeecd8p+48,
        0x1.6beecca73p+52,
        0x1.b02b930689p+56,
        0x1.0e1b3be415ap+61,
        0x1.6283be9b5c62p+65,
        0x1.e77526159f06cp+69,
        0x1.5e5c335f8a4cep+74,
        0x1.06c52687a7b9ap+79,
        0x1.9a940c33f6121p+83,
        0x1.4d9849ea37eebp+88,
        0x1.19787e5d9f316p+93,
        0x1.ec92dd23d6967p+97,
        0x1.be6518687a785p+102,
        0x1.a27ec6e1f2d0dp+107,
        0x1.956ad0aae33a4p+112,
        0x1.956ad0aae33a4p+117,
        0x1.a21627303a541p+122,
        0x1.bc3789a33df96p+127,
        0x1.e5dcbe8a8bc8cp+132,
        0x1.114c2b2deea0fp+138,
        0x1.3c0011ed1bea1p+143,
        0x1.774015499125fp+148,
        0x1.c95619f1a8e64p+153,
        0x1.1dd5d037098fep+159,
        0x1.6e39f2c684406p+164,
        0x1.e0ac0ea48d948p+169,
        0x1.42f399d68f1fcp+175,
        0x1.bc0ef38704cbbp+180,
        0x1.383a833aef5f3p+186,
        0x1.c0d41ca4b818ep+191,
        0x1.499bc508f7324p+197,
        0x1.ee69a78d72cb6p+202,
        0x1.7a88e4484be3bp+208,
        0x1.27baf2587b49ep+214,
        0x1.d751f23d047dcp+219,
        0x1.7ef294d193a63p+225,
        0x1.3d20e33d8e45ap+231,
        0x1.0b93bfbbf00acp+237,
        0x1.cbe5f18b04928p+242,
        0x1.92693359a4003p+248,
        0x1.6665b1bbd6102p+254,
        0x1.44cc291239feap+260,
        0x1.2b6c35dccd76cp+266,
        0x1.18b5727f009f5p+272,
        0x1.0b8cf1210c97ep+278,
        0x1.0330899804332p+284,
        0x1.fe478ee34844ap+289,
        0x1.fe478ee34844ap+295,
        0x1.0320568f6ab2ep+302,
        0x1.0b395943e6087p+308,
        0x1.17c0097314d0dp+314,
        0x1.293c0a0a461dep+320,
        0x1.4074bad313983p+326,
        0x1.5e7fac56dd6e8p+332,
        0x1.84d5a3305da69p+338,
        0x1.b5705796695b6p+344,
        0x1.f2f423e7902c4p+350,
        0x1.207524c1df599p+357,
        0x1.5209471331bdp+363,
        0x1.916b0466cb107p+369,
        0x1.e2f4c14bac4fcp+375,
        0x1.264d25ca1d009p+382,
        0x1.6b473aa57bcccp+388,
        0x1.c619094edabffp+394,
        0x1.1f5bd7e3e66d7p+401,
        0x1.702dac9bff3c4p+407,
        0x1.dd7b3bda4f022p+413,
        0x1.3958df4743d96p+420,
        0x1.a02a088aa61cbp+426,
        0x1.179c3dbd279b5p+433,
        0x1.7c1863ed21d72p+439,
        0x1.0550c4b30743ep+446,
        0x1.6b645188f61a6p+452,
        0x1.ff0512a89a152p+458,
        0x1.6b4d9b43dd8bp+465,
        0x1.051fc798c73bfp+472,
        0x1.7b722e0a01831p+478,
        0x1.16a7d9cf591c4p+485,
        0x1.9da1274fc845fp+491,
        0x1.3638dd7bd6347p+498,
        0x1.d62e2fafb0a78p+504,
        0x1.67fb5c8283404p+511,
        0x1.166c698cf183bp+518,
        0x1.b30964ec395dcp+524,
        0x1.574569a26544p+531,
        0x1.118b502d68b23p+538,
        0x1.b83c3509147ecp+544,
        0x1.65b0eb1760a7p+551,
        0x1.256b20d92d49p+558,
        0x1.e5f96e67b300ep+564,
        0x1.963e824aafa2cp+571,
        0x1.56c4bdef04315p+578,
        0x1.23e389bd8992p+585,
        0x1.f5af14bdc472fp+591,
        0x1.b30dd3fc905bap+598,
        0x1.7cac197cfe503p+605,
        0x1.500fee805882dp+612,
        0x1.2b4e306a4ed48p+619,
        0x1.0ce83f7f82d2fp+626,
        0x1.e764f3171d1e4p+632,
        0x1.bd824633209dbp+639,
        0x1.9ab418b722116p+646,
        0x1.7dd36efa41ac2p+653,
        0x1.65f6380a9d916p+660,
        0x1.5262c0fa08f37p+667,
        0x1.42861fee5088p+674,
        0x1.35ece2af0162bp+681,
        0x1.2c3d7b998957ap+688,
        0x1.25340ab3f01f9p+695,
        0x1.209f3a89205f1p+702,
        0x1.1e5dfc140e1e5p+709,
        0x1.1e5dfc140e1e5p+716,
        0x1.209ab80c363a9p+723,
        0x1.251d22ec67138p+730,
        0x1.2bfbd1bdf17dfp+737,
        0x1.355bb04be109ep+744,
        0x1.4171452ed7d44p+751,
        0x1.5082946d09f23p+758,
        0x1.62e9b88b007d7p+765,
        0x1.79185413b0855p+772,
        0x1.939c09fd12eebp+779,
        0x1.b3243ac4d8695p+786,
        0x1.d88957d1c3026p+793,
        0x1.026b1c06b6a55p+801,
        0x1.1ca9fcdf65321p+808,
        0x1.3bcc9487d4439p+815,
        0x1.60ce8defbf238p+822,
        0x1.8ce85fadb707ep+829,
        0x1.c19f3c62c956fp+836,
        0x1.006cd07056d39p+844,
        0x1.267cf76103b7p+851,
        0x1.54807e082c4b9p+858,
        0x1.8c5d92b5839p+865,
        0x1.d07da7ecb62ccp+872,
        0x1.11fa1e0c9f746p+880,
        0x1.455903aefd5a3p+887,
        0x1.84e466672ad5dp+894,
        0x1.d3e2cb341f894p+901,
        0x1.1b4a51088f182p+909,
        0x1.594292c26e656p+916,
        0x1.a77ba8027b686p+923,
        0x1.055e51b1882a7p+931,
        0x1.44ab297a8724bp+938,
        0x1.95d5f3d928edep+945,
        0x1.fe771cb7257b3p+952,
        0x1.4307602be5b7fp+960,
        0x1.9b5b6477e6884p+967,
        0x1.07868c5ccfaf4p+975,
        0x1.53b370efa3b7fp+982,
        0x1.b88cb676c8529p+989,
        0x1.1f63cb077cadep+997,
        0x1.7932fa79d3a43p+1004,
        0x1.f2054eb4d96ecp+1011
      }};
    if constexpr(has_native_abi_v<T>)
    {
      if constexpr(scalar_value<T>)
      {
        return (n < 171u) ? dfactorials[n] : inf(as<double>());
      }
      else
      {
        auto test = (n < 171u);
        auto nn = if_else(test, n,  zero);
        auto r =  gather( &dfactorials[0], nn);
        return if_else(test, r, inf(as(r)));
      }
    }
    else
      return apply_over(factorial, n);
  }

  template<signed_integral_value T>
  EVE_FORCEINLINE auto factorial_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    EVE_ASSERT(eve::all(is_gez(n) ), "factorial : some entry elements are not positive");
    return factorial(uint_(n));
  }

  template<floating_real_value T>
  EVE_FORCEINLINE auto factorial_(EVE_SUPPORTS(cpu_), T n) noexcept
  {
    EVE_ASSERT(eve::all(is_flint(n)), "factorial : some entry elements are not flint");
    EVE_ASSERT(eve::all(is_gez(n) )  , "factorial : some entry elements are not positive");
    EVE_ASSERT(eve::all(n <  std::same_as<elt_t, double> ? 171u : 36u )  , "factorial : some entry elements will produce overflow");
    using elt_t = element_type_t<T>;
    auto nn = uint_(n);
    auto r = factorial(nn);
    if constexpr(std::same_as<elt_t, double>) return r; else return float32(r);
  }

}
