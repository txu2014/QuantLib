/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano

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

#if defined(HAVE_CONFIG_H)
    #include <qlo/config.hpp>
#endif

#include <qlo/optimization.hpp>

#include <ql/math/optimization/armijo.hpp>
#include <ql/math/optimization/conjugategradient.hpp>
#include <ql/math/optimization/levenbergmarquardt.hpp>
#include <ql/math/optimization/simplex.hpp>
#include <ql/math/optimization/steepestdescent.hpp>

namespace QuantLibAddin {

    EndCriteria::EndCriteria(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                             QuantLib::Size maxIterations,
                             QuantLib::Size maxStationaryStateIterations,
                             QuantLib::Real rootEpsilon,
                             QuantLib::Real functionEpsilon,
                             QuantLib::Real gradientNormEpsilon,
                             bool permanent)
        : ObjectHandler::LibraryObject<QuantLib::EndCriteria>(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::EndCriteria>(new
            QuantLib::EndCriteria(maxIterations,
                                  maxStationaryStateIterations,
                                  rootEpsilon,
                                  functionEpsilon,
                                  gradientNormEpsilon));
    }

    Simplex::Simplex(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            QuantLib::Real lambda,
            bool permanent) : OptimizationMethod(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::OptimizationMethod>(new
            QuantLib::Simplex(lambda));
    }

    LevenbergMarquardt::LevenbergMarquardt(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                           QuantLib::Real epsfcn,
                                           QuantLib::Real xtol,
                                           QuantLib::Real gtol,
                                           bool permanent) : OptimizationMethod(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::OptimizationMethod>(new
            QuantLib::LevenbergMarquardt(epsfcn, xtol, gtol));
    }

    ArmijoLineSearch::ArmijoLineSearch(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                                       QuantLib::Real eps,
                                       QuantLib::Real alpha,
                                       QuantLib::Real beta,
                                       bool permanent) : LineSearch(properties, permanent) {
        libraryObject_ = boost::shared_ptr<QuantLib::LineSearch>(new
            QuantLib::ArmijoLineSearch(eps, alpha, beta));
    }

    ConjugateGradient::ConjugateGradient(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::LineSearch>& lineSearch,
            bool permanent) : LineSearchBasedMethod(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::OptimizationMethod>(new
            QuantLib::ConjugateGradient(lineSearch));
    }

    SteepestDescent::SteepestDescent(
            const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
            const boost::shared_ptr<QuantLib::LineSearch>& lineSearch,
            bool permanent) : LineSearchBasedMethod(properties, permanent)
    {
        libraryObject_ = boost::shared_ptr<QuantLib::OptimizationMethod>(new
            QuantLib::SteepestDescent(lineSearch));
    }
      
}

