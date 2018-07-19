<h1 align=center>PowerMonitor-CLI</h1>
<p align="center">
    <a href="https://github.com/lucka-me/PowerMonitor-CLI/commits/master"><img alt="Version" src="https://img.shields.io/badge/version-0.1-red.svg"/></a>
    <a href="https://lucka.moe"><img alt="Author" src="https://img.shields.io/badge/author-Lucka-5880C8.svg"/></a>
  <a href="./LICENSE"><img alt="License" src="https://img.shields.io/badge/license-MIT-A31F34.svg"/></a><br>
  <a href="https://www.visualstudio.com/zh-hans/vs/community/"><img alt="IDE" src="https://img.shields.io/badge/IDE-Visual_Studio_Community_2017-8662C2.svg"/></a>
  <a href="https://www.microsoft.com/zh-cn/windows/"><img alt="Platform" src="https://img.shields.io/badge/platform-Windows_CLI-000000.svg"/></a>
    <br/>
    Temperature monitor based on Intel® Power Gadget API.<br/>
    Under development.
</p>

## Description
A temperature monitor in CLI, based on [Intel® Power Gadget](https://software.intel.com/en-us/articles/intel-power-gadget-20) [API](https://software.intel.com/blogs/2014/01/07/using-the-intel-power-gadget-30-api-on-windows), and used to learn about loading DLL dynamically.

## Functions
- Display information of CPU and MSR.
- Fetch and display the frequency, power and temperature every 2 seconds.

## Requirement
### Enviroment and Packages
- [Intel® Power Gadget](https://software.intel.com/en-us/articles/intel-power-gadget-20)

## Reference
- [DLL 调用（2）：C++ 动态调用 DLL | CSDN](https://blog.csdn.net/ezhchai/article/details/78784815)
- [Using the Intel® Power Gadget 3.0 API on Windows | Intel® Software](https://software.intel.com/blogs/2014/01/07/using-the-intel-power-gadget-30-api-on-windows)

## License
The application is licensed under [MIT License](./LICENSE).
Dynamically load a function from a DLL
