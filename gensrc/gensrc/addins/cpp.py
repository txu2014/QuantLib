
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

"""Generate source code for C++ addin."""

from gensrc.addins import addin
from gensrc.addins import cppexceptions
from gensrc.configuration import environment
from gensrc.categories import category
from gensrc.utilities import outputfile
from gensrc.utilities import log
from gensrc.utilities import common

class CppAddin(addin.Addin):
    """Generate source code for C++ addin."""

    #############################################
    # class variables
    #############################################

    voSupported_ = True
    #convertPermanentFlag_ = '''
    #    bool permanentCpp =
    #        ObjectHandler::callOperToScalar<bool>(*permanent, "permanent", false);
    #    if (permanentCpp)
    #        objectPointer->setPermanent();'''
    convertPermanentFlag_ = ''

    #############################################
    # public interface
    #############################################

    def generate(self, categoryList, enumerationList):
        """Generate source code for C++ addin."""

        self.categoryList_ = categoryList
        self.enumerationList_ = enumerationList

        log.Log.instance().logMessage(' begin generating %s...' % self.name_)
        self.generateFunctions()
        log.Log.instance().logMessage(' done generating %s.' % self.name_)

    def generateFunctions(self):
        """Generate source code for all functions in all categories."""
        self.bufferAll_.set({ 'path' : self.relativePath_ })
        loopIncludes = '''\
#include <%s/loop/loop_%s.hpp>
#include <''' + self.relativePath_ + '''/loop.hpp>\n'''
        for cat in self.categoryList_.categories(self.name_,
            self.coreCategories_, self.addinCategories_):
            categoryIncludes = cat.includeList(loopIncludes)
            self.bufferAll_.append("#include <Addins/Cpp/%s.hpp>\n" % cat.name())
            bufferCpp = ''
            bufferHpp = ''
            for func in cat.functions(self.name_): 
                bufferCpp += self.generateFunction(func)
                bufferHpp += self.generateDeclaration(func)
            self.bufferBody_.set({
                'bufferCpp' : bufferCpp,
                'categoryIncludes' : categoryIncludes })
            self.bufferHeader_.set({
                'categoryName' : cat.name(),
                'bufferHpp' : bufferHpp })
            fileNameCpp = '%s%s.cpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameCpp, cat.copyright(), self.bufferBody_)
            fileNameHpp = '%s%s.hpp' % ( self.rootPath_, cat.name())
            outputfile.OutputFile(self, fileNameHpp, cat.copyright(), self.bufferHeader_)
        self.bufferAll_.append("\n")
        fileNameAll = '%saddincpp.hpp' % self.rootPath_
        outputfile.OutputFile(self, fileNameAll, self.copyright_, self.bufferAll_)

    def generateFunction(self, func):
        """Generate source code for a given function."""
        return self.bufferFunction_.set({
            'cppConversions' : func.parameterList().generate(self.cppConversions_),
            'enumConversions' : func.parameterList().generate(self.enumConversions_),
            'functionBody' : func.generateBody(self),
            'functionDeclaration' : func.parameterList().generate(self.functionDeclaration_),
            'functionName' : func.name(),
            'functionReturnType' : self.functionReturnType_.apply(func.returnValue()),
            'libConversions' : func.parameterList().generate(self.libraryConversions_),
            'objectConversions' : func.parameterList().generate(self.objectConversions_),
            'refConversions' : func.parameterList().generate(self.referenceConversions_),
            'returnConversion' : self.returnConversion_.apply(func.returnValue()) })

    def generateDeclaration(self, func):
        """Generate source code for a given function."""
        return self.bufferDeclaration_.set({
            'functionReturnType' : self.functionReturnType_.apply(func.returnValue()),
            'functionDeclaration' : func.parameterList().generate(self.functionDeclaration_),
            'functionName' : func.name() })

    def loopName(self, param):
        """Return the variable name for a loop parameter."""
        if param.type() == common.STRING:
            return param.name()
        else:
            return param.name() + 'Lib'

    #############################################
    # serializer interface
    #############################################

    def serialize(self, serializer):
        """Load/unload class state to/from serializer object."""
        super(CppAddin, self).serialize(serializer)

