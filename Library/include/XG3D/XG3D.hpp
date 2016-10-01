/**
 * @file
 * @brief XG3Dの全てのヘッダをインクルードする。
 * @author akino
 */
#if defined(XG3D_INCLUDED_XG3D_HPP)
#else
#define XG3D_INCLUDED_XG3D_HPP

//------------------------------------------------------------
/// @namespace XG3D 3Dレンダリングに関わるクラス・関数を定義する名前空間。

/// @defgroup XG3D-Enum XG3D:列挙値・定数
#include <XG3D/PrimitiveKind.hpp>
#include <XG3D/TexAddress.hpp>
#include <XG3D/TexFilter.hpp>
#include <XG3D/TexId.hpp>

/// @defgroup XG3D-Env XG3D:環境情報
#include <XG3D/Engine.hpp>

/// @defgroup XG3D-Res XG3D:リソース
#include <XG3D/ResBin.hpp>
#include <XG3D/ResMdl.hpp>
#include <XG3D/ResTex.hpp>
#include <XG3D/ResTexFormat.hpp>

/// @defgroup XG3D-State XG3D:リソースインスタンスの状態
#include <XG3D/StateMaterial.hpp>
#include <XG3D/StateMdlMaterial.hpp>
#include <XG3D/StateMdlTransform.hpp>
// #include <XG3D/StateMdlVisibility.hpp>

/// @defgroup XG3D-System XG3D:システム
#include <XG3D/Renderer.hpp>

/// @defgroup XG3D-Types XG3D:型
#include <XG3D/BuiltInTypes.hpp>

/// @defgroup XG3D-Util XG3D:ユーティリティ
#include <XG3D/RuntimeTex.hpp>
#include <XG3D/RuntimeTexContext.hpp>
#include <XG3D/ITexRes.hpp>
#include <XG3D/TexBuffer.hpp>
#include <XG3D/TexResData.hpp>
#include <XG3D/TexSetting.hpp>
#include <XG3D/VtxBuffer.hpp>

//------------------------------------------------------------
#endif
// EOF
