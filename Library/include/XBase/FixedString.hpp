﻿/**
 * @file
 * @brief FixedString型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_FIXEDSTRING_HPP)
#else
#define XBASE_INCLUDED_FIXEDSTRING_HPP

//------------------------------------------------------------
#include <cstdio>
#include <XBase/BuiltInTypes.hpp>
#include <XBase/StaticAssert.hpp>
#include <XBase/StringTraits.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-String
//@{
    /**
     * @brief 固定長文字列テンプレート構造体。
     * @details 
     * あらかじめ持っている固定長バッファで文字列をやりくりするためalloc,freeが呼ばれない。@n
     * CHAR_TYPE には char もしくは wchar_t を設定してください。@n
     * BUFFER_LENGTH には配列長(notバイト長)を指定してください。@n
     */
    template< typename CHAR_TYPE , size_t BUFFER_LENGTH >
    struct FixedStringPOD
    {
        /// 文字の型。
        typedef CHAR_TYPE CharType;

        /// POD型。
        typedef FixedStringPOD< CHAR_TYPE , BUFFER_LENGTH > PODType;

        /// バッファの容量(配列長でありバイト長ではない)。
        static const size_t BufferLength = BUFFER_LENGTH;
     
        /**
         * @brief printfフォーマットで文字列を作成する。
         * @return 作成された文字列。
         * @param aFormat フォーマット文字列。
         * @details
         * バッファ長が不足したときはAssertに失敗し長さ0の文字列を返します。
         */
        static const PODType FromFormat( const CharType* aFormat , ... )
        {
            PODType str;
            va_list arg;
            va_start( arg, aFormat );
            StringTraits< CharType >::VSNPrintf( str.buffer_ , BufferLength , aFormat , arg );
            va_end(arg);
            return str;
        }        
        
        /**
         * @brief ポインタを取得する。
         * @return バッファの先頭アドレス。
         */     
        const CharType* readPtr()const { return buffer_; }
        CharType*       ptr()          { return buffer_; } ///< @copydoc readPtr
        const CharType* ptr()const     { return buffer_; } ///< @copydoc readPtr   

        /**
         * @brief 指定文字列を設定する。
         * @param aStr 設定する文字列。
         * @details 
         * バッファ長が不足したときはAssertに失敗し長さ0に設定されます。
         */
        void set( const CharType* aStr )
        {
            StringTraits< CharType >::NCopy( buffer_ , BufferLength , aStr );
        }

        /**
         * @brief 文字列の長さを取得する。
         * @return 文字数(バイト長ではない)。終端文字は含めない。
         */
        size_t length()const 
        {
            return StringTraits< CharType >::Length( buffer_ );
        }
        
        // バッファ。直接アクセスすることは想定していない。
        CharType buffer_[ BufferLength ];
    };

    /// FixedStringPOD にコンストラクタを加えたもの。
    template< typename CHAR_TYPE , size_t BUFFER_LENGTH >
    class FixedString : public FixedStringPOD< CHAR_TYPE , BUFFER_LENGTH >
    {
    public:
        /// 長さ0の文字列を作成。
        FixedString()
          : SuperType() 
        {
            SuperType::buffer_[0] = '\0'; 
        }

        /// 指定した文字列をコピーして作成。
        FixedString( const CHAR_TYPE* aStr ) 
            : SuperType() 
        {
            SuperType::set( aStr );
        }

        /// コピーして作成。
        FixedString( 
            const FixedStringPOD< CHAR_TYPE , BUFFER_LENGTH >& aObj 
            )
            : SuperType::PODType()
        {
            static_cast< SuperType& >( *this ) = aObj;
        }

    private:
        typedef FixedStringPOD< CHAR_TYPE , BUFFER_LENGTH > SuperType;
        XBASE_STATIC_ASSERT( TypeTraits::IsPOD< PODType >::Value );
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
