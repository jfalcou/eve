.. _function-acoth:

#####
acoth
#####

**Required header:** ``#include <eve/function/acoth.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ acoth = {};
   }

Function object computing the hyperbolic arccotangent  of an  :ref:`IEEEValue <concept-ieeevalue>`.

``acot(x)`` returns the argument :math:`r` in the interval   :math:`[-\infty, \infty]` such that :math:`\coth(r) == x`.
If :math:`x` is inside :math:`]-1, 1[` the result is a Nan.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes element-wise  the hyperbolic arccotangent of the :ref:`IEEEValue <concept-ieeevalue>`.
* [2] Computes the the hyperbolic arccotangent of the scalar.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` inscotce
* **s**: Scalar floating value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`acosh <function-acosh>`,  :ref:`asinh <function-asinh>`,  :ref:`atanh <function-atanh>`, 
 :ref:`asech <function-asech>`,  :ref:`acsch <function-acsch>`,  :ref:`cosh <function-cosh>`,  :ref:`sinh <function-sinh>`,  :ref:`tanh <function-tanh>`, 
 :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Notes
*******

  -  if the argument is :math:`\pm1`, :math:`\pm\infty` is returned.
  -  if the argument absolute value is less than 1 a NaN is returned.
  -  if the argument is NaN, a NaN is returned 

Example
*******

.. include:: ../../../../test/doc/core/acoth.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/acoth.txt
  :literal:
