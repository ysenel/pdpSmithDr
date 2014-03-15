/*
  Copyright (C) 2011 The SmithDR team, smithdr@labri.fr

  This file is part of SmithDR.

  SmithDR is free software: you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation, either version 3 of
  the License, or (at your option) any later version.

  SmithDR is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with SmithDR.
  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef SD_IMAGE_PROCESSING_EROSION_FILTER_HPP
#define SD_IMAGE_PROCESSING_EROSION_FILTER_HPP

#include "MorphoFilter.hpp"

namespace sd {
  namespace imageprocessing {

    class StructuralElement;

    template<typename T>
    class ErosionFilter
      : public MorphoFilter<T>
    {

    public:

      ErosionFilter(const StructuralElement& element);
      virtual ~ErosionFilter();

      virtual T processNeighborhood(std::vector<T>& neigh);

    private:

      ErosionFilter(const ErosionFilter& f) = delete;
      ErosionFilter& operator=(const ErosionFilter& f) = delete;

    };

  }
}

#include "ErosionFilter.hxx"

#endif /* #! SD_IMAGE_PROCESSING_EROSION_FILTER_HPP */
