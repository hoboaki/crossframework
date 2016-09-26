/**
 * @file
 * @brief RuntimeAssert.hppの実装を記述する。
 * @author akino
 */
#include <XBase/RuntimeAssert.hpp>

//------------------------------------------------------------
namespace XBase {
//------------------------------------------------------------
const char* const RuntimeAssert::Separator      = "############################################################";
const char* const RuntimeAssert::Header         = "Assertion Failed.";
const char* const RuntimeAssert::FileLineFmt    = "File: %s(%d)";
const char* const RuntimeAssert::LabelCondition = "Condition:";
const char* const RuntimeAssert::LabelMessage   = "Message:";

//------------------------------------------------------------
}
//------------------------------------------------------------
// EOF
