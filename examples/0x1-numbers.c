#include "uefi.h"

#define BASE_16	    16
#define BASE_10 	10
#define BASE_2		2
#define NEWLINE 	L"\r\n"

EFI_STATUS Reverse(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, CHAR16* buffer, INTN index){

	INTN i = 0;
	CHAR16 reverse[128];

	while(index >= 0)
		reverse[i++] = buffer[index--];

	reverse[i] = 0;
	
	return Con->OutputString(Con, reverse);
}

EFI_STATUS IntToUnicode(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, INTN Value, INTN Base){

	CHAR16 buffer[128];
	BOOLEAN negative = FALSE;
	INTN i = 0;

	if((Value < 0) && Base == BASE_10){
		negative = TRUE;
		Value *= -1;
	}

	do {
		const CHAR16 digit = (CHAR16)(Value % Base);
		buffer[i++] = digit < 10 ? '0' + digit : 'a' + digit - 10;
		Value /= Base;
	} while (Value && i < 126);

	if(negative)
		buffer[i++] = '-';

	switch(Base){
		case BASE_2:
			buffer[i++] = 'b';
			buffer[i++] = '0';
			break;
		case BASE_16:
			buffer[i++] = 'x';
			buffer[i++] = '0';
			break;
	}

	return Reverse(Con, buffer, i-1);
}

EFI_STATUS OutputInt(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, INTN Value, INTN Base){

	return IntToUnicode(Con, Value, Base);
}

EFI_STATUS OutputNewline(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con){
	return Con->OutputString(Con, NEWLINE);
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdOut = SystemTable->ConOut;

	OutputInt(StdOut, -100, BASE_10);
	OutputNewline(StdOut);
	OutputInt(StdOut, 100, BASE_10);
	OutputNewline(StdOut);
	OutputInt(StdOut, 12345, BASE_10);
	OutputNewline(StdOut);
	OutputInt(StdOut, 5, BASE_2);
	OutputNewline(StdOut);
	OutputInt(StdOut, 0x1234, BASE_16);
	OutputNewline(StdOut);
	OutputInt(StdOut, 0xabcd, BASE_16);
	OutputNewline(StdOut);
	OutputInt(StdOut, 0xdeadbeef, BASE_16);
	OutputNewline(StdOut);

	return EFI_SUCCESS;
}

