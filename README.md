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

* Smart template error messages

##### Smart template error messages

Most methods of glkernel operate a kernel as well as additional parameters. This may lead to a template argument mismatch if a method is called with arguments that do not match the intended signature.
These cases are caught by glkernel and a helpful compile time error message is provided to the developers.

## Using glkernel

Before using glkernel, it is important to get clear about the following three properties of a kernel:
* Dimension
* Cell type
* Component type

###### Dimension
Defines in how many dimensions a kernel extends. Can be compared to the dimension of a tensor.
The dimension is defined implicitly by the kernel's size, which is determined for each dimension.
A kernel of size `{4, 1, 2}` has the dimension _three_.

###### Cell type
The number of cells is determined by the kernel's size. In the example above, the kernel would contain eight cells. These cells can be of different cell types. However, the cell type must be homogeneous for the entire kernel. Cells can be of a scalar (_one_ component per cell) or of a vectorial (_two_, _three_ or _four_ components per cell) type.

###### Component type
The component type specifies of which type the values (= components) within a kernel are. Again, the component type must be homogeneous. This is most likely a matter of precision and `float` or `double` would be appropriate component types.


### As a library

##### Dependencies

Using glkernel requires a C++11 compatible compiler.  
For linking against glkernel: `glm`  
For multithreading support (optional): `OpenMP` for multithreading support  
For building the glkernel tests: `cmake` Version 3.1 or newer  

##### Linking

Glkernel is a header-only library, so linking is as simple as including the headers providing the needed functionality.
For flexibel kernel instantiation, you need to:
```cpp
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glkernel/Kernel.h>
```
This allows the instantiation of kernels with scalar or vectorial cell types. Following this, a kernel can be used within methods of different namespaces each providing specific functionality. According to your purpose, you need to:
```cpp
#include <glkernel/noise.h>     // Kernel generation based on noise
#include <glkernel/sample.h>    // Kernel generation based on sampling
#include <glkernel/sequence.h>  // Kernel generation based on regular sequences
#include <glkernel/scale.h>     // Kernel transformation by range adjustments
#include <glkernel/shuffle.h>   // Kernel transformation by shuffling of elements
#include <glkernel/sort.h>      // Kernel transformation by sorting of elements
```


##### Usage
The following aliases are ___already defined by glkernel___ for comfortable usage:
```cpp
using kernel1  = tkernel<float>;        // Cell type: scalar, Component type: float
using kernel2  = tkernel<glm::vec2>;    // Cell type: vec2,   Component type: float
using kernel3  = tkernel<glm::vec3>;    // Cell type: vec3,   Component type: float
using kernel4  = tkernel<glm::vec4>;    // Cell type: vec4,   Component type: float

using dkernel1 = tkernel<double>;       // Cell type: scalar, Component type: double
using dkernel2 = tkernel<glm::dvec2>;   // Cell type: vec2,   Component type: double
using dkernel3 = tkernel<glm::dvec3>;   // Cell type: vec3,   Component type: double
using dkernel4 = tkernel<glm::dvec4>;   // Cell type: vec4,   Component type: double
```
As you can see from the aliases above, the __cell-__ and __component__ type are specified by the kernel class' template arguments. The __dimension__ must be specified during the instantiation.  
The following snippet shows a basic order in which the glkernel library can be used:

```cpp
auto fkernel2 = glkernel::kernel2{4, 1, 1};         // Instantiate 3D float kernel with two components per cell
glkernel::sample::golden_point_set(fkernel2);       // Generate 'golden point set'
glkernel::scale::range(fkernel2, -0.5f, 0.5f);)     // Scale kernel to [-0.5, 0.5] in each dimension
glkernel::shuffle::random(fkernel2);                // Shuffle elements randomly
```




### Via command line interface
###### glkernel-cmd

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
