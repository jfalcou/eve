.. _function-exp2:

####
exp2
####

**Required header:** ``#include <eve/function/exp2.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexp2r /* implementation defined */ exp2 = {};
   }

Function object computing the  base 2 exponential of(:math:`2^x`) of an :ref:`IEEEValue <concept-ieeevalue>`.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

*  Computes the element-wise   base 2 exponential of the :ref:`IEEEValue <ieeeconcept-value>`.

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

.. include:: ../../../../test/doc/core/exp2.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/exp2.txt
  :literal:
