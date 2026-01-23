# EclairVM

EclairVM is a **stack-based** virtual machine for [Eclairscript](https://github.com/ekler25/eclairscript).

> [!IMPORTANT]  
> This project is currently in a very early development stage.  
> Not all VM features are implemented yet, and APIs may change frequently.

# Current Features
- Bytecode decoding
- Executing basic operand stack operations like: ipush, iadd, isub, cpush, spush etc.
- Outputing characters, strings and numbers
- Jumping to other addresses
- Calling and returning (call stack)

# todo
- More native methods i.e. stdin for reading characters from the user.
- idk

# Usage
> [!NOTE]  
> This is not fully implemented yet! As mentioned above, this project is still in a very early development stage.

`evm file.ebyte`

The `.ebyte` file is currently just a plain text file containing bytecode.

Later on, the `.eclair` file extension will be introduced.  
A `.eclair` file will be a compressed archive containing all the bytecode required to run the program.  
Dynamic linking will also be added later 🌹.

# Example

> [!IMPORTANT]  
> This example doesn't work anymore, I've changed a lot of stuff and I'm too lazy to come up with a new one.

| Hex        | Instruction | Description |
|------------|------------|------------|
| 0B 02 01 E7 | IPUSH 2 01E7 | push int32 value 0x000001E7 onto the operand stack |
| 0B 02 01 E7 | IPUSH 2 01E7 | push int32 value 0x000001E7 onto the operand stack |
| 06          | IADD         | pop the last 2 values from operand stack and push their sum |
| 02 01       | INVH 1       | invoke native host method with index `1` (stdout) |

# Eclairscript

Eclairscript has its own [repository](https://github.com/ekler25/eclairscript).
