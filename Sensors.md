

# Introduction #

This page lists all the sensors implemented in RWT, among example snips for the configuration files required by the program `rwt-dataset-simulator`.


# Sensors #

## 1. Monocular camera ##

One single camera sensor, using a pinhole projection model with optional noise and distortion.

```
[sensor]
// Type of sensor to simulate: 
type = camera

minRange                     = 0    // meters
maxRange                     = 7.0  // meters
camera_pixel_noise_std       = 0    // One sigma of Gaussian noise (pixels)
check_min_features_per_frame = 0    // Raises an error if there are less than these feats in one frame.

//Default value for cameras is (yaw,pitch,roll)=(-90deg,0,-90deg), 
// so +Z of the camera points to +X of the robot.
sensor_pose_on_robot = [0 0 0 -90 0 -90]   // (x,y,z,yaw,pitch,roll), angles in degrees


// Camera parameters: (in format expected by mrpt::utils::TCamera, see doxygen docs)
// Camera parameters: 
resolution = [800 600]
cx         = 400
cy         = 300
fx         = 100
fy         = 100
dist       = [0 0 0 0 0] // [K1 K2 T1 T2 K3]
```

## 2. Stereo camera ##

Two cameras, using a pinhole projection model with optional noise and distortion.

```
[sensor]
// Type of sensor to simulate: 
type = stereo_camera

minRange                     = 0    // meters
maxRange                     = 7.0  // meters
camera_pixel_noise_std       = 0    // One sigma of Gaussian noise (pixels)
check_min_features_per_frame = 0    // Raises an error if there are less than these feats in one frame.

//Default value for cameras is (yaw,pitch,roll)=(-90deg,0,-90deg), 
// so +Z of the camera points to +X of the robot.
sensor_pose_on_robot = [0 0 0 -90 0 -90]   // (x,y,z,yaw,pitch,roll), angles in degrees

// Stereo Camera parameters: (in format expected by mrpt::utils::TStereoCamera, see doxygen docs)
[sensor_LEFT]
resolution = [1024 768]
cx         = 512
cy         = 384
fx         = 200
fy         = 150
dist       = [0 0 0 0 0] // K1 K2 T1 T2 K3

[sensor_RIGHT]
resolution = [1024 768]
cx         = 512
cy         = 384
fx         = 200
fy         = 150
dist       = [0 0 0 0 0] // K1 K2 T1 T2 K3

[sensor_LEFT2RIGHT_POSE]
pose_quaternion = [0.20 0 0  1 0 0 0]   // x y z qr qx qy qz
```


## 3. RGB+D camera ##

One camera sensor which also provides the distance to all detected landmarks, using a pinhole projection model with optional noise and distortion.

```
[sensor]
// Type of sensor to simulate: 
type = camera_range

minRange                     = 0    // meters
maxRange                     = 7.0  // meters
camera_pixel_noise_std       = 0    // One sigma of Gaussian noise (pixels)
check_min_features_per_frame = 0    // Raises an error if there are less than these feats in one frame.

//Default value for cameras is (yaw,pitch,roll)=(-90deg,0,-90deg), 
// so +Z of the camera points to +X of the robot.
sensor_pose_on_robot = [0 0 0 -90 0 -90]   // (x,y,z,yaw,pitch,roll), angles in degrees

// Camera parameters: (in format expected by mrpt::utils::TCamera, see doxygen docs)
// Camera parameters: 
resolution = [800 600]
cx         = 400
cy         = 300
fx         = 100
fy         = 100
dist       = [0 0 0 0 0] // [K1 K2 T1 T2 K3]
```


## 4. "Cartesian" sensor ##

A generic sensor which provides the XYZ coordinates of detected landmarks, in relative coordinates to the sensor.

```
[sensor]
// Type of sensor to simulate: 
type = cartesian_sensor

minRange                     = 0    // meters
maxRange                     = 7.0  // meters
fov_h                        = 180  // Horizontal Field of View (deg)
fov_v                        = 140  // Vertical Field of View (deg)
xyz_noise_std                = 0    // One sigma of Gaussian noise (meters)
check_min_features_per_frame = 0    // Raises an error if there are less than these feats in one frame.

sensor_pose_on_robot = [0 0 0 0 0 0]   // (x,y,z,yaw,pitch,roll), angles in degrees
```

## 5. Range-bearing sensor ##

A generic sensor which provides the distance, yaw and pitch angles to  detected landmarks.

```
[sensor]
// Type of sensor to simulate: 
type = range_bearing

minRange                     = 0    // meters
maxRange                     = 7.0  // meters
fov_h                        = 180  // Horizontal Field of View (deg)
fov_v                        = 140  // Vertical Field of View (deg)
range_noise_std              = 0    // One sigma of Gaussian noise (meters)
yaw_noise_std                = 0    // One sigma of Gaussian noise (deg)
pitch_noise_std              = 0    // One sigma of Gaussian noise (deg)
check_min_features_per_frame = 0    // Raises an error if there are less than these feats in one frame.

sensor_pose_on_robot = [0 0 0 0 0 0]   // (x,y,z,yaw,pitch,roll), angles in degrees
```

## 6. Relative poses (i.e. Graph-SLAM) ##

A "sensor" that measures the relative poses of nearby keyframes.

```
[sensor]
// Type of sensor to simulate: 
type = relative_poses

minRange                     = 0    // meters
maxRange                     = 7.0  // meters

```