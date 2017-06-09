# glkernel
C++ library for pre-computing noise, and random sample-kernels.

## Project Health (master)

| Service | System | Compiler | Targets | Status |
| ------- | ------ | -------- | ------- | ------ |
| Jenkins | Ubuntu 14.04 | GCC 4.8 | all, test | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-linux-gcc4.8)](http://jenkins.hpi3d.de/job/glkernel-linux-gcc4.8)|
| Jenkins | Ubuntu 14.04 | GCC 4.9 | all, test | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-linux-gcc4.9)](http://jenkins.hpi3d.de/job/glkernel-linux-gcc4.9)|
| Jenkins | Ubuntu 14.04 | GCC 5.3 | all, test | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-linux-gcc5.3)](http://jenkins.hpi3d.de/job/glkernel-linux-gcc5.3)|
| Jenkins | Ubuntu 14.04 | Clang 3.5 | all, test | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-linux-clang3.5)](http://jenkins.hpi3d.de/job/glkernel-linux-clang3.5) |
| Jenkins | Windows 8.1 | MSVC 2013 Update 5 | all, test, install | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-windows-msvc2013)](http://jenkins.hpi3d.de/job/glkernel-windows-msvc2013) |
| Jenkins | Windows 8.1 | MSVC 2015 Update 1 | all, test, install | [![Build Status](http://jenkins.hpi3d.de/buildStatus/icon?job=glkernel-windows-msvc2015)](http://jenkins.hpi3d.de/job/glkernel-windows-msvc2015) |

## Features

ToDo

##### Feature

ToDo

## Using glkernel

ToDo

##### Dependencies

ToDo

##### Linking binaries

ToDo

##### glkernel-cmd

Additionally to using glkernel as a library, there is a standalone command line tool to generate kernels from JSON descriptions.
The usage is as follows: ```glkernel-cmd --i {input filename} --o {output filename}```, where {input filename} is a JSON kernel description file and {output file} is a JSON file containing a kernel.

The description file must contain an entry "init-kernel" that describes the size and the number of components of the the kernel that will be generated.
It also has to contain an entry "commands", which is an array of commands that will be executed on the kernel.
For these, all glkernel commands can be used.
The naming convention for them is ```"{namespace}.{function name}"```, e.g. ```"noise.uniform"``` for ```noise::uniform```.
Arguments can be passed as a JSON object, e.g. ```{ "noise.uniform": { "range_min": -1.0, "range_max": 1.0 } }``` will call ```noise::uniform(kernel, -1.0, 1.0)```.

Here is an input JSON for generating 8 samples using golden point set sampling:
```json
{
    "init-kernel": {
        "components": 2,
        "width": 8,
        "height": 1,
        "depth": 1
    },

    "commands": [
        { "sample.golden_point_set": { } },
        { "scale.range": { "range_to_lower": -0.5, "range_to_upper": 0.5 } },
        { "shuffle.random": { } }
    ]
}
```

The generated output JSON will have the following form:
```json
{
    "kernel": [
        [
            [
                [
                    -0.41692,
                    -0.0735727
                ],
                [
                    0.201114,
                    0.0165974
                ],
                [
                    -0.0906823,
                    -0.219471
                ],
                ...
            ]
        ]
    ],
    "size": {
        "depth": 1,
        "height": 1,
        "width": 8
    }
}
```
