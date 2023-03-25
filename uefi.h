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

// PROTOCOLS

// Simple Text Protocol

#define EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL_GUID { 0x387477c2, 0x69c7, 0x11d2, { 0x8e, 0x39, 0x00, 0xa0, 0xc9, 0x69, 0x72, 0x3b }}

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
	EFI_SIMPLE_TEXT_OUTPUT_MODE	Mode;
};

// TABLES

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

typedef struct EFI_SYSTEM_TABLE {
        EFI_TABLE_HEADER		        Hdr;
        CHAR16*				        FirmwareVendor;
        UINT32 				        FirmwareRevision;
        EFI_HANDLE		                ConsoleInHandle;
        UINT64		                        ConIn;
        EFI_HANDLE		                ConsoleOutHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*	ConOut;
        EFI_HANDLE		         	StandardErrorHandle;
        EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL*	StdErr;
        UINT64		            	        RuntimeServices;
        UINT64				        BootServices;
        UINT64				        NumberOfTableEntries;
        UINT64				        ConfigurationTable;
} EFI_SYSTEM_TABLE;

#endif
