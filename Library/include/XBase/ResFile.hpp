/**
 * @file
 * @brief ResFile型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_RESFILE_HPP)
#else
#define XBASE_INCLUDED_RESFILE_HPP

//------------------------------------------------------------
#include <XBase/IAllocator.hpp>

//------------------------------------------------------------
namespace XBase {
    class AutoMemBlock;
}

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-IO
//@{
    /**
     * @brief アプリケーションのリソースファイルにアクセスするクラス。
     * @see ResFileStream
     */
    class ResFile
    {
    public:
        /**
         * @brief 指定のファイルを読み込む。
         * @return 読み込んだデータ。
         * @param aPath ファイルパス。
         * @param aAllocator 読み込んだデータを格納するアロケータ。
         * @details
         * ファイルが見つからない場合、読み込めなかった場合はエラーになります。 @n
         * 戻り値のMemBlockのサイズは読み込んだファイルのサイズと同じです。 @n
         */
        static const AutoMemBlock Read( const char* aPath , IAllocator& aAllocator = IAllocator::Default() );
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
