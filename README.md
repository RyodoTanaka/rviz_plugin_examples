# rviz_plugin_examples
Examples for rviz plugin for `foxy` environment.

# Build
```bash
$ mkdir <colcon_ws>/src
$ cd <colcon_ws>/src
$ git clone -b foxy-devel https://github.com/RyodoTanaka/rviz_plugin_examples.git
$ cd <colcon_ws>
$ rosdep install -i -y -r --from-paths src
$ colcon build
$ source install/setup.bash
```

$ Execute
Do not forget to set path as below.
```bash
$ cd <colcon_ws>
$ source install/setup.bash
```
Then, run the Rviz as below video.
[![rviz-panel](.images/rviz-panel.gif)](https://youtu.be/xL5g6bMIP3w)
