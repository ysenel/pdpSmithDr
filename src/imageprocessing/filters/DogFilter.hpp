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

#ifndef SD_IMAGE_PROCESSING_DOG_FILTER_HPP
#define SD_IMAGE_PROCESSING_DOG_FILTER_HPP

// Implements Difference of Gaussian (DOG)

#include "LinearFilter.hpp"

namespace sd {
  namespace imageprocessing {

    template<typename T>
    class DogFilter
      : public LinearFilter<T>
    {

    public:

      DogFilter(size_t width, size_t height, size_t depth, double sigma1, double sigma2);
      virtual ~DogFilter();

    private:

      DogFilter(const DogFilter& f) = delete;
      DogFilter& operator=(const DogFilter& f) = delete;

    };

  }
}

#include "DogFilter.hxx"

#endif /* #! SD_IMAGE_PROCESSING_DOG_FILTER_HPP */
