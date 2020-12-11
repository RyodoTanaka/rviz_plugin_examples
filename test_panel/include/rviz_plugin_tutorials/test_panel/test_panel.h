#pragma once

#ifndef Q_MOC_RUN
#include <rclcpp/rclcpp.hpp>
#endif

#include <rviz_common/panel.hpp>

#include <std_msgs/msg/float64.hpp>

namespace Ui {
class TestUI;
}

namespace rviz_plugin_tutorials
{
class TestPanel: public rviz_common::Panel
{
  Q_OBJECT
 public:
  TestPanel(QWidget* parent = nullptr);
  ~TestPanel() override;

  void onInitialize() override;
  void onEnable();
  void onDisable();

private Q_SLOTS:
  void dialValueChanged(int value);
  void lineEditChanged();
  void buttonClicked();

protected:
  Ui::TestUI* ui_;
  int value_{0};
  std::string topic_name_{"test_panel"};

  rclcpp::Node::SharedPtr node_;
  rclcpp::Publisher<std_msgs::msg::Float64>::SharedPtr pub_;

  
};
} // end namespace rviz_plugin_tutorials
