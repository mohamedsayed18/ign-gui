#include <iostream>

#include <ignition/gui/Application.hh>
#include <ignition/gui/MainWindow.hh>
#include <ignition/plugin/Register.hh>

#include "KeyPlugin.hh"

using namespace ignition;
using namespace gui;

KeyPlugin::KeyPlugin(): Plugin()
{};


/////////////////////////////////////////////////
KeyPlugin::~KeyPlugin()
{};


void KeyPlugin::LoadConfig(const tinyxml2::XMLElement *_pluginElem)
{
  //it loads the XML file which contains the UI file of Qt
  
  if (this->title.empty())
    this->title = "Key tool";
    // https://doc.qt.io/qt-5/qobject.html#findChild
    ignition::gui::App()->findChild
      <ignition::gui::MainWindow *>()->installEventFilter(this);
}



bool KeyPlugin::eventFilter(QObject *_obj, QKeyEvent * event)
{
    if (event->type() == QEvent::KeyPress)
    {
        std::cout << "key_pressed" << std::endl;
        return true;
    }
    return QObject::eventFilter(_obj, event);
}

void KeyPlugin::sayhello()
        {
          std::cout << "hello_pressed" << std::endl;
        }

// Register this plugin
IGNITION_ADD_PLUGIN(ignition::gui::KeyPlugin,
                    ignition::gui::Plugin);
