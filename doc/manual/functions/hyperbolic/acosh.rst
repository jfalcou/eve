.. _function-acosh:

#####
acosh
#####

**Required header:** ``#include <eve/function/acosh.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ acosh = {};
   }

Function object computing the hyperbolic arccosine  of an  :ref:`IEEEValue <concept-ieeevalue>`.

``acos(x)`` returns the argument :math:`r` in the interval   :math:`[0, \infty]` such that :math:`\cosh(r) == x`.
If :math:`x` is outside :math:`[1, \infty]` the result is a Nan.

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
 :ref:`asech <function-asech>`,  :ref:`acsch <function-acsch>`, :ref:`sinh <function-sinh>`,  :ref:`tanh <function-tanh>`,  :ref:`coth <function-coth>`, 
 :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Notes
*******

  -  if the argument is less than 1, a NaN is returned
  -  if the argument is 1, +0 is returned
  -  if the argument is :math:`\infty`, :math:`\infty` is returned
  -  if the argument is NaN, a NaN is returned 


Example
*******

.. include:: ../../../../test/doc/core/acosh.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/acosh.txt
  :literal:
