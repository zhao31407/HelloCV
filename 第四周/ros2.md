<h1 id="srckx">1主要功能</h1>
就是把项目的各部分拆开，分别把各个部分做好然后再组装成一整个机器人的过程，然后还可以实现信息的互通互享。

ros2是一个系统，可以在各种终端里面使用，vscode或者系统终端都是可以的

ros2有的时候需要用到cmake

<h1 id="Fzj1h">2工作空间</h1>
一个工作空间可以有多个功能包，一个功能包可以有多个节点，包含关系

工作空间里面的src是用来放功能包的，功能包中的src是用来放包中的文件的

<h2 id="k22gO">1.工作空间：</h2>
其实就是一个个人或者团队的仓库或者说目录，里面放置着你这一个项目所有的所有文件

因为都是在终端进行的，所以要区分cmake命令和ros2命令，因为感觉这个cd在cmake中也有

解决：因为cd是到指定目录，是终端的命令，而ros2和cmake都是在终端运行的，所以该有的终端指令都会有的详见Linux笔记版进行复习

在这里，ros2起一个调用的作用调用cmake里的程序

```cpp
source /opt/ros/humble/setup.bash
    所有终端使用ros2之前都要对ros2进行激活
```

```cpp
cmake是这样的
 1. 编写 CMakeLists.txt
 2. 用 cmake 生成 Makefile
 3. 用 make 实际编译
cmake ..
make

ROS2 中是这样的：
cd ~/ros2_ws
colcon build

 colcon 在背后为你执行了：
1. cmake -B build -S src   配置项目
2. cmake --build build     编译项目
3. 安装到 install/ 目录
所以可以理解为ros2一个命令就自动把cmake里的指令内容弄好了
```

<h3 id="Q0Xrc"><font style="color:rgb(15, 17, 21);">创建 ROS2 工作空间的完整流程</font></h3>
<h3 id="cf0f1215"><font style="color:rgb(15, 17, 21);">1. 创建目录结构</font></h3>


```cpp
// 在终端中执行以下命令
mkdir -p ~/ros2_ws/src

    注意-p前面和后面的空格
        1.~  代表我的主目录(/home/zhao/)
        2.-p 参数确保即使父目录不存在也会创建
        3.src 存放源代码（就是用来存放你输入和操作的内容）用于与生成的build什么的区分开
        4.mkdir是创建目录或文件夹的意思
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761566696113-25ee5e05-54b7-401e-b76d-d2733ad94e5b.png)

第一个错是因为忘空格了

<h3 id="9e06a1c7"><font style="color:rgb(15, 17, 21);">2. 验证创建结果</font></h3>
```cpp
 查看目录是否创建成功（ls -la是查找指令）
ls -la ~/ros2_ws/
    //~（波浪号）- 家目录
~
省略了用户主目录


/ 是路径分隔符
在路径中用于分隔目录层级

单独的 / 表示根目录
```

**<font style="color:rgb(15, 17, 21);"></font>**

**<font style="color:#DF2A3F;">注意有些指令只能在功能包里运行</font>**

**<font style="color:rgb(15, 17, 21);">只能在 ros2_ws/ 根目录操作的指令：（其实主要就前面那俩，主要是在新的功能包建立需要刷新工作空间的时候用）</font>**

<font style="color:rgb(15, 17, 21);">colcon build 系列命令</font>

<font style="color:rgb(15, 17, 21);">source install/setup.bash</font>

<font style="color:rgb(15, 17, 21);">colcon list等 workspace 管理命令</font>

<h2 id="yPXKz">2.功能包：</h2>
在包里运行ros2 run等指令

<h3 id="DfH8N">与工作空间的联系：</h3>
功能包相当于工作空间下的子目录

每新建一个功能包就要重新编译一下工作空间

```plain
colcon build --packages-select 新包名
source install/setup.bash
```

<h2 id="ee692f43"><font style="color:rgb(15, 17, 21);">功能包需要重新构建的情况：</font></h2>
<font style="color:rgb(15, 17, 21);">1.修改了 CMakeLists.txt（比如添加了可执行文件配置）</font>

<font style="color:rgb(15, 17, 21);">2 </font><font style="color:rgb(15, 17, 21);">修改了 package.xml</font><font style="color:rgb(15, 17, 21);">（添加了新的依赖）</font>

<font style="color:rgb(15, 17, 21);">3. </font><font style="color:rgb(15, 17, 21);">修改了 C++ 头文件</font><font style="color:rgb(15, 17, 21);">（.h, .hpp）</font>

<font style="color:rgb(15, 17, 21);">4. 添加/删除了源文件</font>

<font style="color:rgb(15, 17, 21);"></font>

拆分开的每一个模块

```cpp
ros2 pkg create my_cpp_package --build-type ament_cmake --dependencies rclcpp std_msgs
功能包创建命令    这个部分是要自己定义的       c++包            （这一项可以没有）依赖项，
                                                              可以添加或删除依赖，
                                                               可以后面手动修改
source install/setup.bash    这里面显示所有功能包所在位置，方便ros2找到的
打开两个终端，都运行一个程序，两个终端就可以通讯了
```

<font style="color:#DF2A3F;">功能包强烈建议在src目录下生成！！！因为colcon只默认在src目录中找包</font>

<h3 id="Lhakx"><font style="color:#000000;">过程</font></h3>
```cpp
1.进入src
    输入：cd ~/ros2_ws/src

        2.创建功能包
            ros2 pkg create my_first_robot --build-type ament_cmake --dependencies rclcpp std_msgs

3. 验证
    ls -la src/

    4. 编译
    colcon build --packages-select my_first_robot//注意是复数，有s
source install/setup.bash

    5. 检查包是否注册
        ros2 pkg list | grep my_first_robot

6. 运行节点
    ros2 run my_first_robot robot_node
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761831262494-c95a5dd1-3a07-4a5e-b7eb-9a2bba449142.png)完成

<h4 id="lr6Kp">其他</h4>
```cpp
ros2 pkg executables   列出所有可执行文件
ros2 pkg executables turtlesim    列出制定可执行文件
ros2 pkg list    列出所有包
ros2 pkg prefix <package-name>  输出某个包所在路径的前缀

```

目的：可以知道ros2 run可以运行什么

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761910438259-3bdb6758-59f9-4d6c-9913-a62c054c6887.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761910509936-3c1b60a9-1c3b-4bd1-b6a9-e78e80417bd8.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761910476254-d30d84e5-d052-47f9-a69b-0f030d911db8.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761910568173-ba4dbc1d-dbc6-4de0-9ff3-ad6a51bebc5d.png)

<h4 id="Fkk6Z">安装获取</h4>
```cpp
sudo apt install ros-<version>-package_name
                      版本，填humble  包的名字
安装完自动放置到系统目录 /opt/ros/humble
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761909590479-ffc54ff3-2621-4371-a74f-6fca1a95138a.png)

从lib或者share里面找

<h3 id="nKS5h"><font style="color:#000000;">问题与解决</font></h3>


```cpp
解决：
1.把别的地方的包移到src中
    mv ~/ros2_ws/1 ~/ros2_ws/src
    前面是包原来在的位置，可改
    mv my_first_robot src/   这种也是移动
    2.直接在src目录下建(其实就是进入src目录然后再建里就行)
    cd ~/ros2_ws/src
    ros2 pkg create my_cpp_package --build-type ament_cmake --dependencies rclcpp std_msgs
```

**<font style="color:rgb(15, 17, 21);">ros pkg</font>**<font style="color:rgb(15, 17, 21);">可以自动生成package.xml 和 CMakeLists.txt这两个东西</font>**<font style="color:rgb(15, 17, 21);">而且</font>**<font style="color:rgb(15, 17, 21);">相当于生成一个标签方便查找，而生成功能包后面那个命名的部分就是标签的名字（上面示例中的my_cpp_package）</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761634271785-512a177f-47f5-46bc-b080-999c565dd6c9.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761634290955-8b42f197-b7ea-4abd-a1d3-8ddc4273d4d9.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761715324642-0b6f0376-42df-46a7-9991-0bc98cd91646.png)

关于功能包的命名

——以小写字母开头

——这里的第三行写出来了功能包的名字是1

——需要注意的是，如果功能包没有写c++的依赖项，vscode是走不了ros2的，所以应该设立时依赖项该写的要写全

**<font style="background-color:#FBDE28;">——包名最好不要用数字开头</font>**因为包会用在很多地方，有些地方的命名是不允许数字开头的，所以

**<font style="color:rgb(15, 17, 21);">解决要加destination </font>****<font style="color:rgb(15, 17, 21);">！指定创建位置</font>**<font style="color:rgb(15, 17, 21);">解决包名问题，使功能包合法，不然可能会直接拒绝创建（因为包名无效）或者创建在其他位置或者自动重命名包，都不大好</font>

<font style="color:rgb(15, 17, 21);">建了一个新的功能包（my_first_robot）</font>

<font style="color:rgb(15, 17, 21);"></font>

通过ros2 pkg延伸出来的

```cpp
list列出系统中所有可用的 ROS2 包
ros2 pkg list
列出


grep查找特定包
ros2 pkg list | grep my_package
相当于在列出所有功能包的基础上再查找特定包
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761830516077-3fab4412-169f-4857-abd7-ed57d38a23ba.png)

关于依赖项要不要添加的问题

依赖能决定你的代码能用什么东西，能调用哪些库，所以依赖项也非常重要，虽然没有依赖项也是可以建起功能包的，但是没有c++的节点那个功能包没什么作用相当于是废的

```cpp
--dependencies rclcpp std_msgs
--dependencies这一部分用来指示后面是依赖项
    rclcpp 表示的是c++语言（如果没有就不能编译c++语言）
    std_msgs - 处理字符串/数字
    这一部分加要处理什么数据

    速度/位置  geometry_msgs
    摄像头/激光雷达 sensor_msgs
    文本/数字  std_msgs
    路径/地图  nav_msgs

    后面还可以加需要的高级功能
    坐标变换  tf2_ros
可视化显示  visualization_msgs
长时间任务  action_msgs
```

<h2 id="kV4Xz">3.<font style="color:rgb(15, 17, 21);">package.xml:</font><font style="color:#DF2A3F;">注意这个和CMakeList无论话题还是服务每一个都需要写对应的</font>（**<font style="color:rgb(15, 17, 21);">加依赖/改信息时更改）</font>**</h2>
<font style="color:rgb(15, 17, 21);">写这个表面项目的信息用来向外出示，包括作者、名字、版本什么什么的；还有这个项目需要从别的项目中引进什么，这样ros2可以进行引进，起一个索引作用</font>

<font style="color:#DF2A3F;">功能包依赖的声明，要让系统知道</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762430715691-129c181d-0334-41ea-a899-0d540e8cac12.png)

上面那个方框是使用说明，下面那个是依赖说明

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761910899799-fc7f57fc-1ef7-414b-974d-65d8d7822b43.png)

<h2 id="Tvqtm"><font style="color:rgb(15, 17, 21);">4.CMakeLists.txt:（</font>**<font style="color:rgb(15, 17, 21);">改代码/加文件时更改</font>**<font style="color:rgb(15, 17, 21);">）</font></h2>
<font style="color:rgb(15, 17, 21);">内部信息说明，用到哪些文件，哪个文件起什么作用</font>

<font style="color:rgb(15, 17, 21);">解释说明源代码文件在哪里、需要链接哪些库、最终要生成哪些可执行文件（比如节点）、如何安装等等</font>

<font style="color:rgb(15, 17, 21);">说明编译规则</font>

<font style="color:rgb(15, 17, 21);">在写完文件之后要更新cmake，具体的来说就是加一部分内容</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762430792862-0e4a1e20-ace8-46e3-ae0f-843d4aeaf0a4.png)

<h1 id="ZCSC3"><font style="color:rgb(15, 17, 21);">3节点</font></h1>
<font style="color:rgb(15, 17, 21);">节点是 </font>**<font style="color:rgb(15, 17, 21);">ROS2 系统中的基本执行单元</font>**

<font style="color:rgb(15, 17, 21);">一个物理存在的机器人，ros在机器人的主板上，控制机器人各个部分的行为，</font>

<font style="color:rgb(15, 17, 21);">而节点之间的通信，相当于各个节点之间建立连接，形成一个完整支持机器人的系统</font>

<font style="color:rgb(15, 17, 21);">像这种</font>

```cpp
ros2 run turtlesim turtlesim_node  这个后面的node就是节点的意思
相当于运行功能包中的一个可执行节点
```

<font style="color:rgb(15, 17, 21);">但是节点不一定带node</font>

<font style="color:rgb(15, 17, 21);">有的像talker什么的就是不带node的节点</font>

<h3 id="WYIbA"><font style="color:rgb(15, 17, 21);">colcon</font></h3>
```cpp

colcon build  后在src的同级会生成build，install，log文件夹
colcon build --packages-select 包名
source install/setup.bash
    单独编译功能包
    colcon build --packages-selcet 你想单独编译的功能包
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761912339731-104f72f5-a23a-4c37-ba13-8dd45370629a.png)



<h2 id="Y2tpO"><font style="color:rgb(15, 17, 21);">生命周期</font></h2>
1. **<font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">初始化：  rclcpp::init()</font>
2. <font style="color:rgb(15, 17, 21);">创建节点 ： std::make_shared<MyNode>()</font>
3. <font style="color:rgb(15, 17, 21);"> 运行 ：  rclcpp::spin(node)</font>
4. <font style="color:rgb(15, 17, 21);"> 关闭 ：  rclcpp::shutdown()</font>

<font style="color:rgb(15, 17, 21);">四种可以持续保持的状态</font>

未配置→待激活→激活→结束

          配置      激活     发生错误，关闭

鱼香ros10.3.3详细说明了如何编写，忘了就去看

<h1 id="i9SQa"><font style="color:rgb(15, 17, 21);">4rqt可视化工具集</font></h1>
可视化插件的集合，跟机器人的功能和状态监视有关

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762004691016-5a29f187-3e8a-4479-b226-baeb8114804a.png)

输入rqt就会出现可视化窗口

打开plugins，找到对应的板块输入对应的需求

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064494590-63a5aaed-343c-408c-bb20-aa632eaef4a8.png)

```plain
sudo apt install ros-humble-rqt-tf-tree -y    下载
rm -rf ~/.config/ros.org/rqt_gui.ini          运行
```

<h1 id="Wntv9">5命令</h1>
<h2 id="Tek0j">1.ros2 run运行命令</h2>
在任何目录中都可以运行，只要说明好包名和文件就可以

```cpp
ros2 run <包名> <可执行文件名>
可执行文件就是CMakeList.txt中定义的文件
    注意，这里是文件名而不是扩展名（也就是说cpp要省掉）
```

可以理解为ros2 run把功能包运行起来生成节点，而这个节点是之前不存在的

看功能包——过程——其他中的如何寻找功能包来确定可执行文件名是什么

<h3 id="V4ySx">问题和解决</h3>
<font style="background-color:#FBDE28;">注意</font>，如果没有写包名和可执行文件的话

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761715252189-b472da79-4627-4cd1-acd0-cff3abe3ebad.png)

会这样报错

```cpp
ros2 run turtlesim turtlesim_node
启动小乌龟
ros2 run turtlesim turtle_teleop_key
还要在另一个终端启动键盘控制节点（这样用键盘上的箭头就可以直接控制小乌龟的移动）
ros2 service call /reset std_srvs/srv/Empty
   清除小乌龟轨迹，让小乌龟回到中心 
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761832914817-47e1b0cd-5274-4052-87ba-d94a510d0ec3.png)

问题：包没有找到

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762514287929-6afbf007-75de-4804-b2de-4f1e158f486e.png)

解决

1.确认包是否存在，且能被ros2系统识别到

```plain
# 回到工作空间根目录
cd ~/Desktop/c/ros2_ws

# 查看工作空间中所有的包
colcon list
重新编译并显示详细输出
找到包的话
colcon build --packages-select subscriber --event-handlers console_direct+


```

<h4 id="Gv4kZ">问题2</h4>
CMakeLists.txt 中缺少 add_executable 语句，所以没有创建任何可执行文件

**<font style="color:#DF2A3F;">解决：文件一定要写在src里面！！！</font>**

<h2 id="hTpku">2.ros2 launch启动和配置完整系统</h2>
```cpp
基本语法
ros2 launch <功能包名称> <启动文件名称>
把信息告诉ros2（与前面的package.xml不一样）
注意找到可打开的文件
列出包的所有文件
ls $(ros2 pkg prefix 包名)/share/包名/
列出包的可执行文件
ls $(ros2 pkg prefix 包名)/lib/包名/
列出包的启动文件
ls $(ros2 pkg prefix 包名)/share/包名/launch/
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761914253663-39e2fdda-8796-42a4-9be6-e4df46b90eb9.png)

<h3 id="FaFUj">与ros2 run异同（launch要比run方便）</h3>
相同点：都可以创建节点

ros2 run：一次启动**一个**节点

ros2 launch：一次启动**多个**节点 + 配置参数



<h2 id="cbIoO">3.ros2 topic 话题有关</h2>
ros2 topic list

```cpp
列出所有当前的话题
ros2 topic list

同时显示话题类型
ros2 topic list -t
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761916673776-46d59ed4-523b-4d85-a437-42f01c4396fb.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761916711492-f1e03d4e-3b4a-4266-8816-db07a2d39350.png)

```cpp
ros2 topic --help     看看当前哪些topic命令可用
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762049113277-b1f59a23-dc3e-4469-ae72-49b7c70ebd01.png)

<h4 id="eVyxJ">ros2 topic echo <话题名称>   <font style="background-color:#FBDE28;">话题名称有哪些注意看node info冒号前内容，为话题名称</font></h4>
```cpp
 实时查看某个话题上流动的数据
ros2 topic echo /turtle1/pose
    这会持续显示小乌龟的位置坐标(x, y, theta等)刷屏
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762049545819-44c88a63-13cb-4130-990e-d8e084e9b5d2.png)

<h4 id="ba0S8">ros2 topic info <话题名称></h4>
```cpp
 查看话题的详细信息
ros2 topic info /turtle1/cmd_vel
     输出会显示：
     - 消息类型
     - 有几个发布者
     - 有几个订阅者
```

<h4 id="KpXbh">ros2 topic pub <话题名称> <消息类型> <数据></h4>
```cpp
 手动向话题发布消息
ros2 topic pub --once /turtle1/cmd_vel geometry_msgs/msg/Twist "{linear: {x: 2.0, y: 0.0, z: 0.0}, angular: {x: 0.0, y: 0.0, z: 1.0}}"
           public相当于公布    后面加话题名发布这个话题  
    
    / --once : 只发布一次  可以不加
    / /turtle1/cmd_vel : 话题名称（控制速度）
    / geometry_msgs/msg/Twist : 消息类型（速度指令）消息的接口
    / 后面的大括号里是具体的数据：线速度2.0，角速度1.0
    注意只要遇到后面有级别的都要加花括号进行分层，冒号后面要有空格
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762050812421-15ec4f4d-ec53-4a67-adfb-c797aeeed179.png)

<h2 id="pdXjc">4. ros2 service   服务相关命令（与大序号7中的内容相关）</h2>
<font style="color:rgb(15, 17, 21);">客户端发送请求，服务器处理请求并返回响应</font>

<h3 id="jgXGl">详细命令：</h3>
<h4 id="rjfZP">ros2 service list</h4>
```cpp
 列出所有可用的服务（当前正在运行的）
ros2 service list
```

有时候list后面加空格-t这是表示接口类型，但是一般不建议加-t因为这样需要手动输入接口类型，但是不加-t，ros2会自动生成接口类型

好处就是通过-t接口，你可以知道对应的信息应该写哪些内容

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762061993502-703cc85b-59d7-47dd-8a28-5fb54fc3b81f.png)

<<从这里看到spawn后面有[ ]这里面的东西你把它list下来就是你要输入的内容

先启动一个程序再用这个检验

这里启动的这个ros2 run turtlesim turtlesim_node

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761918229622-689822d7-c06d-4523-9cb2-7392c48e0bcb.png)

<h4 id="Ae5uW">ros2 service call <服务名称> <服务类型> <参数>    call是用来调用的</h4>
```cpp
 调用服务生成一只新乌龟
ros2 service call /spawn turtlesim/srv/Spawn "{x: 5.5, y: 5.5, theta: 0.0, name: 'turtle2'}"
                  服务名字  服务的消息接口
    # 你会立即看到仿真窗口中出现了第二只乌龟！
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064736800-f884a8e4-8b0e-42aa-8124-5d3c9f93cc77.png)

注意拼写和空格问题

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064562123-b70a3371-68cd-4cab-a058-b4c1578ddcda.png)

可以打开rqt，在services里面找caller

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064681334-3480cc95-bc66-4ec7-b8f5-c7333389849b.png)

进行更改



<h2 id="YRXMl">5. ros2 param 参数相关命令</h2>
<h3 id="KzTGn">详细命令：</h3>
<h4 id="TtZZt">ros2 param list</h4>
```cpp
 列出节点的所有参数
ros2 param list /turtlesim
    # 会看到 background_r, background_g, background_b 等参数
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761918998642-fecc43c0-1a16-43c9-8fdf-a169ed6237f0.png)

```cpp
ros2 param list  列出来的先是节点名（带/的）然后是参数
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762522796626-f84b5e06-0167-404d-a8e0-17f8757964f5.png)

get和set是一对，一个是查找，一个是改变

<h4 id="rvT7w">ros2 param get <节点名> <参数名>  查找参数对应值</h4>
```cpp
 获取参数的当前值
ros2 param get /turtlesim background_b
 输出：Integer value is: 255
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761919056017-28114826-4691-471f-9049-44ab6a653b5f.png)

<h4 id="LeFGt">ros2 param set <节点名> <参数名> <值>  改变参数对应值</h4>
```cpp
 设置参数的值
ros2 param set /turtlesim background_r 150
会立即看到仿真窗口的背景色变了！
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064799669-875662f4-7f98-443c-83fc-dc6ec995cf17.png)

<h4 id="IH9dg">ros2 param describe 参数名   列出参数所代表的详细内容</h4>
```cpp
ros2 param describe 参数名
```



<h2 id="hsvu6">6. ros2 node   与节点相关命令</h2>
<h4 id="ZjqrJ">ros2 node list查看当前运行的节点</h4>
```cpp
查看当前运行的所有节点
ros2 node list
 在运行了 turtlesim_node 后，你会看到：/turtlesim
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761833223925-bc69e588-c1b5-4703-a5f9-baa372643eab.png)

问题与解决：

注意当运行小乌龟程序的时候，如果程序还在运行是不能输入这个ros2 node list的，输入进小乌龟程序是不会有反应的，但是要注意的是，如果关闭小乌龟程序再输入就会导致没有正在运行的程序，不会有提示，直接给出输入框

解决：在vscode右边重启一个终端，在终端里输入ros2 node list，两个终端同时运行可以检测到程序的存在

<h4 id="PNDZB">ros2 node info <节点名> 查看节点详细信息</h4>
```cpp
查看节点的详细信息（非常重要！）
ros2 node info /turtlesim
    
输出包括：
发布哪些话题
订阅哪些话题  
 提供哪些服务
使用哪些服务
 有哪些参数
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761835048050-5d7ad4f1-161b-4767-824c-641894599fa0.png)

上面这一部分

<font style="color:rgb(15, 17, 21);">Subscribers：订阅哪些话题   后面冒号前是话题的名字，冒号后是话题的类型</font>

<font style="color:rgb(15, 17, 21);">Publishers：发布哪些话题 </font>

<font style="color:#81DFE4;">publisher到subscriber信息是单向的</font>

<font style="color:rgb(15, 17, 21);">Service Servers：提供哪些服务 </font>

<font style="color:rgb(15, 17, 21);">Service Clients：使用哪些服务</font>

<font style="color:#81DFE4;">service server和service client信息传递是双向的</font>

<font style="color:rgb(15, 17, 21);">Action Servers：提供哪些动作</font>

<font style="color:rgb(15, 17, 21);">Action Clients：使用哪些动作</font>

<h4 id="dvsRH"><font style="color:rgb(15, 17, 21);">--ros-args 重映射节点名称  再启动一个相同作用但不同名的节点（节点不能重名）</font></h4>
```cpp
ros2 run turtlesim turtlesim_node --ros-args -r __node:=my_turtle
          可执行包名  可执行文件名        重映射       新名字
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761907963091-18b4488c-f96d-49a6-a4bf-15a0a0ce75ac.png)

这样就会同时显示重映射前后的文件

<h2 id="aQ2Yo">7pwd</h2>
显示所在全部路径

8source工作空间

```cpp
source install/setup.bash
```

表示刷新应用列表编译后直接运行ros2识别不到，但是加上source刷新就可以识别到，使新编写的程序能够正常运行

<h2 id="fdwtH">完整练习流程：</h2>
1. **终端2**：查看节点

```cpp
ros2 node list
ros2 node info /turtlesim
```

2. **终端2**：查看话题

```cpp
ros2 topic list
ros2 topic echo /turtle1/pose
```

3. **终端3**：控制小乌龟

```cpp
ros2 run turtlesim turtle_teleop_key
# 用键盘控制小乌龟移动，同时在终端2观察位置变化
```

4. **终端4**：实验其他命令

```cpp
ros2 service list
ros2 param list /turtlesim
ros2 param set /turtlesim background_g 100
```

<font style="color:#DF2A3F;">随手ctrl+s保存代码是个好习惯，不然vscode不给你随时更新</font>

<h1 id="szqJm">6话题 单向传输</h1>
<h2 id="koCwI">1.订阅发布型</h2>
消息类型就是消息接口

订阅话题有话题名称

一个人可以订阅多个话题，一个话题也可以被多个人订阅

**<font style="color:#DF2A3F;">发布只能在文件所在的最小src里面</font>**

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761992341042-10853a1b-4d92-4f08-9500-a4962dfecb0f.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761992367689-0bfdd6f8-ad71-4fa1-92f3-554032ba0e74.png)

```cpp
/这个地方就是功能包建立时设置的依赖项
#include "rclcpp/rclcpp.hpp"  /这个地方是表示使用c++         
#include "std_msgs/msg/string.hpp"   /这个地方表示需要std数据 string表示字符串类型数据 
  /ros2 pkg create my_package --build-type ament_cmake --dependencies rclcpp std_msgs
  /对应的创建包的命令
/rclcpp是c++的客户端库

/  定义节点类
class MyAdvancedNode : public rclcpp::Node {
/使用：rclcpp::Node 基类 
/自己定义类名：类名 MyAdvancedNode
/自己编写：继承语法（和父子继承一样，相当于是把：后的这一部分给你定义的类了） : public rclcpp::Node

public:
/  编写构造函数
MyAdvancedNode() : Node("advanced_node") {  
/构造函数与类名相同   （写不开了，写下面） 
    / 初始化组件
    publisher_ = create_publisher<std_msgs::msg::String>("chatter", 10);
//泛型函数create_publisher（判断方法是后面加<>的）指不依赖具体数据类型的代码，可以存储任何类型
    //"chatter", 10  消息名称，缓存长度
subscriber_ = create_subscription<std_msgs::msg::String>(
        "chatter", 10,
        std::bind(&MyAdvancedNode::message_callback, this, std::placeholders::_1)
        );
    timer_ = create_wall_timer(
        std::chrono::seconds(1), 
        std::bind(&MyAdvancedNode::timer_callback, this)
        );
}

private:
/  编写回调函数
void timer_callback() {
    /函数体
    auto msg = std_msgs::msg::String();
    msg.data = "Timer: " + std::to_string(counter_++);
    publisher_->publish(msg);
    RCLCPP_INFO(get_logger(), "定时发布: '%s'", msg.data.c_str());
}

/  编写回调函数
void message_callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(get_logger(), "收到消息: '%s'", msg->data.c_str());
}

/ 定义成员变量
rclcpp::Publisher<std_msgs::msg::String>::SharedPtr publisher_;  发布者变量
  /           类型定义，这一部分是系统的，不能改     /
rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscriber_; 订阅者变量   除了函数外就这两行需要写
rclcpp::TimerBase::SharedPtr timer_; 定时器变量
int counter_ = 0; 计数器变量
};

/  主函数部分，其实可以与类的部分分开，然后用cmake合成
int main(int argc, char * argv[]) {
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyAdvancedNode>();
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
```

上面写不开了，写下面

缓存长度（19行的10）：有的时候新消息传过来的时候，旧消息没有处理完，新消息就排队称为缓存长度，但有的时候超过缓存长度了，那么越靠前的消息越早被冲掉

<h2 id="TmR0T">public：编写构造函数</h2>
<h3 id="HuOHY">1.创建构造函数</h3>
```cpp
MyAdvancedNode() : Node("advanced_node")
```

<font style="color:rgb(15, 17, 21);">MyAdvancedNode() ：构造函数，与类名相同</font>

**<font style="color:rgb(15, 17, 21);"> </font>**<font style="color:rgb(15, 17, 21);">Node("advanced_node") ： 初始化列表，调用父类构造函数</font>

<font style="color:rgb(15, 17, 21);">"advanced_node" ：</font><font style="color:#DF2A3F;">自己决定</font><font style="color:rgb(15, 17, 21);">的节点名称，要保持唯一性</font>

<h3 id="yeuTk"><font style="color:rgb(15, 17, 21);">2. 创建发布者</font></h3>
```cpp
publisher_ = create_publisher<std_msgs::msg::String>("chatter", 10);
```

<h4 id="VH5wh"><font style="color:rgb(15, 17, 21);">系统定义的，不动的</font></h4>
<font style="color:rgb(15, 17, 21);">create_publisher:创建发布者的方法</font>

<font style="color:rgb(15, 17, 21);">std_msgs::msg::String:</font><font style="color:rgb(15, 17, 21);">消息类型</font>

<h4 id="wUrlk"><font style="color:rgb(15, 17, 21);">自己定义的可以变的</font></h4>
<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">"chatter":自己决定</font><font style="color:rgb(15, 17, 21);">的话题名称（通信频道名）</font>

<font style="color:rgb(15, 17, 21);">"10":</font><font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">自己决定</font><font style="color:rgb(15, 17, 21);">的消息队列大小</font>

<font style="color:rgb(15, 17, 21);"> publisher_ :自己定义的成员变量，保存发布者对象</font>

<h4 id="ggPhh"><font style="color:rgb(15, 17, 21);">3: 创建订阅者</font></h4>
```cpp
subscriber_ = create_subscription<std_msgs::msg::String>(
    "chatter", 10,
    std::bind(&MyAdvancedNode::message_callback, this, std::placeholders::_1)
    );
```

<font style="color:rgb(15, 17, 21);">create_subscription -  系统提供的创建订阅者的方法</font>

<font style="color:rgb(15, 17, 21);">"chatter"</font><font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">自己决定</font><font style="color:rgb(15, 17, 21);">的话题名称（要监听哪个频道）</font>

<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">std::bind(...)系统提供</font><font style="color:rgb(15, 17, 21);">的函数绑定机制</font>

<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);">&MyAdvancedNode::message_callback：自己编写</font><font style="color:rgb(15, 17, 21);">的回调函数</font>

<font style="color:rgb(15, 17, 21);"> std::placeholders::_1  ：系统提供的占位符，表示接收消息参数</font>

<h4 id="Y0WeX"><font style="color:rgb(15, 17, 21);">4: 创建定时器</font></h4>
```cpp
timer_ = create_wall_timer(
    std::chrono::seconds(1), 
    std::bind(&MyAdvancedNode::timer_callback, this)
    );
```

<font style="color:rgb(15, 17, 21);">create_wall_timer 系统提供创建定时器的方法</font>

<font style="color:rgb(15, 17, 21);">std::chrono::seconds(1)：设定</font><font style="color:rgb(15, 17, 21);">的时间间隔（1秒）</font>

<font style="color:rgb(15, 17, 21);">&MyAdvancedNode::timer_callback：定时器回调函数</font>

<h3 id="aT5wd"><font style="color:rgb(15, 17, 21);">回调函数</font></h3>
```cpp
private:
// 编写回调函数
void timer_callback() {
    auto msg = std_msgs::msg::String();
    msg.data = "Timer: " + std::to_string(counter_++);
    publisher_->publish(msg);
    RCLCPP_INFO(get_logger(), "定时发布: '%s'", msg.data.c_str());
}                                                //把c++数据转化成c的类型

// 编写回调函数  
void message_callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(get_logger(), "收到消息: '%s'", msg->data.c_str());
}
```

<h4 id="HheFa"><font style="color:rgb(15, 17, 21);">回调函数1: timer_callback()</font></h4>
```cpp
void timer_callback() {
    // 创建消息对象
    auto msg = std_msgs::msg::String();
    // 设置消息内容
    msg.data = "Timer: " + std::to_string(counter_++);
    // 发布消息
    publisher_->publish(msg);
    // 记录日志
    RCLCPP_INFO(get_logger(), "定时发布: '%s'", msg.data.c_str());
}
```

<font style="color:rgb(15, 17, 21);">每1秒自动执行一次（由定时器触发）</font>

<font style="color:rgb(15, 17, 21);">功能：</font>

1. <font style="color:rgb(15, 17, 21);">创建新的字符串消息</font>
2. <font style="color:rgb(15, 17, 21);">设置消息内容（包含计数器值）</font>
3. <font style="color:rgb(15, 17, 21);">发布消息到 "chatter"话题</font>
4. <font style="color:rgb(15, 17, 21);">打印日志信息</font>

<h4 id="Ax1U1"><font style="color:rgb(15, 17, 21);">回调函数2: message_callback()</font></h4>
```cpp
void message_callback(const std_msgs::msg::String::SharedPtr msg) {
    RCLCPP_INFO(get_logger(), "收到消息: '%s'", msg->data.c_str());
}
```

<font style="color:rgb(15, 17, 21);">每当收到新消息时自动执行</font>

<font style="color:rgb(15, 17, 21);">const std_msgs::msg::String::SharedPtr msg： 接收到的消息</font>

<font style="color:rgb(15, 17, 21);">SharedPtr 是智能指针，自动管理内存</font>

<font style="color:rgb(15, 17, 21);">msg包含实际的消息数据</font>

<font style="color:rgb(15, 17, 21);">功能：打印接收到的消息内容</font>

<h3 id="aZFmb"><font style="color:rgb(15, 17, 21);">完整数据流向</font></h3>
定时器被触发开始，创建消息，设置内容，发布消息，记录日志

节点的功能<font style="color:rgb(15, 17, 21);">每1秒发布一条消息到 "chatter"话题，同时监听 "chatter"话题，收到消息就打印</font>

<h3 id="cKPko">继承调用差别：</h3>
这里要注意调用和继承的差别，

调用就是<font style="background-color:#FBDE28;">临时</font>拿过来使用

继承是子类可以用父类的所有操作，首先是永久的，其次是再使用的时候不用声明

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761713056494-072f0bee-5d23-4d43-a0db-1a615357f33f.png)

出现这种问题就是因为没有设置好工作空间

<h3 id="6a441bd4"><font style="color:rgb(15, 17, 21);">CMakeLists.txt </font></h3>
```cpp
不需要改——CMake最低版本
cmake_minimum_required(VERSION 3.8)

需要改——不同项目要修改的项目名称
project(my_topic_pkg)

不需要改——设置C++标准
    if(NOT CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 14)
            endif()

不需要改（根据消息类型修改）——查找依赖包
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)      std是消息类型geometry，sensor都可以改   

/编译发布者节点
add_executable(talker_node src/talker_node.cpp)  /修改文件名
              修改后的文件名    修改前的文件名
/必须：设置发布者节点的依赖
ament_target_dependencies(talker_node
rclcpp                    文件名
std_msgs              / std根据消息类型修改
)

/编译订阅者节点  
add_executable(listener_node src/listener_node.cpp)  / 修改文件名
               可执行文件名   源代码文件路径
/不改：设置订阅者节点的依赖
ament_target_dependencies(listener_node
rclcpp                    文件名跟着前面修改
std_msgs              /根据消息类型修改
)

/ 第一行不改：安装可执行文件
install(TARGETS
talker_node
listener_node         可执行文件名要跟上面保持一致
DESTINATION lib/${PROJECT_NAME}
)

不改：安装launch文件（如果有）
install(DIRECTORY launch
DESTINATION share/${PROJECT_NAME}
)

 不改：导出依赖
ament_export_dependencies(
rclcpp
std_msgs               根据消息类型修改
)

不改：生成安装脚本，在最后一行
ament_package()
```

依赖包需要

```cpp
#include "std_msgs/msg/string.hpp"
// 需要 ↓
find_package(std_msgs REQUIRED)
```

```cpp
#include "geometry_msgs/msg/twist.hpp"
// 需要 ↓
find_package(geometry_msgs REQUIRED)
```

```cpp
#include "std_srvs/srv/trigger.hpp"
// 需要 ↓
find_package(std_srvs REQUIRED)
```

```cpp
#include "example_interfaces/action/fibonacci.hpp"
// 需要 ↓
find_package(example_interfaces REQUIRED)
    find_package(rclcpp_action REQUIRED)
```

<h3 id="04fb8d02"><font style="color:rgb(15, 17, 21);">package.xml </font></h3>


```cpp
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypelayout="1.0"?>
//包格式声明 - 保持原样 
<package format="3">
    
    // 修改：根据实际情况修改包基本信息
    <name>my_topic_pkg</name>    改成新的包名，要与CMakeLists.txt中project()一致 -->
    <version>1.0.0</version>      版本
    <description>话题(Topic)示例包</description>  //改成自己的包描述 
    <maintainer email="zhao_2926945960@qq.com">zhao</maintainer>  // 改成自己的信息和邮箱 
    <license>Apache-2.0</license>     许可证，不改
    //不改：编译工具依赖 
    <buildtool_depend>ament_cmake</buildtool_depend>

   //不改
    <depend>rclcpp</depend>   //保持原样，所有C++节点都需要 
    <depend>std_msgs</depend>  // 根据消息类型修改，比如geometry_msgs、sensor_msgs等 
   / 执行时依赖 
    <exec_depend>rclcpp</exec_depend>  //不改
    <exec_depend>std_msgs</exec_depend>  //根据消息类型修改，要与上面的depend一致

   /下面的都不改
    <export>
        <build_type>ament_cmake</build_type>  
    </export>
</package>
```

<h3 id="PwSRi">补充</h3>
命令行：终端中输入的东西就是命令行



<h2 id="sqPbG">订阅</h2>
1.首先在工作空间里的src中创建一个文件包

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762506283542-8959601f-1205-411d-91ac-bfc0860664d9.png)

2.



<h2 id="P3VRq">Qos</h2>
1.历史记录

<font style="color:rgb(0, 0, 0);">Keep last: 只缓存最新的N个样本</font>

<font style="color:rgb(0, 0, 0);">keep all：保存所有样本</font>

<font style="color:rgb(0, 0, 0);">2.历史队列深度</font>

<font style="color:rgb(1, 1, 1);">Queue size: 当History设置为Keep Last时有效。(其实就是上面所说的保存N个样本的样本)</font>

3.可靠性reliability

best effort（常用）：专递速度快，但是不能保证能传过去，因为没有确认环节

reliable：保证样本传递，有确认环节

4.持久性

瞬态本地（transient local）：后来订阅者的数据可以被保留

易失性（volatile）：新的订阅者不会看到之前订阅者的数据，因为都被删除了

5.截止时间（deadline）

在此之前接受，不然就接受不了过期了

6.活跃度

automatic

martual by topic

7.租约持续时间



但是ros2帮我们配置好了很多配置文件

<h1 id="qlq2h">7服务 双向传输</h1>
与活动的区别，活动只要编写一个节点，但是服务要编写两个节点，分别写服务端和客户端

顺序是先启动服务端，再客户端调用服务，然后服务端完成客户请求

客户端发送需求到服务端，服务端做一定处理然后把信息返回客户端  

举一个加法的例子

服务端收到的

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762004501987-900b3187-ad00-4275-aa9b-267c183b971f.png)

最后一条是客户端发送及收到的

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762004552460-93852bab-946f-4117-a18b-35300f4063c4.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064539976-a12385df-5ab1-4874-bd92-124e81367828.png)

<h2 id="k3qBl">1.服务端</h2>
```cpp
#include "rclcpp/rclcpp.hpp"
#include "std_srvs/srv/trigger.hpp"  // 触发服务

class GenericServerNode : public rclcpp::Node {
public:
    GenericServerNode() : Node("generic_service_server") {  //  节点名可改
        //  必须：初始化服务端
        //  根据服务类型修改服务名和接口类型
        service_ = this->create_service<std_srvs::srv::Trigger>(
            "generic_service",  //  修改服务名称
            std::bind(&GenericServerNode::handle_request, this,
                     std::placeholders::_1, std::placeholders::_2));
        
        //可改：输出服务启动信息（引号内的都可改）
        RCLCPP_INFO(this->get_logger(), " 服务端启动成功，服务名: /generic_service");
    }

private:
    // 请求处理回调函数（函数名可改）
    void handle_request(
        // 一般不改：根据服务类型修改Request和Response类型
        const std::shared_ptr<std_srvs::srv::Trigger::Request> request,
        std::shared_ptr<std_srvs::srv::Trigger::Response> response) {
        
        // 记录收到请求
        RCLCPP_INFO(this->get_logger(), " 收到服务请求");
        
        
         /业务逻辑处理区域 - 根据实际需求修改
        
        try {
            // 这里添加业务逻辑
            RCLCPP_INFO(this->get_logger(), " 处理请求中...");
            
            // 模拟处理时间（根据实际需要修改或删除）
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            
            // 设置响应结果
            response->success = true;           //  根据服务接口修改
            response->message = "处理成功";     // 根据服务接口修改
            
            RCLCPP_INFO(this->get_logger(), "请求处理完成");
            
        } catch (const std::exception& e) {
            // 必须：错误处理
            RCLCPP_ERROR(this->get_logger(), " 处理请求时出错: %s", e.what());
            response->success = false;          //  根据服务接口修改
            response->message = "处理失败";     //  根据服务接口修改
        }
        
          // 业务逻辑结束
         
    }
    
    // 服务端指针
    rclcpp::Service<std_srvs::srv::Trigger>::SharedPtr service_;   
};

// main函数（基本不变）
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    
    //一般不改： 可以修改节点对象名
    auto server_node = std::make_shared<GenericServerNode>();
    
    RCLCPP_INFO(server_node->get_logger(), " 启动服务端节点");
    rclcpp::spin(server_node);
    
    rclcpp::shutdown();
    RCLCPP_INFO(server_node->get_logger(), " 服务端节点关闭");
    return 0;
}
```

<h2 id="Gsqjz">2.客户端</h2>
```cpp
#include "rclcpp/rclcpp.hpp"
// 根据服务类型修改头文件
#include "std_srvs/srv/trigger.hpp"  // 示例：触发服务

class GenericClientNode : public rclcpp::Node {
public:
    GenericClientNode() : Node("generic_service_client") {  //  修改节点名
        // 初始化客户端
        //  根据服务类型修改服务名和接口类型
        client_ = this->create_client<std_srvs::srv::Trigger>("generic_service");
        
        //  必须：等待服务端可用
        this->wait_for_service();
        
         业务逻辑区域 - 根据实际需求修改
         可以选择：定时调用、条件触发、单次调用等
         
        
        // 示例：定时调用（根据需求修改或删除）
        timer_ = this->create_wall_timer(
            std::chrono::seconds(3),  // 修改调用间隔
            std::bind(&GenericClientNode::send_request, this));
            
        // 或者：立即调用一次（二选一）
        // this->send_request();
    }

private:
    //  必须：等待服务端就绪
    void wait_for_service() {
        RCLCPP_INFO(this->get_logger(), " 等待服务端就绪...");
        while (!client_->wait_for_service(std::chrono::seconds(1))) {
            RCLCPP_INFO(this->get_logger(), " 服务端未就绪，继续等待...");
        }
        RCLCPP_INFO(this->get_logger(), "服务端已就绪");
    }
    
    // 发送请求函数（函数名可改）
    void send_request() {
        RCLCPP_INFO(this->get_logger(), " 发送服务请求");
        
         /请求参数设置区域 - 根据实际需求修改
         
        //  根据服务接口修改请求参数
        auto request = std::make_shared<std_srvs::srv::Trigger::Request>();
        // 示例：设置请求参数
        // request->data = true;  //  根据实际接口设置
        
        
        // 发送异步请求
        auto future = client_->async_send_request(request);
        
        // 等待响应（带超时）
        auto wait_result = rclcpp::spin_until_future_complete(
            this->get_node_base_interface(),
            future, 
            std::chrono::seconds(5)  //  修改超时时间
        );
        
        /响应处理区域 - 根据实际需求修改
         
        if (wait_result == rclcpp::FutureReturnCode::SUCCESS) {
            auto response = future.get();
            
            //  根据服务接口修改响应处理
            if (response->success) {
                RCLCPP_INFO(this->get_logger(), " 服务调用成功: %s", 
                           response->message.c_str());
            } else {
                RCLCPP_WARN(this->get_logger(), " 服务处理失败: %s", 
                           response->message.c_str());
            }
        } else {
            RCLCPP_ERROR(this->get_logger(), " 服务调用超时或失败");
        }
    }
    
    //  必须：客户端指针
    rclcpp::Client<std_srvs::srv::Trigger>::SharedPtr client_;  // 修改服务类型
    
    // 可选：定时器指针（如果使用定时调用）
    rclcpp::TimerBase::SharedPtr timer_;
};

// 必须：main函数（基本不变）
int main(int argc, char** argv) {
    rclcpp::init(argc, argv);
    
    //  可以修改节点对象名
    auto client_node = std::make_shared<GenericClientNode>();
    
    RCLCPP_INFO(client_node->get_logger(), " 启动客户端节点");
    rclcpp::spin(client_node);
    
    rclcpp::shutdown();
    RCLCPP_INFO(client_node->get_logger(), " 客户端节点关闭");
    return 0;
}
```

<h2 id="ade5c082"><font style="color:rgb(15, 17, 21);">3. 编译配置模板 (CMakeLists.txt)</font></h2>
```plain
/不改：CMake最低版本
cmake_minimum_required(VERSION 3.8)

/需要改：项目名称
project(generic_service_pkg)

/一般不改：查找依赖
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_srvs REQUIRED)  # std 根据服务接口修改

不改：编译服务端节点
add_executable(server_node src/server_node.cpp)
不改：设置依赖
ament_target_dependencies(server_node 
  rclcpp 
  std_srvs   / 根据服务接口修改
)

不改：编译客户端节点  
add_executable(client_node src/client_node.cpp)
不改：设置依赖
ament_target_dependencies(client_node 
  rclcpp 
  std_srvs  / 根据服务接口修改
)

//不改：安装目标
install(TARGETS
  server_node
  client_node
  DESTINATION lib/${PROJECT_NAME}
)

# 一般不改：导出依赖
ament_export_dependencies(rclcpp std_srvs)  # std 修改（一般不改）

 不改：生成安装脚本
ament_package()
```

<h2 id="27fbe954"></h2>
<h2 id="8c36849e"><font style="color:rgb(15, 17, 21);">4. 包配置模板 (package.xml)</font></h2>


```plain
<?xml version="1.0"?>
<?xml-model href="http://download.ros.org/schema/package_format3.xsd" schematypelayout="1.0"?>
<package format="3">
              //修改：包信息 
  <name>generic_service_pkg</name>
  <version>1.0.0</version>
  <description>通用服务系统模板</description>
  <maintainer email="your_email@example.com">Your Name</maintainer>
  <license>Apache-2.0</license>

         //不改编译工具 
  <buildtool_depend>ament_cmake</buildtool_depend>

          //不改编译依赖 
  <depend>rclcpp</depend>
  <depend>std_srvs</depend>    // 根据服务接口修改 

  //不改：导出 
  <export>
    <build_type>ament_cmake</build_type>
  </export>
</package>
```

<h1 id="Vdg7M">8参数服务器（详细的和ros2 param一起写了）</h1>
一般系统性的操作是这样的

首先开启一个程序



<h1 id="PMRJR">9<font style="color:rgb(38,38,38);">rviz 可视化</font></h1>
<font style="color:rgb(38,38,38);">终端输入</font>

```plain
rviz2
```

1.打开rviz

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762086103513-4eda32f1-c28b-478a-af6d-f446967e3a89.png)

最左列displays显示数据

选最左列下面的add按钮，添加可视化试图，

2.TF插件显示坐标变化

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762086243463-7db259e8-89c7-4f52-8039-40a70f0e68da.png)

两种分类方式，左边插件，右边话题

3.Grid显示方格坐标

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762086342281-08f27439-ecb6-4e87-80eb-ba6f4511d88a.png)

plane cell count：格子数量，如图为10*10

cell size：显示每个格子一米长宽





![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762086422057-4b04c272-af9f-476b-8737-1aed745cdfca.png)

show names：视图大小调整

<h2 id="l8624">tf相关</h2>
<h3 id="I5y2g"><font style="color:rgb(15, 17, 21);">rqt可视化工具集</font></h3>
可视化插件的集合，跟机器人的功能和状态监视有关

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762004691016-5a29f187-3e8a-4479-b226-baeb8114804a.png)

输入rqt就会出现可视化窗口

打开plugins，找到对应的板块输入对应的需求

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1762064494590-63a5aaed-343c-408c-bb20-aa632eaef4a8.png)

```plain
sudo apt install ros-humble-rqt-tf-tree -y    下载
rm -rf ~/.config/ros.org/rqt_gui.ini          运行
```

```plain
发布base_link到base_laser之间的变换：
ros2 run tf2_ros static_transform_publisher --x 0.1 --y 0.0 --z 0.2 --roll 0.0 --pitch 0.0 --yaw 0.0 --frame-id base_link --child-frame-id base_laser

发布base_laser到wall_point之间的变换：
ros2 run tf2_ros static_transform_publisher --x 0.3 --y 0.0 --z 0.0 --roll 0.0 --pitch 0.0 --yaw 0.0 --frame-id base_laser --child-frame-id wall_point
```

静态tf：安装死的，不会动

<h1 id="IgMau"><font style="color:rgb(38,38,38);">10launch.py 文件</font></h1>
<h2 id="e01N7">1.基本结构</h2>
<font style="color:rgb(15, 17, 21);">ROS2 的启动文件使用 Python 编写，扩展名为 .launch.py。基本结构如下：</font>



```python
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        // 在这里添加节点配置
    ])
```

<h2 id="980a508c"><font style="color:rgb(15, 17, 21);">2. 启动多个节点</font></h2>
<h3 id="f999cb67"><font style="color:rgb(15, 17, 21);">基本示例：启动两个节点</font></h3>


```plain
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        // 节点1：发布者
        Node(
            package='demo_nodes_cpp',
            executable='talker',
            name='my_talker'
        ),
        
        //节点2：订阅者
        Node(
            package='demo_nodes_py',
            executable='listener',
            name='my_listener'
        )
    ])
```

