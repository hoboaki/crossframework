// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_XDATAPLUS_HPP)
#else
#define XG3D_INCLUDED_XDATAPLUS_HPP

#include <XBase/RuntimeAssert.hpp>
#include <XData/XData.hpp>

//------------------------------------------------------------------------------
namespace XG3D {

    // 機能拡張したXDataクラス。
    class XDataPlus : public ::XData::XData
    {
    public:
        // 不正なXDataとして作成。
        XDataPlus() : ::XData::XData(0){}
        // バイナリデータの先頭アドレスを指定して作成。
        XDataPlus( const void* aPtr ) 
            : ::XData::XData( aPtr )
        {
        }

        // 参照解決。
        template< typename T >
        const T* ref( const ::XData::Reference aVal )const
        {
            // ポインタ取得
            const void* ptr = labelAddressWithReference( aVal );

            // エラーチェック
            if ( ::XBase::PointerCheck::InvalidCheck( ptr ) )
            {
                return 0;
            }

            // 結果を返す
            return reinterpret_cast< const T* >( ptr );
        }
        
        // 参照解決(0を許す版)。
        template< typename T >
        const T* safeRef( const ::XData::Reference aVal )const
        {
            // ポインタ取得
            const void* ptr = labelAddressWithReference( aVal );

            // エラーチェック
            if ( !::XBase::PointerCheck::IsValid( ptr ) )
            {
                return 0;
            }

            // 結果を返す
            return reinterpret_cast< const T* >( ptr );
        }
    };

} // namespace
#endif
// EOF
