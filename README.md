# Robot de servicio en el hogar

<!-- program a home service robot that will autonomously map an environtment and navigate to pickup and deliver objects -->
Se programa un robot de servicio en el hogar que mapea de forma autónoma un entorno y navega para recoger y entregar objetos.

Para este objetivo se utiliza la distribución Kinect de ROS en Ubuntu Linux 1604.



## Instalar 

```
git clone https://github.com/ros-perception/slam_gmapping
git clone https://github.com/turtlebot/turtlebot
git clone https://github.com/turtlebot/turtlebot_interactions
git clone https://github.com/turtlebot/turtlebot_simulator
cd ~/catkin_ws/
source devel/setup.bash
rosdep -i install gmapping
rosdep -i install turtlebot_teleop
rosdep -i install turtlebot_rviz_launchers
rosdep -i install turtlebot_gazebo
catkin_make // catkin build
source devel/setup.bash
```

<!-- ```
sudo apt-get install ros-kinetic-turtlebot ros-kinetic-turtlebot-apps ros-kinetic-turtlebot-interactions ros-kinetic-turtlebot-simulator ros-kinetic-kobuki-ftdi ros-kinetic-ar-track-alvar-msgs
```

The vm had an error, but this shouldn't be present in a fresh install

```
git clone git://github.com/ros/rospkg.git
python setup.py install --user
``` 
or (this works for me!)

```
apt-get install python-rospkg
``` -->

###  Prueba de paquetes instalados
<!-- Test the installed packages -->

```
roslaunch turtlebot_gazebo turtlebot_world.launch
roslaunch turtlebot_gazebo gmapping_demo.launch
roslaunch turtlebot_teleop keyboard_teleop.launch
roslaunch turtlebot_rviz_launchers view_navigation.launch
```

## Ejecutar programas

Dado que el robot realiza tareas complejas, se detalla a continuación los diferentes algorimos que componen  la funcionalidad del robot.

Para cada funcionalidad se debe ejecutar el programa correspondiente, denominado **script**

<!-- ### Create a map. 

The script launches the **slam_gmapping** package, this package can create a 2-D occupancy grid map from laser and pose data collected by the mobile robot. To drive the robot in the world is used the teleoperation package.
-->

### Crear un mapa 

El `script test_slam.sh` lanza el paquete **slam_gmapping**, este paquete puede crear un mapa de cuadrícula de ocupación 2-D a partir del láser y los datos de pose recopilados por el robot móvil. Para conducir el robot en el mundo se utiliza el paquete de teleoperación disponible en ROS.

```
sh scripts/test_slam.sh
```

<!-- Create a map driving the robot throught the world via the keyboard. before close de gmapping and rviz terminals, save the map, -->
Este script crea un mapa mediate la navegación del robot por el entorno através del teclado. Antes de cerrar las terminales de gmapping y Rviz, debe guardar el mapa con el siguiente comando,

```
rosrun map_server map_saver -f ~/gmapping_01
```

<!-- ###  Navigation Test 


The test uses the ROS [Navigation Stack](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals), which is based on the Dijkstra's, a variant of the Uniform Cost Search algorithm, to plan the robot trajectory from start to goal position. The ROS navigation stack permits the robot to avoid any obstacle on its path by re-planning a new trajectory once the robot encounters them. -->

### Prueba de navegación

La prueba utiliza la [pila de navegación de ROS](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals), que se basa en el algoritmo Dijkstra, una variante del algoritmo de búsqueda de costo uniforme para planificar la trayectoria del robot desde el inicio hasta la posición objetivo. La pila de navegación ROS permite al robot evitar cualquier obstáculo en su camino al replanear una nueva trayectoria cuando el robot encuentra algún obstáculo.

```
sh scripts/test_navigation.sh
```

ó utilice,

```
rosrun home_service_robot test_navigation.sh
```

<!-- ### Navigation Goal

Send two goals to the [Navigation Stack](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals). The [Amcl](http://wiki.ros.org/amcl) package is a probabilistic localization system for a robot moving in 2D. It implements the Adaptive Monte Carlo Localization approach, which uses a particle filter to track the pose of a robot against a known map. -->

### Navegación a  meta

El siguiente script envía dos objetivos a la [pila de navegación](http://wiki.ros.org/navigation/Tutorials/SendingSimpleGoals). El paquete [AMCL](http://wiki.ros.org/amcl), por otro lado, es un sistema de localización probabilística para un robot que se mueve en 2D. Implementa el enfoque de  Localización de Monte Carlo Adaptativo, que utiliza un filtro de partículas para rastrear la pose de un robot contra un mapa conocido.


```
rosrun home_service_robot pick_objects.sh
```

<!-- ### Modeling Virtual Objects - Markers

Modeling a virtual object with markers in rviz. In order to visualiza the marker you have to manually add it to Rviz. -->

### Modelado de Objetos Virtuales - Marcadores

Modelado de un objeto virtual con marcadores en Rviz. Para visualizar el marcador, debe agregarlo manualmente a [Rviz](http://wiki.ros.org/rviz/DisplayTypes/Marker).


```
rosrun home_service_robot add_markers.sh
```

El marcador permite mostrar las ubicaciones del lugar donde el robot recoje el objeto y luego el lugar donde lo deja, en un entorno virtual.

<!-- ### Home Service Robot

Finally, the last task is to combine all the above functionality, -->

### Robot de servicio en el hogar

Finalmente, la última tarea es combinar todas las funciones anteriores

```
rosrun home_service_robot home_service.sh
```

A continuación se muestra una animación de la ejecución de la tarea en el entorno virtual (vista superior). Se presenta el robot en el entorno de ejecución, donde se observa el mapa construido a traés del algoritmo **slam_gmapping**. El robot navega hacia el punto donde recoge un objeto virtual (cubo rojo), luego, una vez recoge el objeto, lo transporta hacia una segunda posición donde lo deja, esto se representa cuando aparece el cubo rojo.

![](https://github.com/jcorredorc/home_service_robot/blob/2f786e521e4a4d1f9f971a974f29b265bac3a89c/map/homeService.gif)


