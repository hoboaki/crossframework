/**
 * @file
 * @brief PointerCheck型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_POINTERCHECK_HPP)
#else
#define XBASE_INCLUDED_POINTERCHECK_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Debug
//@{
    /// ポインタについて調べる処理を扱う空間。
    struct PointerCheck
    {
        /**
         * @brief 有効なポインタか。
         * @return nullや無効なポインタならfalseを返す。
         */
        static bool IsValid( const_anyptr_t aPtr );

        /**
         * @brief 指定したポインタが無効かどうかAssertでチェックする。
         * @return 無効な場合trueが返る。trueが返ってきたらfail safe code用の処理を書くことを想定。
         */
        static bool InvalidCheck( const_anyptr_t aPtr );
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
