#include <uefi.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	EFI_STATUS status = SystemTable->ConOut->OutputString(SystemTable->ConOut, L"Hello, World!\r\n");

	return status;
}
