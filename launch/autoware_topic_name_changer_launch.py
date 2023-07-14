import launch
import launch_ros.actions
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
  lidar_topic_name = LaunchConfiguration("lidar_topic_name", default ="")
  imu_topic_name = LaunchConfiguration("imu_topic_name", default = "")
  pub_lidar_topic_name = LaunchConfiguration("pub_lidar_topic_name", default ="")
  pub_imu_topic_name = LaunchConfiguration("pub_imu_topic_name", default ="")


  autoware_topic_name_changer = launch_ros.actions.Node(package='autoware_topic_name_changer', executable='autoware_topic_name_changer', output='screen',
    parameters=[{"lidar_topic_name":lidar_topic_name},{"imu_topic_name":imu_topic_name},{"pub_lidar_topic_name":pub_lidar_topic_name},{"pub_imu_topic_name":pub_imu_topic_name}])
  return launch.LaunchDescription([autoware_topic_name_changer])
