import launch
import launch_ros.actions
from launch.substitutions import LaunchConfiguration

def generate_launch_description():
  lidar_topic_name = LaunchConfiguration("lidar_topic_name", default ="/sensing/lidar/top/velodyne_packets")
  imu_topic_name = LaunchConfiguration("imu_topic_name", default = "/sensing/imu/tamagawa/imu_raw")
  gnss_topic_name = LaunchConfiguration("gnss_topic_name", default = "/sensing/gnss/ublox/nav_sat_fix")

  pub_lidar_topic_name = LaunchConfiguration("pub_lidar_topic_name", default ="/velodyne_packets")
  pub_imu_topic_name = LaunchConfiguration("pub_imu_topic_name", default ="/imu/6in1/data_raw")
  pub_gnss_topic_name = LaunchConfiguration("pub_gnss_topic_name", default ="/rtk/fix")

  autoware_topic_name_changer = launch_ros.actions.Node(package='autoware_topic_name_changer', executable='autoware_topic_name_changer', output='screen',
    parameters=[{"lidar_topic_name":lidar_topic_name},{"imu_topic_name":imu_topic_name},{"gnss_topic_name":gnss_topic_name},{"pub_lidar_topic_name":pub_lidar_topic_name},{"pub_imu_topic_name":pub_imu_topic_name},{"pub_gnss_topic_name":pub_gnss_topic_name}])
  return launch.LaunchDescription([autoware_topic_name_changer])
