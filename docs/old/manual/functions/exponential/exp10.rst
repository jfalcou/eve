.. _function-exp10:

#####
exp10
#####

**Required header:** ``#include <eve/function/exp10.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexp10r /* implementation defined */ exp10 = {};
   }

Function object computing the  base 10 exponential of(:math:`10^x`) of an :ref:`IEEEValue <concept-ieeevalue>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

*  Computes the element-wise   base 10 exponential of the :ref:`IEEEValue <ieeeconcept-value>`.

Parameter
*********

* ``x``: Instance of an :ref:`IEEEValue <concept-ieeevalue>`.

Return value
*************

*  A value with the same type as the parameter. 

.. seealso::  :ref:`exp <function-exp>`,  :ref:`exp10 <function-exp10>`,  :ref:`expm1 <function-expm1>`,
  :ref:`log <function-log>`, :ref:`log <function-log>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, 

Example
*******

.. include:: ../../../../test/doc/core/exp10.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/exp10.txt
  :literal:
