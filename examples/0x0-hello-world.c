#include <uefi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\r\n");

	return EFI_SUCCESS;
}
