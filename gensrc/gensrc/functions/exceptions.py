
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

"""Exceptions encountered when processing functions."""

from gensrc.exceptions import exceptions

class FunctionException(exceptions.GensrcException):
    """Exceptions encountered when processing functions."""

class BehaviorLoopParameterException(FunctionException):
    """The configured loop parameter is not defined."""

    BEHAVIOR_LOOP_PARAMETER_ERROR = """
Error processing function %(functionName)s -
Function has been configured to loop on parameter "%(loopParameterName)s"
but there is no input parameter with that name."""

    def __init__(self, functionName, loopParameterName):
        """Initialize the BehaviorLoopParameterException object."""
        self.value_ = BehaviorLoopParameterException.BEHAVIOR_LOOP_PARAMETER_ERROR % {
            'functionName' : functionName,
            'loopParameterName' : loopParameterName }

class BehaviorLoopDefaultException(FunctionException):
    """Default value specified for loop parameter - this is unsupported."""

    BEHAVIOR_LOOP_DEFAULT_ERROR = """
Error processing function %(functionName)s -
A default value has been specified for loop parameter "%(loopParameterName)s",
default values are not supported for loop parameters."""

    def __init__(self, functionName, loopParameterName):
        """Initialize the BehaviorLoopDefaultException object."""
        self.value_ = BehaviorLoopDefaultException.BEHAVIOR_LOOP_DEFAULT_ERROR % {
            'functionName' : functionName,
            'loopParameterName' : loopParameterName }

class BehaviorLoopNonVectorException(FunctionException):
    """Configured loop parameter is not a vector."""

    BEHAVIOR_LOOP_NON_VECTOR_ERROR = """
Error processing function %(functionName)s -
Function has been configured to loop on parameter "%(loopParameterName)s"
but that parameter is not a vector."""

    def __init__(self, functionName, loopParameterName):
        """Initialize the BehaviorLoopNonVectorException object."""
        self.value_ = BehaviorLoopNonVectorException.BEHAVIOR_LOOP_NON_VECTOR_ERROR % {
            'functionName' : functionName,
            'loopParameterName' : loopParameterName }

class BehaviorReturnNonVectorException(FunctionException):
    """Loop function return value is not a parameter."""

    BEHAVIOR_RETURN_NON_VECTOR_ERROR = """
Error processing function %(functionName)s -
Function has been configured to loop,
but the return value is not a vector."""

    def __init__(self, functionName, loopParameterName):
        """Initialize the BehaviorReturnNonVectorException object."""
        self.value_ = BehaviorReturnNonVectorException.BEHAVIOR_RETURN_NON_VECTOR_ERROR % {
            'functionName' : functionName }

