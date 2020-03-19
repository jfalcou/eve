.. _function-toint:

#####
toint
#####

**Required header:** ``#include <eve/function/toint.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ toint = {};
   }

Function object computing the conversion  of a :ref:`Value <concept-value>` to the associated signed integral type.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

*  Converts the parameter to the associated signed integral type.


Parameter
*********

* ``x``: Instance of a  :ref:`Value <concept-value>`.


Return value
*************

* A value of the signed integral type associated to the parameter. 

Note
*****

  - :ref:`saturated_ <feature-decorator>` decorator saturates the conversion.

.. seealso::  :ref:`convert <function-convert>`,  :ref:`tofloat <function-tofloat>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/toint.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/toint.txt
  :literal:
