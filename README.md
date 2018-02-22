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

## Tools

### glkernel-cli

The glkernel-cli tool provides a convenient way to generate and manipulate kernels using the command line.  
The usage is as follows:

```
glkernel-cli [--force] [--beautify] [--output <outputFileName>] [--format <outputFileFormat>] <inputFileName>

Options:
 -b, --beautify  Beautify the output (only applies to json output format)
     --force     Override the output file, if it exists
 -f, --format    File format for the generated / converted kernel (e.g., json, png, h)
 -o, --output    File that the generated / converted kernel will be written to (defaults: <inputFileName>.json for generation, <inputFileName>.png for conversion)
```

- The default output format for kernel generation is JSON
- The default output format for kernel conversion is PNG
- If not output file name is given, the output file name will be deduced from the input file name (here, it would be `kernel.json`)
- If no output format is given, the output format will be deduced from the output file name (explicitly given or deduced)

#### Generating a kernel using JavaScript

Kernels can be generated from JavaScript by simply passing a `.js` file as input to the command line tool.
Examples:

```
$ glkernel-cli kernel.js

$ glkernel-cli kernel.js -o random_noise_kernel.json --force --beautify

$ glkernel-cli kernel.js -o sorted_kernel -f png
```

A JavaScript interface (`JSInterface.h`, `JSInterface.cpp`, `glkernel.js`) allows calling glkernel functionality from user scripts.
It is included in the tool's sources (C++ files), and in the `data/` directory (JavaScript file).
The interface is automatically generated from the existing glkernel API.

__If you extend or change the glkernel API, please [re-generate the JavaScript interface](#generating-the-javascript-interface)!__

##### Writing kernel generation instructions in JavaScript

While the glkernel library uses free functions, the JavaScript API provides manipulation of kernels via object methods on kernel objects.
The API method names are taken from the library.

The following script shows the usage of the JavaScript API by example (it can be found in `scripts/kernel.js`):

```javascript
// create new Kernel2 object (i.e., a 3D kernel of dimensions 10x5x2, holding vec2's as values
var kernel = new Kernel2(10, 5, 2);

// translates to glkernel::sequence::uniform(kernel, 0.0, 1.0)
kernel.sequence.uniform(0.0, 1.0);

// examples for other kernel methods
kernel.shuffle.random();
kernel.scale.range(-1.0, 1.0);

// glkernel::sort::distance for a Kernel2 requires a vec2 as parameter
// vec parameters can be passed as JavaScript arrays
kernel.sort.distance([0.0, 0.0]);
```

#### Converting an existing kernel

After generating a kernel in JSON format, that kernel can be read by the tool to be converted into another representation (e.g., PNG).
This is achieved by simply passing a `.json` file as input to the command line tool.
Examples:

```
$ glkernel-cli kernel.json

$ glkernel-cli kernel.json -o sorted_kernel -f png --force
```

If no output file or format is given, the default output format is PNG.

#### Generating the JavaScript interface

The JavaScript interface files can simply be re-generated using the CMake `generate` target, either from your IDE, or from the project's root folder using the following CMake command:

```
$ cmake --build ./build --target generate
```

This requires Python 2 or 3 to be installed on the system.
Alternatively, the Python script can be executed manually (also from the root folder):

__TODO__: update this if the destination of JS and C++ files are different
```
$ python scripts/generate.py -t scripts/templates -d source/tools/glkernel-cli
```

##### glkernel-cmd

Additionally to using glkernel as a library, there is a standalone command line tool to generate kernels from JSON descriptions.
The usage is as follows: ```glkernel-cmd --i {input filename} --o {output filename}```, where ```{input filename}``` is a JSON kernel description file and ```{output file}``` is a JSON file containing a kernel.

The description file must contain an entry "init-kernel" that describes the size and the number of components of the the kernel that will be generated.
It also has to contain an entry "commands", which is an array of commands that will be executed on the kernel.
For these, all glkernel commands can be used.

The naming convention for applying glkernel commands is ```"{namespace}.{function name}"```, e.g. ```"noise.uniform"``` for ```noise::uniform```.
Arguments can be passed as a JSON object, e.g. ```{ "noise.uniform": { "range_min": -1.0, "range_max": 1.0 } }``` will call ```noise::uniform(kernel, -1.0, 1.0)```.

Here is an input JSON for generating 4 samples using golden point set sampling, scaling them to [-0.5, 0.5] and shuffling them randomly:
```json
{
    "init-kernel": {
        "components": 2,
        "width": 4,
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

The generated output JSON will look like this:
```json
{
    "kernel": [
        [
            [
                [
                    -0.286392,
                    -0.437815
                ],
                [
                    -0.140494,
                    0.180219
                ],
                [
                    0.0955744,
                    -0.201747
                ],
                [
                    0.47754,
                    0.416287
                ]
            ]
        ]
    ],
    "size": {
        "depth": 1,
        "height": 1,
        "width": 4
    }
}

```
