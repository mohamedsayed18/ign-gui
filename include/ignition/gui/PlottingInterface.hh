/*
 * Copyright (C) 2020 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

#ifndef IGNITION_GUI_PLOTTINGINTERFACE_HH_
#define IGNITION_GUI_PLOTTINGINTERFACE_HH_

#include <ignition/gui/Application.hh>
#include "ignition/gui/Export.hh"

namespace ignition
{
namespace gui
{
  /// \brief Interface to Communicate with Qml, and to be a common code between the GuiPlugin and GazeboPlugin
  class PlottingInterface : public QObject
  {
      Q_OBJECT

      /// \brief responsible for accessing the transport messages (publishing and subscribing)
      // private: TransportTopics *transport;

      /// \brief Constructor
      public: explicit PlottingInterface();

      /// \brief Destructor
      public: ~PlottingInterface();

      /// \brief send a signal to qml to plot a data with a value
      /// in _y and with time _x with chart num: _chart
      // modify it to use a GADNAT Object and pass it to javascript
      void emitPlotting(int _chart, float _x , QVariant _y);

      signals: void plot(int _chart, float _x, QVariant _y);
  };
}
}

#endif
