.. _function-exp:

###
exp
###

**Required header:** ``#include <eve/function/exp.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ exp = {};
   }

Function object computing the exponential (:math:`e^x`) of an :ref:`IEEEValue <concept-ieeevalue>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes the element-wise  exponential of the :ref:`wide <type-wide>`.
* [2] Computes the exponential of the scalar.

.. rubric:: Parameters

* **v**: Instance of :ref:`IEEEValue <concept-ieeevalue>`.
* **s**: Scalar value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 

.. seealso::  :ref:`exp2 <function-exp2>`,  :ref:`exp10 <function-*exp10>`,  :ref:`expm1 <function-*expm1>`,
  :ref:`log <function-log>`, :ref:`log2 <function-log2>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, 

Example
*******

.. include:: ../../../../test/doc/core/exp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/exp.txt
  :literal:
