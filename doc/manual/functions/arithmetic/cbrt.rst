.. _function-cbrt:

####
cbrt
####

**Required header:** ``#include <eve/function/cbrt.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ cbrt = {};
   }

Function object computing the cubic root of a :ref:`IEEEValue <concept-ieeevalue>`

Synopsis
********

.. code-block:: c++


   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes the element-wise cubic root value of the :ref:`IEEEValue <concept-ieeevalue>`.

Parameters
**********

* **s**: Instance of a  :ref:`IEEEValue <concept-ieeevalue>`.

Return value
**************

* A value with the same type as the parameter.

Notes
*****

  - If the argument is :math:`\pm0` or :math:`\pm\infty`, it is returned, unchanged
  - If the argument is a NaN, a NaN is returned. 


.. seealso::  :ref:`sqrt <function-sqrt>`,  :ref:`rsqrt <function-rsqrt>`

Example
*******

.. include:: ../../../../test/doc/core/cbrt.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/cbrt.txt
  :literal:
