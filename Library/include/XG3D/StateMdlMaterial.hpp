/**
 * @file
 * @brief StateMdlMaterial型を記述する。
 * @author akino
 */
#if defined(XG3D_INCLUDED_STATEMDLMATERIAL_HPP)
#else
#define XG3D_INCLUDED_STATEMDLMATERIAL_HPP

//------------------------------------------------------------
#include <XBase/NonCopyable.hpp>
#include <XBase/RuntimeAutoArray.hpp>
#include <XG3D/ResMatSet.hpp>
#include <XG3D/ResMdl.hpp>

//------------------------------------------------------------
namespace XG3D {
    class StateMaterial;
}

//------------------------------------------------------------
namespace XG3D {
/// @addtogroup XG3D-State
//@{
    /**
     * @brief モデルが必要とする全Materialに関するState。
     * @details
     * 各関数の引数 aMatIndex はインスタンス元モデルの matRefer のインデックス値に対応します。
     */
    class StateMdlMaterial : public ::XBase::NonCopyable
    {
    public:
        /// @name コンストラクタとデストラクタ
        //@{
        /**
         * @brief コンストラクタ。
         * @param aResMdl インスタンス化するモデル。
         * @param aResMatSet インスタンス化するマテリアルセット。
         * @param aAllocator ワーク領域を確保するためのアロケータ。
         */
        StateMdlMaterial(
            const ResMdl& aResMdl
            , const ResMatSet& aResMatSet
            , ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default()
            );

        /// デストラクタ。
        ~StateMdlMaterial();
        //@}

        /// @name マテリアルアクセス
        //@{
        StateMaterial& material( uint aMatIndex );
        const StateMaterial& material( uint aMatIndex )const;
        //@}

    private:
        ResMdl mResMdl;
        ::XBase::RuntimeAutoArray< StateMaterial > mMaterials;
    };
//@}
}
//------------------------------------------------------------
#endif
// EOF
