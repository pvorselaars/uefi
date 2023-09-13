#ifndef UEFI_H
#define UEFI_H

// Unified Extensible Firmware Interface (UEFI)
// Release 2.10

// CALLING CONVENTION

#define EFIAPI
#define IN
#define OUT
#define OPTIONAL

// DATA TYPES

#define TRUE  		        1
#define FALSE 		        0

#define EFI_SUCCESS	        0
#define EFI_INVALID_PARAMETER	2
#define EFI_UNSUPPORTED	        3
#define EFI_NOT_READY		6
#define EFI_DEVICE_ERROR	7

typedef unsigned char		BOOLEAN;
typedef signed char		INT8;
typedef unsigned char		UINT8;
typedef signed short int	INT16;
typedef unsigned short int	UINT16;
typedef signed long int		INT32;
typedef unsigned long int	UINT32;
typedef signed long long int 	INT64;
typedef unsigned long long int	UINT64;
typedef unsigned char		CHAR8;
typedef unsigned short int	CHAR16;
typedef void			VOID;

typedef INT64			INTN;
typedef UINT64			UINTN;

typedef UINTN			EFI_STATUS;
typedef VOID*			EFI_HANDLE;
typedef VOID*			EFI_EVENT;

//
// PROTOCOLS
// 

// CONSOLE SUPPORT

// Simple Text Output Protocol

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID { 0x387477c2, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

// Colors

#define EFI_BLACK		0x00
#define EFI_BLUE		0x01
#define EFI_GREEN		0x02
#define EFI_CYAN		0x03
#define EFI_RED			0x04
#define EFI_MAGENTA		0x05
#define EFI_BROWN		0x06
#define EFI_LIGHTGRAY		0x07
#define EFI_BRIGHT		0x08
#define EFI_DARKGRAY		0x08
#define EFI_LIGHTBLUE		0x09
#define EFI_LIGHTGREEN		0x0A
#define EFI_LIGHTCYAN		0x0B
#define EFI_LIGHTRED		0x0C
#define EFI_LIGHTMAGENTA	0x0D
#define EFI_YELLOW		0x0E
#define EFI_WHITE		0x0F

#define EFI_TEXT_ATTR(Foreground, Background) (Foreground | (Background << 4))

// Shapes

#define BOXDRAW_HORIZONTAL		        0x2500
#define BOXDRAW_VERTICAL		        0x2502
#define BOXDRAW_DOWN_RIGHT		        0x250c
#define BOXDRAW_DOWN_LEFT		        0x2510
#define BOXDRAW_UP_RIGHT		        0x2514
#define BOXDRAW_UP_LEFT			        0x2518
#define BOXDRAW_VERTICAL_RIGHT		        0x251c
#define BOXDRAW_VERTICAL_LEFT		        0x2524
#define BOXDRAW_DOWN_HORIZONTAL		        0x252c
#define BOXDRAW_UP_HORIZONTAL		        0x2534
#define BOXDRAW_VERTICAL_HORIZONTAL	        0x253c

#define BOXDRAW_DOUBLE_HORIZONTAL	        0x2550
#define BOXDRAW_DOUBLE_VERTICAL		        0x2551
#define BOXDRAW_DOWN_RIGHT_DOUBLE	        0x2552
#define BOXDRAW_DOWN_DOUBLE_RIGHT	        0x2553
#define BOXDRAW_DOUBLE_DOWN_RIGHT	        0x2554
#define BOXDRAW_DOWN_LEFT_DOUBLE	        0x2555
#define BOXDRAW_DOWN_DOUBLE_LEFT	        0x2556
#define BOXDRAW_DOUBLE_DOWN_LEFT	        0x2557

#define BOXDRAW_UP_RIGHT_DOUBLE		        0x2558
#define BOXDRAW_UP_DOUBLE_RIGHT		        0x2559
#define BOXDRAW_DOUBLE_UP_RIGHT		        0x255a
#define BOXDRAW_UP_LEFT_DOUBLE		        0x255b
#define BOXDRAW_UP_DOUBLE_LEFT		        0x255c
#define BOXDRAW_DOUBLE_UP_LEFT		        0x255d

#define BOXDRAW_VERTICAL_RIGHT_DOUBLE	        0x255e
#define BOXDRAW_VERTICAL_DOUBLE_RIGHT	        0x255f
#define BOXDRAW_DOUBLE_VERTICAL_RIGHT	        0x2560

#define BOXDRAW_VERTICAL_LEFT_DOUBLE	        0x2561
#define BOXDRAW_VERTICAL_DOUBLE_LEFT	        0x2562
#define BOXDRAW_DOUBLE_VERTICAL_LEFT	        0x2563

#define BOXDRAW_DOWN_HORIZONTAL_DOUBLE	        0x2564
#define BOXDRAW_DOWN_DOUBLE_HORIZONTAL	        0x2565
#define BOXDRAW_DOUBLE_DOWN_HORIZONTAL	        0x2566

#define BOXDRAW_UP_HORIZONTAL_DOUBLE	        0x2567
#define BOXDRAW_UP_DOUBLE_HORIZONTAL	        0x2568
#define BOXDRAW_DOUBLE_UP_HORIZONTAL	        0x2569

#define BOXDRAW_VERTICAL_HORIZONTAL_DOUBLE	0x256a
#define BOXDRAW_VERTICAL_DOUBLE_HORIZONTAL	0x256b
#define BOXDRAW_DOUBLE_VERTICAL_HORIZONTAL	0x256c

#define BLOCKELEMENT_FULL_BLOCK		        0x2588
#define BLOCKELEMENT_LIGHT_SHADE	        0x2591

#define GEOMETRICSHAPE_UP_TRIANGLE	        0x25b2
#define GEOMETRICSHAPE_RIGHT_TRIANGLE	        0x25ba
#define GEOMETRICSHAPE_DOWN_TRIANGLE	        0x25bc
#define GEOMETRICSHAPE_LEFT_TRIANGLE	        0x25c4

#define ARROW_UP			        0x2191
#define ARROW_DOWN			        0x2193

typedef struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_TEXT_RESET)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_TEST_STRING)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN CHAR16 *String);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_QUERY_MODE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber, OUT UINTN *Columns, OUT UINTN *Rows);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_MODE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ModeNumber);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_ATTRIBUTE)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN ATTRIBUTE);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_CLEAR_SCREEN)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_SET_CURSOR_POSITION)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN UINTN Column, IN UINTN Row);
typedef EFI_STATUS (EFIAPI *EFI_TEXT_ENABLE_CURSOR)(IN EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL *This, IN BOOLEAN Visible);

typedef struct EFI_SIMPLE_TEXT_OUTPUT_MODE {
        INT32   MaxMode;
        INT32   Mode;
        INT32   Attribute;
        INT32   CursorColumn;
        INT32   CursorRow;
        BOOLEAN CursorVisible;
} EFI_SIMPLE_TEXT_OUTPUT_MODE;

struct EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL {
        EFI_TEXT_RESET		        Reset;
        EFI_TEXT_STRING			OutputString;
        EFI_TEXT_TEST_STRING		TestString;
        EFI_TEXT_QUERY_MODE		QueryMode;
        EFI_TEXT_SET_MODE		SetMode;
        EFI_TEXT_SET_ATTRIBUTE		SetAttribute;
        EFI_TEXT_CLEAR_SCREEN		ClearScreen;
        EFI_TEXT_SET_CURSOR_POSITION	SetCursorPosition;
        EFI_TEXT_ENABLE_CURSOR		EnableCursor;
	EFI_SIMPLE_TEXT_OUTPUT_MODE*	Mode;
};

// Simple Text Input Protocol

#define EFI_SIMPLE_TEXT_INPUT_PROTOCOL_GUID { 0x387477c1, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

// Scan codes

#define EFI_NULL 	0x00
#define EFI_UP_ARROW 	0x01
#define EFI_DOWN_ARROW 	0x02
#define EFI_RIGHT_ARROW 0x03
#define EFI_LEFT_ARROW 	0x04
#define EFI_HOME 	0x05
#define EFI_END 	0x06
#define EFI_INSERT 	0x07
#define EFI_DELETE 	0x08
#define EFI_DELETE 	0x08
#define EFI_PAGE_UP 	0x09
#define EFI_PAGE_DOWN 	0x0a
#define EFI_FUNCTION_1 	0x0b
#define EFI_FUNCTION_2 	0x0c
#define EFI_FUNCTION_3 	0x0d
#define EFI_FUNCTION_4 	0x0e
#define EFI_FUNCTION_5 	0x0f
#define EFI_FUNCTION_6 	0x10
#define EFI_FUNCTION_7 	0x11
#define EFI_FUNCTION_8 	0x12
#define EFI_FUNCTION_9 	0x13
#define EFI_FUNCTION_10 0x14
#define EFI_ESCAPE 	0x17

typedef struct EFI_INPUT_KEY {
	UINT16 ScanCode;
	CHAR16 UnicodeChar;
} EFI_INPUT_KEY;

typedef struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL EFI_SIMPLE_TEXT_INPUT_PROTOCOL;

typedef EFI_STATUS (EFIAPI *EFI_INPUT_RESET)(IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, IN BOOLEAN ExtendedVerification);
typedef EFI_STATUS (EFIAPI *EFI_INPUT_READ_KEY)(IN EFI_SIMPLE_TEXT_INPUT_PROTOCOL *This, OUT EFI_INPUT_KEY *Key);

struct EFI_SIMPLE_TEXT_INPUT_PROTOCOL {
	EFI_INPUT_RESET		Reset;
	EFI_INPUT_READ_KEY	ReadKeyStroke;
	EFI_EVENT		WaitForKey;
};

//
// TABLE HEADER
//

#define EFI_SYSTEM_TABLE_SIGNATURE	0x5453595320494249
#define EFI_2_100_SYSTEM_TABLE_REVISION	((2<<16) | (100))
#define EFI_2_90_SYSTEM_TABLE_REVISION	((2<<16) | (90))
#define EFI_2_80_SYSTEM_TABLE_REVISION	((2<<16) | (80))
#define EFI_2_70_SYSTEM_TABLE_REVISION	((2<<16) | (70))
#define EFI_2_60_SYSTEM_TABLE_REVISION	((2<<16) | (60))
#define EFI_2_50_SYSTEM_TABLE_REVISION	((2<<16) | (50))
#define EFI_2_40_SYSTEM_TABLE_REVISION	((2<<16) | (40))
#define EFI_2_31_SYSTEM_TABLE_REVISION	((2<<16) | (31))
#define EFI_2_30_SYSTEM_TABLE_REVISION	((2<<16) | (30))
#define EFI_2_20_SYSTEM_TABLE_REVISION	((2<<16) | (20))
#define EFI_2_10_SYSTEM_TABLE_REVISION	((2<<16) | (10))
#define EFI_2_00_SYSTEM_TABLE_REVISION	((2<<16) | (00))
#define EFI_1_10_SYSTEM_TABLE_REVISION	((1<<16) | (10))
#define EFI_1_02_SYSTEM_TABLE_REVISION	((1<<16) | (02))
#define EFI_SPECIFICATION_VERSION	EFI_SYSTEM_TABLE_REVISION
#define EFI_SYSTEM_TABLE_REVISION	EFI_2_100_SYSTEM_TABLE_REVISION

typedef struct EFI_TABLE_HEADER {
        UINT64 Signature;
        UINT32 Revision;
        UINT32 HeaderSize;
        UINT32 CRC32;
        UINT32 Reserved;
} EFI_TABLE_HEADER;

//
// SERVICES
//

// Boot Services

typedef EFI_STATUS (EFIAPI *EFI_CALCULATE_CRC32)(IN VOID *Data, IN UINTN DataSize, OUT UINT32 *Crc32);

typedef struct EFI_BOOT_SERVICES {
	EFI_TABLE_HEADER			Hdr;

	UINT64					RaiseTPL;
	UINT64					RestoreTPL;

	UINT64					AllocatePages;
	UINT64					FreePages;
	UINT64					GetMemoryMap;
	UINT64					AllocatePool;
	UINT64					FreePool;

	UINT64					CreateEvent;
	UINT64					SetTimer;
	UINT64					WaitForEvent;
	UINT64					SignalEvent;
	UINT64					CloseEvent;
	UINT64					CheckEvent;

	UINT64					InstallProtocolInterface;
	UINT64					ReinstallProtocolInterface;
	UINT64					UninstalProtocolInterface;
	UINT64					HandleProtocol;
	UINT64					Reserved;
	UINT64					RegisterProtocolNotify;
	UINT64					LocateHandle;
	UINT64					LocateDevicePath;
	UINT64					InstallConfigurationTable;

	UINT64					LoadImage;
	UINT64					StartImage;
	UINT64					Exit;
	UINT64					UnloadImage;
	UINT64					ExitBootServices;

	UINT64					GetNextMonotonicCount;
	UINT64					Stall;
	UINT64					SetWatchdogTimer;

	UINT64					ConnectController;
	UINT64					DisconnectController;

	UINT64					OpenProtocol;
	UINT64					CloseProtocol;
	UINT64					OpenProtocolInformation;

	UINT64					ProtocolsPerHandle;
	UINT64					LocateHandleBuffer;
	UINT64					LocateProtocol;
	UINT64					InstallMultipleProtocolInterfaces;
	UINT64					UninstallMultipleProtocolInterfaces;

	EFI_CALCULATE_CRC32			CalculateCrc32;

	UINT64					CopyMem;
	UINT64					SetMem;
	UINT64					CreateEventEx;

} EFI_BOOT_SERVICES;

// SYSTEM TABLE

typedef struct EFI_SYSTEM_TABLE {
        EFI_TABLE_HEADER		        Hdr;
        CHAR16*				        FirmwareVendor;
        UINT32 				        FirmwareRevision;
        EFI_HANDLE		                ConsoleInHandle;
        EFI_SIMPLE_TEXT_INPUT_PROTOCOL*         ConIn;
        EFI_HANDLE		                ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*	ConOut;
        EFI_HANDLE		         	StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*	StdErr;
        UINT64		            	        RuntimeServices;
        EFI_BOOT_SERVICES*		        BootServices;
        UINT64				        NumberOfTableEntries;
        UINT64				        ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
