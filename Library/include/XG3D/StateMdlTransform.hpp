// 文字コード：UTF-8
#if defined(XG3D_INCLUDED_STATEMDLTRANSFORM_HPP)
#else
#define XG3D_INCLUDED_STATEMDLTRANSFORM_HPP

#include <XBase/Matrix34.hpp>
#include <XBase/Matrix44.hpp>
#include <XBase/NonCopyable.hpp>
#include <XBase/RuntimeArray.hpp>
#include <XBase/Vector4.hpp>
#include <XG3D/ResMdl.hpp>

namespace XG3D {
struct MdlLocalMtx;
}

//------------------------------------------------------------------------------
namespace XG3D {

/// @addtogroup XG3D-State
//@{
    /// @brief モデルのTransformに関するState。
    /// @details
/// 各関数の引数 aNodeIndex はインスタンス元モデルの node のインデックス値に対応します。
class StateMdlTransform : public ::XBase::NonCopyable
{
public:
    /// @name コンストラクタとデストラクタ
    //@{
    /// @brief コンストラクタ。
    /// @param aResMdl インスタンス化するモデル。
    /// @param aAllocator ワーク領域を確保するためのアロケータ。
    StateMdlTransform(
        const ResMdl& aResMdl
        , ::XBase::IAllocator& aAllocator = ::XBase::IAllocator::Default()
    );

    /// デストラクタ。
    ~StateMdlTransform();
    //@}

    /// @name 行列計算
    //@{
    void updateWorldMtx(const ::XBase::Mtx34& aMdlMtx = ::XBase::Mtx34::Identity()); ///< ワールド行列を更新する。
    //@}

    /// @name 行列アクセス
    //@{
    const ::XBase::Mtx34 worldMtx(int aNodeIndex)const; ///< 指定番目のノードのワールド行列を取得する。
    //@}

    /// @name 計算結果データ
    //@{
    const ::XBase::Vec4* boneMtxData()const; ///< スキンバインド用ボーン行列データ。
    //@}

private:
    ResMdl mResMdl;
    ::XBase::RuntimeArray< MdlLocalMtx > mLocalMtxs;
    ::XBase::RuntimeArray< ::XBase::Matrix34 > mWorldMtxs;
    ::XBase::RuntimeArray< ::XBase::Vec4 > mBoneMtxs;
    //============================================================
    void resetLocalMtx();
};
//@}

} // namespace
#endif
// EOF
