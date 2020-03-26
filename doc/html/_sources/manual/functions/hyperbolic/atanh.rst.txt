.. _function-atanh:

#####
atanh
#####

**Required header:** ``#include <eve/function/atanh.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ atanh = {};
   }

Function object computing the hyperbolic arctangent  of an  :ref:`IEEEValue <concept-ieeevalue>`.

``atan(x)`` returns the argument :math:`r` in the interval   :math:`[-\infty, \infty]` such that :math:`\tanh(r) == x`.
If :math:`x` is outside :math:`[-1, 1]` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes element-wise  the hyperbolic arctangent of the :ref:`IEEEValue <concept-ieeevalue>`.
* [2] Computes the the hyperbolic arctangent of the scalar.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance
* **s**: Scalar floating value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`acosh <function-acosh>`,  :ref:`asinh <function-asinh>`,  :ref:`acoth <function-acoth>`, 
 :ref:`asech <function-asech>`,  :ref:`acsch <function-acsch>`,  :ref:`cosh <function-cosh>`,  :ref:`sinh <function-sinh>`,  :ref:`coth <function-coth>`, 
 :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Notes
*******

  -  if the argument is :math:`\pm0`, it is returned unmodified
  -  if the argument is :math:`\pm1`, :math:`\pm\infty` is returned.
  -  if the argument absolute value is greater than 1, NaN is returned.
  -  if the argument is NaN, a NaN is returned 

Example
*******

.. include:: ../../../../test/doc/core/atanh.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/atanh.txt
  :literal:
