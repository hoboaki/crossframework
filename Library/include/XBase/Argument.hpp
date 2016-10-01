/**
 * @file
 * @brief Argument型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_ARGUMENT_HPP)
#else
#define XBASE_INCLUDED_ARGUMENT_HPP

//------------------------------------------------------------
#include <XBase/BuiltInTypes.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-System
//@{
    /// エントリーポイントの引数。
    class Argument
    {
    public:
        // 引数の最大数。
        enum { ArgCountMax = 256 };

        // コンストラクタをユーザーが直接呼ぶことは想定していない。
        // 引数のポインタはポインタをコピーするだけでポインタ先はコピーしない。
        // つまりポインタ先のデータを破棄しないように注意すること。
        Argument(
            uint aArgCount
            , const char* const* aArgValues
            , const char* aAppFileName
            , const char* aAppDirPath
            );

        /// @name 引数（実行ファイルの情報は含まれない）
        //@{
        uint        argCount()const;
        const char* argValue( uint aIndex )const;
        //@}

        /// @name 実行ファイル情報
        //@{
        /**
         * @brief 実行ファイルのファイル名。
         * @details 
         * そういう概念がないOSでは長さ0の文字列を返します。 @n
         */
        const char* exeFileName()const;

        /**
         * @brief 実行ファイルのディレクトリへのパス。
         * @details 
         * そういう概念がないOSでは長さ0の文字列を返します。@n 
         * ディレクトリの区切り文字はWindows上でも'/'を使用します。@n
         * c:\\dirname\\FileName.exe ならc:/dirname を返します。 @n
         */
        const char* exeDirPath()const; 
        //@}

    private:
        uint              mArgCount;
        const char*const* mArgValues;
        const char*       mExeFileName;
        const char*       mExeDirPath;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
