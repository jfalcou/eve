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

   template<typename T> constexpr auto operator()( T x ) noexcept;


*  Computes the element-wise  exponential of the :ref:`IEEEValue <ieeeconcept-value>`.

Parameter
*********

* ``x``: Instance of an :ref:`IEEEValue <concept-ieeevalue>`.

Return value
*************

*  A value with the same type as the parameter. 

.. seealso::  :ref:`exp2 <function-exp2>`,  :ref:`exp10 <function-exp10>`,  :ref:`expm1 <function-expm1>`,
  :ref:`log <function-log>`, :ref:`log2 <function-log2>`, :ref:`log10 <function-log10>`, :ref:`log1p <function-log1p>`, 

Example
*******

.. include:: ../../../../test/doc/core/exp.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/exp.txt
  :literal:
