.. _function-acsch:

#####
acsch
#####

**Required header:** ``#include <eve/function/acsch.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ acsch = {};
   }

Function object computing the hyperbolic arccosecant  of the inverse an  :ref:`IEEEValue <concept-ieeevalue>`.

``acsch(x)`` returns the argument :math:`r` in the interval   :math:`[-\infty, \infty]` such that :math:`\sinh(r) == 1/x`.

********
Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T, typename N>  wide<T,N> operator()( wide<T,N> const& v) noexcept;
   template<typename T> constexpr    T         operator()( T s ) noexcept;

* [1] Computes element-wise  the hyperbolic arccosecant of the  :ref:`IEEEValue <concept-ieeevalue>`.
* [2] Computes the the hyperbolic arccosecant of the scalar.

.. rubric:: Parameters

* **v** : An :ref:`concept-IEEEValue` instance
* **s**: Scalar floating value.

.. rubric:: Return value

* [1,2] A value with the same type as the parameter. 


.. seealso::  :ref:`asinh <function-asinh>`,  :ref:`atanh <function-atanh>`,  :ref:`acoth <function-acoth>`, 
 :ref:`acosh <function-acosh>`,  :ref:`asech <function-asech>`, :ref:`sinh <function-sinh>`,  :ref:`tanh <function-tanh>`,  :ref:`coth <function-coth>`, 
 :ref:`cosh <function-cosh>`,  :ref:`sech <function-sech>`

Notes
*******

  -  if the argument is  :math:`\pm0`, :math:`\pm\infty` is returned
  -  if the argument is NaN, a NaN is returned 


Example
*******

.. include:: ../../../../test/doc/core/acsch.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/acsch.txt
  :literal:
