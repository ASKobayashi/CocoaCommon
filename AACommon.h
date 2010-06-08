/*
 
 Project:	Common Utilities
 File:		AACommon.h
 Author:    Aaron Kobayashi <Aaron.Kobayashi@gmail.com>
 Abstract:	Common header for Utilities
 
 */

@class NSString;

#pragma mark --- Logging Functions ---

#ifdef DEBUG
#    define DLog(...) AALOG(__VA_ARGS__)
#	  define DLogMethod() AALOGMETHOD()
#	  define PRE(expression) AAPRECONDITION(expression)
#	  define POST(expression) AAPOSTCONDITION(expression)
#	  define ASSERT(expression) AAASSERT(expression)
#	  define DUMP(expression) AADUMP(expression)
#	  define ALog(...) AALOG(__VA_ARGS__) 
#else
#    define DLog(...) /* */
#	  define DLogMethod() /* */
#	  define PRE(expression) /* */
#	  define POST(expression) /* */
#	  define ASSERT(expression) /* */
#	  define DUMP(expression) /* */
#	  define ALog(...) NSLog(__VA_ARGS__) 
#endif




#if defined(DEBUG) || defined(AA_FORCE_LOGGING)
#define AA_LOGGING_ON
#endif

// This allows you to turn off logging when debugging
#if defined(AA_FORCE_LOGGING_OFF)
#undef AA_LOGGING_ON
#warning Forcing logging off!
#endif

/* Logging Functions */
#if defined(AA_LOGGING_ON)
   void AALogEnabled(char enabled);
   void AALogPrint(const char *type, const char *file, unsigned int line, NSString *fmt, ...);
   void AALogAbort();

   #define AALOGMETHOD()      AALogPrint("METH", __FILE__, __LINE__, @"Called Method: %s", _cmd);
   #define AALOG(fmt, ...)    AALogPrint("LOG", __FILE__, __LINE__, fmt, ##__VA_ARGS__); 
   #define AAWARN(fmt, ...)   AALogPrint("WARN", __FILE__, __LINE__, fmt, ##__VA_ARGS__); 
   #define AAERR(fmt, ...)    AALogPrint("ERR", __FILE__, __LINE__, fmt, ##__VA_ARGS__); 
   #define AADUMP(fmt, ...)   AALogPrint("DUMP", __FILE__, __LINE__, fmt, ##__VA_ARGS__); AALogAbort();
#else // Insert Blanks, since logging is turned off
   #define AALOG(fmt, ...) 
   #define AAWARN(fmt, ...) 
   #define AAERR(fmt, ...)
   #define AADUMP(fmt, ...)
#endif


#pragma mark --- Assertion Functions ---

#if defined(DEBUG) || defined(AA_FORCE_ASSERTIONS_ON)
#define AA_ASSERTIONS_ON
#endif

// This allows you to turn off assertions when debugging
#if defined(AA_FORCE_ASSERTIONS_OFF)
#undef AA_ASSERTIONS_ON
#warning Forcing assertions off!
#endif

#if defined(AA_ASSERTIONS_ON)

   void AAAssertFailed(const char *type, const char *expression, const char *file, unsigned int lineNumber);

   #define AAPRECONDITION(expression)                                      \
      if (!(expression))                                                   \
         AAAssertFailed("PRECONDITION", #expression, __FILE__, __LINE__);

   #define AAPOSTCONDITION(expression)                                     \
      if (!(expression))                                                   \
         AAAssertFailed("POSTCONDITION", #expression, __FILE__, __LINE__);

   #define AAINVARIANT(expression)                                         \
      if (!(expression))                                                   \
         AAAssertFailed("INVARIANT", #expression, __FILE__, __LINE__);

   #define AAASSERT(expression)                                            \
      if (!(expression))                                                   \
         AAAssertFailed("ASSERT", #expression, __FILE__, __LINE__);

#else	// else insert blank lines into the code

   #define AAPRECONDITION(expression)
   #define AAPOSTCONDITION(expression)
   #define AAINVARIANT(expression)
   #define AAASSERT(expression)

#endif
