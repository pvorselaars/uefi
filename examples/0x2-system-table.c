
#include <uefi.h>

#define BASE_16	16
#define BASE_10 10
#define BASE_2	2
#define NEWLINE L"\r\n"

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


EFI_STATUS Output(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, CHAR16 *String){
	return Con->OutputString(Con, String);
}


EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdOut = SystemTable->ConOut;
	
	UINT64 Signature = SystemTable->Hdr.Signature;
	UINTN  Color;
	UINTN  DefaultColor = EFI_TEXT_ATTR(EFI_LIGHTGRAY, EFI_BLACK);

	Output(StdOut, L"Signature:\t\t");

	Color = (Signature == EFI_SYSTEM_TABLE_SIGNATURE) ? EFI_TEXT_ATTR(EFI_GREEN, EFI_BLACK) : EFI_TEXT_ATTR(EFI_RED, EFI_BLACK);
	StdOut->SetAttribute(StdOut, Color);

	OutputInt(StdOut, SystemTable->Hdr.Signature, BASE_16);
	Output(StdOut, NEWLINE);

	StdOut->SetAttribute(StdOut, DefaultColor);

	UINT32 SystemTableRevision = SystemTable->Hdr.Revision;

	Output(StdOut, L"Revision:\t\t");
	Color = (SystemTableRevision == EFI_SYSTEM_TABLE_REVISION) ? EFI_TEXT_ATTR(EFI_GREEN, EFI_BLACK) : EFI_TEXT_ATTR(EFI_RED, EFI_BLACK);
	StdOut->SetAttribute(StdOut, Color);

	OutputInt(StdOut, SystemTable->Hdr.Revision >> 16, BASE_10);
	Output(StdOut, L".");
	OutputInt(StdOut, SystemTable->Hdr.Revision & 0xff, BASE_10);
	Output(StdOut, NEWLINE);

	StdOut->SetAttribute(StdOut, DefaultColor);

	UINT32 HeaderSize = SystemTable->Hdr.HeaderSize;

	Output(StdOut, L"HeaderSize:\t\t");
	Color = (HeaderSize == sizeof(EFI_SYSTEM_TABLE)) ? EFI_TEXT_ATTR(EFI_GREEN, EFI_BLACK) : EFI_TEXT_ATTR(EFI_RED, EFI_BLACK);
	StdOut->SetAttribute(StdOut, Color);

	OutputInt(StdOut, SystemTable->Hdr.HeaderSize, BASE_10);
	Output(StdOut, NEWLINE);

	StdOut->SetAttribute(StdOut, DefaultColor);

	Output(StdOut, L"CRC:\t\t\t");
	OutputInt(StdOut, SystemTable->Hdr.CRC32, BASE_16);
	Output(StdOut, NEWLINE);
	Output(StdOut, NEWLINE);

	Output(StdOut, L"FirmwareVendor:\t\t");
	Output(StdOut, SystemTable->FirmwareVendor);
	Output(StdOut, NEWLINE);

	Output(StdOut, L"FirmwareRevision:\t");
	OutputInt(StdOut, SystemTable->FirmwareRevision >> 16, BASE_10);
	Output(StdOut, L".");
	OutputInt(StdOut, SystemTable->FirmwareRevision & 0xff, BASE_10);
	Output(StdOut, NEWLINE);

	return EFI_SUCCESS;
}
