//==================================================================================================
/**
  EVE - Expressive Vector Engine
  Copyright 2020 Joel FALCOU
  Copyright 2020 Jean-Thierry LAPRESTE

  Licensed under the MIT License <http://opensource.org/licenses/MIT>.
  SPDX-License-Identifier: MIT
**/
//==================================================================================================
#pragma once

#include <array>
#include <eve/constant/nan.hpp>
#include <eve/as.hpp>
#include <eve/function/nbtrue.hpp>
#include <eve/function/logical_andnot.hpp>
#include <eve/concept/value.hpp>

// This is a help for programming efiicient horizontal branching
// supose we have a function special(x) that has a scalar implementation
// using 4 branches as:
// if (x <=  lim1) return f1(x);
// else if (x <=  lim2) return f2(x);
// else if (x <=  lim3) return f3(x);
// else if (x <=  lim4) return f4(x);
// else return f5(x);
// with lim1 <= lim2 <= lim3 <=  lim4
// The simd function can be written as such:

//  hz_device hz;
//  hz.first_interval(f1, lim1, x) &&
//  hz.next_interval(f2, lim2) &&
//  hz.next_interval(f3, lim3) &&
//  hz.last_interval(f4, f5, lim4);
//  return hz.result();

// if last_interval is not called the results for x > limn (greater limit used are 0
// by default,  but can be set with the class construtor hz(init)

namespace eve::detail
{
  template < typename T> struct hz_device
  {
    template < typename U >
    hz_device(U remain)
      : nb_(0),
        notdone_(true),
        test0_(true),
        test_(false),
        r_(remain)
    {};

    hz_device()
      : nb_(0),
        notdone_(true),
        test0_(true),
        test_(false),
        r_(0)
    {};

    auto result() const noexcept { return r_; }
    auto notdone() const noexcept { return notdone_; }
    auto reset(T remain = eve::nan(eve::as<T>()))  noexcept
    {
      nb_ = 0;
      notdone_ = false;
      test0_ = true;
      test_ = false;
      r_ = remain;
    }

    template <typename F, typename U>
    bool first_interval(F const & f, U const & val, T x) noexcept
    {
      x_ = x;
      test0_ = x_ <= val;
      if constexpr(eve::scalar_value<T>)
      {
        r_ = test0_ ? f(x_) : r_;
        notdone_ = !test0_;
      }
      else
      {
        if (notdone_)
        {
          test_ = test0_;
          std::size_t nbc = nbtrue(test_);
          if (nbc > 0)
          {
            r_ = if_else(test_, f(x_), r_);
            nb_+= nbc;
            notdone_ = (nbc <  T::static_size);
          }
        }
      }
      return notdone_;
    }

    template <typename F, typename U>
    bool intermediate(F const & f) noexcept
    {
      f();
      return notdone_;
    }

    template <typename F, typename U>
    bool next_interval(F const & f, U const & val) noexcept
    {
      test0_ = x_ <= val;
      if constexpr(eve::scalar_value<T>)
      {
        r_ = test0_ ? f(x_) : r_;
        notdone_ = !test0_;
      }
      else
      {
        if (notdone_)
        {
          test_ = logical_andnot(test0_, test_);
          std::size_t nbc = nbtrue(test_);
          if (nbc > 0)
          {
            r_ = if_else(test_, f(x_), r_);
            nb_+= nbc;
            notdone_ = (nbc <  T::static_size);
          }
          test_ = test0_;
        }
      }
      return notdone_;
    }

    template <typename F, typename G, typename U>
    bool last_interval(F const & f, G const & g, U const & val) noexcept
    {
      test0_ = x_ <= val;
      if constexpr(eve::scalar_value<T>)
      {
        r_ = test0_ ? f(x_) : g(x_);
        notdone_ = false;
      }
      else
      {
        if (notdone_)
        {
          test_ = logical_andnot(test0_, test_);
          std::size_t nbc = nbtrue(test_);
          if (nbc > 0)
          {
            r_ = if_else(test_, f(x_), r_);
            nb_+= nbc;
            if (nb_ <  T::static_size)
            {
              r_ = if_else(test0_, r_, g(x_));
            }
            notdone_ = false;
          }
        }
      }
      return notdone_;
    }

//     template <typename F, typename U>
//     bool last_interval(F const & f, U const & val) noexcept
//     {
//       test0_ = x_ > val;
//       if constexpr(eve::scalar_value<T>)
//       {
//         r_ = test0_ ? f(x_) : r_;
//         notdone_ = false;
//       }
//       else
//       {
//         if (notdone_)
//         {
//           std::size_t nbc = nbtrue(test0_);
//           if (nbc > 0)
//           {
//             r_ = if_else(test0_, f(x_), r_);
//             notdone_ = false;
//           }
//         }
//       }
//       return notdone_;
//     }

  private:
    std::size_t nb_;
    bool        notdone_;
    logical<T>  test0_;
    logical<T>  test_;
    T           r_;
    T           x_;

  };
}
