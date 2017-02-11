// 文字コード：UTF-8
#if defined(AE_G3D_INCLUDED_AE_G3D_HPP)
#else
#define AE_G3D_INCLUDED_AE_G3D_HPP

/// @namespace AeG3d 3Dレンダリングに関わるクラス・関数を定義する名前空間。

/// @defgroup AeG3d-Enum AeG3d:列挙値・定数
#include <ae/g3d/PrimitiveKind.hpp>
#include <ae/g3d/TexAddress.hpp>
#include <ae/g3d/TexFilter.hpp>
#include <ae/g3d/TexId.hpp>

/// @defgroup AeG3d-Env AeG3d:環境情報
#include <ae/g3d/Engine.hpp>

/// @defgroup AeG3d-Res AeG3d:リソース
#include <ae/g3d/ResBin.hpp>
#include <ae/g3d/ResMdl.hpp>
#include <ae/g3d/ResTex.hpp>
#include <ae/g3d/ResTexFormat.hpp>

/// @defgroup AeG3d-State AeG3d:リソースインスタンスの状態
#include <ae/g3d/StateMaterial.hpp>
#include <ae/g3d/StateMdlMaterial.hpp>
#include <ae/g3d/StateMdlTransform.hpp>
// #include <ae/g3d/StateMdlVisibility.hpp>

/// @defgroup AeG3d-System AeG3d:システム
#include <ae/g3d/Renderer.hpp>

/// @defgroup AeG3d-Types AeG3d:型
#include <ae/g3d/BuiltInTypes.hpp>

/// @defgroup AeG3d-Util AeG3d:ユーティリティ
#include <ae/g3d/RuntimeTex.hpp>
#include <ae/g3d/RuntimeTexContext.hpp>
#include <ae/g3d/ITexRes.hpp>
#include <ae/g3d/TexBuffer.hpp>
#include <ae/g3d/TexResData.hpp>
#include <ae/g3d/TexSetting.hpp>
#include <ae/g3d/VtxBuffer.hpp>

#endif
// EOF
