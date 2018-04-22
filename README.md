# SPEAR: C++/SPIR-V Shader Runtime

## Overview

SPEAR is a integrated domain specific language translating C++17 to SPIR-V at host runtime.

## Supported features

## Restrictions

## Contributing

The SPEAR project and the Tracy renderer is maintained by Fabian Wahlster and is hosted at https://github.com/razor8/SPEAR.

### Source code organization

* `SPIRVGen`: Core spear library
* `SPIRVGenTest`: Simple testbed project
* `SPIRVShaderFactory`: Dynamic shader library example project
* `spirvtools`: Target output folder for spirv-tool cmake
* `glm`: Math types
* `boost`: for boost.DLL

### Tests

### Optional dependency on Vulkan

## Build

* Build boost system & filesystem by running bootstrap & b2
* Use CMake to generate SPIR-V tools projects in VulkanSDK/spirv-tools and target folder Source/spirvtools as output

Currently only Visual Studio 2017 is supported, therefore SPIRV-V Tools must be generated with VS 2017 64bit as target.

## Library

### Usage

## License
```
Copyright (c) 2018 Fabian Wahlster.

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
```