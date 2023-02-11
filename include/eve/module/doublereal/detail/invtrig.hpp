//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Project Contributors
  SPDX-License-Identifier: BSL-1.0
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/doublereal/regular/traits.hpp>
#include <eve/module/doublereal/detail/utilities.hpp>

////////////////////////////////////////////////////////////////////////////////////////////////////
/// just asin ansd acos and atan, asec and acsc are taken directly from math
////////////////////////////////////////////////////////////////////////////////////////////////////

namespace eve::detail
{

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::asin_, Z const& xx) noexcept
  {
    using doublereal_t =  element_type_t<Z>;
    using A10 = kumi::result::generate_t<10, doublereal_t>;
    using A11 = kumi::result::generate_t<11, doublereal_t>;
    auto PQ = [](){
      if constexpr(std::same_as<underlying_type_t<doublereal_t>, double>)
      {
        const A10 P = {
          doublereal_t(-0x1.9d0942ac2db01p-1, 0x1.7dabb4e469b92p-55),
          doublereal_t(0x1.83a6e8696d152p+5, -0x1.ab717185afbdcp-49),
          doublereal_t(-0x1.a982804d7b4bfp+9, -0x1.bda924b1c38f5p-46),
          doublereal_t(0x1.a9f3264322fe8p+12, 0x1.610aed66aa433p-43),
          doublereal_t(-0x1.cf9d6843d14a8p+14, -0x1.7728d659f1564p-40),
          doublereal_t(0x1.295a81ae41948p+16, 0x1.e9ce10adfb248p-38),
          doublereal_t(-0x1.ce400ed7777e7p+16, -0x1.9dacd5a8a59a1p-38),
          doublereal_t(0x1.abe739eb96973p+16, 0x1.c1931181a9d2p-38),
          doublereal_t(-0x1.b1ea7ddacbf2cp+15, -0x1.dacdbcbcd6401p-41),
          doublereal_t(0x1.72fa9c31d86e9p+13, -0x1.b38332b20f4efp-41)
        };
        const A11 Q = {
          doublereal_t(0x1p+0, 0x0p+0),
          doublereal_t(-0x1.4038060f6089p+6, 0x1.82ce4d583f7adp-50),
          doublereal_t(0x1.c654c02ac0731p+10, 0x1.092498eefc55ap-45),
          doublereal_t(-0x1.23b8b15497b3p+14, -0x1.d78ce51bf9cbep-42),
          doublereal_t(0x1.9973a974ea7e7p+16, -0x1.e5d459ffbed0ep-38),
          doublereal_t(-0x1.587005bf1d678p+18, 0x1.f5df7722233c9p-36),
          doublereal_t(0x1.6a9cc7c01e2b5p+19, 0x1.51f25df3137efp-37),
          doublereal_t(-0x1.e1985aeabfba1p+19, -0x1.4678df83a14d9p-35),
          doublereal_t(0x1.87e0aee47f0c2p+19, 0x1.46739957c76fbp-35),
          doublereal_t(-0x1.64bd0391e739p+18, 0x1.6ee1f9f4de078p-38),
          doublereal_t(0x1.163bf5256252ep+16, 0x1.b95d99fa7484dp-38)
        };
        return kumi::tuple{P, Q};
      }
      else //float
      {
        const A10 P = {
          doublereal_t(-0x1.9d0942p-1, -0x1.585b6p-26),
          doublereal_t(0x1.83a6e8p+5, 0x1.a5b454p-21),
          doublereal_t(-0x1.a9828p+9, -0x1.35ed3p-17),
          doublereal_t(0x1.a9f326p+12, 0x1.0c8bfap-14),
          doublereal_t(-0x1.cf9d68p+14, -0x1.0f452ap-12),
          doublereal_t(0x1.295a82p+16, -0x1.46f9aep-10),
          doublereal_t(-0x1.ce400ep+16, -0x1.aeeefcp-9),
          doublereal_t(0x1.abe73ap+16, -0x1.46968cp-12),
          doublereal_t(-0x1.b1ea7ep+15, 0x1.29a06ap-12),
          doublereal_t(0x1.72fa9cp+13, 0x1.8ec374p-14)
        };
        const A11 Q = {
          doublereal_t(0x1p+0, 0x0p+0),
          doublereal_t(-0x1.403806p+6, -0x1.ec112p-23),
          doublereal_t(0x1.c654cp+10, 0x1.560398p-17),
          doublereal_t(-0x1.23b8b2p+14, 0x1.56d09ap-11),
          doublereal_t(0x1.9973aap+16, -0x1.162b04p-9),
          doublereal_t(-0x1.587006p+18, 0x1.038a62p-8),
          doublereal_t(0x1.6a9cc8p+19, -0x1.ff0ea6p-8),
          doublereal_t(-0x1.e1985ap+19, -0x1.d57f74p-6),
          doublereal_t(0x1.87e0aep+19, 0x1.c8fe18p-6),
          doublereal_t(-0x1.64bd04p+18, 0x1.b8631cp-8),
          doublereal_t(0x1.163bf6p+16, -0x1.b53b5ap-9)
        };
        return kumi::tuple{P, Q};
      }
    };
    auto pq = PQ();
    auto posx = is_gtz(xx);
    auto a = abs(xx);
    auto hf = half(as(xx));
    if constexpr(scalar_value<Z>)
    {
      if (a > one(as(a))) return nan(as(a));
      if( a < Z(1.0e-18 )) return xx;
      auto zz = a;
      auto z = a;
      auto greater = z >  hf;
      if(greater)
      {
        zz = hf - zz;
        zz = ldexp( zz + hf, -1 );
        z = sqrt( zz );
      }
      else
      {
        zz = sqr(zz);
      }
      auto [P, Q] = pq;
      auto p = zz * horner( zz, P)/horner( zz, Q);
      z = z * p + z;
      if(greater)
      {
        z = z + z;
        z = pio_2(as(z)) - z;
      }
      return posx ? z :-z;
    }
    else
    {
    auto r = nan(as(a));
    auto notdone = a <= one(as(a));
      auto hf = half(as(xx));
      auto small = [](auto y) {return y; };
      auto great = [pq, hf](auto z) {
        auto [P, Q] = pq;
        auto zz = hf -z;
        zz = ldexp( zz + hf, -1 );
        z = sqrt( zz );
        auto p = zz * horner( zz, P)/horner( zz, Q);
        z = z * p + z;
        z = z + z;
        z = pio_2(as(z)) - z;
        return z;
      };
      auto medium = [pq](auto z) {
        auto [P, Q] = pq;
        auto zz = sqr(z);
        auto p = zz * horner( zz, P)/horner( zz, Q);
        z = z * p + z;
        return z;
      };

      if( eve::any(notdone) )
      {
        notdone = next_interval(small, notdone, is_less(a, Z(1.0e-18)), r, a);
        if( eve::any(notdone) )
        {
          notdone = next_interval(great, notdone, a >  hf, r, a);
          if( eve::any(notdone) ) { last_interval(medium, a <= hf, r, a); }
        }
      }
      return if_else(posx, r, -r);
    }
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::acos_, Z const& x) noexcept
  {

    if constexpr(scalar_value<Z>)
    {
      if (eve::abs(x) > one(as(x))) return nan(as(x));
      if( x < mhalf(as(x)) )
        return pi(as(x)) - 2 * asin(sqrt(average(one(as(x)), x)));
      if( x > half(as(x)) )
        return 2 * asin(sqrt(average(one(as(x)),-x)));
      return  pio_2(as(x)) - asin(x);
    }
    else if constexpr(has_native_abi_v<Z>)
    {
      auto r = nan(as(x));
      auto notdone = x <= one(as(x));
      auto small = [](auto x) { return pi(as(x)) - 2*asin(sqrt(average(one(as(x)), x))) ; };
      auto great = [](auto x) { return 2*asin(sqrt(average(one(as(x)),-x))); };
      auto medium = [](auto x) { return  pio_2(as(x)) - asin(x); };

      if( eve::any(notdone) )
      {
        notdone = next_interval(small, notdone, x < mhalf(as(x)), r, x);
        if( eve::any(notdone) )
        {
          notdone = next_interval(great, notdone, x > half(as(x)), r, x);
          if( eve::any(notdone) ) { last_interval(medium, abs(x) <= half(as(x)), r, x); }
        }
      }
      return r;
    }
    else
      return apply_over(acos, x);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::atan_, Z const& x) noexcept
  {
    if constexpr(has_native_abi_v<Z>)
      return asin(x/sqrt(inc(sqr(x))));
    else
      return apply_over(atan, x);
  }

  template<typename Z>
  auto
  doublereal_unary_dispatch(eve::tag::acot_, Z const& x) noexcept
  {
    if constexpr(has_native_abi_v<Z>)
      return signnz(x)*asin(rec(sqrt(inc(sqr(x)))));
    else
      return apply_over(acot, x);
  }

  //atan2
  template<typename Z>
  auto
  doublereal_binary_dispatch(eve::tag::atan2_, Z const& a0,  Z const & a1) noexcept
  {
    auto q = eve::abs(a0 / a1);
    auto z = atan(q);
    return if_else(is_positive(a1), z, (pi(eve::as(a0)) - z)) * signnz(a0);
  }
 }
