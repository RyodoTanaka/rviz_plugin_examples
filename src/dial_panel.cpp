#include <rviz_plugin_examples/dial_panel.h>
#include <class_loader/class_loader.hpp>

#include "ui_dial_panel.h"

namespace rviz_plugin_examples
{
static const rclcpp::Logger LOGGER = rclcpp::get_logger("rviz.plugin.examples.dial_panel");


DialPanel::DialPanel(QWidget* parent) : Panel(parent),  ui_(new Ui::DialUI())
{
  node_ = std::make_shared<rclcpp::Node>("dial_panel", "rviz_plugin_examples");
  ui_->setupUi(this);
}

DialPanel::~DialPanel() = default;

void DialPanel::onInitialize()
{
  connect(ui_->dial, SIGNAL(valueChanged(int)), this , SLOT(dialValueChanged(int)));
  connect(ui_->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

  ui_->line_edit->setPlaceholderText("Input topic name (Default : dial)");

  connect(ui_->line_edit,  SIGNAL(textChanged(const QString &)), this, SLOT(lineEditChanged()));

  pub_ = node_->create_publisher<std_msgs::msg::Float64>(topic_name_, 1);
  parentWidget()->setVisible(true);
}

void DialPanel::onEnable()
{
  show();
  parentWidget()->show();
}

void DialPanel::onDisable()
{
  hide();
  parentWidget()->hide();
}

void DialPanel::lineEditChanged()
{
  std::string old_topic_name = topic_name_
  if(ui_->line_edit->text().isEmpty())
    topic_name_ = "dial"
  else
    topic_name_ = ui_->line_edit->text().toStdString();
  
  RCLCPP_INFO(LOGGER, "You set the topic name : %s", topic_name_.c_str());
  
  if(old_topic_name != tipc_name_)
    pub_ = node_->create_publisher<std_msgs::msg::Float64>(topic_name_, 1);
}

void DialPanel::dialValueChanged(int value)
{
  ui_->lcd->display(value);
  value_ = value;
  RCLCPP_INFO(LOGGER, "You set the value : %d", value_);
}

void DialPanel::buttonClicked()
{
  std_msgs::msg::Float64 msg;
  msg.data = static_cast<double>(value_);
  pub_->publish(msg);
  RCLCPP_INFO(LOGGER, "You pushed the button.");
}

}  // namespace rviz_plugin_examples

CLASS_LOADER_REGISTER_CLASS(rviz_plugin_examples::DialPanel, rviz_common::Panel)
