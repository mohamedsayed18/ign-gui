#ifndef IGNITION_GUI_HELLOPLUGIN_HH_
#define IGNITION_GUI_HELLOPLUGIN_HH_

#include <memory>

#include <ignition/gui/qt.h>
#include <ignition/gui/Plugin.hh>

/* 
For qml file
https://doc.qt.io/qt-5.9/qml-qtquick-keyevent.html
*/


namespace ignition
{
  namespace gui
  {
    class KeyPlugin : public ignition::gui::Plugin  //inherited from Qobject
    {
        Q_OBJECT

        public: KeyPlugin();    //constructor
        public: virtual ~KeyPlugin();   //destructor
        
        public: virtual void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;
        protected: bool eventFilter(QObject *_obj, QKeyEvent * event); 
        //I removed override, errorr: marked ‘override’, but does not override 

        protected slots: void sayhello();
    };
  }
}

#endif
