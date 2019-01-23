# SCCP Library

This is an implementation of the C-based KPABE methods required for COLABRIQ's Decentralized Knowledge Graph
based on Zeutro's OpenABE (https://github.com/zeutro/openabe).

Please agree to LICENSE.md and read CONTRIBUTING.md before using this code. Note that like the Zeutro OpenABE
library, this code is licensed under the Affero GPL v3 by virtue of its linking. In order to use this
implementation with scos-kpabe you must publish under the GPL or obtain a priorietary license for Zeutro's
library from Zeutro LLC (https://www.zeutro.com/).

## Build

### Linux

The Linux library is required to build our docker images.
This is the best supported build.

To build the Linux version of the shared library, use docker-compose as follows:

`docker-compose -f ./build.yml up`

This will produce `libsccp.so` in `lib/`

### macOS

You can also build on your local macOS system.
You'll need to download and compile openabe somewhere to your system.

See https://github.com/zeutro/openabe/releases

Manually set the env variable ZROOT to wherever you expand this to.

Once built, you can simply run `make` in this directory to produce `lib/libsccp.dylib`

### Windows

Not currently supported.
Your best bet is to build the docker containers.
