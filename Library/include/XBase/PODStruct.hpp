/**
 * @file
 * @brief PODStruct型を記述する。
 * @author akino
 */
#if defined(XBASE_INCLUDED_PODSTRUCT_HPP)
#else
#define XBASE_INCLUDED_PODSTRUCT_HPP

//------------------------------------------------------------
#include <XBase/StaticAssert.hpp>
#include <XBase/TypeTraits.hpp>

//------------------------------------------------------------
namespace XBase {
/// @addtogroup XBase-Types
//@{
    /**
     * @brief PODClassの既定クラスとなる構造体。
     * @details バイナリデータの定義で使うことを想定しています。
     */
    template< typename T >
    struct PODStruct
    {
        /// 値の型名。
        typedef T ValueType; 
        
        /**
         * @brief 既定値(0で初期化された値)を取得する。
         * @return 初期化された値。
         */
        static const ValueType DefaultValue(){ return ValueType(); }
        
        /**
         * @brief 値のポインタを取得。
         * @return 値のポインタ。
         */
        const ValueType* ptr()const { return &readRef(); }
        ValueType*       ptr()      { return &ref(); }     ///< @copydoc ptr()const

        /**
         * @brief コピーされた値を取得。
         * @return コピーされた値。
         */
        const ValueType  get()const { return readRef(); }

        /**
         * @brief 値の参照を取得。
         * @return 値の参照。
         */
        const ValueType& readRef()const { return value_; }
        const ValueType& ref()const     { return value_; } ///< @copydoc readRef
        ValueType&       ref()          { return value_; } ///< @copydoc readRef
        //@}

        /**
         * @brief 暗黙変換の実装。
         * @return 値の参照。
         */
        operator const ValueType& ()const { return readRef(); }
        
        /**
         * @brief 暗黙変換の実装。
         * @return 値の参照。
         */
        operator ValueType& ()            { return ref(); }
        
        // 値。直接アクセスすることは想定していない。
        ValueType value_;

    private:
        XBASE_STATIC_ASSERT( TypeTraits::IsPOD< typename ValueType >::Value );         // POD型のチェック。
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
