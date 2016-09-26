/**
 * @file
 * @brief XBaseの全てのヘッダをインクルードする。
 * @author akino
 */
#if defined(XBASE_INCLUDED_XBASE_HPP)
#else
#define XBASE_INCLUDED_XBASE_HPP

//------------------------------------------------------------
/// @namespace XBase XLibraryの基本となるクラス・関数・マクロ群を定義する名前空間。

/// @defgroup XBase-Collection XBase:コレクション
#include <XBase/BitSet.hpp>
#include <XBase/RuntimeArray.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include <XBase/RuntimeMArray.hpp>

/// @defgroup XBase-Env XBase:環境情報
#include <XBase/Compiler.hpp>
#include <XBase/Config.hpp>
#include <XBase/Endian.hpp>
#include <XBase/OS.hpp>

/// @defgroup XBase-DateTime XBase:日時
#include <XBase/Calendar.hpp>
#include <XBase/Time.hpp>
#include <XBase/TimeSpan.hpp>

/// @defgroup XBase-Debug XBase:デバッグ・エラー処理
#include <XBase/Console.hpp>
#include <XBase/DivideCheck.hpp>
#include <XBase/EnumCheck.hpp>
#include <XBase/FunctionAttribute.hpp>
#include <XBase/PointerCheck.hpp>
#include <XBase/RuntimeAssert.hpp>
#include <XBase/RuntimeError.hpp>
#include <XBase/StaticAssert.hpp>

/// @defgroup XBase-IO XBase:ファイル操作
#include <XBase/IReadStream.hpp>
#include <XBase/ResFile.hpp>
#include <XBase/ResFileStream.hpp>
#include <XBase/SeekOrigin.hpp>

/// @defgroup XBase-HID XBase:HID
#include <XBase/KeyBitSet.hpp>
#include <XBase/Keyboard.hpp>
#include <XBase/KeyKind.hpp>
#include <XBase/HID.hpp>
#include <XBase/Mouse.hpp>
#include <XBase/MouseBtnBitSet.hpp>
#include <XBase/MouseBtnKind.hpp>
#include <XBase/Touch.hpp>
#include <XBase/TouchTap.hpp>

/// @defgroup XBase-Math XBase:数学
#include <XBase/AABBox2.hpp>
#include <XBase/AABBox2i.hpp>
#include <XBase/Angle.hpp>
#include <XBase/Degree.hpp>
#include <XBase/Infinity.hpp>
#include <XBase/Math.hpp>
#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XBase/PI.hpp>
#include <XBase/Quaternion.hpp>
#include <XBase/Radian.hpp>
#include <XBase/Random.hpp>
#include <XBase/Vector2.hpp>
#include <XBase/Vector2i.hpp>
#include <XBase/Vector3.hpp>
#include <XBase/Vector3i.hpp>
#include <XBase/Vector4.hpp>
#include <XBase/Vector4i.hpp>

/// @defgroup XBase-Memory XBase:メモリ
#include <XBase/AutoMemBlock.hpp>
#include <XBase/AutoPtr.hpp>
#include <XBase/AutoSPPtr.hpp>
#include <XBase/IAllocator.hpp>
#include <XBase/MemBlock.hpp>
#include <XBase/ScopedPtr.hpp>

/// @defgroup XBase-String XBase:文字列
#include <XBase/FixedString.hpp>
#include <XBase/ShortString.hpp>
#include <XBase/StringTraits.hpp>
#include <XBase/ToShortString.hpp>

/// @defgroup XBase-System XBase:システム
#include <XBase/Application.hpp>
#include <XBase/Argument.hpp>
#include <XBase/Display.hpp>
#include <XBase/DisplayContext.hpp>
#include <XBase/EntryPoint.hpp>
#include <XBase/Screen.hpp>

/// @defgroup XBase-Thread XBase:スレッド
#include <XBase/Thread.hpp>

/// @defgroup XBase-Util XBase:ユーティリティ
#include <XBase/ArrayLength.hpp>
#include <XBase/Color4.hpp>
#include <XBase/Color4b.hpp>
#include <XBase/ExplicitSingleton.hpp>
#include <XBase/FrameCounter.hpp>
#include <XBase/Hash.hpp>
#include <XBase/Ref.hpp>
#include <XBase/Reference.hpp>
#include <XBase/Placement.hpp>
#include <XBase/Pointer.hpp>
#include <XBase/ScreenPos.hpp>
#include <XBase/Unused.hpp>
#include <XBase/ValueInRange.hpp>

/// @defgroup XBase-Types XBase:型
#include <XBase/Bool.hpp>
#include <XBase/BuiltInTypes.hpp>
#include <XBase/Enum.hpp>
#include <XBase/PODClass.hpp>
#include <XBase/PODTypes.hpp>
#include <XBase/ScalerClass.hpp>

//------------------------------------------------------------
#endif
// EOF
