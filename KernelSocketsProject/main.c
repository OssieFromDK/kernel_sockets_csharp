#include "includes.h"

void MainThread(void* Context)
{
	UNREFERENCED_PARAMETER(Context);

	InitializeSocketServer((uint16_t)9095); // Port 9095

	DebugLog("Main Thread Started");

	return;
}

NTSTATUS DriverEntry(PDRIVER_OBJECT DriverObject, PUNICODE_STRING RegistryPath)
{
	UNREFERENCED_PARAMETER(DriverObject);
	UNREFERENCED_PARAMETER(RegistryPath);

	HANDLE ThreadHandle;
	return PsCreateSystemThread(&ThreadHandle, THREAD_ALL_ACCESS, 0, 0, 0, MainThread, 0);
}