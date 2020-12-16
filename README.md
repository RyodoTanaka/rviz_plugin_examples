# rviz_plugin_examples
Examples for rviz plugin for `melodic` environment.

# Build
```bash
$ mkdir <catkin_ws>/src
$ cd <catkin_ws>/src
$ git clone -b melodic-devel https://github.com/RyodoTanaka/rviz_plugin_examples.git
$ cd <catkin_ws>
$ rosdep install -i -y -r --from-paths src
$ catkin build
$ source devel/setup.bash
```

$ Execute
Do not forget to set path as below.
```bash
$ cd <catkin_ws>
$ source devel/setup.bash
```
Then, run the Rviz as below video.
[![rviz-panel](.images/rviz-panel.gif)](https://youtu.be/xL5g6bMIP3w)
