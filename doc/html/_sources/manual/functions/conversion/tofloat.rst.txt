.. _function-tofloat:

#######
tofloat
#######

**Required header:** ``#include <eve/function/tofloat.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ tofloat = {};
   }

Function object converts to the associated floating type.

Synopsis
********

.. code-block:: c++
  :linenos:

   template<typename T> constexpr auto operator()( T x ) noexcept;

* Converts element-wise  :ref:`Value <concept-value>` to the associated  :ref:`Ieee Value <concept-ieeevalue>` type.


Parameter
*********

* ``x``: Instance of a  :ref:`Value <concept-value>`.

Return value
*************

* A value of the floating type associated to the parameter. 

Notes
*****

  - if ``sizeof(T)`` is less than 8 the associated base type is ``float`` else ``double``

  - :ref:`saturated_ <feature-decorator>` decorator saturates the conversion.


.. seealso::  :ref:`convert <function-convert>`,  :ref:`toint <function-toint>`,  :ref:`touint <function-touint>`

Example
*******

.. include:: ../../../../test/doc/core/tofloat.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/tofloat.txt
  :literal:
