#!/bin/bash
# Copyright (c) 2023 Huawei Device Co., Ltd.
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#kernel deps dir, must be a git repo
DEPS=(
    "kernel/linux/build"
    "kernel/linux/linux-5.10"
    "kernel/linux/patches"
    "kernel/linux/config"
    "third_party/bounds_checking_function"
    "device/soc/hisilicon/common/platform/wifi"
    "third_party/FreeBSD/sys/dev/evdev"
    "drivers/hdf_core"
)

function is_kernel_change
{
    ROOT_PATH=$1
    BUILD_INFO_PATH=$ROOT_PATH/out/kernel/checkpoint

    if [ ! -d "$BUILD_INFO_PATH" ]; then
        mkdir -p $BUILD_INFO_PATH
    fi

    touch $BUILD_INFO_PATH/last_build.info
    rm -f $BUILD_INFO_PATH/current_build.info

    for dep in ${DEPS[@]}
    do
        echo $ROOT_PATH/$dep: >> $BUILD_INFO_PATH/current_build.info
        echo ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" >> $BUILD_INFO_PATH/current_build.info
        cd $ROOT_PATH/$dep
        git show --stat >> $BUILD_INFO_PATH/current_build.info
        cd -
        echo "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<" >> $BUILD_INFO_PATH/current_build.info
    done

    diff $BUILD_INFO_PATH/last_build.info $BUILD_INFO_PATH/current_build.info
}
