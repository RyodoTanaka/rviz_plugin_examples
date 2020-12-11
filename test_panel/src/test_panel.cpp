#include <rviz_plugin_tutorials/test_panel/test_panel.h>

#include "ui_test_panel.h"

namespace rviz_plugin_tutorials
{
static const rclcpp::Logger LOGGER = rclcpp::get_logger("rviz.plugin.tutorials.test_panel");


TestPanel::TestPanel(QWidget* parent) : Panel(parent),  ui_(new Ui::TestUI())
{
  node_ = std::make_shared<rclcpp::Node>("TestPanel_core", "rviz_plugin_tutorials");
  ui_->setupUi(this);
}

TestPanel::~TestPanel() = default;

void TestPanel::onInitialize()
{
  connect(ui_->dial, SIGNAL(valueChanged(int)), this , SLOT(dialValueChanged(int)));
  connect(ui_->pushButton, SIGNAL(clicked()), this, SLOT(buttonClicked()));

  ui_->line_edit->setPlaceholderText("Input topic name (Default : test_panel)");

  connect(ui_->line_edit,  SIGNAL(textChanged(const QString &)), this, SLOT(lineEditChanged()));

  pub_ = node_->create_publisher<std_msgs::msg::Float64>(topic_name_, 1);
  parentWidget()->setVisible(true);
}

void TestPanel::onEnable()
{
  show();
  parentWidget()->show();
}

void TestPanel::onDisable()
{
  hide();
  parentWidget()->hide();
}

void TestPanel::lineEditChanged()
{
  if(ui_->line_edit->text().isEmpty())
    ui_->line_edit->setText(QString::fromStdString(topic_name_));
  else
    topic_name_ = ui_->line_edit->text().toStdString();

  pub_ = node_->create_publisher<std_msgs::msg::Float64>(topic_name_, 1);
}

void TestPanel::dialValueChanged(int value)
{
  ui_->lcd->display(value);
  value_ = value;
  RCLCPP_INFO(LOGGER, "You set the value : %d", value_);
}

void TestPanel::buttonClicked()
{
  std_msgs::msg::Float64 msg;
  msg.data = static_cast<double>(value_);
  pub_->publish(msg);
  RCLCPP_INFO(LOGGER, "You pushed the button.");
}

}  // namespace rviz_plugin_tutorials
