## Gait Analysis and Interactive Training [![Build Status](https://travis-ci.com/bmanga/rtep2019_team18.svg?branch=master)](https://travis-ci.com/bmanga/rtep2019_team18)

This project aims to create a wearable Raspberry Pi system which analyses the patient's walking pattern through a number of IMUs distributed along the legs and pressure sensors in special soles.

This data is then analysed to identify an incorrect walking gait due to hemiplegia caused by a stroke and is then able to provide guidance and exercises to aid rehabilitation in real time.

<p align="center">
	<img src="https://user-images.githubusercontent.com/13623481/51919339-1f36b600-23db-11e9-9939-d928cba637c1.png"
	 title="Gait"  height="500" >
</p>

See the [Wiki](https://github.com/bmanga/rtep2019_team18/wiki) for more information. 

### Prerequisites
* [conan](https://conan.io/) package manager - it can be installed by running ```pip install conan```
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
