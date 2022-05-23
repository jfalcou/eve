//================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/special.hpp>
#include <eve/module/polynomial/regular/horner.hpp>
#include <eve/module/polynomial/regular/derivative.hpp>
#include <eve/module/polynomial/regular/primitive.hpp>
#include <eve/module/polynomial/regular/polyval.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/range.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/reduce2.hpp>
#include <eve/algo/reverse.hpp>
#include <eve/algo/views/reverse.hpp>
#include <eve/views/reverse.hpp>
#include <eve/algo/iota.hpp>
#include <eve/algo/fill.hpp>
#include <eve/algo/find.hpp>
#include <eve/algo/as_range.hpp>
#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>

namespace eve
{
  //================================================================================================
  //! @addtogroup simd_types
  //! @{
  //================================================================================================
  //! @brief representation of polynoms and monoms
  //!
  //! **Required header:** `#include <eve/module/polynomial.hpp>`
  //!
  //! eve::polynom and monom are templates structure representing respactivly polynomials with real
  //! or complex floating coefficients (resp polynomials with only one non zero coefficient).
  //! polynomials are internally based on std:vectors of coefficients on the fundamental basis and in
  //! decreasing powers order, but:
  //!
  //!  \f$ \displaystyle p(x) = \sum_0^n p[i]x^{i]\f$
  //!
  //!
  //! @tparam Type  Underlying scalar floating point type
  //!
  //! provided operators and functions are :
  //!
  //! - constructors
  //!    - trivial constructor provides the null polynomial (of degree -1) with no coefficients
  //!    - a constructor from a range of coefficients in decreasing power order
  //!    - a constructor from an initializer list of coefficients in decreasing power order
  //!    - a constructor from a range of elements in increasing power order (with second parameter eve::upward);
  //!
  //! - operators :
  //!     - +,  -, *, /, %, +=, -=, *=, /=, %=, <<, >>
  //!
  //!       binary operators accept mix of polynom, momom, value_type in any order.
  //!       monomial multiplication can be replaced by shift operators
  //!       division and remainder with null second parameter are UB.
  //!
  //!    - operator(): p(x) evaluates the polynomial p at x. x can be a scalar, an simd value or a range of scalar
  //!                  of the underlying type
  //!                  Take care that if a non const range is evaluted,  it is evaluated in place
  //!    - operator[]: p[i] return the coefficient of order i of the polynomial (i.e. of the monomial \f$x^i\f$.
  //!                  In particular 0 if i is not in the range \f$[0, degree(p)]\f$. (This operator is const).
  //!    - operator==: Two polynomials are equal if and only if they have the same degree and the same coefficients.
  //!    - operator!=: Two polynomials are not equal if and only if they do not have the same degree or two coefficients differ.
  //!
  //!@warning : this is a simple polynomial class not fit for big or sparse polynomials,  but for monomials or
  //!           dense polynomials of small degrees (in particular fft is not used for implementing *
  //!           (i.e. polynomial multiplication which could be written as a convolution)
  //!
  //! - friend functions
  //!     - degree returns the polynomial degree, i.e. the greatest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - valuation returns the polynomial valuation i.e. the lest power for which the polynomial
  //!       has a non null coefficient (-1 for the null polynomial)
  //!     - remquo computes both the quotient and remainder of euclidian division
  //!     - young(n, p0) suppress all coefficients of degree greater than n,  thus giving the regular part
  //!       of the Taylor-Young devlopment of the polynom
  //!     - young_remainder(n, p0) zeroes all the lower n coefficients of p0 : one have
  //!       young(n, p0)+young_remainder(n, p0) == p0.
  //!       concat(p1, p0) if n is the degree of p0, return the polynom \f$x^{n+1}p1+p0\f$.
  //!     - is_null returns true if and only if the polynomial is of degree -1
  //!     - is_constant returns true if and only if the polynomial is of degree less than 1
  //!     - is_monomial returns true if and only if the polynomial has only one non null coef
  //!     - derivative(p, n) computes the nth derivative of p
  //!     - primive(p, n)    computes a primitive of order n of p (the one with valuation greater or equal to n)
  //!
  //================================================================================================

  template<floating_scalar_value Type>
  struct polynom;


  template<floating_scalar_value Type>
  struct monom
  {
    /// Underlying type
    using value_type = Type;
    using monom_t  = monom<value_type>;
    using polynom_t = polynom<value_type>;
    friend polynom_t;
    using data_t = typename polynom_t::data_t;

    monom():deg(-1), data(0){};
    monom(value_type val, int degree) :deg(degree), data(val){if (data == 0) deg = -1; };
    monom(int degree) :deg(degree), data(value_type(1)){};

    explicit operator polynom_t()
    {
      return *this;
    };

    template<integral_value I>
    auto operator[](I const & i) const noexcept
    {
      if constexpr(scalar_value<I>)
        return (i == 0) ? data :value_type(0);
      else
        return if_else(is_eqz(i), data, zero);
    }

    monom_t friend operator*(monom_t const & m1,  monom_t const & m2)
    {
      if (m1.deg < 0 || m2.deg < 0) return monom_t();
      return monom_t(m1.data*m2.data, m1.deg+m2.deg);
    }

    monom_t friend operator*(monom_t const & m1,  value_type const & m2)
    {
      if (m1.deg < 0 || is_eqz(m2)) return monom_t();
      return monom_t(m1.data*m2, m1.deg);
    }

    monom_t friend operator*(value_type const & m1, monom_t const & m2 )
    {
      return m2*m1;
    }

    monom_t & operator*= (monom_t const & m)
    {
      return *this = (*this)*m;
    }

    polynom_t friend operator+(monom_t const & m0,  monom_t const & m1)
    {
      auto maxd = max(m0.deg, m1.deg);
      data_t r;
      r.resize(maxd+1);
      auto d = m0.deg-m1.deg;
      if (d == 0)
      {
        r[0] = m1.data+m0.data;
      }
      else if (m0.deg > m1.deg)
      {
        r[0] = m0.data;
        r[d] = m1.data;
      }
      else
      {
        r[0] = m1.data;
        r[-d] = m0.data;
      }
      return polynom_t(r);
    }

    polynom_t friend operator+(monom_t const & m0,  value_type const & m1)
    {
      if(is_null(m0)) return polynom_t(m1);
      else
      {
        polynom_t p(m0);
        p += m1;
        return p;
      }
    }

    polynom_t friend operator-(monom_t const & m0,  monom_t const & m1)
    {
      return m0+(-m1);
    }

    polynom_t friend operator-(monom_t const & m1,  value_type const & m0)
    {
      if(is_eqz(m0)) return polynom_t(m1);
      else
      {
        polynom_t p(m1);
        p -= m0;
        return p;
      }
    }

    int friend degree(monom_t const & m)
    {
      return m.deg;
    }

    value_type friend valuation(monom_t const & m)
    {
      return m.deg;
    }

    bool friend is_null(monom_t const & m)
    {
      return is_eqz(m.data);
    }

    bool friend is_constant(monom_t const & m)
    {
      return m.deg == 0;
    }

     bool friend is_monomial(monom_t const & )
    {
      return true;
    }

    monom_t friend operator-(monom_t const & m)
    {
      return monom_t(-m.data, m.deg);
    }

    kumi::tuple<monom_t, monom_t> friend remquo(monom_t const & m0, monom_t const & m1)
    {
      if (m1.data == 0) return {monom_t(-1, nan(as<value_type>())), monom_t(-1, nan(as<value_type>()))};
      if (m0.deg >= m1.deg)
        return {monom_t(), monom_t(m0.data/m1.data, m0.deg-m1.deg)};
      else
        return {monom_t(m0.data, m0.deg), monom_t()};
    }

    monom_t friend operator/(monom_t const & m0, monom_t const & m1)
    {
      auto [_, q] = remquo(m0, m1);
      return q;
    }

    auto operator/=(monom_t const & m1)
    {
      auto [_, q] = remquo(*this, m1);
      return *this = q;
    }

    monom_t friend operator%(monom_t const & m0, monom_t const & m1)
    {
      auto [r, _] = remquo(m0, m1);
      return r;
    }

    auto operator%=(monom_t const & m1)
    {
      auto [r, _] = remquo(*this, m1);
      return *this = r;
    }
    auto operator()(floating_value auto const & x)
    {
      return pow(x, deg)*data;
    }

    template <detail::range R>
    friend void tagged_dispatch( eve::tag::polyval_, inplace_type const&
                               , monom_t const & p, R & x)  noexcept
    {
      auto eval = [ p ](auto e){return pow(e, p.deg)*p.data; };
      eve::algo::transform_inplace(x, eval);
    }

    template <detail::range R>
    friend  R tagged_dispatch( eve::tag::polyval_, monom_t const & p, const R & x)  noexcept
    {
      return p(x);
    }

    template <detail::range R> [[nodiscard]] R operator()(R const & x) const noexcept
    {
      auto px(x);
      auto eval = [ this ](auto e){return pow(e, this->deg)*this->data; };
      eve::algo::transform_inplace(px, eval);
      return px;
    }

    friend bool operator==(monom_t const & p0, monom_t const & p1)
    {
      return (degree(p0) == degree(p1) && (p0.data == p1.data));
    }

    friend bool operator!=(monom_t const & p0, monom_t const & p1)
    {
      return (degree(p0) != degree(p1) || (p0.data == p1.data));
      if(degree(p0) != degree(p1)) return true;
      return degree(p0-p1) != -1;
    }

    template <class charT, class traits> friend
    inline std::basic_ostream<charT, traits>&
    operator << (std::basic_ostream<charT, traits>& os, const monom_t& m)
    {
      os << polynom_t(m);
      return os;
    }

    void normalize()
    {
      if (data == 0) deg = -1;
    }

    friend monom_t young(int n, monom_t const & m0)
    {
      return (n >= degree(m0)) ? m0 : monom_t();
    }

    friend monom_t young_remainder(int n, monom_t const & m0)
    {
      return (n >= degree(m0)) ? monom_t() : m0;
    }

  private :
    int deg;
    value_type data;
  };

  template<floating_scalar_value Type>
  struct polynom
  {
    /// Underlying type
    using value_type = Type;
    using polynom_t  = polynom<value_type>;
    using data_t     = std::vector<value_type>;
    using monom_t    = monom<value_type>;
    friend monom_t;

    // constructors
    polynom() :data(0) {}

    polynom(value_type const & v) : data(1, v){};
    polynom(std::initializer_list<value_type> const & c) : data(c){}

    template <detail::range R>
    polynom(R const & r) : polynom(r, downward_type()){}

    template < decorator Ordering, detail::range R>
    polynom(R const & r, Ordering const &)
      requires(is_one_of<Ordering>(detail::types<upward_type, downward_type> {}))
    {
      auto size = end(r)-begin(r);
      data.resize(size);
      if constexpr(std::same_as<Ordering, upward_type>)
        eve::algo::reverse_copy(r, data);
      else
        eve::algo::copy(r, data);
      normalize();
    }

    polynom(monom_t const & m) : data(degree(m)+1)
    {
      if (degree(m) >= 0) data[0] = m.data;
    };

    //==============================================================================================
    //== degree and valuation
    //==============================================================================================
    friend inline int degree(polynom_t const & p) noexcept
    {
      return p.data.size()-1;
    }

    friend inline int valuation(polynom_t const & p) noexcept
    {
      if (degree(p) == -1) return -1;
      auto r = algo::views::reverse(p.data);
      auto z = eve::algo::find_if(r, is_nez);
      return z-r.begin();
    }

    //==============================================================================================
    //== coefficients, index can be scalar or simd, but only for reading.
    //== Out of range returns 0
    //==============================================================================================
    template<integral_value I>
    auto operator[](I const & i) const noexcept
    {
      I d = degree(*this);
      if constexpr(scalar_value<I>)
        return (i >= 0 && i <= d) ? data[d-i] : zero(as<value_type>());
      else
        return if_else(i >= 0 && i <= d, gather(&data[0], d-i), zero);
    }

    //==============================================================================================
    //== evaluation
    //==============================================================================================
    template <floating_value T>
    auto operator()(T const & x) noexcept
    {
      if constexpr(simd_value<T>)
      {
       return horner(x, data);
      }
      else
      {
        using w_t =   eve::wide<T>;
        auto zz =  value_type(1);
        w_t xx([&zz, x](auto ,  auto){ auto z = zz; zz *= x; return z;});
        auto xc = zz;
        bool domul = false;
        auto sum = [&domul, &xx, xc](auto &s, auto v) {
          s = eve::fam(s, v, xx);
          if (domul) xx*= xc; else domul = true;
          return s;
        };
//        auto r = data;
        auto r = algo::views::reverse(data);
        eve::algo::reverse_copy(data, r);
        return eve::algo::reduce2[eve::algo::no_aligning][eve::algo::unroll<1>]
          (r, std::make_pair(sum, eve::zero(eve::as<T>()))
          , eve::add, eve::zero(eve::as<T>()));
      }
    }

    template <detail::range R>
    friend void tagged_dispatch( eve::tag::polyval_, inplace_type const&
                               , polynom_t const & p, R & x)  noexcept
    {
      auto horn = [ p ](auto e){return horner(e, p.data); };
      eve::algo::transform_inplace(x, horn);
    }

    template <detail::range R>
    friend  R tagged_dispatch( eve::tag::polyval_, polynom_t const & p, const R & x)  noexcept
    {
      return p(x);
    }

    template <detail::range R> [[nodiscard]] R operator()(R const & x) const noexcept
    {
      auto px(x);
      auto horn = [ this ](auto e){return horner(e, this->data); };
      eve::algo::transform_inplace(px, horn);
      return px;
    }

    //==============================================================================================
    //== derivatives
    //==============================================================================================

    friend polynom_t & tagged_dispatch( eve::tag::derivative_, inplace_type const &, polynom_t & p) noexcept
    {
      value_type n = degree(p);
      if(n < 0) return p;
      else if(n <= 1){ p.data.resize(n); return p;}
      else
      {
        auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), n+1);
        auto mult = [](auto pair) {
          auto [x, y] = pair;
          return x *= y;
        };
        eve::algo::transform_to(eve::algo::views::zip(p.data, factors), p.data, mult);
        p.data.resize(n);
        return p;
      }
    }

    [[nodiscard]] friend polynom_t tagged_dispatch( eve::tag::derivative_, polynom_t const & p0) noexcept
    {
      auto p = p0;
      return inplace(derivative)(p);
    }

    [[nodiscard]] friend polynom_t tagged_dispatch( eve::tag::derivative_
                                                  , polynom_t const & p0, size_t m) noexcept
    {
      auto p = p0;
      return inplace(derivative)(p, m);
    }

    friend polynom_t tagged_dispatch( eve::tag::derivative_
                                    , inplace_type const &, polynom_t & p, size_t m) noexcept
    {
      int n = degree(p);
      if (int(m) > n)  { p.data.resize(0); return p; }
      else if (int(m) == n) { p.data.resize(1); return p.data[0] = value_type(factorial(m));}
      else if (m == 0) return p;
      else if (m == 1) return inplace(derivative)(p);
      else
      {
        auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), n-m+1);
        data_t f(n-m+1);
        p.data.resize(n-m+1);
        eve::algo::copy(factors, f);
        auto mult = [](auto pair){
          auto [x, y] = pair;
          return x *= y;
        };
        eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, mult);
        for(size_t i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, dec);
          eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, mult);
        }
        return p;
      }
    }



    [[nodiscard]] friend auto tagged_dispatch( eve::tag::derivative_, polynom_t const & p
                                             , size_t m, eve::callable_all_) noexcept
    {
      int n = degree(p);
      std::vector<polynom_t> ders(m+1);
      ders[0] = p;
      if (m == 0 || n <= 0) return ders;
      ders[1] = derivative(p);
      if (m == 1) return ders;
      value_type nvt = n;
      auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), nvt+1);
      data_t f(n+1);
      data_t datad(n+1);
      eve::algo::copy(factors, datad);
      eve::algo::copy(factors, f);
      auto mult = [](auto pair) {
        auto [x, y] = pair;
        return x *= y;
      };
      eve::algo::transform_to(eve::algo::views::zip(datad, p.data), datad, mult);

      for(size_t i=2; i <= eve::min(size_t(n), m); ++i)
      {
        eve::algo::transform_inplace(f, dec);
        eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, mult);
        datad.resize(n-i+1);
        f.resize(n-i+1);
        ders[i] = polynom_t(datad);
      }
      return ders;
    }

    //==============================================================================================
    //== primitives
    //==============================================================================================
    friend polynom_t & tagged_dispatch( eve::tag::primitive_
                                      , inplace_type const &, polynom_t & p) noexcept
    {
      int n = degree(p);
      if(n < 0) return p;
      else if(n <= 1){ p.data.resize(n); return p;}
      else
      {
        value_type nvt = n+1;
        auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
        auto divi = [](auto pair){
          auto [x, y] = pair;
          return x /= y;
        };
        eve::algo::transform_to(eve::algo::views::zip(p.data, factors), p.data, divi);
        p.data.resize(n+2);
        return p;
      }
    }

    [[nodiscard]] friend polynom_t tagged_dispatch( eve::tag::primitive_
                                                  , polynom_t const & p) noexcept
    {
      int n = degree(p);
      if(n < 0) return polynom_t();
      else
      {
        value_type nvt = n+1;
        auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
        data_t datad(n+1);
        eve::algo::copy(p.data, datad);
        auto divi = [](auto pair){
            auto [x, y] = pair;
            return x /= y;
        };
        eve::algo::transform_to(eve::algo::views::zip(datad, factors), datad, divi);
        datad.resize(n+2);
        polynom_t prim(datad);
        return prim;
      }
    }

    [[nodiscard]] friend polynom_t tagged_dispatch( eve::tag::primitive_, polynom_t & p
                                    , size_t m) noexcept
    {
      size_t n = degree(p);
      if (m == 0 || n < 0) return p;
      else if (m == 1) return primitive(p);
      else
      {
        value_type nvt = n+1;
        auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
        data_t f(n+1);
        data_t datad(n+1);
        eve::algo::copy(p.data, datad);
        eve::algo::copy(factors, f);
        auto divi = [](auto pair)
          {
            auto [x, y] = pair;
            return x /= y;
          };
        eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
        for(size_t i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, inc);
          eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
        }
        datad.resize(n+m+1);
        polynom_t integ(datad);
        return integ;
      }
    }

    friend polynom_t tagged_dispatch( eve::tag::primitive_, inplace_type const &
                                    , polynom_t & p, size_t m) noexcept
    {
      size_t n = degree(p);
      if (m == 0 || n < 0) return p;
      else if (m == 1) return inplace(primitive)(p);
      else
      {
        value_type nvt = n+1;
        auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)),n+1);
        data_t f(n+1);
        eve::algo::copy(factors, f);
        auto divi = [](auto pair) {
          auto [x, y] = pair;
          return x /= y;
        };
        eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
        for(size_t i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, inc);
          eve::algo::transform_to(eve::algo::views::zip(p.data, f), p.data, divi);
        }
        p.data.resize(n+m+1);
        return p;
      }
    }

    [[nodiscard]] friend auto tagged_dispatch( eve::tag::primitive_
                                             , polynom_t const & p, size_t m
                                             , eve::callable_all_) noexcept
    {
      int n = degree(p);
      std::vector<polynom_t> prims(m+1);
      prims[0] = p;
      if (m == 0 || n <= 0) return prims;
      prims[1] = primitive(p);
      if (m == 1) return prims;
      value_type nvt = n+1;
      auto factors = eve::algo::views::iota_with_step(nvt, mone(as(nvt)), n+1);
      data_t f(n+1);
      data_t datad(n+1);
      eve::algo::copy(p.data, datad);
      eve::algo::copy(factors, f);
      auto divi = [](auto pair) {
        auto [x, y] = pair;
        return x /= y;
      };
      eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);

      for(size_t i=2; i <= m; ++i)
      {
        eve::algo::transform_inplace(f, inc);
        eve::algo::transform_to(eve::algo::views::zip(datad, f), datad, divi);
        prims[i] = polynom_t(datad);
        prims[i].data.resize(n+i+1);
      }
      return prims;
    }

    //==============================================================================================
    //=== operators
    //==============================================================================================

    //==============================================================================================
    //=== operator+ family
    //==============================================================================================
    friend polynom_t operator+(polynom_t const & p0, polynom_t const & p1)
    {
      int const n0 = p0.data.size();
      int const n1 = p1.data.size();
      int offset = abs(n0-n1);
      polynom_t r;
      r.data.resize(max(n0, n1));
      auto doit =  [&r, offset](auto const & p0,  auto const & p1) {
        std::copy(p1.data.begin(), p1.data.end(), r.data.begin()+offset);
        eve::algo::copy(p1.data, eve::algo::as_range(r.data.begin()+offset, r.data.end()));
        auto addi = [](auto pair){
          auto [x, y] = pair;
          return x+y;
        };
        eve::algo::transform_to(eve::algo::views::zip(r.data, p0.data), r.data, addi);
        r.normalize();
        return r;
      };
      return (n0 > n1) ? doit(p0, p1) : doit(p1, p0);
    }

    friend polynom_t operator+(polynom_t const & p0, value_type const & v)
    {
      if (is_eqz(v)) return p0;
      else if (degree(p0) < 0) return polynom_t(v);
      else
      {
        auto r(p0);
        r.data[degree(r)] += v;
        r.normalize();
        return r;
      }
    }

    friend polynom_t operator+(value_type const & v, polynom_t const & p0)
    {
      return p0+v;
    }

    friend polynom_t operator+(polynom_t const & p0, monom_t const & m)
    {
      auto dm = degree(m);
      if (dm < 0) return p0;
      else
      {
        auto r(p0);
        if (dm > degree(p0)) r.data.resize(dm+1);
        r.data[degree(r)-m.deg] += m.data;
        r.normalize();
        return r;
      }
    }

    friend polynom_t operator+(monom_t const & m, polynom_t const & p0)
    {
      return p0+m;
    }

    template < typename Other>
    polynom_t & operator+= (Other const & other)
    {
      return *this = *this+other;
    }

    //==============================================================================================
    //=== operator- family
    //==============================================================================================
    friend polynom_t operator-(polynom_t const & p0)
    {
      data_t mp0 = p0.data;
      eve::algo::transform_inplace(mp0, minus);
      return polynom_t(mp0);
    }

    template < typename Other>
    friend polynom_t operator-(polynom_t const & p0, Other const & o)
    {
      return p0+(-o);
    }

    template < typename Other>
    polynom_t & operator-= (Other const & other)
    {
      return *this = *this-other;
    }

    //=== operator* family
    friend polynom_t operator*(polynom_t const & p0, polynom_t const &  p1)
    {
      const size_t p1s = p1.data.size();
      const size_t size = p0.data.size() + p1s - 1;
      data_t r(size, value_type(0));
      auto b = r.begin();
      for (size_t i = 0; i < p0.data.size(); ++i, ++b) {
        auto p0i = p0.data[i];
        auto addit = [p0i](auto p){
          auto [ripj, p1j] = p;
          return fam(ripj, p0i, p1j);
        };
        auto z = eve::algo::as_range(b, b+p1s);
        eve::algo::transform_to(eve::algo::views::zip(z, p1.data), z , addit);
      }
      return polynom_t(r);
    }

    friend polynom_t operator*(polynom_t const & p0, value_type const & f)
    {
      auto r(p0);
      eve::algo::transform_inplace(r.data, [f](auto e){return e*f; });
      r.normalize();
      return r;
    }

    friend polynom_t operator*(value_type const & f, polynom_t const & p0)
    {
      auto r(p0);
      eve::algo::transform_inplace(r.data, [f](auto e){return e*f; });
      return r;
    }

    friend polynom_t operator*(polynom_t const & p0, monom_t const & m)
    {
      auto d = degree(m);
      if (d < 0) return polynom_t();
      else
      {
        polynom_t r(p0);
        r = r*m[0];
        if (d ==  0) return r;
        r.data.resize(p0.data.size()+d);
        return r;
      }
    }

    friend polynom_t operator*(monom_t const & m, polynom_t const & p0)
    {
      return p0*m;
    }

    template <typename Other>
    polynom_t & operator*= (Other const & other)
      requires(is_one_of<Other>(detail::types<polynom_t, monom_t, value_type> {}))
    {
      if constexpr(std::same_as<value_type, Other>)
      {
        eve::algo::transform_inplace(data, [other](auto e){return e*other; });
        normalize();
      }
      else if  constexpr(std::same_as<monom_t, Other>)
      {
        eve::algo::transform_inplace(data, [other](auto e){return e*other.data; });
        if (other.deg > 0) data.resize(data.size()+other.deg);
      }
      else
      {
        return *this = (*this)*other;
      }
      return *this;
    }

    //==============================================================================================
    //=== operator/ family and remquo
    //==============================================================================================
    friend kumi::tuple<polynom_t, polynom_t> remquo(polynom_t const & p0, polynom_t const & d)
    {
      int const n0 = p0.data.size();
      int const n1 = d.data.size();
      if (n1 == -1) return {d, polynom_t()};
      if (n1 == 0) {
        if (is_eqz(d.data[0])) return  {d, polynom_t()};
        else return {polynom_t(), p0*rec(d.data[0])};
      }
      if (n0 < n1) return {p0, polynom_t()};
      else
      {
        polynom_t r(p0);
        int i = -1;
        int deg = n0-n1;
        polynom_t q;
        q.data.resize(deg+1);
        while (degree(r) >= 0 && degree(r) >= degree(d))
        {
          auto t = r.data[0]/d.data[0];
          q.data[++i] = t;
          r = r-monom(t, deg)*d;
          --deg;
        }

        return {r, q};
      }
    }

    friend kumi::tuple<polynom_t, polynom_t> remquo(polynom_t const & p0, value_type const & d)
    {
      return {polynom_t(), p0*rec(d)};
    }

    friend kumi::tuple<polynom_t, polynom_t> remquo(polynom_t const & p0, monom_t const & d)
    {
      auto degd = degree(d);
      auto degp0= degree(p0);
      if (degd < 0)           return {polynom_t(), polynom_t()};
      else if (degd == 0)     return {polynom_t(), p0*rec(d.data)};
      else if (degd > degree(p0))  return {polynom_t(d), polynom_t()};
      else
      {
        auto q(p0);
        q.data.resize(degp0-degd+1);
        eve::algo::transform_inplace(q.data, [d](auto e){return e/d.data;});
        auto r(p0);
        r.data.resize(degd);
        eve::algo::copy(eve::algo::as_range(p0.data.begin()+degp0-degd+1, p0.data.end()), r.data);
        r.normalize();
        return {r, q};
      }
    }

    template < typename O>
    friend polynom_t operator/(polynom_t const & p0, O const & p1)
      requires(is_one_of<O>(detail::types<polynom_t, monom_t, value_type> {}))
    {
      if constexpr(std::same_as<O, value_type>)
      {
        auto fac =  rec(p1);
        return (is_not_finite(fac) || is_eqz(fac)) ? polynom_t() : p0*fac;
      }
      else
      {
        auto [_, q] = remquo(p0, p1);
        return q;
      }
    }

    template < typename O>
    auto operator/= (O const & p1)
      requires(is_one_of<O>(detail::types<polynom_t, monom_t, value_type> {}))
    {
      return *this = *this/p1;
    }

    template < typename O>
    friend polynom_t operator%(polynom_t const & p0, O const & p1)
      requires(is_one_of<O>(detail::types<polynom_t, monom_t, value_type> {}))
    {
      if constexpr(std::same_as<O, value_type>)
      {
        return polynom_t();
      }
      else
      {
        auto [r, _] = remquo(p0, p1);
        return r;
      }
    }

    template < typename O>
    auto operator%= (O const & p1)
      requires(is_one_of<O>(detail::types<polynom_t, monom_t, value_type> {}))
    {
      return *this = *this%p1;
    }

    //==============================================================================================
    //=== young and young_remainder
    //==============================================================================================

    friend polynom_t young(int n, polynom_t const & p0)
    {
      auto d = degree(p0);
      if (n >= d)
        return p0;
      else if (n == -1)
        return polynom_t();
      else
        return polynom_t(eve::algo::as_range(p0.data.begin()+d-n, p0.data.end()));
    }

    friend polynom_t young_remainder(int n, polynom_t const & p0)
    {
      auto d = degree(p0);
      if (n > d)
        return polynom_t();
      else if (n == -1)
        return p0;
      else
      {
        polynom_t yr(p0);
        eve::algo::fill(eve::algo::as_range(yr.data.begin()+d-n, yr.data.end()), value_type(0));
        return yr;
      }
    }

    //==============================================================================================
    //=== concat
    //==============================================================================================
    friend polynom_t concat(polynom_t const & p0, polynom_t const & p1)
    {
      auto d = degree(p0);
      if (d == -1) return p1;
      else return p0+monom_t(value_type(1), d+1)*p1;
    }


    //==============================================================================================
    //=== operator ==  and !=
    //==============================================================================================
    friend bool operator==(polynom_t const & p0, polynom_t const & p1)
    {
      if(degree(p0) != degree(p1)) return false;
      return degree(p0-p1) == -1;
    }

    friend bool operator==(polynom_t const & p0, monom_t const & p1)
    {
      if(degree(p0) != degree(p1)) return false;
      if(!is_monomial(p0)) return false;
      return (p0[0] == p1.data);
    }

    friend bool operator==( monom_t const & p0, polynom_t const & p1)
    {
      return p1 == p0;
    }

    friend bool operator!=(polynom_t const & p0, polynom_t const & p1)
    {
      if(degree(p0) != degree(p1)) return true;
      return degree(p0-p1) != -1;
    }

    friend bool operator!=(polynom_t const & p0, monom_t const & p1)
    {
      return (degree(p0) != degree(p1) || !is_monomial(p0)) ? true : (p0[0] != p1.data);
    }

    friend bool operator!=( monom_t const & p0, polynom_t const & p1)
    {
      return p1 != p0;
    }

    //==============================================================================================
    //=== predicates
    //==============================================================================================

    friend bool is_null(polynom_t const & p0)
    {
      return degree(p0) == -1;
    }

    friend bool is_constant(polynom_t const & p0)
    {
      return degree(p0) <=  0;
    }

    friend bool is_monomial(polynom_t const & p0)
    {
      return degree(p0) == valuation(p0);
    }

    //==============================================================================================
    //=== ostream
    //==============================================================================================
    template <class charT, class traits> friend
    inline std::basic_ostream<charT, traits>&
    operator << (std::basic_ostream<charT, traits>& os, const polynom<value_type>& poly)
    {
      auto const s = poly.data.size();
      if (s == 0)
        os << value_type(0);
      else if (s == 1)
        os << poly.data[0];
      else
      {
        auto c = poly.data[0];
        auto z = eve::abs(c);
        auto neg = is_ltz(c);
        if(eve::abs(z) == one(as(z)))
          os << (neg ? "-" : "");
        else
          os << std::noshowpos << poly.data[0];
        os << "x";
        if (s-1 != 1) os << "^" << (s-1);
        for( unsigned i = 1; i < poly.data.size()-1; ++i)
        {
          auto c = poly.data[i];
          if(is_nez(c))
          {
            auto z = eve::abs(c);
            auto neg = is_ltz(c);
            if(z == one(as(z))) os << (neg ? "-" : "+");
            else                os << std::showpos << c;
            if (s-i-1 == 1)     os << "x";
            else                os << "x" << "^"<< (s-i-1);
          }
        }
        if(is_nez(poly.data[s-1])) os << std::showpos << poly.data[s-1];
         os << std::noshowpos;
      }
      return os;
    }

    void normalize()
    {
      auto z = eve::algo::find_if(data, is_nez);
      data.erase(data.begin(), z);
    }

  private :

    static void internal_print(const std::string & name, data_t const & d)
    {
      std::cout << std::endl << name << std::endl;

      for(auto cur = d.begin(); cur != d.end(); ++cur)
      {
        std::cout << *cur << ",  ";
      }
    }

    data_t data;
  };
}
