#include <rviz_plugin_examples/dial_panel.h>
#include <pluginlib/class_list_macros.h>
#include <std_msgs/Float64.h>

#include "ui_dial_panel.h"

namespace rviz_plugin_examples
{
DialPanel::DialPanel(QWidget* parent) : Panel(parent),  ui_(new Ui::DialUI())
{
  ui_->setupUi(this);
}

DialPanel::~DialPanel() = default;

void DialPanel::onInitialize()
{
  connect(ui_->dial, SIGNAL(valueChanged(int)), this , SLOT(dialValueChanged(int)));
  connect(ui_->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

  ui_->line_edit->setPlaceholderText("Input topic name (Default : dial)");

  connect(ui_->line_edit,  SIGNAL(textChanged(const QString &)), this, SLOT(lineEditChanged()));

  pub_ = nh_.advertise<std_msgs::Float64>("dial", 1);
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
  std::string old_topic_name = topic_name_;
  if(ui_->line_edit->text().isEmpty())
    topic_name_ = "dial";
  else
    topic_name_ = ui_->line_edit->text().toStdString();

  ROS_INFO("You set the topic name : %s", topic_name_.c_str());

  if(old_topic_name != topic_name_)
    pub_ = nh_.advertise<std_msgs::Float64>(topic_name_, 1);
}

void DialPanel::dialValueChanged(int value)
{
  ui_->lcd->display(value);
  value_ = value;
  ROS_INFO("You set the value : %d", value_);
}

void DialPanel::buttonClicked()
{
  std_msgs::Float64 msg;
  msg.data = static_cast<double>(value_);
  pub_.publish(msg);
  ROS_INFO("You pushed the button.");
}

}  // namespace rviz_plugin_examples

PLUGINLIB_EXPORT_CLASS(rviz_plugin_examples::DialPanel, rviz::Panel )
