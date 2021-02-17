<h1 align="center">RISC-V Interpreter</h1>
<p>
  <img alt="Version" src="https://img.shields.io/badge/version-2.0-blue.svg?cacheSeconds=2592000" />
</p>

This is a simulator for a single-cycle 32-bit RISC-V CPU.
- 

## Install

```sh
g++ *.cpp -o cpusim
```

## Usage

The  input  command  is ```./cpusim <inputFile> <-dVal>```, where “Val” would be either 0 (i.e., no print at all), 1 (print final register values), 2 (print final memory values), and 3 (for both).

Instructions are saved in “instMem” (in unsigned decimal format, where each line is one byte). In addition to three “InstMem” files in “debug” folder, there are three files: “br”, “lw/sw”, and “r-type”. These  files  show  the  actual  assembly  program  for  each  of  “instMem”  files.  Each file has three columns. These columns show the memory address (in hex), the instruction (in hex), and the actual assembly instruction. 

For example, ```14: 00f06693ori x13 x0 15``` shows that this instruction’s address is 14 (in hex), its binary value (NOTE: shown in hex) is 00f06693, and the assembly representation is ```ori x13 x0 15```(NOTE: imm values are all in decimal). 

## Run tests

```sh
./cpusim traces/test/instMem-test.txt -d3
```
