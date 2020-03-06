.. _function-pow:

###########
pow
###########

**Required header:** ``#include <eve/function/pow.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ pow = {};
   }

Function object computing :math:`x^y`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>             wide<T,N> operator()( wide<T,N> const& v, wide<T,N> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U x                ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( U         const& x, wide<T,N> const& w ) noexcept;
   template<typename T>             constexpr T           operator()( T s, T t ) noexcept;

* [1-3] Computes  element-wise the first parameter raised to the power  of the second.
* [4]   Computes the first parameter raised to the power  of the second.   

.. rubric:: Parameters

* **v**, **w**: Instances of :ref:`IEEEValue <concept-ieeevalue>`.
* **x** : Scalar floating point value. 
* **s**, **t**: Scalar floating point values of same type.

.. rubric:: Return value

* [1-3] A value with the same type as wide parameter.
* [4] A value of type **T**.


*******
Notes
*******

* Using `pow(x, y)` for :ref:`concept-ieeevalue` entries is similar to :math:`x^y`.

* The implementation is conform to the IEEE requirements, but no exeception is ever raised.

    - pow(:math:`+0`, exp), where exp is a negative odd integer, returns :math:`+\infty` 
    - pow(:math:`-0`, exp), where exp is a negative odd integer, returns :math:`-\infty`
    - pow(:math:`\pm0`, exp), where exp is negative, finite, and is an even integer or a non-integer, returns :math:`+\infty`
    - pow(:math:`\pm0`, :math:`-\infty`) returns :math:`+\infty`
    - pow(:math:`+0`, exp), where exp is a positive odd integer, returns :math:`+0`
    - pow(:math:`-0`, exp), where exp is a positive odd integer, returns :math:`-0`
    - pow(:math:`\pm0`, exp), where exp is positive non-integer or a positive even integer, returns :math:`+0`
    - pow(-1, :math:`\pm\infty`) returns 1
    - pow(+1, exp) returns 1 for any exp, even when exp is NaN
    - pow(base, :math:`\pm0`) returns 1 for any base, even when base is NaN
    - pow(base, exp) returns NaN if base is finite and negative and exp is finite and non-integer.
    - pow(base, :math:`-\infty`) returns :math:`+\infty` for any |base|<1
    - pow(base, :math:`-\infty`) returns :math:`+0` for any |base|>1
    - pow(base, :math:`+\infty`) returns :math:`+0` for any |base|<1
    - pow(base, :math:`+\infty`) returns :math:`+\infty` for any |base|>1
    - pow(:math:`-\infty`, exp) returns :math:`-0` if exp is a negative odd integer
    - pow(:math:`-\infty`, exp) returns :math:`+0` if exp is a negative non-integer or even integer
    - pow(:math:`-\infty`, exp) returns :math:`-\infty` if exp is a positive odd integer
    - pow(:math:`-\infty`, exp) returns :math:`+\infty` if exp is a positive non-integer or even integer
    - pow(:math:`+\infty`, exp) returns :math:`+0` for any negative exp
    - pow(:math:`+\infty`, exp) returns :math:`+\infty` for any positive exp
    except where specified above, if any argument is NaN, NaN is returned 

* With raw_ decorator  uses the naive formula (:math:`e^{y\log x}'
         and so does not care for limits and leads to lower accuracy. In particular it returns NaN for negative base
 

*******
Options
*******

*******
Example
*******

.. include:: ../../../../test/doc/core/pow.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/pow.txt
  :literal:
