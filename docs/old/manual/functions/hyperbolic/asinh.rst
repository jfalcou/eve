.. _function-asinh:

#####
asinh
#####

**Required header:** ``#include <eve/function/asinh.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ asinh = {};
   }

Function object computing the hyperbolic arcsine  of an  :ref:`IEEEValue <concept-ieeevalue>`.

``asin(x)`` returns the argument :math:`r` in the interval   :math:`[-\infty, \infty]` such that :math:`\sinh(r) == x`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes element-wise  the hyperbolic arcsine of the :ref:`IEEEValue <concept-ieeevalue>`.
* [2] Computes the the hyperbolic arcsine of the scalar.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance
* **s**: Scalar floating value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`acosh <function-acosh>`,  :ref:`atanh <function-atanh>`,  :ref:`acoth <function-acoth>`, 
 :ref:`asech <function-asech>`,  :ref:`acsch <function-acsch>`, :ref:`cosh <function-cosh>`,  :ref:`tanh <function-tanh>`,  :ref:`coth <function-coth>`, 
 :ref:`sech <function-sech>`,  :ref:`csch <function-csch>`

Notes
*******

  -  if the argument is :math:`\pm0` or :math:`\pm\infty`, it is returned unmodified 
  -  if the argument is NaN, a NaN is returned 

Example
*******

.. include:: ../../../../test/doc/core/asinh.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/asinh.txt
  :literal:
