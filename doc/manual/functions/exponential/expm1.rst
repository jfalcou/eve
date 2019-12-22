.. _function-expm1:

######
expm1
######

**Required header:** ``#include <eve/function/expm1.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpm1r /* implementation defined */ expm1 = {};
   }

Function object computing the  exponential minus one of(:math:`e^x-1`) of an :ref:`IEEEValue <concept-ieeevalue>`,
with good accuracy even near 0.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpm1r    T         operator()( T s ) noexcept;

* [1] Computes the element-wise exponential minus oneof the :ref:`wide <type-wide>`.
* [10] Computes the base 10  exponential of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`IEEEValue <concept-ieeevalue>`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,10] A value with the same type as the parameter. 

.. seealso::  :ref:`exp <function-exp>`,  :ref:`expm1 <function-*expm1>`,  :ref:`exp10 <function-*exp10>`,
  :ref:`log <function-log>`, :ref:`log <function-log>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, 

Example
*******

.. include:: ../../../../test/doc/core/expm1.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/expm1.txt
  :literal:
