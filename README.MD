# UEFI

## UEFI declarations in a single header

Declarations as specified by [EUFI 2.10](https://uefi.org/specs/UEFI/2.10/) with no external dependencies. These declarations are contained in a single header allowing you to include `<uefi.h>` and build an EFI application for x86_64 hardware with UEFI compliant firmware.

NOTE: Currently, only the data types, System Table, Simple Text Output Control and the Simple Text Input Control are implemented. Plan is to implement the entire specification.

### Building & testing

Building applications using this header is currently only tested using [`clang`](https://clang.llvm.org) and [`lld`](https://lld.llvm.org). Both `clang` and `lld` require specific flags to compile and link an EFI binary.

```
# make

UEFI Interactive Shell v2.2
EDK II
UEFI v2.70 (EDK II, 0x00010000)
Mapping table
      FS0: Alias(s):HD0a1:;BLK1:
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)/
	  HD(1,GPT,732A5FC6-E3E3-4DB6-B5A5-2A0E2B34260A,0x800,0x177DF)
     BLK0: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)
     BLK2: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)

Press ESC in 5 seconds to skip startup.nsh or any other key to continue.
Shell> fs0:
FS0:\> ls
Directory of: FS0:\
03/23/2023  19:48               2,560  0x0-hello-world.efi
03/23/2023  19:48              10,549  NvVars
          2 File(s)      13,109 bytes
          0 Dir(s)
FS0:\> 0x0-hello-world.efi
Hello, World!
FS0:\>
```

### Acknowledgements

Inspired by

* https://github.com/yoppeh/efi
* https://github.com/AndreVallestero/minimal-efi
* https://gitlab.com/bztsrc/posix-uefi/
