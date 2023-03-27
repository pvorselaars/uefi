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

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE* SystemTable){

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* StdOut = SystemTable->ConOut;

	UINTN Columns;
	UINTN Rows;
	EFI_STATUS Status;
	UINTN i;

	StdOut->SetMode(StdOut, StdOut->Mode->MaxMode - 1);
	
	for(i = 0; i < StdOut->Mode->MaxMode; i++){
		Status = StdOut->QueryMode(StdOut, i, &Columns, &Rows);

		if(Status == EFI_SUCCESS){
			if(StdOut->Mode->Mode == i) {
				Output(StdOut, L"*");
			} else {
				Output(StdOut, L" ");
			}
			OutputInt(StdOut, i, BASE_10);
			Output(StdOut, L": ");
			OutputInt(StdOut, Columns, BASE_10);
			Output(StdOut, L"x");
			OutputInt(StdOut, Rows, BASE_10);
			OutputNewline(StdOut);
		}
	}


	return EFI_SUCCESS;
}

