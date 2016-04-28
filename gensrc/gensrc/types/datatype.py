
"""
 Copyright (C) 2007, 2008 Eric Ehlers

 This file is part of QuantLib, a free-software/open-source library
 for financial quantitative analysts and developers - http://quantlib.org/

 QuantLib is free software: you can redistribute it and/or modify it
 under the terms of the QuantLib license.  You should have received a
 copy of the license along with this program; if not, please email
 <quantlib-dev@lists.sf.net>. The license is also available online at
 <http://quantlib.org/license.shtml>.

 This program is distributed in the hope that it will be useful, but WITHOUT
 ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 FOR A PARTICULAR PURPOSE.  See the license for more details.
"""

"""A class to contain all of the information that gensrc requires
for a type such as a native C++ type or a user defined class."""

from gensrc.utilities import common
from gensrc.serialization import serializable

class DataType(serializable.Serializable):
    """A class to contain all of the information that gensrc requires
    for a type such as a native C++ type or a user defined class."""

    #############################################
    # class variables
    #############################################

    groupName_ = 'DataTypes'

    #############################################
    # public interface
    #############################################

    def value(self):
        """Return the data type."""
        return self.value_

    def nativeType(self):
        """Return the underlying native type that corresponds to
        the given data type."""
        return self.nativeType_

    def defaultSuperType(self):
        """Return the default supertype that is configured for
        this datatype."""
        return self.defaultSuperType_

    #############################################
    # serializer interface
    #############################################

    def serialize(self, serializer):
        """Load/unload class state to/from serializer object."""
        serializer.serializeAttribute(self, common.NATIVE_TYPE)
        serializer.serializeAttribute(self, common.DEFAULT_SUPER_TYPE)
        serializer.serializeValue(self)

    def postSerialize(self):
        """Invoke any post serialization behavior that may be required."""
        self.name_ = self.value_

class DataTypeDict(serializable.Serializable):
    """Wrapper for a dictionary of DataType objects."""

    #############################################
    # public interface
    #############################################

    def dataTypes(self):
        """Return the dictionary of DataType objects."""
        return self.dataTypes_

    #############################################
    # serializer interface
    #############################################

    def serialize(self, serializer):
        """Load/unload class state to/from serializer object."""
        serializer.serializeObjectDict(self, DataType)

