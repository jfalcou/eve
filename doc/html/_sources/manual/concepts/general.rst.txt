.. _concept-general:

Concepts
========

The main Concepts defined by **EVE** are the :ref:`concept-vectorizable` and :ref:`concept-vectorized`
one. Those two Concepts are used to define which type can be turned into a SIMD compatible type
and what expressions and operations are valid for such a SIMD compatible type.

From those two Concepts, we define the :ref:`concept-value`-related Concepts that describes the types
usable as arguments of **EVE**'s functions. They are the :ref:`concept-ieeevalue`, the
:ref:`concept-integralvalue` and the :ref:`concept-logicalvalue` Concepts which represent 
types which can be either :ref:`concept-vectorizable`
or :ref:`concept-vectorized` and supports a subset of numerical properties.

This ambivalence around the SIMD or scalar status of types modeling these Concepts is what
make **EVE** 's functions usable with both regular scalar type (e.g. calling ``eve::cos(4.f)``)
and SIMD ones (e.g. calling ``eve::cos( eve::wide<float>(4.f))``). Such behavior will be paramount
to support the polymorphic aspect of the SIMDCallable Concepts, thus allowing polymorphic function
objects to be used for both scalar and SIMD computation.

Finally, the :ref:`concept-value`  Concept aggregates all types modeling either :ref:`concept-ieeevalue` or
:ref:`concept-integralvalue`. Similarly, the :ref:`concept-logicalvalue` Concept defines types that represent
SIMD-compatible logical values.

.. toctree::
   :maxdepth: 1

   vectorizable
   vectorized
   ieeevalue
   integralvalue
   value
   logical
   logicalvalue
