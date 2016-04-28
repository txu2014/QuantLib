/* -*- mode: c++; tab-width: 4; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/*
 Copyright (C) 2006, 2007 Ferdinando Ametrano
 Copyright (C) 2007 Chiara Fornarola
 Copyright (C) 2006, 2007 Marco Bianchetti
 Copyright (C) 2006, 2007 Cristina Duminuco
 Copyright (C) 2006, 2007 Giorgio Facchinetti

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

#ifndef qla_driftcalculators_hpp
#define qla_driftcalculators_hpp

#include <oh/libraryobject.hpp>

#include <ql/types.hpp>

namespace QuantLib {
    class LMMDriftCalculator;
    class LMMNormalDriftCalculator;
    class CMSMMDriftCalculator;
    class SMMDriftCalculator;
    class Matrix;
    class LMMCurveState;
    class CMSwapCurveState;
    class CoterminalSwapCurveState;
}

namespace QuantLibAddin {
   
    class LMMDriftCalculator : public ObjectHandler::LibraryObject<QuantLib::LMMDriftCalculator> {
      public:
        LMMDriftCalculator(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                           const QuantLib::Matrix& pseudo,
                           const std::vector<QuantLib::Rate>& displacements,
                           const std::vector<QuantLib::Time>& taus,
                           QuantLib::Size numeraire,
                           QuantLib::Size alive,
                           bool permanent);
        std::vector<QuantLib::Real> compute(
            const QuantLib::LMMCurveState& cs) const;
        std::vector<QuantLib::Real> computePlain(
            const QuantLib::LMMCurveState& cs) const;
        std::vector<QuantLib::Real> computeReduced(
            const QuantLib::LMMCurveState& cs) const;
      private:
        mutable std::vector<QuantLib::Real> drifts_;
    };

    class LMMNormalDriftCalculator : public ObjectHandler::LibraryObject<QuantLib::LMMNormalDriftCalculator> {
      public:
        LMMNormalDriftCalculator(
                        const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                        const QuantLib::Matrix& pseudo,
                        const std::vector<QuantLib::Time>& taus,
                        QuantLib::Size numeraire,
                        QuantLib::Size alive,
                        bool permanent);
        std::vector<QuantLib::Real> compute(
            const QuantLib::LMMCurveState& cs) const;
        std::vector<QuantLib::Real> computePlain(
            const QuantLib::LMMCurveState& cs) const;
        std::vector<QuantLib::Real> computeReduced(
            const QuantLib::LMMCurveState& cs) const;
      private:
        mutable std::vector<QuantLib::Real> drifts_;
    };

    class CMSMMDriftCalculator : public ObjectHandler::LibraryObject<QuantLib::CMSMMDriftCalculator> {
      public:
        CMSMMDriftCalculator(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                             const QuantLib::Matrix& pseudo,
                             const std::vector<QuantLib::Rate>& displacements,
                             const std::vector<QuantLib::Time>& taus,
                             QuantLib::Size numeraire,
                             QuantLib::Size alive,
                             QuantLib::Size spanningFwds,
                             bool permanent);
        std::vector<QuantLib::Real> compute(
            const QuantLib::CMSwapCurveState& cs) const;
      private:
        mutable std::vector<QuantLib::Real> drifts_;
    };

    class SMMDriftCalculator : public ObjectHandler::LibraryObject<QuantLib::SMMDriftCalculator> {
      public:
        SMMDriftCalculator(const boost::shared_ptr<ObjectHandler::ValueObject>& properties,
                           const QuantLib::Matrix& pseudo,
                           const std::vector<QuantLib::Rate>& displacements,
                           const std::vector<QuantLib::Time>& taus,
                           QuantLib::Size numeraire,
                           QuantLib::Size alive,
                           bool permanent);
        std::vector<QuantLib::Real> compute(
            const QuantLib::CoterminalSwapCurveState& cs) const;
      private:
        mutable std::vector<QuantLib::Real> drifts_;
    };

}

#endif

