#pragma once

#ifndef Q_MOC_RUN
#include <ros/ros.h>
#endif

#include <rviz/panel.h>

namespace Ui {
class DialUI;
}

namespace rviz_plugin_examples
{
class DialPanel: public rviz::Panel
{
  Q_OBJECT
 public:
  DialPanel(QWidget* parent = nullptr);
  ~DialPanel() override;

  void onInitialize() override;
  void onEnable();
  void onDisable();

private Q_SLOTS:
  void dialValueChanged(int value);
  void lineEditChanged();
  void buttonClicked();

protected:
  Ui::DialUI* ui_;
  int value_{0};
  std::string topic_name_{"dial"};

  ros::NodeHandle nh_;
  ros::Publisher pub_;
};
} // end namespace rviz_plugin_examples
