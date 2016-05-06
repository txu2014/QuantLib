/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2004, 2005, 2006, 2007, 2008 Eric Ehlers
 Copyright (C) 2006, 2008 Plamen Neykov
 Copyright (C) 2008 Nazcatech sprl Belgium

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
*/

/*! \file
    \brief Class Object - Define interface for Objects to be stored in the Repository
*/

#ifndef oh_object_hpp
#define oh_object_hpp

#include <oh/ohdefines.hpp>
#include <oh/valueobject.hpp>
#include <oh/exception.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>

namespace ObjectHandler {

    //! Interface for Objects to be stored in the ObjectHandler Repository.
    /*! Objects are constructed by the client and passed to
        Repository::storeObject() for storage in the Repository.

        All member functions of this class are implemented inline.  This is not
        for performance reasons; the entire implementation of the class must appear
        in the header file in order to allow derived classes to inherit from Object
        across DLL boundaries on the Windows platform.
    */
    class Object {        
    public:
        //! \name Structors
        //@{
        //! Default constructor.
        /*! Construct an Object.  To store the resulting Object in the
            Repository, call
            \code
                Repository::instance().storeObject(objectID, object);
            \endcode
        */
        Object(
            const boost::shared_ptr<ValueObject>& properties = boost::shared_ptr<ValueObject>(),
            bool permanent = false)
            : mProps(properties), permanent_(permanent) {}
        //! Empty virtual destructor.
        virtual ~Object() {}
        //@}

        //! \name ValueObjects
        //@{
        //! Retrieve the ValueObject associated with this Object.
        const boost::shared_ptr<ValueObject>& properties() const {
            return mProps;
        }
        //@}

        //! \name Properties
        //@{
        //! Retrieve the property names as a std::set.
        std::set<std::string> propertyNames() const;
        //! Retrieve the property names as a std::vector.
        std::vector<std::string> propertyNamesVector() const;
        //! Retrieve the value of a given property.
        /*! Forward the request to the associated ValueObject.
            Throw an exception if the Object has no property by that name.
        */
        property_t propertyValue(const std::string &propertyName) const;
        //@}

        //! \name Permanent Objects
        //@{
        //! Query the value of the "permanent" flag.
        /*! Permanent Objects remain in the Repository after a call to
            Repository::deleteAllObjects() or Repository::collectGarbage().

            This feature allows a finer level of granularity in maintaining
            the contents of the Repository.
        */
        const virtual bool &permanent() const { return permanent_; }
        //@}

        //! \name Logging
        //@{
        //! Write this Object's properties (from the ValueObject) to the given stream.
        /*! This function is called by the logging framework.  Derived classes may
            override this function if additional information is available.
        */
        virtual void dump(std::ostream &out);
        //@}

        //! The width of a column of data written to the log file.
        static const int logColumnWidth = 20;

    private:
        // The ValueObject associated with this Object.
        boost::shared_ptr<ValueObject> mProps;
        // Flag to indicate whether this Object is permanent.
        bool permanent_;
        // Assignment operator declared but not implemented - assignment is not supported.
        Object& operator= (const Object&);
        // Copy ctor declared but not implemented - copy construction is not supported.
        Object(const Object&);
    };

    inline std::set<std::string> Object::propertyNames() const {
        if(mProps)
            return mProps->getPropertyNames();
        else
            return std::set<std::string>();
    }

    inline std::vector<std::string> Object::propertyNamesVector() const {
        if(mProps)
            return mProps->getPropertyNamesVector();
        else
            return std::vector<std::string>();
    }

    inline property_t Object::propertyValue(const std::string &propertyName) const {
        if (mProps)
            return mProps->getProperty(propertyName);
        OH_FAIL("ObjectHandler error: attempt to retrieve property "
            << "with unknown name '" << propertyName << "'");
    }

    inline void Object::dump(std::ostream &out) {
        out << std::endl;
        std::set<std::string> propertyNames = this->propertyNames();
        for (std::set<std::string>::const_iterator i = propertyNames.begin(); 
                i != propertyNames.end(); ++i) {
            std::string propertyName = *i;
            property_t propertyValue = this->propertyValue(propertyName);
            out << "property = " << std::left << std::setw(logColumnWidth) << propertyName;
            out << " value = " << std::left << std::setw(logColumnWidth) << propertyValue << std::endl;
        }
        out << "Permanent = " << std::left << std::setw(logColumnWidth) 
            << std::boolalpha << permanent_ << std::endl;
        out << std::endl;
    }

    //! Log the given Object to the given stream.
    inline std::ostream &operator<<(std::ostream &out, const boost::shared_ptr<Object> &object) {
        object->dump(out);
        return out;
    }

}

#endif

