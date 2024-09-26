# Examples
File where some examples and execution suggestions are shown.


---
## _Auxiliar_

1. **Aruco markers printing**.
Executable that is usefull if you wanna print on your own your first Aruco markers using OpenCV.
_Examples of use:_
    - `./printMarkers`

1. **Ovis installation test**.
Executable that is usefull if you wanna test if the ovis installation is correct.
_Examples of use:_
    - `./testOvis`




---
## _Applications_

### A. **Main application**

Main executable where some applications of the fiducial markers are built and shown.

[//]: # ( How to execute: )
[//]: # ( ./mainApp CAMERA_ID CAMERA_PARAMS_FILE )

_Examples of use:_
- `./mainApp 2 ../data/streamCamLogiCalibration.yml`




### B. **Main application** + **Ovis**

Application where, having already the functionalities of the base application, we explore a bit the Ovis module, by the use of 3D objects.

[//]: # ( How to execute: )
[//]: # ( ./mainAppOvis CAMERA_ID CAMERA_PARAMS_FILE [ CUSTOM_OBJECT_FILE CUSTOM_OBJECT_FOLDER_ABSOLUTE_PATH ])

_Examples of use:_
- `./mainAppOvis 2 ../data/streamCamLogiCalibration.yml`
- `./mainAppOvis 2 ../data/streamCamLogiCalibration.yml --customObject=ava.mesh --customObjectFolder=/home/paul/Workspace/OtherWorkspaces/OpenCV_Ogre/2_Applications/ExampleApplication/data`