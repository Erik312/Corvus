# Corvus
Corvus is a minimal dependency text based web browser built mostly from scratch using modern c++.

## Installation
**Corvus currently only supports linux**

Download the source files

Install any necessary system dependencies. Reference the dockerfile for the dependencies needed.

**You will need GCC-15 or newer**

**Corvus uses ImGui as a static library for the gui system.** You will need to grab the source files, compile and create an archive.

## Building
Corvus uses make as a build system.

Create a libs and includes folder in the project directory.

Place ImGui ar lib in the libs folder and neccesary headers in the includes folder.

Use the make command.

```

make

```

## Usage
Corvus currently only supports http/1.0 and https/1.0

Run the exectubale

```

./corvus http://example.org/

```
