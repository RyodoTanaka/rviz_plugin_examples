#pragma once

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif

#include <rviz_common/panel.hpp>
#include <std_msgs/msg/float64.hpp>

namespace Ui {
class DialUI;
}

namespace rviz_plugin_examples
{
class DialPanel: public rviz_common::Panel
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

  rclcpp::Node::SharedPtr node_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pub_;
};
} // end namespace rviz_plugin_examples
