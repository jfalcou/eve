.. _function-fnms:

##############
fnms
##############

**Required header:** ``#include <eve/function/fnms.hpp>``

.. code-block:: c++

   namespace eve
   {
      constexpr /* implementation defined */ fnms = {};
   }

Function object performing a fused negate-multiply-sub between three :ref:`Values <concept-value>` of same element type


********
Synopsis
********


.. code-block:: c++

   template<typename T,typename U,typename V>  auto operator()( T const& x, U cons & y, V const & z ) noexcept;

* performs element-wise fused negate-multiply-sub of the three parameters

Parameters
**********

* Each parameter  ``x``, ``y`` and ``z``  must be an instance of a :ref:`Value <concept-value>`.
* All  :ref:`concept-vectorized` parameters must share the same type
* If at least one parameter is  :ref:`concept-vectorized`, all  :ref:`concept-vectorizable` ones will be converted to 
  its base type prior any other computation.
* If all parameters are  :ref:`concept-vectorizable` they must share the same :ref:`Ieee Value <concept-value>` type.

Return value
**************

* If any parameter is  :ref:`concept-vectorized`, a value of this type else a value of  
  the common type of the  :ref:`concept-vectorizable` parameters.

Notes
*****

    - The call ``fnms(x, y, z)`` is similar to ``-x*y-z``

      But really conformant fused negate-multiply-sub also implies

      - only one rounding

      - nointermediate" overflow

      Our ``fnms`` provides this for all :ref:`concept-integralvalue` types and also each time it is reasonable
      in terms of performance for :ref:`concept-ieeevalue` ones (i.e. if the system has the hard
      wired capability).

      If you need pedantic fnms capabilities in all circumstances in your own
      code you can use the :ref:`pedantic_ <feature-decorator>`  or :ref:`numeric_ <feature-decorator>` decorators
      (although it can be very expensive).

    - With the :ref:`pedantic_ <feature-decorator>` decorator:  ensures the fnms conformant properties and allows SIMD
      acceleration if available.

    - With the :ref:`numeric_ <feature-decorator>` decorator: decorator ensures the whole fma conformant properties
      and allows SIMD acceleration if available.

*******
Example
*******

.. include:: ../../../../test/doc/core/fnms.cpp
  :literal:

Possible output:

.. include:: ../../../../test/doc/core/fnms.txt
  :literal:
