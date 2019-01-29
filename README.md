## Gait Analysis and Interactive Training [![Build Status](https://travis-ci.com/bmanga/rtep2019_team18.svg?branch=master)](https://travis-ci.com/bmanga/rtep2019_team18)

This project aims to create a Raspberry Pi system which analyses the patient's walking pattern through a number of IMUs distributed along the legs and pressure sensors in special soles.

This data is then analysed to identify an incorrect walking gait due to hemiplegia caused by a stroke and is then able to provide guidance and exercises to aid rehabilitation in real time.


### Prerequisites
* [conan](https://conan.io/) package manager - it can be installed by running ```pip install conan```

### Build Instructions
From within the cloned repository directory :
* ```mkdir build && cd build```
* ```conan install ..```
* ``` cmake ..```
* ```make```

Or use your favourite ```cmake``` configuration
