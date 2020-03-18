.. _function-asech:

#####
asech
#####

**Required header:** ``#include <eve/function/asech.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ asech = {};
   }

Function object computing the hyperbolic arccosine  of the inverse an  :ref:`IEEEValue <concept-ieeevalue>`.

``asech(x)`` returns the argument :math:`r` in the interval   :math:`[1, \infty]` such that :math:`\cosh(r) == 1/x`.
If :math:`x` is outside :math:`[0,1]` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes element-wise  the hyperbolic arccosine of the :ref:`IEEEValue <concept-ieeevalue>`.
* [2] Computes the the hyperbolic arccosine of the scalar.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance
* **s**: Scalar floating value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`asinh <function-asinh>`,  :ref:`atanh <function-atanh>`,  :ref:`acoth <function-acoth>`, 
 :ref:`acosh <function-acosh>`,  :ref:`acsch <function-acsch>`, :ref:`sinh <function-sinh>`,  :ref:`tanh <function-tanh>`,  :ref:`coth <function-coth>`, 
 :ref:`cosh <function-cosh>`,  :ref:`csch <function-csch>`

Notes
*******

  -  if the argument is greater than 1, a NaN is returned
  -  if the argument is 1, +0 is returned
  -  if the argument is 0`, :math:`\infty` is returned
  -  if the argument is NaN, a NaN is returned 


Example
*******

.. include:: ../../../../test/doc/core/asech.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/asech.txt
  :literal:
