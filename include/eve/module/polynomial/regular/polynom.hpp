//==================================================================================================
/*
  EVE - Expressive Vector Engine
  Copyright : EVE Contributors & Maintainers
  SPDX-License-Identifier: MIT
*/
//==================================================================================================
#pragma once

#include <eve/module/core.hpp>
#include <eve/module/polynomial/regular/horner.hpp>
#include <eve/detail/overload.hpp>
#include <eve/concept/range.hpp>
#include <eve/algo/copy.hpp>
#include <eve/algo/transform.hpp>
#include <eve/algo/views/reverse.hpp>
#include <eve/algo/views/zip.hpp>
#include <eve/algo/reverse.hpp>
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
  //!
  //! - methods
  //!    - p.derivative(n) computes the nth derivative of p
  //!    - p.primive(n)    computes a primitive of order n of p (the one with valuation greater or equal to n)
  //!
  //!      - with n = 0 these methods return the polynomial itself
  //!      - if n is negative p.derivative(n) is equivalent to p.integral(-n)
  //!      - if n is negative p.integral(n) is equivalent to p.derivative(-n)
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

    friend struct polynom<value_type>;

    monom():deg(-1), data(0){};
    monom(value_type val, int degree) :deg(degree), data(val){};

    monom_t friend operator*(monom_t const & m1,  monom_t const & m2)
    {
      if (m1.deg < 0 || m2.deg < 0) return monom_t();
      return monom_t(m1.data*m2.data, m1.deg+m2.deg);
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
      return false;
    }

    bool friend is_constant(monom_t const & m)
    {
      return m.deg == 0;
    }

     bool friend is_monomial(monom_t const & m)
    {
      return true;
    }

    monom_t friend operator-(monom_t const & m)
    {
      return monom_t(-m.data, m.deg);
    }
    auto operator()(floating_value auto const & x)
    {
      return pow(x, deg)*data;
    }

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
    friend inline int degree(polynom<value_type> const & p) noexcept
    {
      return p.data.size()-1;
    }

    friend inline int valuation(polynom<value_type> const & p) noexcept
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
      auto d = degree(*this);
      if constexpr(scalar_value<I>)
      {
        return (i >= 0 && i <= degree(*this) ? data[d-i] : zero(as<value_type>()));
      }
      else
      {
        return if_else(i >= 0 && i <= degree(*this), gather(&data[0], d-i), zero);
      }
    }

    //==============================================================================================
    //== evaluation
    //==============================================================================================
    [[nodiscard]] auto operator()(floating_value auto const & x) noexcept
    {
      return horner(x, data);
    }

    template <detail::range R> void operator()(R & x) const noexcept
    {
      auto horn = [this](auto e){return horner(e, this->data); };
      eve::algo::transform_inplace(x, horn);
    }

    template <detail::range R> [[nodiscard]] auto operator()(R const & x) const noexcept
    {
      R r(x);
      this->operator()(r);
      return r;
    }

    //==============================================================================================
    //== derivatives and primitives
    //==============================================================================================
    polynom_t derivative() const noexcept
    {
      value_type n = degree(*this);
      auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), degree(*this)+1);
      data_t datad(degree(*this)+1);

      eve::algo::copy(factors, datad);
      auto mult = [](auto pair)
        {
          get<0>(pair) *= get<1>(pair);
          return pair;
        };
      eve::algo::transform_inplace(eve::algo::views::zip(datad, data), mult);
      datad.resize(n);
      polynom_t der(datad);
      return der;
    }

    polynom_t primitive() const noexcept
    {
      value_type n = degree(*this);
      auto factors = eve::algo::views::iota_with_step(n+1, mone(as(n)), degree(*this)+1);
      data_t datad(degree(*this)+1);
      eve::algo::copy(factors, datad);
      auto divi = [](auto pair)
        {
          get<0>(pair) = get<1>(pair)/get<0>(pair);
          return pair;
        };
      eve::algo::transform_inplace(eve::algo::views::zip(datad, data), divi);
      datad.push_back(value_type(0));
      polynom_t integ(datad);
      return integ;
    }

    polynom_t derivative(int m) const noexcept
    {
      value_type n = degree(*this);
      if (m < 0)       return primitive(-m);
      else if (m > n)       return polynom_t(data_t(0));
      else if (m == 0) return *this;
      else if (m == 1) return derivative();
      else
      {
        auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), degree(*this)+1);
        data_t f(degree(*this)+1);
        data_t datad(degree(*this)+1);
        eve::algo::copy(factors, datad);
        eve::algo::copy(factors, f);
        auto mult = [](auto pair)
          {
            get<0>(pair) *= get<1>(pair);
            return pair;
          };
        eve::algo::transform_inplace(eve::algo::views::zip(datad, data), mult);

        for(int i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, dec);
          eve::algo::transform_inplace(eve::algo::views::zip(datad, f), mult);
        }
        datad.resize(n-m+1);
        polynom_t der(datad);
        return der;
      }
    }

    std::vector<polynom_t> derivatives(size_t m) const noexcept
    {
      value_type n = degree(*this);
      std::vector<polynom_t> ders(m+1, polynom_t());
      ders[0] = *this;
      if (m >= 1u) ders[1] = this->derivative();
      if(m <= 1u) return ders;
      auto factors = eve::algo::views::iota_with_step(n, mone(as(n)), degree(*this)+1);
      data_t f(degree(*this)+1);
      data_t datad(degree(*this)+1);
      eve::algo::copy(factors, datad);
      eve::algo::copy(factors, f);
      auto mult = [](auto pair)
        {
          get<0>(pair) *= get<1>(pair);
          return pair;
        };
      eve::algo::transform_inplace(eve::algo::views::zip(datad, data), mult);

      for(int i=2; i <= min(n, m); ++i)
      {
        eve::algo::transform_inplace(f, dec);
        eve::algo::transform_inplace(eve::algo::views::zip(datad, f), mult);
        datad.resize(n-i+1);
        ders[i] = polynom_t(datad);
      }
      return ders;
    }

    polynom_t primitive(int m) const noexcept
    {
      value_type n = degree(*this);
      if (m < 0)       return derivative(-m);
      else if (m == 0) return *this;
      else if (m == 1) return primitive();
      else
      {
        auto factors = eve::algo::views::iota_with_step(n+1, mone(as(n)), degree(*this)+1);
        data_t f(degree(*this)+1);
        data_t datad(degree(*this)+1);
        eve::algo::copy(data, datad);
        eve::algo::copy(factors, f);
        auto mult = [](auto pair)
          {
            get<0>(pair) /= get<1>(pair);
            return pair;
          };
        eve::algo::transform_inplace(eve::algo::views::zip(datad, f), mult);
        for(int i=2; i <= m; ++i)
        {
          eve::algo::transform_inplace(f, inc);
          eve::algo::transform_inplace(eve::algo::views::zip(datad, f), mult);
        }
        datad.resize(n+m+1);
        polynom_t integ(datad);
        return integ;
      }
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
        if (dm > degegree(p0)) r.data.resize(dm+1);
        r.data[degree(r)] += m.data;
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
      return *this+other;
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
      return *this-other;
    }

    //=== operator* family
    friend polynom_t operator*(polynom_t const & p0, polynom_t const &  p1)
    {
      const size_t size = p0.data.size() + p1.data.size() - 1;
      data_t r(size);
      for (size_t i = 0; i < p0.data.size(); ++i) {
        auto p0i = p0.data[i];
        auto addit = [p0i](auto p){
          auto [ripj, p1j] = p;
          return fam(ripj, p0i, p1j);
        };
        auto z = eve::algo::as_range(r.begin()+i, r.end());
        eve::algo::transform_to(eve::algo::views::zip(z, p1.data), z , addit);
      }

      return polynom_t(r);
    }

    friend polynom_t operator*(polynom_t const & p0, value_type const & f)
    {

      auto r(p0);
      eve::algo::transform_inplace(r.data, [f](auto e){return e*f; });
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
      if (m.deg < 0) return polynom_t();
      else
      {
        polynom_t r(p0);
        r = r*m.data;
        if (m.deg ==  0) return r;
        r.data.resize(p0.data.size()+m.deg);
        return r;
      }
    }

    friend polynom_t operator*(monom_t const & m, polynom_t const & p0)
    {
      return p0*m;
    }

    template < typename Other>
    polynom_t & operator*= (Other const & other)
    {
      return (*this)*other;
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
      if (n0 < n1) return {polynom_t(), d};
      else
      {
        polynom_t r(p0);
        int i = -1;
        int deg = n0-n1;
        polynom_t q;
        std::cout << "deg" << deg << std::endl;
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
      if (degd < 0)           return {polynom_t(), p0};
      else if (degd == 0)     return {polynom_t(), p0*rec(d.data)};
      else if (degd > degree(p0))  return {d, polynom_t()};
      else
      {
        auto q(p0);
        q.data.resize(degp0-degd);
        auto r(p0);
        eve::algo::copy(r.data, eve::algo::as_range(p0.data+degp0-degd, p0.qata.end));
        q.data.resize(degd);
        return {r, q};
      }
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

    friend bool operator!=(polynom_t const & p0, polynom_t const & p1)
    {
      if(degree(p0) != degree(p1)) return true;
      return degree(p0-p1) != -1;
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
            if(z == one(as(z)))
              os << (neg ? "-" : "+");
            else
              os << std::showpos << c;
            if (s-i-1 == 1)
              os << "x";
            else
              os << "x^"<< (s-i-1);
          }
        }
        if(is_nez(poly.data[s-1]))
          os << std::showpos << poly.data[s-1];
         os << std::noshowpos;
      }
      return os;
    }
//  private :

    static void internal_print(const std::string & name, data_t const & d){
      std::cout << std::endl << name << std::endl;
      for(size_t i=0; i < d.size(); ++i)
      {
        std::cout << d[i] << ",  ";
      }
      std::cout << std::endl;
    }

     void normalize()
    {
      auto z = eve::algo::find_if(data, is_nez);
      data.erase(data.begin(), z);
    }
    data_t data;
  };
}
