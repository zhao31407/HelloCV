<h1 id="gw4P0">一。准备工作</h1>
测试OpenCV的版本

```cpp
echo '#include <opencv2/opencv.hpp>' > temp.cpp && echo '
int main(){std::cout << CV_VERSION << std::endl; return 0;}' 
>> temp.cpp && g++ -o temp temp.cpp `pkg-config --cflags --libs opencv4` 2>
/dev/null && ./temp || echo "OpenCV未正确安装"
```



显示后面直接跟出版本，显示版本4.5.4

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761090772332-fa4f1462-273d-4fa0-938b-8898f6e3d352.png)

OpenCV也相当一个工具，通过vscode这个平台来实现

<h1 id="P1jsv">二。图像读取与显示</h1>
前情提要，cv是opencv中的命名空间（就像std是c++的命名空间一样）,使系统明白该从哪里调取

不写的话容易起冲突，但是写了又太麻烦，知道这么个事，先不写，报错了再说<font style="background-color:#FBDE28;">不是一个类名</font>

<h2 id="f424ef89"><font style="color:rgb(15, 17, 21);">1. 读取图像：cv::imread()</font>只能读取照片</h2>
<font style="background-color:#FBDE28;">注意！！</font>如果只是读取，没有显示的话是不会生成新文件的，所以终端是有反应的，但是却没有新图像的生成

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761141897887-1f0ac098-3e37-45d1-82c9-a695982ee2c7.png)

<h3 id="e0587c44"><font style="color:rgb(15, 17, 21);">常用标志：</font></h3>
```cpp
cv::IMREAD_COLOR：读取为彩色图像（默认），忽略透明度。
cv::IMREAD_GRAYSCALE：读取为灰度图像。
cv::IMREAD_UNCHANGED：保留原样，包括透明度通道
```

<font style="color:rgb(15, 17, 21);"></font>

<h6 id="veFUA"><font style="color:rgb(15, 17, 21);"></font><font style="color:rgb(15, 17, 21);"> 透明度通道 (Alpha Channel)图像的透明程度</font></h6>
<font style="color:rgb(15, 17, 21);">1.图像的</font>**<font style="color:rgb(15, 17, 21);">第四个通道</font>**<font style="color:rgb(15, 17, 21);">（在 RGB 之后）</font>

<font style="color:rgb(15, 17, 21);">2.表示每个像素的</font>**<font style="color:rgb(15, 17, 21);">不透明度</font>**

<font style="color:rgb(15, 17, 21);">3.取值范围：0（完全透明）~ 255（完全不透明）</font>

<h3 id="614fc656"><font style="color:rgb(15, 17, 21);">示例：</font></h3>
```cpp
#include <opencv2/opencv.hpp>//引用OpenCV的头文件，其实就是把那些东西用进来

int main() {//main后面是有小括号的不然main会红后面的也会红这个小括号表示参数列表
    // 读取彩色图像
    cv::Mat image_color = cv::imread("image.jpg", cv::IMREAD_COLOR);
    
    // 读取灰度图像
    cv::Mat image_gray = cv::imread("image.jpg", cv::IMREAD_GRAYSCALE);
    
    // 检查图像是否读取成功
    if (image_color.empty() || image_gray.empty()) {
        std::cout << "图像读取失败！" << std::endl;
        return -1;
    }
    
    return 0;
}
```

**1.项目根目录**：就是你存放所有代码的地方

需要一个.vscode/文件夹来放跟OpenCV有关的文件，但是不需要将用到OpenCV的文件放到里面

<font style="color:rgb(15, 17, 21);background-color:#FBDE28;">2.Ctrl+S：快捷键，用于保存</font>

<font style="color:rgb(15, 17, 21);background-color:#FFFFFF;">如果include标红了，这说明OpenCV找不到头文件，这时候就要改c-cpp-properties.json,用下面这一段代码替代，这样红色就消失了</font>

```cpp
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**",
                "/usr/include/opencv4",
                "/usr/include/opencv4/opencv2",
                "/usr/include/x86_64-linux-gnu/opencv4/opencv2"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/g++",
            "cStandard": "c17",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761110662846-9288211b-437a-4109-ab9c-fbf540d4814e.png)这个标错表示找不到照片，需要通过终端寻找或者建立一张新照片（我用的照片名字是1.jpg）

所以应该是

```cpp
# 进入项目目录
cd ~/Desktop/yc

# 查看当前目录有哪些文件
ls -la

# 查看是否有 1.jpg 文件
ls -la *.jpg
```

**核心是照片不用存在于程序所在的目录，但是对于照片的表示会不同**

<h4 id="xVgP7"><font style="color:rgb(15, 17, 21);">情况1：图像在项目目录内</font></h4>
```cpp
项目目录/
├── 程序.cpp
└── image.jpg
```

**<font style="color:rgb(15, 17, 21);">代码：</font>**<font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);background-color:#FBDE28;">imread("image.jpg")</font><font style="color:rgb(15, 17, 21);">这样他就可以直接在目录里找到</font>

<h4 id="ob2E2"><font style="color:rgb(15, 17, 21);">情况2：图像在其他目录</font></h4>
```cpp
项目目录/
└── 程序.cpp

其他位置/
└── photo.jpg
```

**<font style="color:rgb(15, 17, 21);">代码需要完整路径：</font>**<font style="color:rgb(15, 17, 21);"> </font>`<font style="color:rgb(15, 17, 21);background-color:#FBDE28;">imread("/home/zhao/Pictures/photo.jpg")</font>`<font style="color:rgb(15, 17, 21);">这样需要先到那个目录才能找到文件</font>

<h4 id="cqYHO"><font style="color:rgb(15, 17, 21);"> </font><font style="color:rgb(15, 17, 21);background-color:#FBDE28;">注意：</font></h4>
**<font style="color:rgb(15, 17, 21);">"home 是小区，zhao 是你家房门号"</font>**

<font style="color:rgb(15, 17, 21);">1./home/ = 整个小区（有很多户）</font>

<font style="color:rgb(15, 17, 21);">2./home/zhao/ = 你的家（你的个人空间）</font>

<font style="color:rgb(15, 17, 21);">3.所以要写home表示你的主目录的话就</font><font style="color:rgb(15, 17, 21);background-color:#FBDE28;">必须写上zhao</font><font style="color:rgb(15, 17, 21);">，不然还会找不到</font>

<h4 id="nWi5A"><font style="color:rgb(15, 17, 21);background-color:#FBDE28;">现实路径小技巧：</font></h4>
<font style="color:rgb(15, 17, 21);">你可以在终端中直接拖拽文件来获取完整路径：</font>

```cpp
# 输入 ls 然后直接把图像文件拖到终端里
ls [把1.jpg文件拖到这里]
```

<font style="color:rgb(15, 17, 21);">这样会自动显示文件的完整路径！</font>

<h4 id="fyxgy">文件名报错</h4>
![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761131031182-77fdcedb-782e-49e9-a6eb-f7ff22732208.png)

<font style="color:#DF2A3F;">注意Desktop是大写</font>

**解决**

<h5 id="H6oZs"><font style="color:rgb(15, 17, 21);"></font><font style="color:rgb(15, 17, 21);"> Linux 路径各部分含义：</font></h5>
```cpp
/home/zhao/Desktop/文件夹名
```

```plain
/ = 根目录（整个文件系统的起点）
 home/ = 所有用户的主目录文件夹
zhao/ = 你的用户名（你的个人主目录）
Desktop/ = 桌面文件夹
文件夹名/ = 你的项目文件夹名称
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761131266193-30816c20-14c5-4a7b-9914-00a43fa2b797.png)

需要大写，虽然本来就在这个目录里，如果是子目录蓝色部分就会增多

<h2 id="c315c7f4"><font style="color:rgb(15, 17, 21);">2. 图像显示：cv::imshow() 与 cv::waitKey()</font></h2>
<h3 id="7cf723fa"><font style="color:rgb(15, 17, 21);">cv::imshow() 作用</font></h3>
<font style="color:rgb(15, 17, 21);">创建窗口并显示图像。起一个显示的作用</font>

<font style="color:rgb(15, 17, 21);">承接上文，如果光有imread的话这个图像是不会显示出来的，，但是有了这个图像就会显示</font>

```cpp
cv::imshow(窗口名称, 图像数据);
```

imshow有两个参数

**<font style="color:rgb(15, 17, 21);">1.第一个参数</font>**<font style="color:rgb(15, 17, 21);">：窗口的标题（字符串）</font>

**<font style="color:rgb(15, 17, 21);">2.第二个参数</font>**<font style="color:rgb(15, 17, 21);">：要显示的图像（cv::Mat）</font>

所以只写前面那一个参数的时候就会报错

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761142877906-17a0fe76-87bf-49a8-8ac2-8ea2ab35078c.png)

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761142893873-87620525-e09a-4788-8d43-ae96bf3c870e.png)

这个时候imshow里面只有一个参数

```cpp
#include <opencv2/opencv.hpp>
#include <iostream> 

int main(){

cv::Mat image_color = cv::imread("1.jpg", cv::IMREAD_COLOR);
//这里显示变量名为image_color了
所以，下面imshow里也一定要是image_color,不能写image_varities什么的
cv::imshow("1.jpg",image_color);
return 0
;}
```

<h3 id="678cbbc1"><font style="color:rgb(15, 17, 21);">cv::waitKey() 作用</font></h3>
<font style="color:rgb(15, 17, 21);">等待键盘输入,控制窗口显示时间,必要的窗口事件处理</font>

```cpp
#include <opencv2/opencv.hpp>
#include <iostream> 

int main(){

cv::Mat image_color = cv::imread("1.jpg", cv::IMREAD_COLOR);
cv::imshow("1.jpg",image_color);
cv::waitKey(0); 
return 0
;}
```

  
 cv::imshow和cv::waitKey一起用就会显示图像![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761145354315-c9d3f628-8c8b-4bc9-bdcd-83cce6ffdc95.png)

<h5 id="i2uxy">需要注意的是：</h5>
1.只有cv::imshow就像迅速开灯迅速关灯一样，不会出现窗口

2.只有cv::waitKey就是连灯都打不开

3.两个一起用前面的是打开，后面的是维持，这样才能达到窗口打开并维持一段时间的效果

**<font style="background-color:#FBDE28;">注意</font>****：waitKey主要用于最后图像的显示，所以基本所有跟图像有关的操作都要在此之前（包括后面的灰度化滤波）**

<h2 id="a7ypE">保存图像cv::imwrite()</h2>
<font style="color:rgb(15, 17, 21);">cv::imwrite()：</font><font style="color:rgb(15, 17, 21);"> 用于将</font><font style="color:#000000;background-color:#96A7FD;">内存</font><font style="color:rgb(15, 17, 21);">中的图像（cv::Mat 对象）保存为图像文件。</font>

<font style="color:rgb(15, 17, 21);">什么是内存，这里的内存不同于电脑中所存的文件（应该是叫硬盘），他是一个暂时的，所依附的程序消失他也会消失，而cv::imwrite就是将他留下来的，这样程序结束，图像不会随之消失</font>

```cpp
  bool cv::imwrite(const String& filename, InputArray img);
//布尔型 保存图像(常量 字符串& 文件名, 输入数组 图像数据);
//注意，这里既然是文件名了就是一个字符串，要加双引号
//还要注意图像数据（cv::Mat 对象）不是文件名字符串！
//也就是说，你不能直接把1.jpg写上，而是要写对应的图像数据
//是变量名（比如说你之前写的是image_color,这里也写image_color保持一致）
//而非单单写个image就行
//撑死了用到
//cv::imwrite("灰度图.jpg", gray_image);
  //  cv::imwrite("模糊图.png", blur_image);
    //再多就带个质量参数
    

```

注意，真正写imwrite函数的时候是不用写bool和const的，这只是开发者告诉你应该写什么类型的变量的，是下面这样的

```cpp
cv::imwrite("output.jpg", image);
//"output.jpg"是你要输出的文件名
```

最终程序是这样的

```cpp
#include <opencv2/opencv.hpp>
#include <iostream> 

int main(){

cv::Mat image_color = cv::imread("1.jpg", cv::IMREAD_COLOR);
cv::imshow("1.jpg",image_color);
cv::waitKey(0); 
 cv::imwrite("2.jpg",image_color);
return 0
;}
```



![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761147299523-f8533b78-d040-453f-a0b0-3ba7e382827e.png)

然后会再生成一个图像

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761147326481-ce709263-98ba-46aa-b248-5c7ab0278e4d.png)

当然1.jpg也会弹出

<h1 id="xLlQ2">三。图像属性</h1>
```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 读取图像 - imread函数从文件加载图像到内存。image="   .jpg"
    Mat image = imread("your_image.jpg");
    
    // 检查图像是否成功加载
    // empty()函数检查Mat对象是否包含数据
    if (image.empty()) {
        cout << "无法加载图像！请检查文件路径是否正确" << endl;
        return -1;
    }
    
    // 获取图像属性
    // rows: 图像的高度，单位是像素
    // 图像由一行行的像素组成，rows就是总共有多少行
    int rows = image.rows;
    
    // cols: 图像的宽度，单位是像素  
    // 下面是一个赋值
    int cols = image.cols;
    
    // channels: 颜色通道数
    // 1通道 = 灰度图，3通道 = 彩色图(BGR)，4通道 = 带透明度的图(BGRA)
    int channels = image.channels();
    
    cout << "图像尺寸: " << cols << " x " << rows << endl;
    cout << "通道数: " << channels << endl;
    cout << "图像总像素数: " << cols * rows << endl;//相当于问一个表格有几个格
    
    return 0;
}
```

<font style="color:rgb(15, 17, 21);">1.rows= 表格的总行数</font>

<font style="color:rgb(15, 17, 21);">2.cols= 每行的单元格数</font>

<font style="color:rgb(15, 17, 21);">3.channels= 每个单元格里包含的数据个数</font>

<h3 id="edaab8a8"><font style="color:rgb(15, 17, 21);">为什么是 image.at<Vec3b>(y, x)而不是 (x, y)</font></h3>
```cpp
// 理解：矩阵访问顺序是 (行, 列) 也就是 (y, x)
    // 想象坐标系：
    // (0,0) (1,0) (2,0)  
    // (0,1) (1,1) (2,1)  
    // (0,2) (1,2) (2,2)  ← 这是y方向（行）
        ↑这是x方向（列）
    // 设置特定位置的像素为红色
    int y = 1;  // 第2行（从0开始计数）
    int x = 2;  // 第3列（从0开始计数）
cout << "访问的位置：第" << y << "行，第" << x << "列" << endl;


smallImage.at<Vec3b>(y, x) = Vec3b(0, 0, 255);
    // 关键解释开始：
    // image.at<Vec3b>(y, x) 的含义：
    // 1. image.at<> 是访问像素的方法
    // 2. <Vec3b> 是模板参数，表示我们要访问的是3个uchar组成的数据
    //    - Vec3b = Vector of 3 unsigned chars (3个无符号字符组成的向量)
    //    - 每个uchar取值范围0-255，代表颜色强度
    // 3. (y, x) 参数：y是行索引，x是列索引
    //就是行和列要一起用三个量，不是说第一个量是行用，第二个量是列用
    
    // 设置像素为红色
    // Vec3b(blue, green, red) - 注意是BGR顺序！
    // Vec3b(0, 0, 255) 表示：
    //   blue = 0, green = 0, red = 255 → 纯红色
    
```

<h1 id="MMrVX">四。视频读取</h1>
<h2 id="78a3c141"><font style="color:rgb(15, 17, 21);">1. VideoCapture 类</font></h2>
<h3 id="2592a32c"><font style="color:rgb(15, 17, 21);">VideoCapture 是什么？</font></h3>
<font style="color:rgb(15, 17, 21);"> 是OpenCV中用于视频捕获的类，它可以：</font>

<font style="color:rgb(15, 17, 21);">1.从摄像头实时捕获视频</font>

<font style="color:rgb(15, 17, 21);">2.从视频文件读取帧</font>

<font style="color:rgb(15, 17, 21);">3.从图像序列读取帧</font>

<font style="color:rgb(15, 17, 21);">4.总结来说就是读取视频或者读取帧的工具</font>

<h2 id="b58bba4b"><font style="color:rgb(15, 17, 21);"></font><font style="color:rgb(15, 17, 21);">打开视频源的三种方式</font></h2>
<h3 id="ce1043eb"><font style="color:rgb(15, 17, 21);">方式1：打开摄像头</font></h3>
现生成视频



```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    // 创建 VideoCapture 对象
    VideoCapture cap;
    //cap只是一个对象名可以随便改，VideoCapture是个类，这个不能改

    cap.open(0);

    // 打开默认摄像头（通常是电脑自带的摄像头）
    // 参数 0 表示默认摄像头
    // 如果有多个摄像头，可以尝试 1, 2, 3...

    // 检查摄像头是否成功打开
    if (!cap.isOpened()) {
        cout << "错误：无法打开摄像头！" << endl;
        return -1;
    }

    cout << "摄像头成功打开！" << endl;

    // 释放摄像头资源（重要！）
    cap.release();
    return 0;
}
```

<h3 id="552dcaa8"><font style="color:rgb(15, 17, 21);">方式2：打开本地视频文件</font></h3>


```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main() {
    VideoCapture cap;
    
    // 打开本地视频文件
    // 参数是视频文件的路径
    cap.open("D:/videos/sample.mp4");  // Windows路径
    // cap.open("/home/user/videos/sample.mp4");  // Linux路径
    
    if (!cap.isOpened()) {
        cout << "错误：无法打开视频文件！" << endl;
        cout << "请检查：" << endl;
        cout << "1. 文件路径是否正确" << endl;
        cout << "2. 文件格式是否支持" << endl;
        cout << "3. 视频编码器是否安装" << endl;
        return -1;
    }
    
    cout << "视频文件成功打开！" << endl;
    
    cap.release();
    return 0;
}
```

<font style="color:#DF2A3F;">注意</font>

```cpp
VideoCapture TrafficLight.mp4
//会报错，因为VideoCapture后面是不能跟.的
//所以要想用VideoCapture的话，就要先设置一个变量然后用这个变量打开文件
```

```cpp
VideoCapture cap;                    // 创建对象
cap.open("TrafficLight.mp4");       // 打开视频文件
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761222180097-1a9d4a26-a07b-4b93-98ca-2853562a7192.png)

一开始的代码，frame的位置是错的

**原因**

```cpp
1.Mat frame;
 Mat 是OpenCV的图像矩阵类
frame 是变量名（可以改成任何名字）
含义：创建一个空的图像容器，准备接收摄像头数据
2.builtinCamera >> frame;
作用：从摄像头读取一帧图像数据，存入frame变量
相当于：builtinCamera.read(frame);
```

<font style="color:rgb(15, 17, 21);">在上面那个程序中如果</font><font style="color:rgb(15, 17, 21);">builtinCamera >> frame在if语句外的话，if不成立语句也会运行可能会导致未定义行为导致程序崩溃，打开了就没事</font>

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761223946541-8acb6c9b-0878-4265-9a6a-549a5a43f4ae.png)

没有错误，可以运行，但是注意，只打开摄像头是不会有提示框的，所以是看不出来程序是否是运行的



<h5 id="DNNUn">运行时出现的问题——没有视频显示</h5>
**原因：**

<font style="color:rgb(15, 17, 21);"> cap.open("TrafficLight.mp4")只是</font>**<font style="color:rgb(15, 17, 21);">建立连接</font>**<font style="color:rgb(15, 17, 21);">，就像打开一本书的封面。</font>

<font style="color:rgb(15, 17, 21);">cap >> frame才是</font>**<font style="color:rgb(15, 17, 21);">真正读取内容</font>**<font style="color:rgb(15, 17, 21);">，就像一页一页地看书。</font>

imshow("Video", frame)显示帧（把图像显示在窗口）

连起来是这样的

```cpp
cap.open("TrafficLight.mp4");  // 1. 连接文件
cap >> frame;                  // 2. 读取帧（从文件获取图像数据）
imshow("Video", frame);        // 3. 显示帧（把图像显示在窗口）
```

<font style="color:rgb(15, 17, 21);">也就是说，如果只是输入open的话，是不会出现视频的</font>

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(){
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    waitKey(0);
    return 0; }//比如一开始的这样，程序不会报错，但是视频打不开
```

修改：

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;
int main(){
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    if(cap.isOpened()){
        Mat frame;
        cap >> frame;           
        imshow("Video", frame); 
        waitKey(0);  
    }
    return 0; }
```

<h2 id="TOjL1"><font style="color:rgb(15, 17, 21);">2.灰度化滤波</font></h2>
<h3 id="mTt61">1.滤波</h3>
<font style="color:rgb(15, 17, 21);">就是——</font>

**<font style="color:rgb(15, 17, 21);">1.去噪</font>**<font style="color:rgb(15, 17, 21);">：去掉照片上的杂点</font>

**<font style="color:rgb(15, 17, 21);">2.平滑</font>**<font style="color:rgb(15, 17, 21);">：让图像更柔和</font>

**<font style="color:rgb(15, 17, 21);">3.锐化</font>**<font style="color:rgb(15, 17, 21);">：让边缘更清晰（像增强细节）</font>

<h3 id="VWCgu">2.这是灰度化</h3>
```cpp
cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
// frame: 输入图像（彩色）
// grayFrame: 输出图像（灰度）
// COLOR_BGR2GRAY: 转换类型（BGR转灰度）
```

要使用灰度化的时候记得要声明：

```cpp
 Mat frame, grayFrame; 
```

这个cap>>frame之前是各种声明

```cpp
Mat frame, grayFrame;
```

写全了是这样的

```cpp
#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

int main(){
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    
    if(cap.isOpened()){
        Mat frame, grayFrame;  // 在这里声明grayFrame
        
        cap >> frame;           
        
        // 先进行灰度化处理
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
        
        // 然后显示结果
        imshow("原始视频", frame); 
        imshow("灰度视频", grayFrame);//可以理解虽然生成灰度滤波
        //，但是原文件还是存在的,所以前面还可以用frame
        
        waitKey(0);  
    }
    
    return 0; 
}
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761230215433-17908e60-3a00-43fd-a008-b0ea7f952377.png)![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761230315257-c7a968a1-12bb-405b-a68e-4defe519edde.png)



<h3 id="iwbCG">3.<font style="color:rgb(15, 17, 21);">使用循环逐帧读取视频</font></h3>
相比于一帧提取，只是多了两个步骤，第一个是while（true）循环来一帧帧调取，

还有就是waitKey里面不能是0了，要开始控制播放的速度了

<h4 id="DfOWQ"><font style="color:rgb(15, 17, 21);">1. while循环 - 负责"一帧一帧地读"</font></h4>
```cpp
while (true) {
    cap >> frame;      // 读一帧
    if (frame.empty()) break;  // 没帧可读就退出
    // 处理这一帧...
}
```

<h4 id="NBn4S"><font style="color:rgb(15, 17, 21);">2.播放速度的调整：</font></h4>
```cpp
// 快速播放 (15ms ≈ 66帧/秒)
waitKey(15);

// 正常播放 (30ms ≈ 33帧/秒)  
waitKey(30);

// 慢速播放 (100ms ≈ 10帧/秒)
waitKey(100);

// 极慢播放，一帧一帧看 (按任意键继续)
waitKey(0);
```

```cpp
#include <opencv2/opencv>
#include <iostream>
using namespace cv;
using namespace std;
int main(){
    VideoCapture cap;
    cap.open("TrafficLight.mp4");
    while(true){
    if(cap.isOpened()){
        Mat frame,grayFrame;
        cap >> frame;            
        cvtColor(frame, grayFrame, COLOR_BGR2GRAY);
        imshow("灰度视频",grayFrame);
        imshow("原视频",frame);
        waitKey(30); } 
        
    }
    return 0; }
```

与前面的程序相比多了两个黄色的部分，实现逐帧提取，要注意while的控制范围，是在一个循环里面，也就是一帧，一般在waitKey后，因为到waitKey一般就是显示图像，到最后了

出现问题：不好退出图像

设置按q建退出

```cpp
if (waitKey(30) == 'q') {  // 按q键退出
    break;
}
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761232086050-d4379da1-ab69-4995-bcb1-d30c2a0354f5.png)

这样一摁就可以关闭图像啦

<h1 id="Z0ciJ">五。基础图像处理与几何变换</h1>
<h2 id="o4OlO">1.<font style="color:rgb(15, 17, 21);"></font><font style="color:rgb(15, 17, 21);">色彩空间 - 图像的"不同表达方式"</font></h2>
<h3 id="427e5060"><font style="color:rgb(15, 17, 21);">就像用不同语言描述同一个物体：所以要转成hsv方便计算机识别</font></h3>
**<font style="color:rgb(15, 17, 21);">1.BGR</font>**<font style="color:rgb(15, 17, 21);">：OpenCV的默认语言（蓝-绿-红）</font>

**<font style="color:rgb(15, 17, 21);">2.RGB</font>**<font style="color:rgb(15, 17, 21);">：人眼的看法（红-绿-蓝）</font>

**<font style="color:rgb(15, 17, 21);">3.HSV</font>**<font style="color:rgb(15, 17, 21);">：按颜色属性描述（什么颜色-多鲜艳-多亮）</font>

**<font style="color:rgb(15, 17, 21);">4.灰度</font>**<font style="color:rgb(15, 17, 21);">：黑白照片模式</font>

```cpp
// 这些是OpenCV已经定义好的常量，直接使用：
COLOR_BGR2RGB     // BGR转RGB
COLOR_BGR2GRAY    // BGR转灰度  
COLOR_BGR2HSV     // BGR转HSV
COLOR_RGB2BGR     // RGB转BGR
cvtColor(image, rgb, COLOR_BGR2RGB);   // 转成红绿蓝顺序
cvtColor(image, hsv, COLOR_BGR2HSV);   // 转成色相-饱和度-明度
cvtColor(image, gray, COLOR_BGR2GRAY); // 转成黑白
// 这些是OpenCV的常量，不能改：
COLOR_BGR2RGB    // ✅ OpenCV定义的
COLOR_BGR2GRAY   // ✅ OpenCV定义的  
COLOR_BGR2HSV    // ✅ OpenCV定义的
Mat              // ✅ OpenCV定义的类
// 这些变量名是你自己起的，可以改成任何名字：
Mat rgb;         // 你可以改成：Mat red_green_blue;
Mat hsv;         // 你可以改成：Mat color_space;  
Mat gray;        // 你可以改成：Mat black_white;

Mat my_image;    // ✅ 合法
Mat photo123;    // ✅ 合法
Mat img;         // ✅ 合法
```



<h3 id="7a9f7cfa"><font style="color:rgb(15, 17, 21);"> Mat内容</font></h3>
<font style="color:rgb(15, 17, 21);">Mat是OpenCV的</font>**<font style="color:rgb(15, 17, 21);">图像容器类</font>**

<font style="color:rgb(15, 17, 21);">和int，string一样是一种数据类型</font>

<font style="color:rgb(15, 17, 21);">Mat rgb, hsv, gray：</font><font style="color:rgb(15, 17, 21);"> 这一行的意思是：</font>**<font style="color:rgb(15, 17, 21);">一次性声明三个Mat类型的变量，</font>**

**<font style="color:rgb(15, 17, 21);">记住变量声明完变量是空的，需要赋值变量里才有东西</font>**

<h2 id="153439e3"><font style="color:rgb(15, 17, 21);">2. 各类算子与滤波算法 （降低干扰，使画面清洁）</font></h2>
<h3 id="c255ede4"><font style="color:rgb(15, 17, 21);">就像处理一张旧照片：</font></h3>
**<font style="color:rgb(15, 17, 21);">1.高斯滤波</font>**<font style="color:rgb(15, 17, 21);">：让图像变柔和，减少细节</font>

**<font style="color:rgb(15, 17, 21);">2.中值滤波</font>**<font style="color:rgb(15, 17, 21);">：去除随机噪点（像去掉照片上的灰尘）</font>

**<font style="color:rgb(15, 17, 21);">3.边缘检测</font>**<font style="color:rgb(15, 17, 21);">：找出物体的轮廓线</font>

```cpp
Mat image = imread("old_photo.jpg");

Mat blurred, cleaned, edges;
GaussianBlur(image, blurred, Size(5,5), 0);    // 轻微模糊
medianBlur(image, cleaned, 5);                 // 去噪点
Canny(image, edges, 50, 150);                  // 提取边缘
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761233056773-e09a97fb-6f93-4d9e-a8e3-ad1e8ca88bf9.png)

<h2 id="b606dc9a"><font style="color:rgb(15, 17, 21);">3. 形态学操作 - 图像的"胖瘦改变的"</font></h2>
一般来说线条越明显越好

**<font style="color:rgb(15, 17, 21);">1.膨胀</font>**<font style="color:rgb(15, 17, 21);">：让线条变粗（填补断线）</font>

**<font style="color:rgb(15, 17, 21);">2.腐蚀</font>**<font style="color:rgb(15, 17, 21);">：让线条变细（去除毛刺）</font>

**<font style="color:rgb(15, 17, 21);">3.开运算</font>**<font style="color:rgb(15, 17, 21);">：先变细再变粗（去除小点）</font>

**<font style="color:rgb(15, 17, 21);">4.闭运算</font>**<font style="color:rgb(15, 17, 21);">：先变粗再变细（连接断线）</font>

```cpp
Mat binary_image; // 一张黑白图纸
Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));

Mat thicker, thinner, cleaned_dots, connected;
dilate(binary_image, thicker, kernel);    // 线条变粗
erode(binary_image, thinner, kernel);     // 线条变细
morphologyEx(binary_image, cleaned_dots, MORPH_OPEN, kernel);   // 去小点
morphologyEx(binary_image, connected, MORPH_CLOSE, kernel);     // 连断线
//变量名
Mat binary_image;        // 变量名：binary_image
Mat kernel;              // 变量名：kernel
Mat thicker;             // 变量名：thicker
Mat thinner;             // 变量名：thinner  
Mat cleaned_dots;        // 变量名：cleaned_dots
Mat connected;           // 变量名：connected
```

<h2 id="b702423b"><font style="color:rgb(15, 17, 21);">4. 图像的裁剪与缩放 </font></h2>


```cpp
Mat photo = imread("family_photo.jpg");

// 裁剪 - 从大图中选出一部分
Rect region(100, 50, 400, 300);  // 从(100,50)开始，宽400高300
Mat face = photo(region);         // 只保留人脸部分

// 缩放 - 改变图像尺寸
Mat smaller, larger;
resize(photo, smaller, Size(), 0.5, 0.5);   // 缩小一半
resize(photo, larger, Size(), 2.0, 2.0);    // 放大两倍
```



<h2 id="a1f04871"><font style="color:rgb(15, 17, 21);">5. 图形绘制和文字绘制 </font></h2>
<h3 id="YiGcW">rectangle图形绘制：</h3>
```cpp
rectangle(目标图像, 矩形位置, 颜色, 线宽);
retangle(frame, redbox, Scalar(0, 0, 255), 3)
//相当于把redbox加到frame视频里位置大小由redbox决定，
//注意，redbox也是你设置的一个变量
```

<h3 id="LXfNA"><font style="color:rgb(15, 17, 21);">putText 文字绘制：</font></h3>
```cpp
putText(图像, 文字, 位置, 字体, 大小, 颜色, 粗细);
```

<h4 id="gPshz"><font style="color:rgb(15, 17, 21);">参数解释与使用：</font></h4>
反正挺复杂的

```cpp
putText(frame, "RED", Point(box.x, box.y-10), 
        FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255), 2);
```

<h4 id="bm6sr"><font style="color:rgb(15, 17, 21);">其他常用字体：（后面用到再说）</font></h4>
```cpp
FONT_HERSHEY_SIMPLEX     // 正常字体
FONT_HERSHEY_PLAIN       // 小字体
FONT_HERSHEY_DUPLEX      // 复杂字体  
FONT_HERSHEY_COMPLEX     // 更复杂字体
FONT_HERSHEY_TRIPLEX     // 最复杂字体
```

<h2 id="667217cf"><font style="color:rgb(15, 17, 21);">6. 仿射变换、透射变换 </font></h2>
其实就是让图形规矩一点

<h3 id="c189b1a7"><font style="color:rgb(15, 17, 21);">仿射变换：保持直线平行性的调整</font></h3>


```cpp
// 比如校正倾斜的文档
Mat document = imread("scanned_doc.jpg");

Point2f src[3] = {Point2f(50,50), Point2f(400,50), Point2f(50,300)};
Point2f dst[3] = {Point2f(30,30), Point2f(400,30), Point2f(30,300)};

Mat transform = getAffineTransform(src, dst);
Mat corrected;
warpAffine(document, corrected, transform, document.size());
```

<h3 id="0f777672"><font style="color:rgb(15, 17, 21);">透射变换：透视效果校正</font></h3>


```cpp
// 比如把斜着拍的文档变成正面视图
Point2f src[4] = {Point2f(100,150), Point2f(380,120), 
                  Point2f(400,350), Point2f(120,380)};
Point2f dst[4] = {Point2f(0,0), Point2f(500,0), 
                  Point2f(500,400), Point2f(0,400)};

Mat perspective = getPerspectiveTransform(src, dst);
Mat front_view;
warpPerspective(image, front_view, perspective, Size(500,400));
```



<h2 id="f143d58b"><font style="color:rgb(15, 17, 21);">7. 颜色提取 - 图像的"颜色筛选器"</font></h2>
```cpp
// 常见颜色的HSV范围：
Scalar lower_red(0, 100, 100);    Scalar upper_red(10, 255, 255);    // 红色
Scalar lower_green(35, 50, 50);   Scalar upper_green(85, 255, 255);  // 绿色
Scalar lower_blue(100, 50, 50);   Scalar upper_blue(130, 255, 255);  // 蓝色
//注意，这个lower...和这个upper...都是变量名，实际上写的不是这样的
inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), red_mask);
//写成了是这样的

```

```cpp
Mat traffic_image = imread("street.jpg");
Mat hsv;
cvtColor(traffic_image, hsv, COLOR_BGR2HSV);

// 提取红色（交通灯、标志牌）
Mat red_mask;
inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), red_mask);
//这一步是告诉程序什么是红色的

// 只保留红色区域
Mat red_only;
traffic_image.copyTo(red_only, red_mask);
```

<h4 id="shECZ">inRange各部分的样子</h4>
```cpp
inRange(输入图像, 颜色下限, 颜色上限, 输出掩码);
```

<h3 id="FyvaL">第二行hsv</h3>
为什么要把BRG转成hsv，因为hsv更利于计算机理解

注意，计算机使用hsv的时候是黑白色，也就是说如果你最后想要彩色图像的话就要最后把hsv转成BRG

```cpp
cvtColor(frame, hsv, COLOR_BGR2HSV);  
// 只要一个H范围：
Scalar(0,100,100) 到 Scalar(10,255,255)  // 所有红色都在这里！
//相比于BRG，hsv找颜色更方便
```





```cpp
// hsv 是一个Mat类型的变量，用来存储HSV格式的图像
Mat hsv;  // 这就像：Mat frame; 一样，都是图像容器
//其实就是自定义的变量，只不过这样写大家都认识，可读性比较高

// hsv 需要先被赋值（存储HSV图像数据），然后才能用在inRange中
```

<h4 id="Ef0bQ"><font style="color:rgb(15, 17, 21);">1.H（色相）- 是什么颜色 </font><font style="color:rgb(15, 17, 21);"></font></h4>
<font style="color:rgb(15, 17, 21);">就像选基础颜色：</font>

+ <font style="color:rgb(15, 17, 21);">0° = 红色</font>
+ <font style="color:rgb(15, 17, 21);">60° = 黄色</font>
+ <font style="color:rgb(15, 17, 21);">120° = 绿色</font>
+ <font style="color:rgb(15, 17, 21);">180° = 蓝色</font>

**<font style="color:rgb(15, 17, 21);">记住</font>**<font style="color:rgb(15, 17, 21);">：在OpenCV中，这个范围是 </font>**<font style="color:rgb(15, 17, 21);">0-179</font>**

<h4 id="QnJUX"><font style="color:rgb(15, 17, 21);">2.S（饱和度）- 颜色有多浓 </font><font style="color:rgb(15, 17, 21);"></font></h4>
<font style="color:rgb(15, 17, 21);">就像加多少白色：</font>

+ <font style="color:rgb(15, 17, 21);">0 = 全是白色（没颜色）</font>
+ <font style="color:rgb(15, 17, 21);">255 = 纯颜色（最鲜艳）</font>

**<font style="color:rgb(15, 17, 21);">几个常用的</font>**<font style="color:rgb(15, 17, 21);">：</font>

+ <font style="color:rgb(15, 17, 21);">S=255 → 大红</font>
+ <font style="color:rgb(15, 17, 21);">S=100 → 粉红（加了白色）</font>
+ <font style="color:rgb(15, 17, 21);">S=0 → 白色（完全没颜色）</font>

<h4 id="FEArW"><font style="color:rgb(15, 17, 21);">3.V（明度）- 颜色有多亮 </font><font style="color:rgb(15, 17, 21);"></font></h4>
<font style="color:rgb(15, 17, 21);">就像加多少黑色：</font>

+ <font style="color:rgb(15, 17, 21);">0 = 全黑</font>
+ <font style="color:rgb(15, 17, 21);">255 = 最亮</font>

<h3 id="v3uRR"><font style="color:rgb(15, 17, 21);">第七行</font></h3>
```cpp
inRange(hsv, Scalar(0, 120, 70), Scalar(10, 255, 255), red_mask);
//在HSV图像中，找出所有颜色在 (0,120,70) 到 (10,255,255) 范围内的像素，
//把这些位置标记为白色，其他的标记为黑色，结果存到 red_mask 中
inRange(
    hsv,                    // 输入：HSV格式的图像
    Scalar(0, 120, 70),     // 下限：H=0, S=120, V=70 (浅红色)
    Scalar(10, 255, 255),   // 上限：H=10, S=255, V=255 (亮红色)  
    red_mask                // 输出：结果掩码（黑白图像）
);
```

![](https://cdn.nlark.com/yuque/0/2025/png/61614341/1761314898466-db9fa73c-7947-4094-af3a-cc1f238fd177.png)能识别到红色了





```cpp
Mat industrial_image = imread("machine_parts.jpg");
Mat gray, binary;
cvtColor(industrial_image, gray, COLOR_BGR2GRAY);
threshold(gray, binary, 128, 255, THRESH_BINARY);

// 找出所有零件的轮廓
vector<vector<Point>> contours;
findContours(binary, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);

// 分析每个零件的形状
Mat analyzed = industrial_image.clone();
for (auto contour : contours) {
    double area = contourArea(contour);
    if (area > 1000) {  // 只分析大零件
        drawContours(analyzed, vector<vector<Point>>{contour}, -1, Scalar(0,255,0), 2);
    }
}
```

<h3 id="J4a2d">cap>>frame</h3>
```cpp
cap >> frame;  // 相当于：用手机拍一张照片，存到"相册frame"里,
//就是读取每一帧然后放到frame这个变量里进行后续操作
```



```cpp
vector<vector<Point>> contours;
findContours(red_mask, contours, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
```

<h2 id="cwfLj">8.函数</h2>
<h3 id="QEZzH">1.vconcat(图像合并，但是上下、左右叠加，不是多层合成)</h3>
**<font style="color:rgb(15, 17, 21);">Qf：叠加（Blend/Overlay）：</font>**

<font style="color:rgb(15, 17, 21);">图像之间</font>**<font style="color:rgb(15, 17, 21);">有重叠</font>**<font style="color:rgb(15, 17, 21);">会产生混合效果</font>

<h3 id="pui4s">2.findContours(为了与函数保持对应，容器可以设置为颜色_contours)</h3>
```cpp
findContours(输入图像, 输出轮廓, 检索模式, 近似方法);
```

<h3 id="UdP5r">3.putText(文字在图层上输入用的)</h3>


```cpp
putText(图像, 文字, 位置, 字体, 大小, 颜色, 粗细);
```

<h4 id="HIqzl"><font style="color:rgb(15, 17, 21);">参数解释与使用：</font></h4>
```cpp
putText(frame, "RED", Point(box.x, box.y-10), 
        FONT_HERSHEY_SIMPLEX, 0.8, Scalar(0, 0, 255), 2);
```

<h3 id="p0bNy"><font style="color:rgb(15, 17, 21);">参数说明：</font></h3>
```cpp
1. frame：目标图像（要在哪张图片上写字）
2. “RED”：要显示的文字内容
3. Point(box.x, box.y-10)：文字位置（x坐标, y坐标）
  ○ box.x：矩形框左上角的x坐标
  ○ box.y-10：矩形框左上角往上10像素（让文字在框上方）
4. FONT_HERSHEY_SIMPLEX：字体样式
5. 0.8：字体大小
6. Scalar(0, 0, 255)：文字颜色（B=0, G=0, R=255 → 红色）
7. 2：文字线条粗细
```

<h4 id="CutzV"><font style="color:rgb(15, 17, 21);">其他常用字体：（后面用到再说）</font></h4>
```cpp
FONT_HERSHEY_SIMPLEX     // 正常字体
FONT_HERSHEY_PLAIN       // 小字体
FONT_HERSHEY_DUPLEX      // 复杂字体  
FONT_HERSHEY_COMPLEX     // 更复杂字体
FONT_HERSHEY_TRIPLEX     // 最复杂字体
```

<h3 id="YcZcw">4.rectangle</h3>
```cpp
rectangle(目标图像, 矩形位置, 颜色, 线宽);
```

5.auto关键字

自动类型推断，这样就不用写出来具体是哪个类型了

