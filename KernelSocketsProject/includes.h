#pragma once
#include <ntifs.h>
#include <ntddk.h>
#include <ntstrsafe.h>
#include <wsk.h>

#define DebugLog(x, ...) DbgPrintEx(0,0,x,__VA_ARGS__)

#include "defs.h"
#include "ksocket.h"
#include "berkeley.h"
#include "socketserver.h"