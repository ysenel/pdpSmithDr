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

#include <core/ViewNode.hpp>
#include <core/image/ImageView.hpp>
#include <core/image/Image.hpp>
#include <frontend/lib/ComputedImageViewAlgorithm.hpp>
#include <frontend/lib/AlgorithmManager.hpp>
#include <frontend/lib/AlgorithmInfo.hpp>
#include <frontend/lib/Parameter.hpp>
#include <PluginDefs.hpp>
#include <Types.hpp>

#include <vector>

#include <iostream>

template<typename T>
class SeuillagePlugin
  : public sd::frontend::ComputedImageViewAlgorithm<T>
{

public:

  SeuillagePlugin() : sd::frontend::ComputedImageViewAlgorithm<T>(m_name, m_input) {}

  virtual ~SeuillagePlugin() {
#ifdef DEBUG
    std::cout << "~" << m_name << std::endl;
#endif
  }

  virtual const std::string& name() const {
    return m_name;
  }

  virtual SeuillagePlugin* clone() {
    return new SeuillagePlugin;
  }

  virtual bool run() {
#ifdef DEBUG
    std::cout << "Running " << m_name << ": \n";
#endif
    const std::vector<sd::core::ViewNode*>& parents = this->getPreviousViewNodes();
    if (parents.size() != 2) {
#ifdef DEBUG
      std::cout << "\tExpecting 2 parents exactly, found " << parents.size() << ". Abort!\n";
#endif
      return false;
    }

    sd::core::ImageView_<T>* image1 = static_cast<sd::core::ImageView_<T>*>(parents[0]);
    //sd::core::ImageView_<T>* image2 = static_cast<sd::core::ImageView_<T>*>(parents[1]);
/*#ifdef DEBUG
    std::cout << "\tWorking with image1: " << image1->name() << std::endl;
    std::cout << "\tWorking with image2: " << image2->name() << std::endl;

    std::cout << image1->size() << std::endl;
    std::cout << image2->size() << std::endl;

    std::cout << image1->information() << std::endl;
    std::cout << image2->information() << std::endl;
#endif*/

    /*if (image1->information() != image2->information()) {
#ifdef DEBUG
      std::cout << "Incompatible images! Abort!\n";
#endif
      return false;
    }*/

    if (image1->channelType() != sd::core::DataType_<T>()) {
#ifdef DEBUG
      std::cout << "Bad image type! Abort!\n" << image1->channelType().toString() << " != " << sd::core::DataType_<T>().toString() <<std::endl;
#endif
      return false;
    }

    /*if (image1->channelType() != image2->channelType()) {
#ifdef DEBUG
      std::cout << "Incompatible image types! Abort!\n";
#endif
      return false;
    }*/

    sd::Size sz = image1->size();
    this->init(image1->information());
    const unsigned int nbChannels = image1->nbChannels();
    T* resultData = this->getData();
    std::fill(resultData, resultData+sz.dataSize(), 0);
    //this->setMinMax(0, std::max(image1->getMax(), image2->getMax()));
    
    sd::frontend::Parameter p;
    this->getParams("seuil", p);
    int seuil = p.getInteger();
#ifdef DEBUG
    std::cout << "\tseuil=" << seuil << std::endl;
#endif
 
    // here compute result...
    auto it1 = image1->begin();
    //auto it2 = image2->begin();
    auto endR = this->end();
    for (auto itR = this->begin(); itR != endR; ++itR, ++it1) {
      for (unsigned int i=0; i<nbChannels; ++i){
        if (it1(i) < seuil){
         itR(i) = 0;
       }
       else
          itR(i) = 255;
    }
  }

    return true;
}

private:
  static const std::string m_name;
  static const sd::frontend::AlgorithmInfo m_input;
  static const sd::frontend::AlgorithmInfo m_output;
};

template<typename T> const std::string SeuillagePlugin<T>::m_name = "Demonstration:SeuillagePlugin";
template<typename T> const sd::frontend::AlgorithmInfo SeuillagePlugin<T>::m_input
= sd::frontend::make_info(sd::core::ObjectDescription::ImageView(sd::core::DataType_<T>(),
                 sd::core::ObjectDescription::ANY_CARD,
                 sd::core::ObjectDescription::ANY_CARD),
        sd::core::ObjectDescription::ImageView(sd::core::DataType_<T>(),
                 sd::core::ObjectDescription::ANY_CARD,
                 sd::core::ObjectDescription::ANY_CARD));

// Register our plugin
extern "C"
SMITHDR_PLUGIN_API
void
registerPlugin()
{
  sd::frontend::ParameterList parameters;
  parameters.push_back(sd::frontend::Parameter("seuil", 150, 0, 255));

  sd::frontend::registerAlgorithm(new SeuillagePlugin<sd::UINT8>, parameters);
  sd::frontend::registerAlgorithm(new SeuillagePlugin<sd::INT8>, parameters);
  sd::frontend::registerAlgorithm(new SeuillagePlugin<sd::UINT16>, parameters);
  sd::frontend::registerAlgorithm(new SeuillagePlugin<sd::INT16>, parameters);
  sd::frontend::registerAlgorithm(new SeuillagePlugin<float>, parameters);
  sd::frontend::registerAlgorithm(new SeuillagePlugin<double>, parameters);
}
