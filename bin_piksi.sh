#!/bin/bash

source /opt/ros/noetic/setup.bash
source /home/ubuntu/Poseidon/src/workspace/devel/setup.bash

roslaunch /home/ubuntu/Poseidon/src/workspace/launch/piksi.launch time_now:=$(date +%Y.%m.%d_%H%M%S)


