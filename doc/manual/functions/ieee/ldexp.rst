.. _function-ldexp:

#####
ldexp
#####

**Required header:** ``#include <eve/function/ldexp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ ldexp = {};
   }

Function object performing a shift to the left of an :ref:`IntegralValue <concept-integralvalue>`  by
another :ref:`IntegralValue <concept-value>`  with the same number of elements and same element size.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename U, typename N> wide<T,N> operator()( wide<T,N> const& v, wide<U,M> const& w ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( wide<T,N> const& v, U s ) noexcept;
   template<typename T, typename N, typename U> wide<T,N> operator()( T                s, wide<U,M> const& w ) noexcept;
   template<typename T, typename U> constexpr   T         operator()( T s, U t ) noexcept;

* [1] Computes element-wise product :math:`v2^w`.
* [2] Computes element-wise product :math:`v2^s`.
* [3] Computes element-wise product :math:`s2^w`.
* [4] Computes  :math:`s2^t`.

.. rubric:: Parameters

* **v**, Instance of :ref:`type-wide` satisfying  the :ref:`IEEEValue <concept-ieeevalue>` concept.
* **w**: Instance of :ref:`type-wide` satisfying  the :ref:`IntegralValue <concept-integralvalue>` concept.
* **s**  Floating point value.
* **t**: Integer value.

.. rubric:: Return value

* [1,2,4] A value with the same type as the first parameter.
* [3] A value of type **wide<T,N>**.


.. seealso::  :ref:`frexp <function-frexp>`, :ref:`ifrexp <function-ifrexp>`, :ref:`mantissa <function-mantissa>`, :ref:`exponent <function-exponent>`, 

*******
Example
*******

.. include:: ../../../../test/doc/core/ldexp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/ldexp.txt
  :literal:
