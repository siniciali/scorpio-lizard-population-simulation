#ifndef DIAGNOSTIC_H
#define DIAGNOSTIC_H

#include <iostream>
#include <cmath>


static int gNumTests = 0;
static int gErrors = 0;
static int gRes = 0;

#define exec(cmd, comment) \
  if (std::string(#comment).length() > 2) \
    std::cout << "    [Exec] " #cmd " /* " #comment " */" << std::endl; \
  else \
    std::cout << "    [Exec] " #cmd << std::endl; \
  cmd;


#define eqAssertPrec(a, b, p)						\
  gNumTests++; \
  gRes = (std::abs((a) - (b)) <= p) ? 0 : 1;					\
  if (gRes != 0) { \
    std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
         << "      !!   Expected: " << (b) << std::endl \
         << "      !!   Obtained: " << (a) << std::endl;\
  } else { \
    std::cout << "    [Pass] " #a " == " #b << std::endl; \
  } \
  gErrors += gRes;

#define eqAssert(a, b) \
  gNumTests++; \
  gRes = ((a)==(b)) ? 0 : 1; \
  if (gRes != 0) { \
    std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
         << "      !!   Expected: " << (b) << std::endl \
         << "      !!   Obtained: " << (a) << std::endl;\
  } else { \
    std::cout << "    [Pass] " #a " == " #b << std::endl; \
  } \
  gErrors += gRes;

#define neqAssert(a, b) \
  gNumTests++; \
  gRes = ((a)!=(b)) ? 0 : 1; \
  if (gRes != 0) { \
    std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
         << "      !!   Expected: " << (b) << std::endl \
         << "      !!   Obtained: " << (a) << std::endl;\
  } else { \
    std::cout << "    [Pass] " #a " != " #b << std::endl; \
  } \
  gErrors += gRes;


#define assertNULL(a) \
  gNumTests++; \
  gRes = ((a)==0) ? 0 : 1; \
  if (gRes != 0) { \
    std::cout << "    [Fail] line " << __LINE__ << " " << #a ": " << std::endl \
         << "      !!   Expected: 0" << std::endl \
         << "      !!   Obtained: " << (a) << std::endl;\
  } else { \
    std::cout << "    [Pass] " #a " == 0"<< std::endl; \
  } \
  gErrors += gRes;

static void diagnostic()
{
    gRes = 0;
    std::cout << std::endl
    << "=======================================" << std::endl
    << (gNumTests-gErrors) << "/" << gNumTests << " tests passed (" << gErrors << " failed)." << std::endl
    << "=======================================" << std::endl;
    //return gErrors;
}

#endif
