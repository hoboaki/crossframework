/**
 * @file
 * @brief TexSetting型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_TEXSETTING_HPP)
#else
#define XG3D_INCLUDED_TEXSETTING_HPP

//------------------------------------------------------------
#include <XBase/Bool.hpp>
#include <XBase/Enum.hpp>
#include <XG3D/Engine.hpp>
#include <XG3D/TexAddress.hpp>
#include <XG3D/TexFilter.hpp>

#if defined(XG3D_ENGINE_GLSERIES)
    #include <XG3D/TexSetting_GL.hpp>
#endif

//------------------------------------------------------------
namespace XG3D {
    class TexBuffer;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-Util
//@{
    /// テクスチャの設定。
    class TexSetting
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /// デフォルトの設定で作成。
        TexSetting();
        //@}

        /// @name 設定
        //@{
        /**
         * @brief アクティブ状態の取得。
         * @details
         * 初期値は非アクティブです。@n
         * 非アクティブ状態だとテクスチャ処理されません。
         */
        bool isActive()const;
        void setIsActive( bool aIsActive );  ///< @brief アクティブ状態の設定。 @see isActive()        

        /**
         * @brief バッファのバインド状態の取得。
         * @details
         * 初期値は false 状態です。
         */
        bool isBoundBuffer()const;
        void bindBuffer( const TexBuffer& ); ///< @brief 使用するバッファを設定。 @see isBoundBuffer() @details バインド済み状態でバインドした場合、設定が上書きされます。
        void unbindBuffer();  ///< @brief バッファがバインドされていない状態にする。 @see isBoundBuffer() @details バインドされていない状態でこれを呼んだ場合。何もしません。

        /**
         * @brief 縮小補間方法の取得。
         * @details
         * 初期値は TexIntpKind_Nearest です。@n
         */
        TexFilter minFilter()const;
        void setMinFilter( TexFilter ); ///< @brief 縮小補間方法の設定。 @see minFilter()
        
        /**
         * @brief 拡大補間方法の取得。
         * @details
         * 初期値は TexIntpKind_Nearest です。@n
         */
        TexFilter magFilter()const;
        void setMagFilter( TexFilter ); ///< @brief 拡大補間方法の設定。 @see magFilter()

        /**
         * @brief U座標のアドレッシングモードの取得。
         * @details
         * 初期値は TexAddress_Wrap です。@n
         */
        TexAddress addressU()const;
        void setAddressU( TexAddress ); ///< @brief U座標のアドレッシングモードの設定。 @see addressU()
        
        /**
         * @brief V座標のアドレッシングモードの取得。
         * @details
         * 初期値は TexAddress_Wrap です。@n
         */
        TexAddress addressV()const;
        void setAddressV( TexAddress ); ///< @brief V座標のアドレッシングモードの設定。 @see addressV()
        //@}

        // 内部実装用関数群。
        const TexSetting_EXT& ext_()const;
        TexSetting_EXT& ext_();

    private:
        TexSetting_EXT  mEXT;
        ::XBase::Bool32 mIsActive;
        ::XBase::Enum8< TexFilter > mMinFilter;
        ::XBase::Enum8< TexFilter > mMagFilter;
        ::XBase::Enum8< TexAddress > mAddressU;
        ::XBase::Enum8< TexAddress > mAddressV;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
