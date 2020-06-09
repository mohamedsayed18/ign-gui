#include <iostream>

#include <ignition/gui/Application.hh>
#include <ignition/gui/MainWindow.hh>
#include <ignition/plugin/Register.hh>

#include <ignition/msgs.hh>
#include <ignition/transport.hh>

#include "KeyPlugin.hh"

using namespace ignition;
using namespace gui;

KeyPlugin::KeyPlugin(): Plugin()
{
  // Create a transport node and advertise a topic.
  /*
  ignition::transport::Node node;
  std::string topic = "/foo";
  auto pub = node.Advertise<ignition::msgs::StringMsg>(topic);
  if (!pub)
  {
    std::cerr << "Error advertising topic [" << topic << "]" << std::endl;
  }
  */
  pub = node.Advertise<ignition::msgs::StringMsg>(topic);
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
        QString s = keyEvent->text();
        std::string utf8_text = s.toUtf8().constData();
        std::cout << utf8_text << std::endl;
        KeyPlugin::pub.Publish(msg);
        return true;
    }
    return QObject::eventFilter(_obj, _event);
}

void KeyPlugin::sayhello()
        {
          std::cout << "hello_pressed" << std::endl;
        }

// Register this plugin
IGNITION_ADD_PLUGIN(ignition::gui::KeyPlugin,
                    ignition::gui::Plugin);
