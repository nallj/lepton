# Lepton
![](https://img.shields.io/github/tag/pandao/editor.md.svg)
v0.8.0

** Table of Contents **
* Features
* Style
* To-do List

### Features

- Translates a randomly generated task graph from Task Graph For Free (TGFF) into application traces to be used by Drachma.

### Style
To the best of the author's ability, this project conforms to the "C++ Core Guidelines" found here <https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md>.  Any exceptions or additional rules may be located within the .styleguide file.

### Keywords
* IP (Intellectual Property) - Represents a unique hardware specification that may occupy a module within a region.
* module - A portion within a region that is able to configured with one or more IPs.
* region - A section of the theoretical FPGA that houses one or more modules.  May be static or reconfigurable.
* RR (Reconfigurable Region) - A region containing modules that may be reconfigured during runtime.
* SR (Static Region) - A region that is configured on start and cannot be reconfigured at any point in runtime.

### To-do List     
* Consider splitting mapper class into mapper/tracer classes or tracer/tracerHelper classes.
* Pursuant to the previous, consider name changes for mapper and graphMapper classes.
* Replace fileReader class with proper file parsing library.
* Consider using JSON or something similar as the format for configuration files (research alternatives).
* Change the .t2d file along with corresponding data structures and logic.
 + Option 1: Latencies no longer on IP (simply list out IPs with no arguments)
        srX module Y: ipA base_latency upper_bound_jitter lower_bound_jitter
        rrX module Y: { ipA base_latency upper lower, ... }
 + Option 2: Change IP verbiage to "ipx base latency" and "ipx upper/lower bound jitter"
     
        srX module Y: ipA [base_latency_change [new_upper_bound_jitter [new_lower_bound_jitter]]]
        rrX module Y: { ipA [base_latency_change [new_upper [new_lower]]], ... }

  This would be a more accurate representation of possible real-life applications.
  
* Add ability to provide random seed within .lep file.
* Implement least cost application execution.
