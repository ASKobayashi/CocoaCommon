/*
 
 Project:	Common Utilities
 File:		AACommon.h
 Author:    Aaron Kobayashi <Aaron.Kobayashi@gmail.com>
 Abstract:	Common header for Utilities
 
 */

#import "AACommon.h"
#include	<stdio.h>		
#include	<stdlib.h>
#include	<stdarg.h>		
#include <string.h>

#import <Foundation/Foundation.h>

#pragma mark --- Logging Functions ---

static char __AALoggingEnabled = 1;

void AALogEnabled(char enabled) { __AALoggingEnabled = enabled; }
void AALogAbort() { abort(); }
void AALogPrint(const char *type, const char *file, unsigned int line, NSString *fmt, ...) {
   va_list ap;
	
   if(!__AALoggingEnabled)
		return;   

	// Get the time
	NSDate *date = [[NSDate alloc] init];
	NSDateFormatter *outputFormatter = [[NSDateFormatter alloc] init];
	[outputFormatter setDateFormat:@"HH:mm:ss"];
	NSString *timestamp = [outputFormatter stringFromDate:date];
	[outputFormatter release];
	[date release];
	
   va_start(ap, fmt);
   NSString *filePath = [[NSString alloc] initWithCString:file];
   NSString *fileName = [[filePath lastPathComponent] retain];
   NSString *headStr = [[NSString alloc] initWithFormat:@"%@:%@:%d: %s: ", timestamp, fileName, line, type];
   NSString *msgStr = [[NSString alloc] initWithFormat:fmt arguments:ap];
   NSString *logStr = [[NSString alloc] initWithFormat:@"%@%@\n", headStr, msgStr];
   va_end(ap);
   
   fprintf(stderr, "%s", [logStr cStringUsingEncoding:NSASCIIStringEncoding]);

   [filePath release];
   [fileName release];
	[headStr release];
   [msgStr release];
   [logStr release];
}


#pragma mark --- Assertion Functions ---
static char __AAShouldAbortOnAssertFailure = 1;

void AAShouldAbortOnAssertFailureEnabled(char enabled) { __AAShouldAbortOnAssertFailure = enabled; }
void AAAssertFailed(const char *type, const char *expression, const char *file, unsigned int line) {
   AALogPrint(type, file, line, @"Failed, requires '%s'", expression);
   if(__AAShouldAbortOnAssertFailure)
      abort();
}

#if defined(AA_ASSERTIONS_ON) || defined(DEBUG)

static void _OBAssertionLoad(void) __attribute__((constructor));
static void _OBAssertionLoad(void) {
#ifdef AA_ASSERTIONS_ON
   NSLog(@"*** Assertions are ON ***");
#elif DEBUG
   NSLog(@"*** Assertions are OFF ***");
#endif
}
#endif

