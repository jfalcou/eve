.. _function-touint:

######
touint
######

**Required header:** ``#include <eve/function/touint.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ touint = {};
   }

Function object computing the conversion  of a :ref:`Value <concept-value>` to the associated signed integral type.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

* Converts element-wise  :ref:`Value <concept-value>` to the associated unsigned :ref:`ntegral Value <concept-integralvalue>` type.

Parameter
*********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
*************

* A value of the unsigned integral type associated to the parameter. 

Note
*****

  - :ref:`saturated_ <feature-decorator>` decorator saturate the conversion.

.. seealso::  :ref:`convert <function-convert>`,  :ref:`tofloat <function-tofloat>`,  :ref:`toint <function-toint>`

Example
*******

.. include:: ../../../../test/doc/core/touint.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/touint.txt
  :literal:
