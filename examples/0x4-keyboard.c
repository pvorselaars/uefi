#include <uefi.h>

#define BASE_16	16
#define BASE_10 10
#define BASE_2	2
#define NEWLINE L"\r\n"

EFI_STATUS Output(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, CHAR16* String){
	return Con->OutputString(Con, String);
}

EFI_STATUS Reverse(EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* Con, CHAR16* buffer, INTN index){

	INTN i = 0;
	CHAR16 reverse[128];

	while(index >= 0)
		reverse[i++] = buffer[index--];

	reverse[i] = 0;
	
	return Output(Con, reverse);
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
	return Output(Con, NEWLINE);
}

UINTN StringLength(CHAR16* string){
	UINTN length = 0;

	while(*string++){
		length++;
	}

	return length;
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	EFI_SIMPLE_TEXT_INPUT_PROTOCOL*  StdIn = SystemTable->ConIn;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdOut = SystemTable->ConOut;
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdErr = SystemTable->StdErr;

	EFI_STATUS Status;

	Status = StdIn->Reset(StdIn, FALSE);

	if(Status == EFI_DEVICE_ERROR){
		Output(StdErr, L"Unable to reset input device\r\n");
		return Status;
	}

	EFI_INPUT_KEY Key;
	CHAR16 buffer[2];
	buffer[1] = 0;

	do {
		Status = StdIn->ReadKeyStroke(StdIn, &Key);
		if (Status == EFI_SUCCESS){
			OutputInt(StdOut, Key.ScanCode, BASE_16);
			Output(StdOut, L": ");
			buffer[0] = Key.UnicodeChar;
			Output(StdOut, buffer);
			OutputNewline(StdOut);
		}

	} while (Key.ScanCode != EFI_ESCAPE);
	
	return EFI_SUCCESS;
}

