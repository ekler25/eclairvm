# EclairVM

EclairVM is a **stack-based** virtual machine for [Eclairscript](https://github.com/ekler25/eclairscript).

> [!IMPORTANT]  
> This project is currently in a very early development stage.  
> Not all VM features are implemented yet, and APIs may change frequently.

# Current Features
- Bytecode decoding
- Executing basic operand stack operations like: ipush, iadd, isub, cpush, spush etc.
- Outputing characters, strings and numbers
- jumping to other addresses

# todo
- call stack
- more native methods i.e. stdin for reading characters from the user
- idk

# Usage
> [!NOTE]  
> This is not fully implemented yet! As mentioned above, this project is still in a very early development stage.

`evm file.ebyte`

The `.ebyte` file is currently just a plain text file containing bytecode.

Later on, the `.eclair` file extension will be introduced.  
A `.eclair` file will be a compressed archive containing all the bytecode required to run the program.  
Dynamic linking will also be added later 🌹.

# Eclairscript

Eclairscript has its own [repository](https://github.com/ekler25/eclairscript).
