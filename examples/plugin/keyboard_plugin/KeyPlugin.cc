#include <iostream>

#include <ignition/gui/Application.hh>
#include <ignition/gui/MainWindow.hh>
#include <ignition/plugin/Register.hh>

#include <ignition/msgs.hh>
#include <ignition/transport.hh>
#include <ignition/msgs/twist.pb.h>

#include "KeyPlugin.hh"

using namespace ignition;
using namespace gui;

KeyPlugin::KeyPlugin(): Plugin()
{
  pub = node.Advertise<ignition::msgs::Twist>(topic);
}


/////////////////////////////////////////////////
KeyPlugin::~KeyPlugin()
{}


void KeyPlugin::LoadConfig(const tinyxml2::XMLElement *_pluginElem)
{
  //it loads the XML file which contains the UI file of Qt
  if (this->title.empty())
    this->title = "Key tool";
    // https://doc.qt.io/qt-5/qobject.html#findChild
    ignition::gui::App()->findChild
      <ignition::gui::MainWindow *>()->QuickWindow()->installEventFilter(this);
}



bool KeyPlugin::eventFilter(QObject *_obj, QEvent *_event)
{
  /*
  todo: to get specif keys
  if( QString("1234567890").indexOf( keyEvent->text() ) != -1 )
  */
    // Prepare the message.
    ignition::msgs::StringMsg msg;
    msg.set_data("HELLO");

    if (_event->type() == QEvent::KeyPress)
    {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(_event);
        KeyPlugin::keyloop(keyEvent);
        return true;
    }
    return QObject::eventFilter(_obj, _event);
}


void KeyPlugin::keyloop(QKeyEvent *key_press)
{
  /*
  https://doc.qt.io/archives/qtjambi-4.5.2_01/com/trolltech/qt/core/Qt.Key.html
  */
  double linear = 0;
  double angular = 0;
  if(key_press->key() == Qt::Key_Up)
  {
    linear = 1.0;
    std::cout << "UP" << std::endl;
  }
  else if (key_press->key() == Qt::Key_Down)
  {
    linear = -1.0;
    std::cout << "Down" << std::endl;
  }
  else if (key_press->key() == Qt::Key_Right)
  {
    angular = -1.0;
    std::cout << "RIGHT" << std::endl;
  }
  else if (key_press->key() == Qt::Key_Left)
  {
    angular = 1.0;
    std::cout << "LEFT" << std::endl;
  }

  
  ignition::msgs::Twist cmdVelMsg;  
  cmdVelMsg.mutable_linear()->set_x(linear);
  cmdVelMsg.mutable_angular()->set_z(angular);
  pub.Publish(cmdVelMsg);
}


// Register this plugin
IGNITION_ADD_PLUGIN(ignition::gui::KeyPlugin,
                    ignition::gui::Plugin);
