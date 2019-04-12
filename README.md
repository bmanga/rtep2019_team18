# Gait Analysis and Interactive Training [![Build Status](https://travis-ci.com/bmanga/rtep2019_team18.svg?branch=master)](https://travis-ci.com/bmanga/rtep2019_team18)

<p align="center">
	<img src="https://user-images.githubusercontent.com/46964367/56052054-6846a700-5d48-11e9-9294-2bcc49930567.jpeg"
	 height="250" >
</p>

## Overview and Impact
GAIT is about the development of a Raspberry Pi wearable system which analyses the user's walking characteristics and provides targeted training in two separate modes, namely Gait and Training mode.

In Gait mode, data is analysed and classified in real time by use of a deep convolutional neural network which automatically predicts the nature of the gait from the signals received from IMUs mounted on the lower limb and pressure sensors embedded in modified insoles. Training mode offers typical game-based rehabilitation exercises, including weight shifting and calf pushes, and provides both auditory and visual feedback to the user, with games being streamed to an exernal screen.

This device aims to promote neuroplasticity for motor rehabilitation of stroke patients and may therefore become an auxiliary tool in the recovery of motor functions of stroke survivors.

<p align="center">
	<img src="https://user-images.githubusercontent.com/13623481/51919339-1f36b600-23db-11e9-9939-d928cba637c1.png"
	 title="Gait"  height="500" >
</p>


## Team

See the [Wiki](https://github.com/bmanga/rtep2019_team18/wiki) for more information. 

### Prerequisites
* [conan](https://conan.io/) package manager - it can be installed by running ```pip install conan```
  * Make sure you have added the bincrafters remote repository. If not, run:<br/>
 ```conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan```
* [cmake](https://cmake.org/) build system version 3.8 or above

### Build Instructions
From within the cloned repository directory :
* ```mkdir build && cd build```
* ```conan install ..```
* ``` cmake ..```
* ```make```

Or use your favourite ```cmake``` configuration.

### Contributions Guidelines
All code is formatted through `clang-format` according to the `.clang-format` file. `clang-format-6.0` is the recommended version as that's the one used in CI.

The utility script `utils/format_diff_code.sh` (to be run from project root directory) is provided in order to automatically format the changes.

Alternatively, you can copy `utils/pre-commit` into the `.git/hooks` folder to automatically run `clang-format` on commits.
