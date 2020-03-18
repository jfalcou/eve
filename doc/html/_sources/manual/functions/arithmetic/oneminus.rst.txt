.. _function-oneminus:

########
oneminus
########

**Required header:** ``#include <eve/function/oneminus.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ oneminus = {};
   }

Function object computing ``1-x`` of a :ref:`Value <concept-value>` x.

Synopsis
********

.. code-block:: c++

   template<typename T> constexpr T operator()( T const & x ) noexcept;

*  Computes ``1-x`` element-wise.

Parameter
*********

* Instance of a :ref:`Value <concept-value>`.

Return value
**************

* A value with the same type as the parameter.


Options
*******

  - the :ref:`saturated_ <feature-decorator>` decorator acts as ``saturated_(sub)(1,x)``


Example
*******

.. include:: ../../../../test/doc/core/oneminus.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/oneminus.txt
  :literal:
