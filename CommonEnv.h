#pragma once

#include <Windows.h>

#ifndef EXPORT
#define EXPORT __declspec(dllexport)
#endif

#ifdef __cplusplus
#include <stdexcept>
#endif

#ifdef __cplusplus
#define Bool bool
#else
typedef int Bool;
#define true 1
#define false 0
#define nullptr 0
#endif


typedef float numtype;
#define DATE_FORMAT "YYYYMMDDHHMI"
#define DATE_FORMAT_LEN 12

#define USE_ORCL
#define USE_GPU

