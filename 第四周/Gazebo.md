<h1 id="hU5hJ">1.安装使用</h1>
```python
sudo apt install gazebo
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762175885572-523de9c5-ec6e-4dca-9705-6d9d8073e5c4.png)

<h2 id="BDt2F">下载模型</h2>
```python
mkdir -p ~/.gazebo    安装名为gazebo的文件夹
cd ~/.gazebo          进入这个文件夹
git clone http://gitee.com/ohhuo/gazebo_models.git ~/.gazebo/models
//下载模型

```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762176896248-6ab23f06-2be9-4330-822e-9b3351077f57.png)

<h2 id="JK9xp">下载gazebo插件</h2>
```python
sudo apt install ros-humble-gazebo-ros
```

<h2 id="qEkiX">启动gazebo，并加载ros2插件</h2>
<font style="color:rgb(52, 73, 94);">安装完成后，通过下面的命令行来启动gazebo并加载ros2插件。</font>

```shell
gazebo --verbose -s libgazebo_ros_init.so -s libgazebo_ros_factory.so
一般输入gazebo，就进入gazebo了
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762176503515-e135ab6c-c174-403c-9c84-9d44521d37e7.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762177015937-f6e5250a-4f9b-4bec-9ab6-fe3f8a20cc99.png)

这里有添加的模型

保存文件到vscode文件所在文件夹，这样vscode可以打开gazebo生成的文件

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762180144097-b292ef62-d4a2-4252-956a-133f6570e16c.png)

关于操作可以移动物体坐标，可以添加物体，左键拉长，右键取消

机器人建模使用URDF，输入以下代码将UPDF转成sdf类型

```shell
sudo apt install ros-$ROS_DISTRO-gazebo-ros-pkgs
```

<h1 id="Mtivf">认识各种基本操作</h1>
<h2 id="y8BD7">world表示现有的模型</h2>
![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762237230057-1c677da1-bac9-4c0f-943a-0d2ecd8fe28e.png)

双击可以进入一个模型进行参数修改

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762237345857-012f4741-7e55-4ab7-b5f7-ad697844cc58.png)

<h2 id="Z0dUp">与world平级的layer是图层的意思</h2>
![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762237818138-0e7d5452-2b0d-4c60-be75-4e8ae63f5e7e.png)

    ↑ 选择场景模型                                                                                          ↑   复制/粘贴场景模型 

            ↑移动场景模型                                                                                               ↑模型对齐  

                   ↑旋转模型                                                                                                      ↑一个模型                            ↑缩放模型                                                                                      捕捉到另一个模型

                                                                                                 ↑在场景中添加灯光

                                                                                                                           更换观测视角↑

一打开gazebo应该就有一个空白的世界，打开原来生成的世界就有一个之前有生成过的世界，<font style="color:#DF2A3F;">需要注意的是，</font>一个gazebo里面就是一个世界，所以不能同时开多个gazebo

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762238599193-0df78574-1802-4c32-a94f-8767f3180608.png)

<h2 id="S4jHR">点击左下角世界运行</h2>
![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762238635029-fd6c15bd-5412-41ba-a868-ca3fb1fe56c0.png)

反重力方块会落地

点击双竖杠暂停播放

<font style="color:rgb(15, 17, 21);">Reset World：所有模型的位置和姿态都会被重置到你点击“播放”之前的状态。（本次播放之前）</font>

<h2 id="UvF4Y"><font style="color:rgb(15, 17, 21);">在世界中加入模型</font></h2>
<font style="color:rgb(15, 17, 21);">1.左侧工具栏</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762238821769-16e3648b-fcae-493d-88c6-76a470afcd3f.png)

2.上栏基本图形

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762238862755-34f9ad69-aaec-405c-90ef-8de0ce0bd94a.png)

<h2 id="PUPVJ"><font style="color:rgb(38,38,38);">理解 .world 和 .sdf 文件结构</font></h2>
<font style="color:rgb(15, 17, 21);">.sdf文件：世界中选中物体的具体信息说明</font>

<font style="color:rgb(15, 17, 21);">.world文件：gazebo里面整个世界的详细说明</font>

```cpp
<?xml version='1.0'?>  //文件版本
<sdf version='1.9'>
  <model name='my_first_cube'>    //物体名字                 ↓滚转，俯仰，偏航 
    <pose>0 0 0.5 0 0 0</pose> //初始位置，对应<x> <y> <z> <roll> <pitch> <yaw>
    <static>false</static>     // 受不受现实物理影响（比如重力（false不受））

    <link name='link'>//链接关节点，一个简单的模型（如立方体）只有一个链接
      <pose>0 0 0 0 0 0</pose>

      //碰撞属性：定义了物体的物理边界
      <collision name='collision'>
        <geometry>
          <box>        //<geometry> 定义了形状，这里是 <box>，尺寸是 1x1x1 米。
            <size>1 1 1</size>
          </box>
        </geometry>
      </collision>

      //视觉属性：定义了物体看起来的样子 
      <visual name='visual'>
        <geometry>
          <box>
            <size>1 1 1</size>
          </box>
        </geometry>
        <material>
          <ambient>0.8 0.2 0.2 1</ambient> //RGBA颜色 (深红色) 
        </material>
      </visual>

      //物理属性：定义了物体的质量、惯性等 
      <inertial>
        <mass>5.0</mass> // 质量 5公斤 
        <inertia>
          // 惯性矩阵 (对于立方体有标准公式)
          <ixx>0.416667</ixx>
          <ixy>0.0</ixy>
          <ixz>0.0</ixz>
          <iyy>0.416667</iyy>
          <iyz>0.0</iyz>
          <izz>0.416667</izz>
        </inertia>
      </inertial>
    </link>
  </model>
</sdf>
```

```cpp
<?xml version='1.0'?>
<sdf version='1.9'>
  <world name='default'>

    <环境设置 >
    //物理引擎参数
    <physics name='default_physics' type='ode'>//定义整个世界的开始
      <max_step_size>0.001</max_step_size> // 最大仿真步长 (秒)
      <real_time_factor>1.0</real_time_factor> //目标实时因子 
      <real_time_update_rate>1000.0</real_time_update_rate> //更新频率
    </physics>

    //场景光照 
    <scene>
      <ambient>0.4 0.4 0.4 1</ambient> // 环境光颜色 
      <background>0.7 0.7 0.7 1</background> // 背景色 
      <shadows>true</shadows> // 是否开启阴影 
    </scene>

    //全局光照 
    <light name='sun' type='directional'>
      <cast_shadows>true</cast_shadows>
      <pose>0 0 10 0 0 0</pose>
      <diffuse>0.8 0.8 0.8 1</diffuse> // 漫反射光颜色
      <specular>0.2 0.2 0.2 1</specular> // 高光颜色
    </light>

    <引入模型>
    //地面 
    <include>
      <uri>model://ground_plane</uri>
    </include>

    //阳光 
    <include>
      <uri>model://sun</uri>
    </include>

    <放置自己的模型>
    //方式一：使用 <include> 引入外部模型 
    <include>
      <uri>model://pioneer2dx</uri> // 从模型库引入一个机器人 
      <name>my_pioneer</name> // 在世界中给它起个新名字 
      <pose>2 0 0.2 0 0 0</pose> // 设置它的位姿 
    </include>

    //方式二：直接内联编写模型 (就是我们上面定义的立方体) 
    <model name='my_cube'>
      <pose>0 0 0.5 0 0 0</pose>
      <static>false</static>
      <link name='link'>
        ...   ← 这里省略了和上面立方体一样的 collision, visual, inertial 内容 
      </link>
    </model>

  </world>
</sdf>
```



1. **<font style="color:rgb(15, 17, 21);"><physics></font>**

<font style="color:rgb(15, 17, 21);">设置世界的 </font>**<font style="color:rgb(15, 17, 21);">物理引擎</font>**<font style="color:rgb(15, 17, 21);">（如 ODE, Bullet）和其参数。</font>

<font style="color:rgb(15, 17, 21);">max_step_size：仿真计算的精度。步长越小，越精确，但计算量越大。</font>

<font style="color:rgb(15, 17, 21);">real_time_factor：目标是1.0，意味着仿真1秒，真实世界也过去1秒。如果电脑性能不够，这个值会小于1，表示仿真变慢了。</font>

2. **<font style="color:rgb(15, 17, 21);"><scene>和 <light></font>**<font style="color:rgb(15, 17, 21);">：</font>

<font style="color:rgb(15, 17, 21);">世界的 </font>**<font style="color:rgb(15, 17, 21);">视觉效果</font>**<font style="color:rgb(15, 17, 21);">，如环境光、背景色、阴影和主光源（太阳）。</font>

**<font style="color:rgb(15, 17, 21);">3.<include> 标签（</font>****<font style="color:#DF2A3F;">非常重要！</font>****<font style="color:rgb(15, 17, 21);">）</font>**<font style="color:rgb(15, 17, 21);">：</font>

<font style="color:rgb(15, 17, 21);">这是 </font>**<font style="color:rgb(15, 17, 21);">模块化</font>**<font style="color:rgb(15, 17, 21);"> 的关键！你不需要在每个世界里都重新定义地面和太阳。</font>

```cpp
<uri>model://ground_plane</uri>
    
告诉 Gazebo：去模型库（通常在 ~/.gazebo/models 和 /usr/share/gazebo-11/models）里
找到名为 ground_plane 的模型，然后把它的整个 SDF 定义包含到我这里来。”
```

<font style="color:rgb(15, 17, 21);">可以通过 <pose> 和 <name>来覆盖被引入模型的初始位姿和名字。</font>

3. **<font style="color:rgb(15, 17, 21);">内联 <model></font>**<font style="color:rgb(15, 17, 21);">：</font>

<font style="color:rgb(15, 17, 21);">可以直接把模型的 SDF 代码写在世界文件里面，像定义 my_cube一样。</font>

<font style="color:rgb(15, 17, 21);">4,。joint（关节）好像用不到o.O</font>

<h4 id="Z4XUc">总结</h4>
<font style="color:rgb(15, 17, 21);">每一个link下面都有很多物理属性（惯性和碰撞属性）因为gazebo是一个物理仿真平台</font>

<font style="color:rgb(15, 17, 21);">为link添加gazebo标签，和gazebo控制插件</font>

**<font style="color:rgb(15, 17, 21);">其实</font>**<font style="color:rgb(15, 17, 21);">还有一个XACRO的文件，其实是一个进步后的极简化版本，可以把一些重复的部分缩成一个部分0（四个轮子都一样用一个宏定义全部定义而不是左轮右轮）</font>

<font style="color:rgb(15, 17, 21);">功能更丰富</font>

<h3 id="u3JdZ"><font style="color:rgb(15, 17, 21);">打开gazebo中已生成的文件</font></h3>
感觉和ros2正常打开文件是一样的，小乌龟里面也有一个打开小乌龟并且实用键盘控制

<h4 id="gogmN">1.有launch.py</h4>
```plain
ros2 launch 你的包名 gazebo_launch.launch.py
```

<h4 id="SScTx"><font style="color:rgb(15, 17, 21);">2. 如果只有可执行文件</font></h4>
```plain
# 终端1：启动Gazebo
ros2 launch gazebo_ros gazebo.launch.py

# 终端2：运行你的C++节点
ros2 run 你的包名 你的节点名称
```

<h4 id="nGyXh">这个是启用键盘控制（标准键盘控制节点）</h4>
```plain
ros2 run teleop_twist_keyboard teleop_twist_keyboard
```

<h4 id="XFLz4">问题机器人不出来怎么办</h4>
```plain
ros2 service call /gazebo/delete_entity gazebo_msgs/srv/DeleteEntity '{name: "pig_robot"}'
```



<h1 id="oSld3"><font style="color:rgb(15, 17, 21);">相机添加（原有的机器人已经生成，在上面添加）</font></h1>
<h2 id="jSTYS"><font style="color:rgb(38,38,38);">添加深度相机</font></h2>
<font style="color:rgb(15, 17, 21);">深度相机可以同时捕捉彩色图像和深度信息（每个像素点的距离）</font>

```plain
<sensor name='depth_camera' type='depth'>
  <pose>0.15 0 0.1 0 0 0</pose>  //初始位置 
  
  <camera name='main_depth_camera'>
    <horizontal_fov>1.047</horizontal_fov>
    <image>
      <width>640</width>
      <height>480</height>
      <format>R8G8B8</format>
    </image>
    <depth_camera> //深度相机特有配置 
      <output>depth_image</output>
    </depth_camera>
    <clip>
      <near>0.05</near>
      <far>10.0</far>
    </clip>
  </camera>

  <always_on>true</always_on>
  <update_rate>30</update_rate>

  // 深度相机使用专门的插件 
  <plugin name='depth_camera_plugin' filename='libgazebo_ros_depth_camera.so'>
    <ros>
      <namespace>/my_robot</namespace>
    </ros>
    <camera_name>depth_camera</camera_name>
    <frame_name>depth_camera_optical_frame</frame_name>
    <image_topic_name>depth/image_raw</image_topic_name>
    <depth_image_topic_name>depth/image_raw</depth_image_topic_name>
    <point_cloud_topic_name>depth/points</point_cloud_topic_name>
    <camera_info_topic_name>depth/camera_info</camera_info_topic_name>
  </plugin>
</sensor>
```

<font style="color:rgb(15, 17, 21);"></font>

<h2 id="UR38I"><font style="color:rgb(38,38,38);">RGB 摄像头</font></h2>
```plain
<model name='my_robot'>
  <link name='base_link'>
    // 机器人的基本结构 (collision, visual, inertial) 

    // 添加 RGB 摄像头传感器 
    <sensor name='rgb_camera' type='camera'>
      // 传感器相对于 base_link 的位置和朝向 
      <pose>0.1 0 0.1 0 0 0</pose> // 在机器人前方 (x) 和略高 (z) 的位置 
      
      <camera name='main_camera'>
        <horizontal_fov>1.047</horizontal_fov> //视野角度 60度 (约1.047弧度) 
        <image>
          <width>640</width>   //图像宽度
          <height>480</height> //图像高度 
          <format>R8G8B8</format> //图像格式 
        </image>
        <clip>
          <near>0.05</near> // 最近可视距离 
          <far>10.0</far>   //最远可视距离
        </clip>
      </camera>

      // 始终启用 
      <always_on>true</always_on>
      // 更新频率 (Hz) 
      <update_rate>30</update_rate>

      // ROS 2 插件 - 这是与 ROS 通信的桥梁
      <plugin name='rgb_camera_plugin' filename='libgazebo_ros_camera.so'>
        <ros>
          <namespace>/my_robot</namespace> // ROS 命名空间 
        </ros>
        <camera_name>rgb_camera</camera_name> // 相机名称 
        <frame_name>rgb_camera_optical_frame</frame_name> // 坐标系 
        <image_topic_name>image_raw</image_topic_name> //图像话题 
        <camera_info_topic_name>camera_info</camera_info_topic_name> // 相机信息话题 
      </plugin>
    </sensor>
  </link>
</model>
```

<font style="color:rgb(38,38,38);">IMU 传感器(惯性测量单元)</font>

```plain
<sensor name='imu_sensor' type='imu'>
  <pose>0 0 0.05 0 0 0</pose> // 通常放在机器人的重心位置 
  
  <imu>
    // 可以配置噪声参数，使仿真更真实 
    <noise>
      <type>gaussian</type>
      <rate>
        <mean>0.0</mean>
        <stddev>0.0002</stddev>
      </rate>
      <accel>
        <mean>0.0</mean>
        <stddev>0.017</stddev>
      </accel>
    </noise>
  </imu>

  <always_on>true</always_on>
  <update_rate>100</update_rate> // IMU通常需要更高频率 

  // IMU 插件 
  <plugin name='imu_plugin' filename='libgazebo_ros_imu_sensor.so'>
    <ros>
      <namespace>/my_robot</namespace>
    </ros>
    <topic_name>imu</topic_name> // IMU数据话题 
    <frame_name>imu_link</frame_name> //IMU坐标系 
  </plugin>
</sensor>
```

<h2 id="FtDt0">话题输出格式</h2>
<h2 id="oyiOb">须知</h2>
gazebo输出有两种形式，而话题的输出格式是下面那一种

<font style="color:rgb(15, 17, 21);">1.仿真模型描述格式：xml</font>

<font style="color:rgb(15, 17, 21);">2.运行时数据通信格式：主要是ROS消息</font>

<font style="color:rgb(15, 17, 21);">区分：xml主要是在配置阶段使用</font>

<font style="color:rgb(15, 17, 21);">xml是一个大类，不是单指某一种文件形式，而是一个合集</font>

<font style="color:rgb(15, 17, 21);">如下：</font>

<font style="color:rgb(15, 17, 21);">.world 文件是 SDF 格式的 XML</font>

<font style="color:rgb(15, 17, 21);">.urdf 文件</font><font style="color:rgb(15, 17, 21);">是 URDF 格式的 XML</font>

<font style="color:rgb(15, 17, 21);">.xacro 文件是 XACRO 格式的 XML（urdf增强版）</font>

<font style="color:rgb(15, 17, 21);">单个机器人的物理模型</font>

```plain
<robot name="my_robot">
  <link name="base_link">
    <visual>
      <geometry>
        <cylinder length="0.1" radius="0.2"/>
      </geometry>
    </visual>
  </link>
</robot>
```

整个世界的仿真（是gazebo的原生样子）

```plain
<sdf version="1.6">
  <world name="default">
    <include>
      <uri>model://ground_plane</uri>
    </include>
    <include>
      <uri>model://sun</uri>
    </include>
  </world>
</sdf>
```

<font style="color:rgb(15, 17, 21);">让 URDF 支持变量、宏、条件语句，避免重复代码</font>

```plain
<xacro:macro name="default_inertial" params="mass">
  <inertial>
    <mass value="${mass}"/>
    <inertia ixx="0.1" ixy="0.0" ixz="0.0" iyy="0.1" iyz="0.0" izz="0.1"/>
  </inertial>
</xacro:macro>
```

机器人模型不单指robot，圆柱体，长方体这种几何图形在gazebo里也是机器人

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762684456501-48b5033b-573d-495c-bde0-8058e0de81e9.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762684484703-ac814009-88b2-4f53-8a65-35c9edf519c9.png)



![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762684510751-bd27e962-eec9-4faf-955c-378535ad6b30.png)

<h3 id="9fe19ab6"><font style="color:rgb(15, 17, 21);">1.</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">深度相机</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">(sensor_msgs/msg/Image)</font></h3>
<font style="color:rgb(15, 17, 21);">header: 时间戳和坐标系</font>

<font style="color:rgb(15, 17, 21);">height/width: 图像分辨率</font>

<font style="color:rgb(15, 17, 21);">encoding: 像素编码格式</font>

<font style="color:rgb(15, 17, 21);">data: 原始图像数据</font>

<h3 id="ff447028"><font style="color:rgb(15, 17, 21);">2.</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">RGB摄像头</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">(sensor_msgs/msg/Image)</font></h3>
<font style="color:rgb(15, 17, 21);">同上，用于彩色图像</font>

<h3 id="6f6b4372"><font style="color:rgb(15, 17, 21);">3.</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">激光雷达</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">(sensor_msgs/msg/LaserScan)</font></h3>
<font style="color:rgb(15, 17, 21);">ranges[]: 距离数据数组</font>

<font style="color:rgb(15, 17, 21);">angle_min/max: 扫描角度范围</font>

<font style="color:rgb(15, 17, 21);">range_min/max: 有效距离范围</font>

<h3 id="8d71386f"><font style="color:rgb(15, 17, 21);">4.</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">IMU</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">(sensor_msgs/msg/Imu)</font></h3>
<font style="color:rgb(15, 17, 21);">orientation: 四元数朝向</font>

<font style="color:rgb(15, 17, 21);">angular_velocity: 角速度</font>

<font style="color:rgb(15, 17, 21);">linear_acceleration: 线加速度</font>

**<font style="color:rgb(15, 17, 21);"></font>**

<h2 id="xdsoc"><font style="color:rgb(15, 17, 21);">创建机器人和启动模式</font></h2>
<h4 id="0f753b2a">**<font style="color:rgb(15, 17, 21);">步骤1：创建ROS工作空间和包</font>**</h4>


```plain
// 创建并编译工作空间
mkdir -p ~/catkin_ws/src
cd ~/catkin_ws/src
catkin_init_workspace
cd ..
catkin_make

//创建ROS包
cd ~/catkin_ws/src
catkin_create_pkg my_robot_gazebo roscpp gazebo_ros
cd ..
catkin_make
```

<font style="color:rgb(15, 17, 21);">1.catkin_ws：ROS的标准工作空间目录名（catkin是ROS的构建系统）</font>

<font style="color:rgb(15, 17, 21);">2.src：存放源代码的目录</font>

<font style="color:rgb(15, 17, 21);">3.catkin_init_workspace：初始化工作空间，创建必要的配置文件</font>

<font style="color:rgb(15, 17, 21);">4.catkin_make：编译工作空间（就像C++项目的make）</font>

<font style="color:rgb(15, 17, 21);">5.-p：如果最后一个文件夹所在的父目录有不存在的，就自动创立</font>

<h4 id="addceeb6">**<font style="color:rgb(15, 17, 21);">步骤2：创建机器人模型文件</font>**</h4>
<font style="color:rgb(15, 17, 21);">在 ~/catkin_ws/src/my_robot_gazebo 目录下创建以下结构：</font>

```plain
mkdir -p ~/catkin_ws/src/my_robot_gazebo/urdf
mkdir -p ~/catkin_ws/src/my_robot_gazebo/launch
mkdir -p ~/catkin_ws/src/my_robot_gazebo/worlds
```

**<font style="color:rgb(15, 17, 21);">创建URDF模型文件：</font>**<font style="color:rgb(15, 17, 21);"> urdf/simple_robot.urdf</font>

<font style="color:#DF2A3F;">urdf本身并不需要使用客户端库，所以不需要添加依赖</font>

```plain
ros2 run robot_state_publisher robot_state_publisher pig_robot.urdf
//发布urdf
```

<font style="color:#DF2A3F;"></font>



```plain
<robot name="simple_robot">
  <link name="base_link">    //link用来描述外观属性，name表示名字下面<>都是link下的属性
    <inertial>
      <mass value="5.0"/>
      <inertia ixx="0.1" ixy="0.0" ixz="0.0" iyy="0.1" iyz="0.0" izz="0.1"/>
    </inertial>
    <visual>                //visual用来描述机器人的外观
      <geometry>             //用来描述几何形状
        <cylinder length="0.2" radius="0.15"/>
      </geometry>
      <material name="blue">
        <color rgba="0 0 1 1"/>
      </material>
    </visual>
    <collision>    //看似与visual内容一样，实则描述的是机器人运动过程中的状态
      <geometry>
        <cylinder length="0.2" radius="0.15"/>
      </geometry>
    </collision>
  </link>

  <!-- 添加激光雷达 -->
  <gazebo reference="base_link">
    <sensor name="laser_sensor" type="ray">
      <pose>0 0 0.1 0 0 0</pose>
      <ray>
        <scan>
          <horizontal>
            <samples>360</samples>
            <min_angle>-3.14159</min_angle>
            <max_angle>3.14159</max_angle>
          </horizontal>
        </scan>
        <range>
          <min>0.1</min>
          <max>10.0</max>
        </range>
      </ray>
      <plugin name="laser_controller" filename="libgazebo_ros_laser.so">
        <topicName>/scan</topicName>
        <frameName>base_link</frameName>
      </plugin>
    </sensor>
  </gazebo>
</robot>
```

补充：

visual下面的origin是相对初始位置的偏移

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762523980280-451c897b-3eea-4ce6-99d8-ba8b6fbcb9ac.png)

不需要的时候都为0

<h4 id="4e7fb4b2">**<font style="color:rgb(15, 17, 21);">步骤3：创建启动文件</font>**<font style="color:rgb(15, 17, 21);"> launch/my_robot.launch</font></h4>
```plain
<launch>
  <!-- 启动Gazebo空世界 -->
  <include file="$(find gazebo_ros)/launch/empty_world.launch">
    <arg name="paused" value="false"/>
    <arg name="use_sim_time" value="true"/>
    <arg name="gui" value="true"/>
    <arg name="headless" value="false"/>
    <arg name="debug" value="false"/>
  </include>

  <!-- 将URDF加载到参数服务器 -->
  <param name="robot_description" textfile="$(find my_robot_gazebo)/urdf/simple_robot.urdf" />

  <!-- 在Gazebo中生成机器人 -->
  <node name="spawn_urdf" pkg="gazebo_ros" type="spawn_model" 
        args="-param robot_description -urdf -model my_simple_robot -x 0 -y 0 -z 0.1" />
</launch>
```

**<font style="color:rgb(15, 17, 21);">Gazebo话题的输出模式，C++程序在 rostopic echo /topic_name命令里看到的那个格式</font>**





```plain
# 1. 首先启动Gazebo仿真（假设你有一个机器人模型）
roslaunch your_robot_gazebo your_world.launch

//各个名字解析
//启动一个名为 your_world.launch 的启动文件
//这个文件位于名为 your_robot_gazebo 的ROS包中
//该文件会同时启动Gazebo仿真环境和机器人模型

# 2. 查看有哪些话题
rostopic list
# 你会看到类似： /scan, /odom, /camera/image_raw

# 3. 查看激光雷达数据的实时输出
rostopic echo /scan
```

**<font style="color:rgb(15, 17, 21);">你会看到这样的输出在屏幕上滚动：</font>**

```plain
header:
  seq: 12345
  stamp:
    secs: 1627890000
    nsecs: 123456789
  frame_id: "laser_link"
angle_min: -3.14159
angle_max: 3.14159
angle_increment: 0.0174533
time_increment: 0.0
scan_time: 0.1
range_min: 0.1
range_max: 10.0
ranges: [0.5, 0.51, 0.49, 2.3, inf, 1.2, ..., 0.6]
intensities: [100, 105, 98, ..., 110]
```

**<font style="color:rgb(15, 17, 21);">这就是Gazebo话题的输出模式</font>**



<h3 id="70d1f2ad">**<font style="color:rgb(15, 17, 21);">二、 这个输出模式在C++代码中怎么用？</font>**</h3>
<font style="color:rgb(15, 17, 21);">现在看C++代码如何接收这个</font>**<font style="color:rgb(15, 17, 21);">完全一样的数据</font>**<font style="color:rgb(15, 17, 21);">：</font>



```plain
#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h> // 包含对应的消息类型

// 当收到/scan话题的数据时，这个函数会被自动调用
void scanCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
    // 现在，msg对象里面的数据，和在rostopic echo里看到的完全一样！
    
    // 访问正前方的距离（就是ranges数组的中间值）
    int center_index = msg->ranges.size() / 2;
    float front_distance = msg->ranges[center_index];
    
    // 打印出来，你会发现和rostopic echo里的某个ranges值对应
    ROS_INFO("正前方距离: %.2f 米", front_distance);
    
    // 访问最小角度
    ROS_INFO("扫描起始角度: %.2f 弧度", msg->angle_min);
    
    // 访问坐标系信息
    ROS_INFO("数据来自坐标系: %s", msg->header.frame_id.c_str());
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "my_node");
    ros::NodeHandle nh;
    
    // 订阅/scan话题，指定消息类型和回调函数
    ros::Subscriber sub = nh.subscribe("/scan", 10, scanCallback);
    
    // 保持程序运行，持续接收数据
    ros::spin();
    
    return 0;
}
```



<h3 id="0b35dfa8">**<font style="color:rgb(15, 17, 21);">三、 总结</font>**</h3>
1. **<font style="color:rgb(15, 17, 21);">输出模式 = rostopic echo显示的那个结构</font>**

<font style="color:rgb(15, 17, 21);">有header、angle_min、ranges等字段</font>

<font style="color:rgb(15, 17, 21);">每个字段都有具体的值</font>

2. **<font style="color:rgb(15, 17, 21);">在C++中 = 对应的消息类对象</font>**

<font style="color:rgb(15, 17, 21);">sensor_msgs::LaserScan 类</font>

<font style="color:rgb(15, 17, 21);">用 msg->字段名 来访问数据</font>

<font style="color:rgb(15, 17, 21);">数据内容和 rostopic echo看到的完全一致</font>

3. **<font style="color:rgb(15, 17, 21);">这不是XML</font>**

<font style="color:rgb(15, 17, 21);">XML是用来配置模型的（机器人长什么样）</font>

<font style="color:rgb(15, 17, 21);">话题输出是运行时数据（机器人看到了什么）</font>

<h3 id="21a9a312">**<font style="color:rgb(15, 17, 21);">四、 调试</font>**</h3>
<font style="color:rgb(15, 17, 21);">当你不知道某个话题的输出格式时：</font>

**<font style="color:rgb(15, 17, 21);">先看类型</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. 

```plain
rostopic type /odom
# 输出：nav_msgs/Odometry
```

**<font style="color:rgb(15, 17, 21);">再看详细结构</font>**<font style="color:rgb(15, 17, 21);">：</font>

2. rosmsg show nav_msgs/Odometry

**<font style="color:rgb(15, 17, 21);">最后看实时数据</font>**<font style="color:rgb(15, 17, 21);">：</font>

3. rostopic echo /odom

**<font style="color:rgb(15, 17, 21);">在C++代码中按照同样的结构访问</font>**<font style="color:rgb(15, 17, 21);">：</font>

4. 

```plain
// 对应rostopic echo里看到的pose.position.x
double robot_x = msg->pose.pose.position.x;
```

**<font style="color:rgb(15, 17, 21);">记住：在 rostopic echo 里看到什么，就能在C++代码中用 msg-> 访问到什么！</font>**

<font style="color:rgb(15, 17, 21);">这就是Gazebo话题的输出模式 - 既不是神秘的XML，也不是复杂的概念，就是你在终端里看到的那个数据结构，直接对应到C++代码中的对象成员</font>

<h3 id="cIQOi"><font style="color:rgb(15, 17, 21);">五、练习</font></h3>
在vscode里面安装urdf插件，这样写的时候会有提示补全

ctrl+/快速出现注释块  <!--  -->

把imu固定在base_link上面，就要用到关节用于组合机器人的部件，相互连接

把子部件固定在父部件上

**<font style="color:#DF2A3F;">功能包一定要colcon！！！</font>**

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762667676092-f756bc90-f6f1-41a0-96ee-39adefacf180.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762667697003-2ba38ca7-14e5-46c0-8038-684137c8ade8.png)

<font style="color:rgb(15, 17, 21);">urdf_to_graphviz src/pig_robot.urdf运行的时候从子目录里面找对应的文件，所以不要进入文件外最里层文件</font>

```plain
urdf_to_graphviz pig_robot.urdf
//用这个建立urdf和gv
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762668245421-6ea98ce2-079e-4841-8c9b-180437263aec.png)

运行产生文件pdf和gv，显示刚才的文件连接关系

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762668273638-4899711d-a578-487c-acf4-6787e668482d.png)

<h3 id="waeQN">问题自检</h3>
```plain
xmllint --noout pig_robot.urdf
```

用上面这个信息实现文件自检，来查看问题出在哪里

<h2 id="H0TsG">rviz2</h2>
接着上面的内容，用上面生成的那个机器人

在vscode的终端输入

```plain
rviz2
```

打开rviz，然后点右下角add添加RobotModel

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762668807633-ad824a9a-e7f1-4990-b9db-09db17d7b632.png)

将话题topic改成文件file，用来将生成的机器人移进来

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762668791090-caf32a1a-77bc-4b59-afde-7659a66ec43f.png)

<font style="color:#DF2A3F;">注意：移的是urdf</font>

然后从description file里面添加

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762670246157-24ae2479-20f1-4c6a-b12f-3ed7c2b038f6.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762670349051-67a04860-da0e-42c8-a6f9-dc4288e47140.png)

上面爆红的base 与TF有关

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762670463496-7ede67f0-7481-4aa2-8563-2adb4501c604.png)

fixed frame从map改成base_link后，外面的父体（也就是圆柱体）就变得透明因为base_link找到base_link的TF了

rviz不会加载物体之间的关系

<font style="color:rgb(15, 17, 21);">根本原因：TF坐标系的发布</font>

```plain
ros2 run robot_state_publisher robot_state_publisher src/pig_robot/src/pig_robot.urdf
```

命令解决三件事

1. **<font style="color:rgb(15, 17, 21);">读取URDF文件</font>**<font style="color:rgb(15, 17, 21);">：解析你的机器人模型结构</font>
2. **<font style="color:rgb(15, 17, 21);">计算TF变换</font>**<font style="color:rgb(15, 17, 21);">：根据joint定义计算各个link之间的位置关系</font>
3. **<font style="color:rgb(15, 17, 21);">发布TF数据</font>**<font style="color:rgb(15, 17, 21);">：通过/tf话题持续发布坐标系变换信息</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762672120411-2b57d07a-ea8b-453d-aa1d-bd1446008d4e.png)

<h4 id="okwN9"><font style="color:rgb(15, 17, 21);">验证方法：</font></h4>


```plain
/ 查看TF树
ros2 run tf2_tools view_frames

/ 查看具体的TF变换
ros2 run tf2_ros tf2_echo base_link imu_link
```

回应显示

```plain
digraph G {
"base_link" -> "imu_link"[label=" Broadcaster: default_authority\nAverage rate: 10000.0\nBuffer length: 0.0\nMost recent transform: 0.0\nOldest transform: 0.0\n"];
edge [style=invis];
//表示两个连接关系建立成功
 subgraph cluster_legend { style=bold; color=black; label ="view_frames Result";
"Recorded at time: 1762672384.0962932"[ shape=plaintext ] ;
//tf关系建立成功但是缺少odom坐标系
}->"base_link";
//所有transform时间都是0.0，说明是静态TF（没有运动数据）
}

```

解决方案，添加轮子

在终端创建完整的文件

```plain
cat > ~/Desktop/c/try_ws/src/pig_robot/src/pig_robot_complete.urdf << 'EOF'
<?xml version="1.0"?>
<robot name="pig_robot">
    <link name="base_link">
        <visual>
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <cylinder radius="0.10" length="0.12"/>
            </geometry>
            <material name="white_material">
                <color rgba="1.0 1.0 1.0 0.5"/>
            </material>
        </visual>
    </link>
    
    <!-- 添加轮子用于运动 -->
    <link name="left_wheel">
        <visual>
            <geometry>
                <cylinder radius="0.05" length="0.02"/>
            </geometry>
            <material name="black_material">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>
    
    <link name="right_wheel">
        <visual>
            <geometry>
                <cylinder radius="0.05" length="0.02"/>
            </geometry>
            <material name="black_material">
                <color rgba="0.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>
    
    <!-- 关节连接 -->
    <joint name="left_wheel_joint" type="continuous">
        <parent link="base_link"/>
        <child link="left_wheel"/>
        <origin xyz="0.0 0.08 0.0" rpy="1.5708 0 0"/>
        <axis xyz="0 1 0"/>
    </joint>
    
    <joint name="right_wheel_joint" type="continuous">
        <parent link="base_link"/>
        <child link="right_wheel"/>
        <origin xyz="0.0 -0.08 0.0" rpy="1.5708 0 0"/>
        <axis xyz="0 1 0"/>
    </joint>
    
    <link name="imu_link">
        <visual>
            <origin xyz="0.0 0.0 0.0" rpy="0.0 0.0 0.0"/>
            <geometry>
                <box size="0.02 0.02 0.02"/>
            </geometry>
            <material name="red_material">
                <color rgba="1.0 0.0 0.0 1.0"/>
            </material>
        </visual>
    </link>
    
    <joint name="imu_joint" type="fixed">
        <origin xyz="0.15 0.0 0.06" rpy="0.0 0.0 0.0"/>
        <parent link="base_link"/>
        <child link="imu_link"/>
    </joint>
    
    <!-- Gazebo控制插件 -->
    <gazebo>
        <plugin name="diff_drive_controller" filename="libgazebo_ros_diff_drive.so">
            <command_topic>/cmd_vel</command_topic>
            <odometry_topic>/odom</odometry_topic>
            <odometry_frame>odom</odometry_frame>
            <robot_base_frame>base_link</robot_base_frame>
            <publish_odom>true</publish_odom>
            <publish_odom_tf>true</publish_odom_tf>
            <publish_wheel_tf>true</publish_wheel_tf>
            <wheel_separation>0.16</wheel_separation>
            <wheel_diameter>0.1</wheel_diameter>
        </plugin>
    </gazebo>
</robot>
EOF
```

打开机器人

发布机器人描述用的工作空间

```plain
cd ~/Desktop/c/try_ws//进入工作空间
ros2 run robot_state_publisher robot_state_publisher src/pig_robot/src/pig_robot_complete.urdf

```

<font style="color:rgb(15, 17, 21);">在Gazebo仿真环境中生成你的机器人实体</font>

<font style="color:rgb(15, 17, 21);">从"设计图"（URDF文件）→ 变成"实物"（Gazebo中的3D模型）</font>

<font style="color:#DF2A3F;">如果没有这一步</font>

<font style="color:rgb(15, 17, 21);">有机器人的"设计图"（URDF），RViz能看到机器人模型</font>

<font style="color:rgb(15, 17, 21);">但Gazebo世界里是空的，</font>

<font style="color:rgb(15, 17, 21);">没有实际的机器人 无法进行物理仿真（碰撞、运动、传感器等）</font>

<h2 id="kgcZP"><font style="color:rgb(38,38,38);"> cmd_vel 、TF、odom 关系</font></h2>
<font style="color:rgb(15, 17, 21);">cmd_vel：行动指令</font>

<font style="color:rgb(15, 17, 21);">odom：记录里程数</font>

<font style="color:rgb(15, 17, 21);">TF：各个节点之间的关系</font>

<h3 id="d129095d"><font style="color:rgb(15, 17, 21);">2.1 cmd_vel   速度指令</font></h3>
<font style="color:rgb(15, 17, 21);">机器人按照这个指令进行移动</font>

```plain
# geometry_msgs/Twist 消息结构
linear:
  x: 0.2    # 前进速度 0.2 m/s
  y: 0.0    # 横向速度  
  z: 0.0    # 上升速度
angular:
  x: 0.0    # 翻滚角速度
  y: 0.0    # 俯仰角速度  
  z: 0.5    # 偏航角速度 0.5 rad/s
```



<h3 id="fd001028"><font style="color:rgb(15, 17, 21);">2.2 odom - 里程计信息</font></h3>
<font style="color:rgb(15, 17, 21);">机器人</font>**<font style="color:#DF2A3F;">自己估计</font>**<font style="color:rgb(15, 17, 21);">的位置（基于轮子编码器等）</font>

<font style="color:rgb(15, 17, 21);">相关数据：</font>

<font style="color:rgb(15, 17, 21);">轮子编码器：测量轮子转了多少圈</font>

<font style="color:rgb(15, 17, 21);">IMU：测量转向角度</font>

<font style="color:rgb(15, 17, 21);">通过数学计算得出位置变化</font>



```plain
# nav_msgs/Odometry 关键信息
header:
  frame_id: "odom"    / 参考坐标系
pose:                  / 位置和朝向
  position: {x: 1.2, y: 0.5, z: 0.0}      / 坐标
  orientation: {x: 0, y: 0, z: 0, w: 1}   / 四元数朝向
twist:                 / 速度
  linear: {x: 0.2, y: 0.0, z: 0.0}
  angular: {x: 0.0, y: 0.0, z: 0.1}
```

<h3 id="401b7da1"><font style="color:rgb(15, 17, 21);">2.3 TF - 坐标系变换</font></h3>
<font style="color:rgb(15, 17, 21);">描述机器人各个部件在空间中的相对位置关系(跟机器人各个部位之间的联系有关</font>

```plain
map (全局地图坐标系)
    ↓
odom (里程计坐标系) 
    ↓
base_footprint (机器人底面中心)
    ↓
base_link (机器人基座中心)
    ↓
camera_link    laser_link    wheel_link
```

<h2 id="3fb4de29"></h2>
<h1 id="Sl5yw"><font style="color:rgb(38,38,38);">键盘控制或节点发布话题控制机器⼈移动</font></h1>
首先需要注意的是，控制面板上的上栏左栏什么的不是键盘控制，<font style="color:rgb(15, 17, 21);">真正的键盘控制是</font><font style="color:rgb(15, 17, 21);">通过ROS2话题发布cmd_vel</font>

URDF用于描述机器人的外观属性等

```plain
ros2 run teleop_twist_keyboard teleop_twist_keyboard
启动键盘控制
```

<h1 id="de1b4dea"><font style="color:rgb(15, 17, 21);">在RViz中订阅Gazebo话题 </font></h1>
<h2 id="0da17f4c"><font style="color:rgb(15, 17, 21);">1. 启动仿真环境</font></h2>
<h3 id="1b5b0302"><font style="color:rgb(15, 17, 21);">终端1：启动Gazebo仿真</font></h3>
```plain
终端1：启动Gazebo
ros2 launch gazebo_ros gazebo.launch.py

 终端2：发布你的机器人描述
ros2 run robot_state_publisher robot_state_publisher src/pig_robot/pig_robot.urdf

 终端3：在Gazebo中生成你的机器人
ros2 run gazebo_ros spawn_entity -topic /robot_description -entity pig_robot
```

**<font style="color:#DF2A3F;">记得是不同的终端</font>**

发布

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762678183619-9baf9c53-80bd-4985-80a7-b4074b187bb9.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762678155078-0f3d9c1c-136c-4d15-a72f-45673a60b7cd.png)

生成

<h4 id="WiLAV">问题ros2崩掉了</h4>
在<font style="color:#DF2A3F;">系统的终端</font>里输入（注意，不是vscode的）

```plain
killall -9 gzserver gzclient ros2 python3 2>/dev/null
```

然后重启守护进程

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762679200098-df5ad2d4-6197-44fd-bb11-3e51c219cb59.png)

验证

```plain
ros2 topic list
```



<h3 id="eb60b9d4"><font style="color:rgb(15, 17, 21);">终端2：启动RViz</font></h3>


```plain
# 启动RViz
ros2 run rviz2 rviz2
```

<h2 id="206af3da"><font style="color:rgb(15, 17, 21);">2. 在RViz中配置显示</font></h2>
<h3 id="cd001605"><font style="color:rgb(15, 17, 21);">2.1 添加摄像头图像显示</font></h3>
**<font style="color:rgb(15, 17, 21);">步骤</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. <font style="color:rgb(15, 17, 21);">在RViz左侧</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Displays</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">面板点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Add</font>**
2. <font style="color:rgb(15, 17, 21);">选择</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Image</font>**
3. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">OK</font>**

**<font style="color:rgb(15, 17, 21);">配置</font>**<font style="color:rgb(15, 17, 21);">：</font>

```plain
Image Properties:
  - Topic: /camera/image_raw
  - Transport: raw
  - Queue Size: 10
```

<h3 id="80265c9b"><font style="color:rgb(15, 17, 21);">2.2 添加激光雷达显示</font></h3>
**<font style="color:rgb(15, 17, 21);">步骤</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Add</font>**
2. <font style="color:rgb(15, 17, 21);">选择</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">LaserScan</font>**
3. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">OK</font>**

**<font style="color:rgb(15, 17, 21);">配置</font>**<font style="color:rgb(15, 17, 21);">：</font>

```plain
LaserScan Properties:
  - Topic: /scan
  - Size: 0.05
  - Color: Green
```

<h3 id="e9439008"><font style="color:rgb(15, 17, 21);">2.3 添加坐标系显示</font></h3>
**<font style="color:rgb(15, 17, 21);">步骤</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Add</font>**
2. <font style="color:rgb(15, 17, 21);">选择</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">TF</font>**
3. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">OK</font>**

**<font style="color:rgb(15, 17, 21);">配置</font>**<font style="color:rgb(15, 17, 21);">：（显示是这样的）</font>

```plain
TF Properties:
  - Show Names: ✓
  - Show Arrows: ✓
  - Show Axes: ✓
```

<h2 id="a48b773a"><font style="color:rgb(15, 17, 21);">3. 检查Gazebo发布的话题</font></h2>
<h3 id="cb254ead"><font style="color:rgb(15, 17, 21);">终端3：查看可用话题</font></h3>
```plain
 查看所有话题
ros2 topic list

 查看摄像头话题
ros2 topic info /camera/image_raw

查看激光雷达话题  
ros2 topic info /scan

查看TF话题
ros2 topic info /tf
```

<h2 id="05fa41f4"><font style="color:rgb(15, 17, 21);">4. 验证数据流</font></h2>
<h3 id="e19818cd"><font style="color:rgb(15, 17, 21);">检查摄像头数据</font></h3>


```plain
# 查看摄像头图像信息
ros2 topic hz /camera/image_raw

# 查看图像消息详情
ros2 interface show sensor_msgs/msg/Image
```

<h3 id="254a345a"><font style="color:rgb(15, 17, 21);">检查激光雷达数据</font></h3>
```plain
# 查看激光雷达数据频率
ros2 topic hz /scan

# 查看激光数据内容
ros2 topic echo /scan --no-arr | head -10
```

<h3 id="17d468c0"><font style="color:rgb(15, 17, 21);">在RViz中添加地图</font></h3>
**<font style="color:rgb(15, 17, 21);">步骤</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Add</font>**
2. <font style="color:rgb(15, 17, 21);">选择</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Map</font>**
3. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">OK</font>**

**<font style="color:rgb(15, 17, 21);">配置</font>**<font style="color:rgb(15, 17, 21);">：</font>

```plain
Map Properties:
  - Topic: /map
  - Alpha: 0.7
```

<h2 id="6ed48373"><font style="color:rgb(15, 17, 21);">6. 添加目标识别结果显示</font></h2>
<h3 id="c4b64457"><font style="color:rgb(15, 17, 21);"> 添加标记显示（用于边界框等）</font></h3>
**<font style="color:rgb(15, 17, 21);">步骤</font>**<font style="color:rgb(15, 17, 21);">：</font>

1. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Add</font>**
2. <font style="color:rgb(15, 17, 21);">选择</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Marker</font>**
3. <font style="color:rgb(15, 17, 21);">点击</font><font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">OK</font>**

**<font style="color:rgb(15, 17, 21);">配置</font>**<font style="color:rgb(15, 17, 21);">：</font>

```plain
Marker Properties:
  - Topic: /detection_markers
  - Namespace: detection
```

<h2 id="BXEd6">Gazebo插件</h2>
实现机器人内容的共享

<font style="color:rgb(15, 17, 21);">Gazebo插件是</font>**<font style="color:rgb(15, 17, 21);">动态共享库</font>**<font style="color:rgb(15, 17, 21);">（.so文件），可以连接到Gazebo仿真环境中的不同组件，用于</font>**<font style="color:rgb(15, 17, 21);">扩展和自定义</font>**<font style="color:rgb(15, 17, 21);">仿真的行为。</font>

<h3 id="313302d8"><font style="color:rgb(15, 17, 21);">核心概念：</font></h3>
<font style="color:rgb(15, 17, 21);">插件形式：C++代码编译成的共享库</font>

<font style="color:rgb(15, 17, 21);">连接目标</font><font style="color:rgb(15, 17, 21);">：可以连接到世界(World)、模型(Model)、传感器(Sensor)、视觉(Visual)等</font>

<font style="color:rgb(15, 17, 21);">作用时机：在仿真运行时动态加载和执行</font>

<font style="color:rgb(15, 17, 21);">插件</font>**<font style="color:rgb(15, 17, 21);">作用</font>**<font style="color:rgb(15, 17, 21);">：</font>

<font style="color:rgb(15, 17, 21);"> 控制机器人的运动和行为</font>

<font style="color:rgb(15, 17, 21);">添加自定义的传感器数据处理</font>

<font style="color:rgb(15, 17, 21);">实现复杂的环境交互</font>

<font style="color:rgb(15, 17, 21);">与ROS等外部系统通信</font>

<font style="color:rgb(15, 17, 21);">创建特殊的仿真效果</font>

<h3 id="AoDJe"><font style="color:rgb(15, 17, 21);">1. 主要插件类型</font></h3>
<h4 id="dgF7o"><font style="color:rgb(15, 17, 21);"> World Plugin（世界插件）</font></h4>
<font style="color:rgb(15, 17, 21);">对于整个仿真世界进行操控，全局的数据调控和调整</font>

**<font style="color:rgb(15, 17, 21);">示例代码结构</font>**<font style="color:rgb(15, 17, 21);">：</font>



```plain
#include <gazebo/gazebo.hh>

namespace gazebo {
    class MyWorldPlugin : public WorldPlugin {
    public:
        void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf) {
            // 初始化代码
            this->world = _world;
            
            // 连接更新回调函数
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(
                std::bind(&MyWorldPlugin::OnUpdate, this));
        }
        
    private:
        void OnUpdate() {
            // 每一仿真步调用的函数
        }
        
        physics::WorldPtr world;
        event::ConnectionPtr updateConnection;
    };
    
    GZ_REGISTER_WORLD_PLUGIN(MyWorldPlugin)
}
```

<h3 id="17205712"><font style="color:rgb(15, 17, 21);"> Model Plugin（模型插件）</font></h3>
**<font style="color:rgb(15, 17, 21);">作用对象</font>**<font style="color:rgb(15, 17, 21);">：单个机器人模型，对于单个机器人运行的操控</font>

**<font style="color:rgb(15, 17, 21);">示例代码结构</font>**<font style="color:rgb(15, 17, 21);">：</font>

```plain
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>

namespace gazebo {
    class MyModelPlugin : public ModelPlugin {
    public:
        void Load(physics::ModelPtr _model, sdf::ElementPtr _sdf) {
            // 保存模型指针
            this->model = _model;
            
            // 获取关节（用于控制）
            this->joint = _model->GetJoint("wheel_joint");
            
            // 连接更新回调
            this->updateConnection = event::Events::ConnectWorldUpdateBegin(
                std::bind(&MyModelPlugin::OnUpdate, this));
        }
        
    private:
        void OnUpdate() {
            // 控制机器人运动
            this->joint->SetForce(0, 10.0);  // 施加力
        }
        
        physics::ModelPtr model;
        physics::JointPtr joint;
        event::ConnectionPtr updateConnection;
    };
    
    GZ_REGISTER_MODEL_PLUGIN(MyModelPlugin)
}
```

<h4 id="B2xOu"><font style="color:rgb(15, 17, 21);">2. 插件的工作流程</font></h4>
<h5 id="Rulzl"><font style="color:rgb(15, 17, 21);">生命周期：（其实各个生命周期基本都是差不多的，创建，初始化，然后结束删除）</font></h5>
<font style="color:rgb(15, 17, 21);">加载插件 → 初始化(Load) → 仿真循环(OnUpdate) → 仿真结束 → 清理</font>

<h5 id="mf1zC"><font style="color:rgb(15, 17, 21);">关键函数：</font></h5>
**<font style="color:rgb(15, 17, 21);">Load()</font>**<font style="color:rgb(15, 17, 21);">：插件加载时调用，用于初始化</font>

**<font style="color:rgb(15, 17, 21);">OnUpdate()</font>**<font style="color:rgb(15, 17, 21);">：每个仿真步调用，用于持续控制</font>

**<font style="color:rgb(15, 17, 21);">Reset()</font>**<font style="color:rgb(15, 17, 21);">：仿真重置时调用</font>

<h4 id="u1mJ1"><font style="color:rgb(15, 17, 21);">3.在URDF/SDF中使用插件</font></h4>
<h3 id="634347b7"><font style="color:rgb(15, 17, 21);">在URDF中：</font></h3>
```plain
<robot name="my_robot">
  <!-- 机器人模型定义 -->
  <link name="base_link">...</link>
  
  <!-- 插件声明 -->
  <gazebo>
    <plugin name="my_controller" filename="libmy_model_plugin.so">
      <parameter_name>value</parameter_name>
    </plugin>
  </gazebo>
</robot>
```

<h3 id="232f079f"><font style="color:rgb(15, 17, 21);">在SDF中：</font></h3>
```plain
<model name="my_robot">
  <!-- 模型定义 -->
  
  <plugin name="my_controller" filename="libmy_model_plugin.so">
    <parameter_name>value</parameter_name>
  </plugin>
</model>
```



